import cv2 as cv

from aruco_tracker import MARKER_LENGTH

# Default calibration paths
DEFAULT_CALIBRATION_FILE_PATH = 'calib/saved'
DEFAULT_CALIBRATION_IMAGES_PATH = 'calib/images'

# Subpixel refining parameters
WIN_SIZE = (11, 11)
ZERO_ZONE = (-1, -1)
MAX_ITER = 30
EPSILON = 0.001
TERMINATION_CRITERIA = (
    cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, MAX_ITER, EPSILON
)

# Camera API
SSH_USERNAME='tl526'
SSH_PASSWORD='Wudqpbgxf1301'
REMOTE_SERVER_ADDRESS = ('gate.eng.cam.ac.uk', 22)
LOCAL_BIND_ADDRESS = 'localhost'

CAMERA_INFO = {
    'idpcam1': ('idpcam1.eng.cam.ac.uk', 8080),
    'idpcam2': ('idpcam2.eng.cam.ac.uk', 8080)
}

CAMERA_DEFAULT_PATH_TEMPLATE = 'http://%s:%d/stream/video.mjpeg'

# Robot
ROBOT_ARUCO_DICTIONARY = cv.aruco.getPredefinedDictionary('DICT4X4_50')
MARKER_LENGTH = 20 # cm
ROBOT_MARKER_ID = 0