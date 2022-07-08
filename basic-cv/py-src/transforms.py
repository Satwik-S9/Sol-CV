import cv2 as cv
import numpy as np


def affine_transform(img: np.ndarray, T: np.ndarray):
    rows, cols, channels = img.shape
    res = np.zeros((rows, cols, channels), np.uint8)
    for i in range(rows):
        for j in range(cols):
            pos_vec = np.array([i, j, 1])
            pos_vec = np.dot(T, pos_vec)
            
            ni = int(pos_vec[0])
            nj = int(pos_vec[1])

            if ni < rows and nj < cols:
                res[i, j] = img[ni, nj]
    
    return res

def get_tranformation_matrix(params: list, op_str: str):
    ...


if __name__ == '__main__':
    img = cv.imread("../images/sample1.jpg")
    T = np.eye(3)
    T[0, 2] = 5
    T[1, 2] = 5

    print(T)
    res = affine_transform(img, T)

    cv.imshow("ORIG", img)
    cv.imshow("TRANS", res)

    cv.waitKey(0)
    cv.destroyAllWindows()