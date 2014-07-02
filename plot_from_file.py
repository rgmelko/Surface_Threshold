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
u = []
for lines in fin:
    line = lines.split()
    x.append(float(line[0]))
    y.append(float(line[3]))
    z.append(float(line[4]))
    u.append(float(line[6]))
plt.title('2D torus, L=24, uncorrelated X errors')
plt.xlabel(r'$p$')
#plt.ylabel(r'$\langle \epsilon(0,0) \cdot \epsilon(L/2,L/2) \rangle^2$')
#plt.ylabel(r'$\langle \epsilon(0,0) \rangle {\rm and} \langle \epsilon(L/2,L/2) \rangle$')
plt.ylabel('Energy correlator 2: Connected correlation function')
#key = str(dd)
#plt.errorbar(x, y,yerr=e)
#key = r'$\langle \epsilon(0,0) \rangle$'
#plt.plot(x, z, '-.', markersize=4, label=key)
#key = r'$\langle \epsilon(L/2,L/2) \rangle$'
#plt.plot(x, u, '-.', markersize=4, label=key)
key = r'$\langle \epsilon(0,0) \epsilon(L/2,L/2) \rangle - \langle \epsilon(0,0) \rangle \langle \epsilon(L/2,L/2) \rangle$ '
plt.plot(x, u, '-o', markersize=4, label=key)
plt.legend(loc=3)
plt.minorticks_on()
#plt.show()
plt.savefig('L24E2.png')
