# -*- coding:utf-8 -*-
 
import sys
 
# 导入OpenCV模块
 
from opencv.cv import *
from opencv.highgui import *
 
if __name__ == '__main__':
 
    # 打开图像
    energy=[0,0,0]
    image = cvLoadImage ("img2.png",1)
    h=image.height
    w=image.width
    for color in range(0,3):
        for i in range(0,h):
            for j in range(0,w):
                energy[color]+=image[i,j][color]
    total_energy=energy[0]+energy[1]+energy[2]
    blue=float(energy[0])/total_energy
    green=float(energy[1])/total_energy
    red=float(energy[2])/total_energy
    print "blue",'\t',blue
    print "green",'\t',green
    print "red",'\t',red
