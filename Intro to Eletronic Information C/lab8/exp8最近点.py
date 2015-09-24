import string
import sys
import math
from opencv.cv import *
from opencv.highgui import *

def get_dir(image,array):#�õ�������arrayΪ����һ��ͼ�����нǵ��list
    bin=list()
    final_dir=list()#�������õ������нǵ��������
    len_array=len(array)
    for i in range(0,36):
        bin.append(0)
    for t in range(0,len_array):
        x=int(array[t][0])
        y=int(array[t][1])
        for i in range(0,36):
            bin[i]=0
        for i in range(x-8,x+8):
            for j in range(y-8,y+8):
                if x<=0 or x+8>=image.width-1 or y<=0 or y+8>=image.height-1:#ȥ���߽��
                    continue 
                tempy=image[j+1,i]-image[j-1,i]
                tempx=image[j,i+1]-image[j,i-1]
                m=math.sqrt(tempx*tempx+tempy*tempy)
                theta=get_theta(tempx,tempy)
                bin[int(theta/10)]+=m
        direction=bin.index(max(bin))#�ҵ���Ȩ������bin�ķ���
        final_dir.append(direction)
    return final_dir


def near(image,array,final_dir):#��������δ��һ��128ά����
    len_array=len(array)
    total_vector=list()#����õ������е��128ά������list
    for t in range(0,len_array):
        bin=list()#����8������
        for i in range(0,8):
            bin.append(0)
        x=int(array[t][0])
        y=int(array[t][1])
        vector=list()
        dir_theta=final_dir[t]*10+5
        pi_theta=float(dir_theta)/360*2*math.pi#��theta��ת��Ϊ���ȣ��������Ǻ�������
        for i in range(-8,8,4):#��16��4*4�����е�8ά����
            for j in range(-8,8,4):
                for k in range(0,4):
                    for l in range(0,4):
                        realx=x+(i+k)*math.cos(pi_theta)-(j+l)*math.sin(pi_theta)
                        #����������ϵ�еĵ㻻�㵽ͼ������ϵ��
                        realy=y+(i+k)*math.sin(pi_theta)+(j+l)*math.cos(pi_theta)
                        posx=int(realx+0.5)#�õ���������Ͻ��е�һ����������
                        posy=int(realy+0.5)
                        if posx<=0 or posy<=0 or posx>=image.width-2 or posy>=image.height-2:
                            continue#ȥ���߽�
                        tempy=image[posy+1,posx]-image[posy-1,posx]
                        tempx=image[posy,posx+1]-image[posy,posx-1]
                        m=math.sqrt(tempx*tempx+tempy*tempy)
                        theta=get_theta(tempx,tempy)
                        bin[int(float((theta-dir_theta+360))%360/45)]+=m
                        #��Ȩֵ�ۼӵ�8��bin�ж�Ӧ��λ�ã������bin����ͼ������ϵ�е��ݶȷ���
                        #��ȥ�ؼ���������õ���
                for m in range(0,8):
                    vector.append(bin[m])#����8ά����
                    bin[m]=0#���8ά�����������´�����
        total_vector.append(vector)#��ÿһ���ؼ����128ά��������total_vector
    return total_vector

def get_vector(total_vector):#��128ά������һ��
    for i in range(0,len(total_vector)):
        temp=total_vector[i]
        square_sum=0
        for j in range(0,128):
            square_sum+=temp[j]*temp[j]
        length=math.sqrt(square_sum)
        if length==0:
            continue
        for j in range(0,128):
            total_vector[i][j]/=float(length)
    return total_vector

def times(vec1,vec2):#һ�������˷��ĸ�������
    result=0
    for i in range(0,128):
        result+=vec1[i]*vec2[i]
    return result

def get_theta(tempx,tempy):#���ݶȷ���theta�ĸ�������
    if tempx!=0:
         theta=math.atan(float(tempy)/tempx)/(2*math.pi)*360
    else:
        if tempy>0:
            theta=90
        if tempy<0:
            theta=270
        else:
            return 0
    if tempx>0 and tempy<0:
        theta+=360
    if tempx<0 and tempy<0:
        theta+=180
    if tempx<0 and tempy>0:
        theta+=180
    return theta


image1 = cvLoadImage ("3.jpg",0)
image2 = cvLoadImage ("target.jpg",0)
infile1=open("3.txt","r")
infile2=open("target.txt","r")
array1=list()#array1������ŵ�һ��ͼƬ�е����нǵ㣨�Զ�ά�������ʽ��
array2=list()
for line in infile1.readlines():
    data=line.strip('\n')
    xandy=data.split()
    x=int(xandy[0])
    y=int(xandy[1])
    temp=[x,y]
    array1.append(temp)
for line in infile2.readlines():
    data=line.strip('\n')
    xandy=data.split()
    x=int(xandy[0])
    y=int(xandy[1])
    temp=[x,y]
    array2.append(temp)
final_dir1=get_dir(image1,array1)
total_vector1=near(image1,array1,final_dir1)#���йؼ����δ��һ��128ά����
compare_vector1=get_vector(total_vector1)#���йؼ���Ĺ�һ����128άsift������
final_dir2=get_dir(image2,array2)
total_vector2=near(image2,array2,final_dir2)
compare_vector2=get_vector(total_vector2)
length1=len(compare_vector1)#��һ��ͼƬ��sift�����ӵĸ��������ǵ�����
length2=len(compare_vector2)
outfile1=open("out1.txt","w")
outfile2=open("out2.txt","w")
for i in range(0,length1):
    maximum=0#��maximum��Ϊ���գ����õ�����ͼƬ��sift�����ӵ����˻����ں������
    for j in range(0,length2):
        temp=times(compare_vector1[i],compare_vector2[j])
        if temp>maximum:
            posx=i
            posy=j
            maximum=temp
    if maximum>0.85:#������sift�˻������ֵ����0.8�����������Ӷ�����ƥ��ͼ��
        outfile1.write(str(array1[posx][0])+'\t'+str(array1[posx][1])+'\n')
        #�����Ӧ�Ĺؼ����x��y����
        outfile2.write(str(array2[posy][0])+'\t'+str(array2[posy][1])+'\n')
infile1.close()
infile2.close()
outfile1.close()
outfile2.close()
