import string
import sys
import math
from opencv.cv import *
from opencv.highgui import *

def get_dir(image,array):#得到主方向，array为储存一个图中所有角点的list
    bin=list()
    final_dir=list()#储存最后得到的所有角点的主方向
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
                if x<=0 or x+8>=image.width-1 or y<=0 or y+8>=image.height-1:#去除边界点
                    continue 
                tempy=image[j+1,i]-image[j-1,i]
                tempx=image[j,i+1]-image[j,i-1]
                sqx=tempx*tempx
                sqy=tempy*tempy
                m=math.sqrt(sqx+sqy)
                theta=get_theta(tempx,tempy)
                bin[int(theta/10)]+=m
        direction=bin.index(max(bin))#找到加权后最大的bin的方向
        final_dir.append(direction)
    return final_dir


def double_linear(image,array,final_dir):#用双线性插值得未归一的128维向量
    bin=list()#储存8个方向
    len_array=len(array)
    total_vector=list()#储存得到的所有点的128维向量的list
    for i in range(0,8):
        bin.append(0)
    for t in range(0,len_array):
        x=int(array[t][0])
        y=int(array[t][1])
        vector=list()
        dir_theta=final_dir[t]*10+5
        pi_theta=float(dir_theta)/360*2*math.pi#将theta角转换为弧度，便于三角函数计算
        for i in range(-8,8,4):#求16个4*4矩阵中的8维向量
            for j in range(-8,8,4):
                for k in range(0,4):
                    for l in range(0,4):
                        theta_value=0#用来储存将要差值运算的梯度方向的结果
                        m_value=0#用来储存将要差值运算的梯度强度的结果
                        realx=x+(4*i+k)*math.cos(pi_theta)-(4*j+l)*math.sin(pi_theta)
                        #将物体坐标系中的点换算到图像坐标系中
                        realy=y+(4*i+k)*math.sin(pi_theta)+(4*j+l)*math.cos(pi_theta)
                        posx=int(realx)#得到双线性差值中的一个顶点坐标
                        posy=int(realy)
                        if posx<=0 or posy<=0 or posx>=image.width-2 or posy>=image.height-2:
                            continue#去除边界
                        tempy=image[posy+1,posx]-image[posy-1,posx]
                        tempx=image[posy,posx+1]-image[posy,posx-1]
                        sqx=tempx*tempx
                        sqy=tempy*tempy
                        m=math.sqrt(sqx+sqy)
                        theta=get_theta(tempx,tempy)
                        theta_value+=theta*(posx+1-realx)*(posy+1-realy)#线性插值
                        m_value+=m*(posx+1-realx)*(posy+1-realy)#对m也进行了线性插值运算
                        tempy=image[posy+2,posx]-image[posy,posx]
                        tempx=image[posy+1,posx+1]-image[posy+1,posx-1]
                        sqx=tempx*tempx
                        sqy=tempy*tempy
                        m=math.sqrt(sqx+sqy)
                        theta=get_theta(tempx,tempy)
                        theta_value+=theta*(realx-posx)*(posy+1-realy)
                        m_value+=m*(realx-posx)*(posy+1-realy)
                        tempy=image[posy+1,posx+1]-image[posy-1,posx+1]
                        tempx=image[posy,posx+2]-image[posy,posx]
                        sqx=tempx*tempx
                        sqy=tempy*tempy
                        m=math.sqrt(sqx+sqy)
                        theta=get_theta(tempx,tempy)
                        theta_value+=theta*(posx+1-realx)*(realy-posy)
                        m_value+=m*(posx+1-realx)*(realy-posy)
                        tempy=image[posy+2,posx+1]-image[posy,posx+1]
                        tempx=image[posy+1,posx+2]-image[posy+1,posx]
                        sqx=tempx*tempx
                        sqy=tempy*tempy
                        m=math.sqrt(sqx+sqy)
                        theta=get_theta(tempx,tempy)
                        theta_value+=theta*(realx-posx)*(realy-posy)
                        m_value+=m*(realx-posx)*(realy-posy)
                        bin[int(float((theta_value-dir_theta+360))%360/45)]+=m_value
                        #将权值累加到8个bin中对应的位置，这里的bin是由图像坐标系中的梯度方向
                        #减去关键点主方向得到的
                for m in range(0,8):
                    vector.append(bin[m])#储存8维向量
                    bin[m]=0#清空8维向量，进行下次运算
        total_vector.append(vector)#将每一个关键点的128维向量存入total_vector
    return total_vector

def get_vector(total_vector):#对128维向量归一化
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

def times(vec1,vec2):#一个向量乘法的辅助程序
    result=0
    for i in range(0,128):
        result+=vec1[i]*vec2[i]
    return result

def get_theta(tempx,tempy):#求梯度方向theta的辅助程序
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
array1=list()#array1用来存放第一个图片中的所有角点（以二维数组的形式）
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
total_vector1=double_linear(image1,array1,final_dir1)#所有关键点的未归一的128维向量
compare_vector1=get_vector(total_vector1)#所有关键点的归一化的128维sift描述子
final_dir2=get_dir(image2,array2)
total_vector2=double_linear(image2,array2,final_dir2)
compare_vector2=get_vector(total_vector2)
length1=len(compare_vector1)#第一张图片中sift描述子的个数（即角点数）
length2=len(compare_vector2)
posx=-1
posy=-1
outfile1=open("3out1.txt","w")
outfile2=open("3out2.txt","w")
for i in range(0,length1):
    maximum=0#以maximum作为参照，来得到两个图片中sift描述子的最大乘积并在后面输出
    for j in range(0,length2):
        temp=times(compare_vector1[i],compare_vector2[j])
        if temp>maximum:
            posx=i
            posy=j
            maximum=temp
    if maximum>0.8:#把两个sift乘积的最大值大于0.8的情况输出，从而绘制匹配图像
        outfile1.write(str(array1[posx][0])+'\t'+str(array1[posx][1])+'\n')
        #输出对应的关键点的x和y坐标
        outfile2.write(str(array2[posy][0])+'\t'+str(array2[posy][1])+'\n')
infile1.close()
infile2.close()
outfile1.close()
outfile2.close()
