import sys
import string
import time
from opencv.cv import *
from opencv.highgui import *
#这个程序中C=2，d=12,d'=24
I=[1,3,7,8]#这里只要修改I的内容，下面的程序会自动算出对应的hamming码
c=2
projection=dict()
for i in range(1,13):
    for num in I:
        if (i-1)*c+1<=num and num<=i*c:
            if projection.has_key(str(i)):
                projection[str(i)].append(num)
            else:
                projection[str(i)]=[num]
hashkeys=projection.keys()

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

def get_hash_key(vector,hashkeys):
    key=list()
    for j in range(0,len(hashkeys)):
        x=vector[int(hashkeys[j])-1]
        for num in projection[hashkeys[j]]:
            if num-c*(int(hashkeys[j])-1)<=x:
                key.append(1)
            else:
                key.append(0)
    return key

def get_hash(total_vector,projection):
    hash_dict={}
    for i in range(0,40):
        key=get_hash_key(total_vector[i],hashkeys)
        if hash_dict.has_key(str(key)):
            hash_dict[str(key)].append(i)
        else:
            hash_dict[str(key)]=[i]
    return hash_dict

def get_target_hash(newtwelve):
    new_key=get_hash_key(newtwelve,hashkeys)
    return new_key

if __name__ == '__main__':
    total_vector=get_all_twelve()
    newtwelve=get_all_target()
    hash_dict=get_hash(total_vector,projection)
    newkey=get_target_hash(newtwelve)
    start=time.clock()
    result_set=hash_dict[str(newkey)]
    for num in result_set:
        if newtwelve==total_vector[num]:
            print "The picture is "+str(num+1)+".jpg"
    end=time.clock()
    delta=end-start
    print "time:",delta
