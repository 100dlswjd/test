a,b = input().split()
a = int(a)
b = str(b)

hap1 = a*int(b[2])
hap2 = a*int(b[1])
hap3 = a*int(b[0])
hap4 = hap1+(hap2*10)+(hap3*100)

print(hap1)
print(hap2)
print(hap3)
print(hap4)
