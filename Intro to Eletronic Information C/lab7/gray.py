# -*- coding:utf-8 -*-
 
import sys
 
# 导入OpenCV模块
 
from opencv.cv import *
from opencv.highgui import *
 
if __name__ == '__main__':
 
    # 打开图像
    gray=list()
    percentage=list()
    image = cvLoadImage ("img1.png",0)
    h=image.height
    w=image.width
    total=w*h
    for i in range(0,256):
        gray.append(0)
    for i in range(0,h):
        for j in range(0,w):
            gray[image[i][j]]+=1
    for i in range(0,256):
        temp=float(gray[i])/total
        percentage.append(temp)
    print "Here are the results:"
    for i in range(0,256):
        print i,'\t',percentage[i]
    
