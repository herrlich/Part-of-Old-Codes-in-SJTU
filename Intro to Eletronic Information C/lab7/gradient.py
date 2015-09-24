# -*- coding:utf-8 -*-
 
import sys
import math
 
# 导入OpenCV模块
 
from opencv.cv import *
from opencv.highgui import *
 
if __name__ == '__main__':
 
    # 打开图像
    gradient=list()
    percentage=list()
    image = cvLoadImage ("img1.png",0)
    h=image.height
    w=image.width
    total=(h-2)*(w-2)
    for i in range(0,361):
        gradient.append(0)
    for i in range(1,h-1):
        for j in range(1,w-1):
            tempx=image[i+1,j]-image[i-1,j]
            tempy=image[i,j+1]-image[i,j-1]
            sqx=tempx*tempx
            sqy=tempy*tempy
            m=int(math.sqrt(sqx+sqy))
            gradient[m]+=1
    for i in range(0,361):
        temp=float(gradient[i])/total
        percentage.append(temp)
    print "Here are the results:"
    for i in range(0,361):
        print i,'\t',percentage[i]
    
