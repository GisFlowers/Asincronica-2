
#include "PPMFile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct strRgbColor {
    int r, g, b;
};

typedef struct strRgbColor* rgbColor;

struct strPPMFile {
    char * name;
    int nameLenght, width, height, max;
    rgbColor ** image;
};

PPMFile ppmFile_create(char * name){
    PPMFile  ppm = (PPMFile) malloc(sizeof(struct strPPMFile));
    printf("%s\n", name); //nombre del archivo como argumento a la funciOn

    FILE * f = fopen(name, "r+"); // lectura y escritura
    if(f == NULL){
        free(ppm);
        return NULL;
    }    
    


    ppm->nameLenght = strlen(name);
    char *nombre = (char *)malloc(ppm->nameLenght * sizeof(char) + 1);
    for (int i = 0; i < ppm->nameLenght; i++) { // Cambiado a < en lugar de <=
        printf("%c\n", name[i]);
        nombre[i] = name[i]; // Cambiado para asignar directamente
    }
    nombre[ppm->nameLenght] = '\0';

    ppm->name = nombre;


    // Asignar valores a width y 
    ppm->width = 0; // Inicializar en 0
    ppm->height = 0; // Inicializar en 0

    fclose(f);



    // Reservar memoria para la matriz de colores
    ppm->image = (rgbColor **)malloc(ppm->height * sizeof(rgbColor *));
    for (int i = 0; i < ppm->height; i++) {
        ppm->image[i] = (rgbColor *)malloc(ppm->width * sizeof(rgbColor));
    }



    printf("Hola");
    return ppm;

}



void ppmFile_destroy(PPMFile pf) {
    if (pf != NULL) {
        free(pf->name);
        for (int i = 0; i < pf->height; i++) {
            free(pf->image[i]);
        }
        free(pf->image);
        free(pf);
    }
}


void ppmFile_blackAndWhite(PPMFile pf) {
    // Implementa la conversión a blanco y negro aquí
}

void ppmFile_grayscale(PPMFile pf) {
    // Implementa la conversión a escala de grises aquí
}

void ppmFile_compress(PPMFile pf) {
    // Implementa la compresión aquí
}

void ppmFile_dithering(PPMFile pf) {
    // Implementa el dithering aquí
}
