import cv2 as cv
import numpy as np

from constants import (
    ROBOT_ARUCO_DICTIONARY,
    TERMINATION_CRITERIA,
    WIN_SIZE,
    ZERO_ZONE,
    MARKER_LENGTH,
    ROBOT_MARKER_ID
)

parameters = cv.aruco.DetectorParameters_create()

class Arena:
    def __init__(self, camera, map, rvec, tvec):
        self.camera = camera
        self.map = map

        # check if np.array?
        # 3x1 or 1x3
        self.rvec = rvec
        self.R = cv.Rodrigues(rvec)
        self.R_transposed = self.R.T

        self.tvec = tvec

    def get_transformation(self, rvec, tvec):
        R, _ = cv.Rodrigues(rvec)
        def transform(coordinates):
            return self.R_transposed.dot(R.dot(coordinates) - self.tvec + tvec)
        return transform

    def find_robot(self, frame):
        gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

        # omitted args parameters
        corners_list, ids, rejected = cv.aruco.detectMarkers(gray, 
                                                ROBOT_ARUCO_DICTIONARY,
                                                parameters,
                                                self.camera.camera_matrix,
                                                self.camera.distortion_coefficents)
        
        try:
            # The first marker that matches the ID
            robot_corners = next(corners for corners, id in zip(corners_list, ids) if id == ROBOT_MARKER_ID)

            # Corner sub-pixel (doubt that it would work)
            robot_corners = cv.cornerSubPix(
                gray, robot_corners, WIN_SIZE, ZERO_ZONE, TERMINATION_CRITERIA)

            # rvec, tvec is 2D array but are vectors
            rvec, tvec, obj_points = cv.aruco.estimatePoseSingleMarkers(
                np.array([robot_corners]), MARKER_LENGTH, self.camera.camera_matrix, self.camera.distortion_coefficients)

            rvec = np.squeeze(rvec)
            tvec = np.squeeze(tvec)
            transform = self.get_transformation(rvec, tvec)

            # centre of the marker
            return transform([0, 0, 0])
        except StopIteration:
            # Not detected
            pass

    def find_dummies(self, frame):
        pass




