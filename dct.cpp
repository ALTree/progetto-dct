
#include <complex.h>
#include <fftw3.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "dct.h"



double * to_double(int m, int n, uint8_t * array)
{
    double * out = new double[m*n];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            out[i*n + j] = (double)array[i*n + j];
    }
    return out;
}

uint8_t * to_uint8_t(int m, int n, double * array)
{
    uint8_t * out = new uint8_t[m*n];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(array[i*n + j] > 255){
                out[i*n + j] = 255;
            } else {
                out[i*n + j] = (uint8_t)array[i*n + j];
            }
        }
    }
    return out;
}

void normalizza(int m, int n, double * array)
{
    double norm1 = 4 * sqrt(m/2.0) * sqrt(n/2.0);
    double norm2 = sqrt(2);

    // normalizzazione globale
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            array[i*n + j] /= norm1;
    }

    // normalizzazione prima riga
    for(int i = 0; i < n; i++)
        array[i] /= norm2;

    // normalizzazione prima colonna
    for(int j = 0; j < (m*n); j+=n)
        array[j] /= norm2;
}

void denormalizza(int m, int n, double * array)
{
    double norm1 = 4 * sqrt(m/2.0) * sqrt(n/2.0);
    double norm2 = sqrt(2);
    double norm3 = 4 * m * n;

    // normalizzazione globale
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            array[i*n + j] = array[i*n + j] / norm3 * norm1;
    }

    // normalizzazione prima riga
    for(int i = 0; i < n; i++)
        array[i] *= norm2;

    // normalizzazione prima colonna
    for(int j = 0; j < (m*n); j+=n)
        array[j] *= norm2;
}

double * dct2(int m, int n, uint8_t * array)
{
    // setup input e output
    double * out = new double[m*n];
    double * in  = to_double(m, n, array);

    // do the fftw3 magic
    fftw_plan plan = fftw_plan_r2r_2d(m, n, in, out, FFTW_REDFT10,
				      FFTW_REDFT10, FFTW_ESTIMATE);
    fftw_execute(plan);

    // normalizzazione
    normalizza(m, n, out);
    return out;
}

uint8_t * idct2(int m, int n, double * array)
{
    // setup input e output
    double * out = new double[m*n];

    // denormalizzazione
    denormalizza(m, n, array);

    // do the fftw3 magic 
    fftw_plan plan = fftw_plan_r2r_2d(m, n, array, out, FFTW_REDFT01,
				      FFTW_REDFT01, FFTW_ESTIMATE);
    fftw_execute(plan);

    return to_uint8_t(m, n, out);
}

void cut_dct(int m, int n, double val, double * array)
{
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
	    if(abs(array[i*n + j]) < val)
		array[i*n + j] = 0.0;
	}
    }
}

void hist(int m, int n, int bins, double * array)
{
    // cerchiamo il valore massimo in array
    double max = -1.0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
	    if(array[i*n + j] > max)
		max = array[i*n + j];
	}
    }

    double bins_width = (max + 100.0) / bins;
    int * hist = new int[bins]();
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
	    hist[ (int)abs(array[i*n + j] / bins_width) ]++;
	}
    }

    FILE * fileptr = fopen("hist.txt", "w");
    fprintf(fileptr, "bins\t%d \n", bins);
    fprintf(fileptr, "width\t%.3f \n", bins_width);
    fprintf(fileptr, "max\t%.3f \n", max);
    for(int i = 0; i < bins; i++)
	fprintf(fileptr, "%d\n", hist[i]);

    fclose(fileptr);
    
}

void print_array(int m, int n, double * array)
{
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%8.3f ", array[i*n + j]);
        putchar('\n');
    }
    printf("\n");
}

void print_iarray(int m, int n, uint8_t * array)
{
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%4d ", array[i*n + j]);
        putchar('\n');
    }
    printf("\n");
}


