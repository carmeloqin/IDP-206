import cv2 as cv
import numpy as np

from itertools import product

img = cv.imread('calib/images/idpcam1 (12-11-2021 15.13.47)/calib_2.jpg')

threshold = 8
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

height, width, _ = img.shape

for y, x in product(range(height), range(width)):
    b, g, r = img[y, x]

    b = int(b)
    g = int(g)
    r = int(r)

    std = np.std([b, g, r])

    if std < threshold:
        img[y, x] = BLACK

cv.imshow('Black', img)
cv.waitKey(0)

