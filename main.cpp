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
        printf("Usa -h alla fine del comando per plottare l'istogramma \n");
        return 1;
    }

    int bins = atoi(argv[2]);
    int cut = atoi(argv[3]);

    /*
    uint8_t in[] = {11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34};
    print_iarray(3, 4, in);
    
    double * out = dct2(3, 4, in);
    print_array(3, 4, out);

    uint8_t * in2 = idct2(3, 4, out);
    print_iarray(3, 4, in2);
    */

    
    // leggi immagine
    CImg<unsigned char> image(argv[1]);
    uint8_t * img = image.data();
    int m = image.height();
    int n = image.width();
    
    // calcola DCT2
    double * dct = dct2(m, n, img);

    // esporta istogramma
    hist(m, n, bins, dct, "hist.txt");

    // tagliataglia
    cut_dct(m, n, cut, dct);

    // esporta istogramma
    hist(m, n, bins, dct, "hist2.txt");

    if(argc==5){
        system("python graph.py");
    }
    
    // calcola IDCT2
    uint8_t * img2 = idct2(m, n, dct);

    // salva img2 su file
    CImg<unsigned char> image2(img2, n, m, 1, 1);
    image2.save(strcat(argv[1], "cut.bmp"), -1, 3);;
    
    
}
