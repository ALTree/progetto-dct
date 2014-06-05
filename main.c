#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "CImg.h"
#include "dct.h"

using namespace cimg_library;

int main(int argc, char ** argv)
{
    if(argc < 2){
        printf("Usa: %s nomefile", argv[0]);
        return 1;
    }

    // leggi immagine
    CImg<unsigned char> image(argv[1]);
    uint8_t * img = image.data();
    
    int m = image.height();
    int n = image.width();
    
    // print_iarray(m, n, img);
    
    // calcola DCT2
    double * dct = dct2(m, n, img);

    print_array(m, n, dct);

    
}
