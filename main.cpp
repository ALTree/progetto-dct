#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#define cimg_display 0
#include "CImg.h"
#include "dct.h"

using namespace cimg_library;

int main(int argc, char ** argv)
{
    if(argc < 4){
        printf("Usa:\t %s nome_file numero_bins taglio \n", argv[0]);
        printf("Usa -h alla fine del comando per plottare l'istogramma");
        return 1;
    }

    int bins = atoi(argv[2]);
    int cut = atoi(argv[3]);
    
    // leggi immagine
    CImg<unsigned char> image(argv[1]);
    uint8_t * img = image.data();
    int m = image.height();
    int n = image.width();
    
    // calcola DCT2
    double * dct = dct2(m, n, img);

    // esporta istogramma
    hist(m, n, bins, dct);

    if(argc==5){
        system("python graph.py");
    }

    // tagliataglia
    cut_dct(m, n, cut, dct);
    
    // calcola IDCT2
    uint8_t * img2 = idct2(m, n, dct);

    // salva img2 su file
    CImg<unsigned char> image2(img2, n, m, 1, 1);
    image2.save(strcat(argv[1], "cut.bmp"), -1, 3);;
    
}
