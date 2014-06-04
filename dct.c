#include <complex.h>
#include <fftw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

    double norm1 = 4 * sqrt(m/2.0) * sqrt(n/2.0);
    double norm2 = sqrt(2);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            out[i*m + j] = out[i*m + j] / norm1;
            if(i == 0 || j == 0)
                out[i*m + j] = out[i*m + j] / norm2;
        }
    }
    out[0] = out[0] / norm2;
    

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%8.3f ", out[i*m + j]);
        }
	   putchar('\n');
    }
    printf("\n");
    
	
    
}
