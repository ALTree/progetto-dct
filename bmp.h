#pragma pack(push, 1)

typedef struct BMPFILEHEADER {
    uint16_t signature;
    uint32_t size;
    uint16_t r1, r2;
    uint32_t offset;
} BMPFILEHEADER;

typedef struct BMPHEADER {
    uint32_t header_size;
    uint32_t width, height;
    uint16_t planes, bpp;
    uint32_t compression;
    uint32_t image_size;
} BMPHEADER;

#pragma pack(pop)

// stampa a schermo le informazioni contenute nei
// file header e bmp header passati
void print_info(BMPFILEHEADER *, BMPHEADER *);

// apre il file .bmp passato come primo parametro,
// ritorna un array con i valori dei bits e riempie
// la struttura BITMAPHEADER passata con le informazioni
// ricavata dell'header del file
uint8_t * open_bmp(FILE * , BMPHEADER *);
