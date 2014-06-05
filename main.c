#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "CImg.h"
#include "dct.h"

using namespace cimg_library;

int main(int argc, char ** argv)
{
    if(argc < 3){
        printf("Usa:\t %s nome_file numero_bins \n", argv[0]);
        return 1;
    }

    int bins = atoi(argv[2]);
    
    // leggi immagine
    CImg<unsigned char> image(argv[1]);
    uint8_t * img = image.data();
    int m = image.height();
    int n = image.width();
    
    // calcola DCT2
    double * dct = dct2(m, n, img);

    // esporta istogramma
    hist(m, n, bins, dct);

    // calcola IDCT2
    uint8_t * img2 = idct2(m, n, dct);
    
}
