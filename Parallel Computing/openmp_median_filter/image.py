from PIL import Image 

img = Image.open("test.png")
width, height = img.size

pix = img.load()

R = []
G = []
B = []

for i in range(height):
    R.append([])
    G.append([])
    B.append([])
    for j in range(width):
        R[i].append(pix[i,j][0])
        G[i].append(pix[i,j][1])
        B[i].append(pix[i,j][2])


for i in range(height):
    for j in range(width):
        print R[i][j],
    print 

for i in range(height):
    for j in range(width):
        print G[i][j],
    print 

for i in range(height):
    for j in range(width):
        print B[i][j],
    print 

