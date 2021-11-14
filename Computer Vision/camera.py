import os
import cv2 as cv

from sshtunnel import open_tunnel
from contextlib import contextmanager
from cv2 import VideoCapture
from datetime import datetime
from threading import Thread
from queue import Queue
from time import time

from constants import (
    CAMERA_DEFAULT_PATH_TEMPLATE,
    CAMERA_INFO,
    REMOTE_SERVER_ADDRESS,
    SSH_USERNAME,
    SSH_PASSWORD,
    LOCAL_BIND_ADDRESS,
    DEFAULT_CALIBRATION_IMAGES_PATH
)


class Camera:
    def __init__(self, name, address, port, local_port=8080, camera_matrix=None, dist_coeff=None):
        self.name = name
        self.address = address
        self.port = port
        self.local_port = local_port
        self.camera_matrix = camera_matrix
        self.dist_coeff = dist_coeff

    @contextmanager
    def _open_camera(self):
        capture = VideoCapture(CAMERA_DEFAULT_PATH_TEMPLATE % (self.address, self.port))
        try:
            yield capture
        finally:
            capture.release()

    @contextmanager
    def _open_camera_ssh_tunnel(self):
        with open_tunnel(
            REMOTE_SERVER_ADDRESS,
            ssh_username=SSH_USERNAME,
            ssh_password=SSH_PASSWORD,
            remote_bind_address=(self.address, self.port),
            local_bind_address=(LOCAL_BIND_ADDRESS, self.local_port)
        ) as tunnel:
            capture = VideoCapture(CAMERA_DEFAULT_PATH_TEMPLATE % (LOCAL_BIND_ADDRESS, self.local_port))
            try:
                yield capture
            finally:
                capture.release()

    def open(self, ssh_tunnel=False):
        if ssh_tunnel:
            return self._open_camera_ssh_tunnel()
        return self._open_camera()

    def _get_default_dirpath(self):
        dirname_template = f'{self.name} (%d-%m-%Y %H.%M.%S)'
        dirpath = DEFAULT_CALIBRATION_IMAGES_PATH + '/' + datetime.now().strftime(dirname_template)
        os.mkdir(dirpath)
        return dirpath

    def _frame_paths(self, dirpath='', prefix='calib_', image_format='jpg', index=0):
        if not dirpath:
                dirpath = self._get_default_dirpath()

        while(True):
            path = f'{dirpath}/{prefix}{index}.{image_format}'
            yield path
            index += 1

    def _fetch_frame(self, cap, queue, path, interval=500):
        start = time()
        while cap.isOpened():
            _, frame = cap.read()
            cv.imshow(f'{self.name}', frame)
            cv.waitKey(2)

            if (time() - start) * 1000 > interval:
                if frame:
                    queue.put((path, frame))
                    start = time()

            if cv.waitKey(2) & 0xFF == ord('q'):
                cv.destroyAllWindows()
                break
        
    def _get_downloader(self, queue, interval=500, *args, **kwargs):
        def downloader():
            for path in self._frame_paths(*args, **kwargs):
                start = time()
                while(True):
                    frame = queue.get()
                    if (time() - start) > interval:
                        cv.imwrite(path, frame)
                    queue.task_done()
        return downloader

    def download_frames(self, ssh_tunnel=False, *args, **kwargs):
        queue = Queue()
        Thread(target=self._get_downloader(queue, *args, **kwargs), daemon=True).start()

        self.show(output=queue, ssh_tunnel=ssh_tunnel, show_info=False)
        queue.join()

    def show(self, output=None, ssh_tunnel=False, show_info=True):
        with self.open(ssh_tunnel=ssh_tunnel) as cap:
            try:
                start = None
                while cap.isOpened():
                    _, frame = cap.read()

                    if show_info:
                        end = time()
                        if start:
                            fps = 1 / (end - start)
                            frame = cv.putText(
                                frame,
                                f'FPS: {fps:.2f}',
                                (0, 64),
                                cv.FONT_HERSHEY_SIMPLEX,
                                1,
                                (0, 0, 255),
                                1,
                                cv.LINE_AA
                            )
                        start = end

                    cv.imshow(f'{self.name}', frame)
                    cv.waitKey(2)
                    if output:
                        output.put(frame)
            except KeyboardInterrupt:
                # print("Cancelling...")
                cv.destroyAllWindows()


idpcam1 = Camera('idpcam1', *CAMERA_INFO.get('idpcam1'), local_port=8081)
idpcam2 = Camera('idpcam2', *CAMERA_INFO.get('idpcam2'), local_port=8082)