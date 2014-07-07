#!/usr/bin/env python
""" Plots data from a text file using matplotlib.
"""

import matplotlib.pyplot as plt
import os

#dirlist = ['L10b','L12b','L16b']

#for dd in dirlist:
data= '01.data' 
fin = open(data, 'r')
x = []
y = []
z = []
u = []
for lines in fin:
    line = lines.split()
    x.append(float(line[0]))
    y.append(float(line[1]))
    z.append(float(line[2]))
    u.append(float(line[10])/4.0)
plt.title('2D torus, L=24, uncorrelated X errors')
plt.xlabel(r'$p$')
#plt.ylabel(r'$\langle \epsilon(0,0) \cdot \epsilon(L/2,L/2) \rangle^2 {\rm and} \langle \epsilon(0,0) \rangle$')
#plt.ylabel(r'$\langle \epsilon(0,0) \rangle {\rm and} \langle \epsilon(L/2,L/2) \rangle$')
plt.ylabel('Global and single-plaquette specific heats')
#key = str(dd)
#plt.errorbar(x, y,yerr=e)
key = r'$C_1$'
plt.plot(x, z, '-o', markersize=4, label=key)
key = r'$C_2/4$'
plt.plot(x, u, '-.', markersize=4, label=key)
#key = r'$\langle \epsilon(0,0) \epsilon(L/2,L/2) \rangle - \langle \epsilon(0,0) \rangle \langle \epsilon(L/2,L/2) \rangle$ '
#plt.plot(x, u, '-o', markersize=4, label=key)
plt.legend(loc=8)
plt.minorticks_on()
#plt.show()
plt.savefig('L24C.png')
