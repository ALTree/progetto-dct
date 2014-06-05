#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "bmp.h"

void print_info(BMPFILEHEADER * file, BMPHEADER * bmp)
{
    printf("\n>> file header: \n");
    printf("\tsignature: %04x \n", file->signature);
    printf("\tsize: %08x \n", file->size);
    printf("\tr1, r2: %04x %04x \n", file->r1, file->r2);
    printf("\toffset: %08x \n", file->offset);

    printf("\n>>> bmp header: \n");
    printf("\theader size: %04x \n", bmp->header_size);
    printf("\twidth: %08x \n", bmp->width);
    printf("\theight: %08x \n", bmp->height);
    printf("\tplanes: %04x \n", bmp->planes);
    printf("\tbpp: %04x \n", bmp->bpp);
    printf("\tcompression: %08x \n", bmp->compression);
    printf("\timage size: %08x \n\n", bmp->image_size);
}

uint8_t * open_bmp(FILE * fileptr, BMPHEADER * bmp_header)
{
    if(fileptr == NULL)
        return NULL;

// legge file header
    BMPFILEHEADER file_header;
    fread(&file_header, sizeof(BMPFILEHEADER), 1, fileptr);

// controlla bmp magic number
    if(file_header.signature != 0x4D42){
        printf("File signature doesn't match!\n");
        return NULL;
    }
// legge bmp header
    fread(bmp_header, sizeof(BMPHEADER), 1, fileptr);

// muove il file pointer all'inizio dei dati dell'immagine
    fseek(fileptr, file_header.offset, SEEK_SET);

    uint64_t img_size = bmp_header->width * bmp_header->height;


    unsigned char * img = malloc(img_size);
    if(!img){
        printf("malloc failed @ line %d\n", __LINE__);
        return NULL;
    }

// legge i dati dell'immagine
    size_t read_code = fread(img, img_size, 1, fileptr);
    if(read_code != 1){
        printf("fread failed @ line %d\n", __LINE__);
        return NULL;
    }

    fclose(fileptr);
    return img;
}

int main(int argc, char ** argv)
{
    if(argc < 2){
        printf("Usa: %s nomefile", argv[0]);
        return 1;
    }

    FILE * fileptr = fopen(argv[1], "rb");

    if(fileptr == NULL){
        printf("fopen failed @ line %d\n", __LINE__);
        return 1;
    }

    BMPHEADER img_info;
    unsigned char * img = open_bmp(fileptr, &img_info);

    uint32_t width = img_info.width;
    uint32_t height = img_info.height;
    uint16_t bpp = img_info.bpp;
    uint32_t compression = img_info.compression;

    printf(" >> img loaded \n");
    printf("\tlarghezza: %d px \n", width);
    printf("\taltezza: %d px \n", height);
    printf("\tbpp: %d \n", bpp);
    printf("\tcompression: %d \n", compression);

    for(int i = 0, j = 0; i < width*height; i++, j++){
        if(j == width){
            putchar('\n');
            j = 0;
        }
        printf("%d ", img[i]);
    }

    printf("\n");

}
