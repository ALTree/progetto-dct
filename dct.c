#include <complex.h>
#include <fftw3.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int n = 2, m = 3;
    int size = n * m;
    double * in, * out;

    fftw_plan plan;
    in = fftw_malloc(sizeof(double) * size);
    out = fftw_malloc(sizeof(double) * size);

    for(int i = 0; i < n; i++){
	for(int j = 0; j < m; j++){
	    in[i*m + j] = (i*m + j) + 1;
	}
    }
    
    for(int i = 0; i < n; i++){
	for(int j = 0; j < m; j++){
	    printf("%4f ", in[i*m + j]);
	}
    }
    printf("\n\n");
    
    plan = fftw_plan_r2r_2d(n, m, in, out, FFTW_REDFT10,
			    FFTW_REDFT10, FFTW_ESTIMATE);

    fftw_execute(plan);

    for(int i = 0; i < n; i++){
	for(int j = 0; j < m; j++){
	    printf("%4f ", out[i*m + j]);
	}
    }
    printf("\n");
    
	
    
}
