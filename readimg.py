import numpy as np
import cv2 as cv

drawing = False  # 如果按下鼠标，则为真
mode = True  # 如果为真，绘制矩形。按 m 键可以切换到曲线
ix, iy = -1, -1

img = None


# 鼠标回调函数


def draw_circle(event, x, y, flags, param):
    global ix, iy, drawing, mode
    if event == cv.EVENT_LBUTTONDOWN:
        drawing = True
        ix, iy = x, y
    elif event == cv.EVENT_MOUSEMOVE:
        if drawing:
            if mode:
                cv.rectangle(img, (ix, iy), (x, y), (0, 255, 0), -1)
            else:
                cv.circle(img, (x, y), 5, (0, 0, 255), -1)
    elif event == cv.EVENT_LBUTTONUP:
        drawing = False
        if mode:
            cv.rectangle(img, (ix, iy), (x, y), (0, 255, 0), -1)
            print((x, y))
        else:
            cv.circle(img, (x, y), 5, (0, 0, 255), -1)


def mouse():
    global img
    img = np.zeros((512, 512, 3), np.uint8)

    cv.namedWindow('image')
    cv.setMouseCallback("image", draw_circle)

    while True:
        cv.imshow("image", img)
        if cv.waitKey():
            break

    cv.destroyAllWindows()


def nothing(x):
    pass


def paint():
    global img
    img = np.zeros((300, 512, 3), np.uint8)
    cv.namedWindow('image')
    cv.createTrackbar('R', 'image', 0, 255, nothing)
    cv.createTrackbar('G', 'image', 0, 255, nothing)
    cv.createTrackbar('B', 'image', 0, 255, nothing)
    switch = '0: OFF\n1: ON'
    cv.createTrackbar(switch, 'image', 0, 1, nothing)
    while True:
        cv.imshow('image', img)
        k = cv.waitKey(1);
        if k == 27:
            break
        r = cv.getTrackbarPos('R', 'image')
        g = cv.getTrackbarPos('G', 'image')
        b = cv.getTrackbarPos('B', 'image')
        s = cv.getTrackbarPos(switch, 'image')

        if s == 0:
            img[:] = 0
        else:
            img[:] = [b, g, r]
    cv.destroyAllWindows()


if __name__ == '__main__':
    paint()
