import os
import time
import cv2 as cv
import numpy as np
from typing import Optional
from warnings import warn

def quantize(path: str, level: int = 8):
    ...

def resize(img, dim: Optional[tuple] = None, 
           scale: Optional[int] = None, method: str = "bilinear"):
    if method not in ["bilinear", "bicubic", "nearest"]:
        raise ValueError("'method' not in {}".format(["bilinear", "bicubic", "nearest"]))
    
    if (dim is None and scale is None):
        warn("Warning: No Dimension / Scale provided returning original image")
        return img
    if (dim is not None and scale is not None):
        warn("Warning: both dimension and scale provided using 'dim' only")
        scale = None

