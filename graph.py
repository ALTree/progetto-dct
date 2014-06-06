#!/usr/bin/env python

from __future__ import print_function
import numpy as np
import pylab as P

def main(nome, frase):
	# valori dei parametri
	parametri = {}

	# istogramma
	hist = np.array([], dtype='int32')


	# smacinamento file col risultato
	with open(nome) as t:
		for _ in range(3):
			row = t.readline()
			desc = row.split('\t')
			parametri[desc[0]] = float(desc[1][:-2])
		
		for row in t:
			hist = np.append(hist, int(row[:-1]))

	base = np.arange(0, parametri['max'], parametri['width'])

	width = parametri['width']

	#
	# comparazione tempi iterativa simmetrica
	#
	P.figure()


	P.bar(base, hist, width=width, color='b', label='simmetriche', log=True)


	#P.xticks(base, tuple(base))
	P.xlabel('Frequenze')
	tit = 'Istogramma delle frequenze della DCT con ' + str(parametri['bins']) + ' bins -' + frase
	P.suptitle(tit)

if __name__ == '__main__':
	main("hist.txt", " pre taglio")
	main("hist2.txt", " post taglio")
	P.show()
