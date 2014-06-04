#include <complex.h>
#include <fftw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int m = 3, n = 4;
    int size = m * n;
    double * out;

    fftw_plan plan;
    //in = fftw_malloc(sizeof(double) * size);
    out = fftw_malloc(sizeof(double) * size);

    double in[] = {11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34}; 
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%8.3f ", in[i*n + j]);
        }
        putchar('\n');
    }
    printf("\n\n");
    
    plan = fftw_plan_r2r_2d(m, n, in, out, FFTW_REDFT10,
			    FFTW_REDFT10, FFTW_ESTIMATE);

    fftw_execute(plan);

    double norm1 = 4 * sqrt(m/2.0) * sqrt(n/2.0);
    double norm2 = sqrt(2);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            out[i*n + j] = out[i*n + j] / norm1;
            if(i == 0 || j == 0)
                out[i*n + j] = out[i*n + j] / norm2;
        }
    }
    out[0] = out[0] / norm2;
    

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%8.3f ", out[i*n + j]);
        }
        putchar('\n');
    }
    printf("\n");
    
	
    
}
