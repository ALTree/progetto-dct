#!/usr/bin/env python
import numpy as np
import pylab as P

# valori dei parametri
parametri = {}

# istogramma
hist = np.array([], dtype='int32')


# smacinamento file col risultato
with open('hist.txt') as t:
	for _ in range(3):
		row = t.readline()
		desc = row.split('\t')
		parametri[desc[0]] = float(desc[1][:-2])
	
	for row in t:
		hist = np.append(hist, int(row[:-1]))

print(parametri)
print(hist)
print('len hist: ', len(hist))
base = np.arange(0, parametri['max'], parametri['width'])

print(base)
print('len base: ', len(hist))

width = parametri['width'] * 0.8

#
# comparazione tempi iterativa simmetrica
#
P.figure()


P.bar(base, hist, width=width, color='b', label='simmetriche', log=True)


#P.xticks(base, tuple(base))
P.xlabel('Metodo utilizzato')
P.ylabel('Tempi')
tit = 'Istogramma delle frequenze della DCT con ' + str(parametri['bins']) + ' bins'
P.suptitle(tit)

P.show()

