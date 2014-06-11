#!/usr/bin/env python

from __future__ import print_function
import numpy as np
import pylab as P
import sys

def main(mode, nome, frase):
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
	step = parametri['max'] / 10
	xticks = np.arange(0, parametri['max'], step)

	width = parametri['width']

	P.figure()

	P.bar(base, hist, width=width, color='b', label='simmetriche', log=True)

	P.xticks(xticks, tuple(xticks.astype('int32')), rotation=45)
	P.xlabel('Frequenze')
	tit = 'Istogramma delle frequenze della DCT ' + frase + '\n visualizzati: ' + str(int(parametri['bins'])) + ' bins - dimensione bin: ' +  str(int(parametri['width']))
	P.title(tit, fontweight='bold', fontsize=14)
	P.tight_layout(rect = [0.03, 0, 0.97, 1])
	
	if mode is '1':
		P.show()
	else:
		fnome = frase + '.eps'
		P.savefig(fnome)

if __name__ == '__main__':
	main(sys.argv[1], sys.argv[2], sys.argv[3])
