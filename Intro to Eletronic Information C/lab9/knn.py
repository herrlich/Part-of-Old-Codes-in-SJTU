import sys
import string
import time
from opencv.cv import *
from opencv.highgui import *

def get_data(filename):
    twelve=list()
    p=list()
    image = cvLoadImage (filename,1)
    width=image.width
    height=image.height
    semi_w=width/2
    semi_h=height/2
    red=0
    green=0
    blue=0
    for i in range(0,semi_w):
        for j in range(0,semi_h):
            red+=image[j,i][2]
            blue+=image[j,i][0]
            green+=image[j,i][1]
    total=red+green+blue
    p.append(float(blue)/total)
    p.append(float(green)/total)
    p.append(float(red)/total)
    red=0
    green=0
    blue=0
    for i in range(0,semi_w):
        for j in range(semi_h,height):
            red+=image[j,i][2]
            blue+=image[j,i][0]
            green+=image[j,i][1]
    total=red+green+blue
    p.append(float(blue)/total)
    p.append(float(green)/total)
    p.append(float(red)/total)
    red=0
    green=0
    blue=0
    for i in range(semi_w,width):
        for j in range(0,semi_h):
            red+=image[j,i][2]
            blue+=image[j,i][0]
            green+=image[j,i][1]
    total=red+green+blue
    p.append(float(blue)/total)
    p.append(float(green)/total)
    p.append(float(red)/total)
    red=0
    green=0
    blue=0
    for i in range(semi_w,width):
        for j in range(semi_h,height):
            red+=image[j,i][2]
            blue+=image[j,i][0]
            green+=image[j,i][1]
    total=red+green+blue
    p.append(float(blue)/total)
    p.append(float(green)/total)
    p.append(float(red)/total)
    for k in range(0,12):
        if p[k]>=0 and p[k]<0.3:
            twelve.append(0)
        if p[k]>=0.3 and p[k]<0.6:
            twelve.append(1)
        if p[k]>=0.6:
            twelve.append(2)
    return twelve

def get_all_twelve():
    total_vector=list()
    for t in range(1,41):
        filename=str(t)+".jpg"
        twelve=get_data(filename)
        total_vector.append(twelve)
    return total_vector

def get_all_target():
    new_twelve=get_data("target.jpg")
    return new_twelve

total_vector=get_all_twelve()
new_twelve=get_all_target()
start=time.clock()
for i in range(0,40):
    if total_vector[i]==new_twelve:
        print "The picture is "+str(i+1)+".jpg"
end=time.clock()
delta=end-start
print "time:",delta
