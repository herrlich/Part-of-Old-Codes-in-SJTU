from PIL import Image 

img = Image.open("test.png")
after = open("done.txt", "r")
width, height = img.size

pix = img.load()

R = []
G = []
B = []

print height
for i in range(height):
    R.append([])
    R[i] = map(lambda s: int(s.strip()), after.next().split())

for i in range(height):
    G.append([])
    G[i] = map(lambda s: int(s.strip()), after.next().split())

for i in range(height):
    B.append([])
    B[i] = map(lambda s: int(s.strip()), after.next().split())

for i in range(height):
    for j in range(width):
        pix[i,j] = (R[i][j], G[i][j], B[i][j])

img.save("test2.png")
