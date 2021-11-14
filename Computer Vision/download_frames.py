# from camera_api import FrameDownloader

# downloader = FrameDownloader('idpcam2', prefix='calib_', ssh_tunnel=False)

# downloader.start()

from camera import idpcam1, idpcam2

# idpcam1.show(ssh_tunnel=True)
# idpcam2.show(ssh_tunnel=True)
idpcam1.download_frames(ssh_tunnel=True)