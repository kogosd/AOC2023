from math import *

def calc(t, r):
    d = sqrt((t/2)**2 -r)
    x1 = t/2 + d
    x2 = t/2 - d
    return (floor(x1) - ceil(x2) + 1)

t = 71530
r = 940200
print(calc(t,r))

t = 51926890
r = 222203111261225
print(calc(t,r))

t = 51926890000000000000
r = 222203111261225000000000000
print(calc(t,r))
