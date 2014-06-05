

// converte uint8_t* in double*
double * to_double(int, int, uint8_t *);

// normalizzazione fftw3
void normalizza(int, int, double *);

// dct2 sull'array uint8_t
double * dct2(int, int, uint8_t *);

// dct2 sull'array uint8_t
uint8_t * idct2(int, int, double *);

// stampa array
void print_array(int, int, double *);
void print_iarray(int, int, uint8_t *);
