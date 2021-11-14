import numpy as np
import cv2
import cv2.aruco as aruco

from PnP import get_transformation_to_world

DEFAULT_DICTIONARY = aruco.DICT_4X4_50
MARKER_LENGTH = 20

class ArucoTracker:
    def __init__(self, camera_matrix, distortion_coefficents, path=1):
        self.cap = cv2.VideoCapture(path)
        self.camera_matrix = camera_matrix
        self.distortion_coefficents = distortion_coefficents

    def track(self):
        get_transformation = get_transformation_to_world()

        while(True):
            if self.cap.isOpened():
                break
            cv2.waitKey(1000)
    
        while(True):   
            ret, frame = self.cap.read()

            # operations on the frame
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

            # set dictionary size depending on the aruco marker selected
            aruco_dict = aruco.Dictionary_get(DEFAULT_DICTIONARY)

            # detector parameters can be set here (List of detection parameters[3])
            parameters = aruco.DetectorParameters_create()
            parameters.adaptiveThreshConstant = 10

            corners, ids, rejected_img_points = aruco.detectMarkers(gray, aruco_dict,
                                                                parameters=parameters,
                                                                cameraMatrix=self.camera_matrix,
                                                                distCoeff=self.distortion_coefficents)
            
            # font for displaying text (below)
            font = cv2.FONT_HERSHEY_SIMPLEX

            # check if the ids list is not empty
            # if no check is added the code will crash
            if np.all(ids != None):

                # estimate pose of each marker and return the values
                # rvet and tvec-different from camera coefficients
                rvec, tvec ,_ = aruco.estimatePoseSingleMarkers(corners, MARKER_LENGTH, self.camera_matrix, self.distortion_coefficents)
                #(rvec-tvec).any() # get rid of that nasty numpy value array error

                for i in range(0, ids.size):
                    # draw axis for the aruco markers
                    aruco.drawAxis(frame, self.camera_matrix, self.distortion_coefficents, rvec[i], tvec[i], 10)

                # draw a square around the markers
                aruco.drawDetectedMarkers(frame, corners)


                # code to show ids of the marker found
                strg = ''
                for i in range(0, ids.size):
                    strg += str(ids[i][0])+', '

                # cv2.putText(frame, "Id: " + strg, (0,64), font, 1, (0,255,0),2,cv2.LINE_AA)

                transform = get_transformation(tvec, rvec)
                coords = transform([0, 0, 0])

                coords = ['{:.2f}'.format(x) for x in coords.tolist()[0]]
                cv2.putText(frame, "Coords: " + ','.join(coords), (0,64), font, 1, (0,255,0),2,cv2.LINE_AA)

            else:
                # code to show 'No Ids' when no markers are found
                cv2.putText(frame, "No Ids", (0,64), font, 1, (0,255,0),2,cv2.LINE_AA)

            # display the resulting frame
            cv2.imshow('frame',frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        # When everything done, release the capture
        self.cap.release()

        