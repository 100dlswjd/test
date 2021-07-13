n = int(input())
a = str(input())
a_list = []
for x in range(0,n):
    a_list.append(int(a[x]))
h = sum(a_list)
print(h)
