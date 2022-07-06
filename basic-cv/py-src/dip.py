from multiprocessing.sharedctypes import Value
import os
import time
import cv2 as cv
import numpy as np
from typing import Optional
from warnings import warn

def quantize(img: np.ndarray, level: int):
    if (level > 8) or (not isinstance(level, int)): 
        raise ValueError("arg `level: int` should be within 8")
    
    rows, cols, channels = img.shape

    if level == 2:
        for i in range(rows):
            for j in range(cols):
                for c in range(channels):
                    if img[i][j][c] < 128:
                        img[i][j][c] = 0
                    else:
                        img[i][j][c] = 255

        return img
    else:
        for i in range(rows):
            for j in range(cols):
                for c in range(channels):
                    for m in range(level):
                        bar1 = int(m * (256 // level)) \
                            if m * (256 // level) < 255 else 255
                        
                        bar2 = int((m+1) * (256 // level)) \
                             if m * (256 // level) < 255 else 255

                        if (img[i][j][c] >= bar1 and img[i][j][c] < bar2):
                            img[i][j][c] = bar1
        return img
