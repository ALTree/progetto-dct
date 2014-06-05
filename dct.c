#include <complex.h>
#include <fftw3.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "dct.h"



double * to_double(int m, int n, uint8_t * array)
{
    double * out = (double *)malloc(sizeof(double) * m * n);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            out[i*n + j] = (double)array[i*n + j];
    }
    return out;
}

uint8_t * to_uint8_t(int m, int n, double * array)
{
    uint8_t * out = (uint8_t *)malloc(sizeof(uint8_t) * m * n);
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
    double * out = (double *)fftw_malloc(sizeof(double) * m * n);
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
    double * out = (double *)fftw_malloc(sizeof(double) * m * n);

// denormalizzazione
    denormalizza(m, n, array);

// do the fftw3 magic 
    fftw_plan plan = fftw_plan_r2r_2d(m, n, array, out, FFTW_REDFT01,
        FFTW_REDFT01, FFTW_ESTIMATE);
    fftw_execute(plan);

    return to_uint8_t(m, n, out);
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

/*
int main(void)
{
    int m = 3, n = 4;
    uint8_t in[] = {11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34}; 

    print_iarray(m, n, in);

    double * out = dct2(m, n, in);
    print_array(m, n, out);

    uint8_t * inv = idct2(m, n, out);
    print_iarray(m, n, inv);
}
*/
