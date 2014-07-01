#!/usr/bin/env python
""" Plots data from a text file using matplotlib.
"""

import matplotlib.pyplot as plt
import os

#dirlist = ['L10b','L12b','L16b']

#for dd in dirlist:
data= '00.data' 
fin = open(data, 'r')
x = []
y = []
z = []
for lines in fin:
    line = lines.split()
    x.append(float(line[0]))
    y.append(float(line[1]))
    z.append(float(line[2]))
plt.title('2D torus, L=20, uncorrelated errors')
plt.xlabel(r'$p$')
plt.ylabel(r'$\langle E(0,0) \times E(L/2,L/2) \rangle$')
#key = str(dd)
#plt.errorbar(x, y,yerr=e)
plt.plot(x, y, '-o', markersize=4)
plt.plot(x, z, '-s', markersize=4)
#plt.legend(loc=6)
plt.show()
#plt.savefig('L20.pdf')
