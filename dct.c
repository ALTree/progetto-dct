#include <complex.h>
#include <fftw3.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int n = 3, m = 4;
    int size = n * m;
    double * out;

    fftw_plan plan;
    //in = fftw_malloc(sizeof(double) * size);
    out = fftw_malloc(sizeof(double) * size);

    double in[] = {11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34}; 
    
    for(int i = 0; i < n; i++){
	for(int j = 0; j < m; j++){
	    printf("%8.3f ", in[i*m + j]);
	}
	putchar('\n');
    }
    printf("\n\n");
    
    plan = fftw_plan_r2r_2d(n, m, in, out, FFTW_REDFT10,
			    FFTW_REDFT10, FFTW_ESTIMATE);

    fftw_execute(plan);

    for(int i = 0; i < n; i++){
	for(int j = 0; j < m; j++){
	    printf("%8.3f ", out[i*m + j]);
	}
	putchar('\n');
    }
    printf("\n");
    
	
    
}
