#!/usr/bin/python2.7

import math

print "char LUT[256] = {"
for i in range(0, 64):
    for j in range(0, 4):
        k = i*4.0 + j
        print format(int(79.0*(1.0 + 0.5*math.sin(k*2.0*math.pi/256.0))), '#04X') + ", ",
    print ""

print "};"
