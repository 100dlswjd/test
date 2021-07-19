num = int(input())
a = list()
for x in range(0,num):
    a.append(int(input()))

a.sort()

for x in range(0,num):
    print(a[x])
