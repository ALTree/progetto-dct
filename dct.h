

// converte uint8_t* in double*
double * to_double(int, int, uint8_t *);

// converte double* in uint8_t
uint8_t * to_uint8_t(int m, int n, double * array);

// normalizzazione fftw3
void normalizza(int, int, double *);

// denormalizzazione fftw3
void denormalizza(int m, int n, double *);

// dct2 sull'array uint8_t
double * dct2(int, int, uint8_t *);

// idct2 sull'array uint8_t
uint8_t * idct2(int, int, double *);

// stampa istogramma
void hist(int, int, int, double *);

// stampa array
void print_array(int, int, double *);
void print_iarray(int, int, uint8_t *);
