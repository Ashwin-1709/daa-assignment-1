import matplotlib.pyplot as plt
coord = list()
n = int(input())
curcol = 0
col = ["#a7d52a", "#dff429", "#f6c137", "#f25e40", "#c32a94", "#7328b6", "#3438bd", "#3f77c4", "#4daecf", "#52c67f", "#79c725"]
collen = len(col)
for i in range(n) :
    x , y = map(float , input().split())
    temp = [x , y]
    coord.append(temp)
coord.append(coord[0])
xs , ys = zip(*coord)
plt.figure()
plt.fill(xs , ys , col[curcol % collen])
plt.savefig('original')
plt.figure()
curcol += 1
n_p = int(input())
for i in range(n_p) : 
    m = int(input())
    coord_dec = list()
    vert = list(map(float , input().split()))
    curptr = 0
    for j in range(m) :
        x = vert[curptr]
        y = vert[curptr + 1]
        temp = [x , y]
        coord_dec.append(temp)
        curptr += 2
    coord_dec.append(coord_dec[0])
    nx , ny = zip(*coord_dec)
    plt.fill(nx , ny , col[curcol % collen])
    curcol += 1
plt.savefig('before_merge')
plt.figure()
curcol += 1
n_d = int(input())
for i in range(n_d) : 
    m = int(input())
    coord_dec = list()
    vert = list(map(float , input().split()))
    curptr = 0
    for j in range(m) :
        x = vert[curptr]
        y = vert[curptr + 1]
        temp = [x , y]
        coord_dec.append(temp)
        curptr += 2
    coord_dec.append(coord_dec[0])
    nx , ny = zip(*coord_dec)
    plt.fill(nx , ny , col[curcol % collen])
    curcol += 1
plt.savefig('after_merge')
plt.show()
