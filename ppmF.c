#include "PPMFile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Estructura rgbColor
struct strRgbColor {
    unsigned char r, g, b; 
};

typedef struct strRgbColor rgbColor;

// Estructura PPMFile
struct strPPMFile {
    char* name;
    int nameLength, width, height, max;
    rgbColor* image;
};

// FunciOn para crear un PPMFile
PPMFile ppmFile_create(char* name) {
    PPMFile ppm = (PPMFile)malloc(sizeof(struct strPPMFile));
    if (ppm == NULL) {
        fprintf(stderr, "Error en la asignación de memoria para PPMFile\n");
        return NULL;
    }

    // Copiar el nombre del archivo
    ppm->name = strdup(name);
    ppm->nameLength = strlen(name);
    
    // Abrir el archivo en modo lectura
    FILE* f = fopen(name, "rb");
    if (f == NULL) {
        fprintf(stderr, "Error al abrir el archivo\n");
        free(ppm->name);
        free(ppm);
        return NULL;
    }

    // Leer la cabecera del archivo PPM
    char format[3];
    if (fscanf(f, "%2s", format) != 1 || strcmp(format, "P6") != 0) {
        fprintf(stderr, "Formato PPM inválido\n");
        fclose(f);
        free(ppm->name);
        free(ppm);
        return NULL;
    }
    
    if (fscanf(f, "%d %d", &ppm->width, &ppm->height) != 2) {
        fprintf(stderr, "Error al leer el ancho y el alto de la imagen\n");
        fclose(f);
        free(ppm->name);
        free(ppm);
        return NULL;
    }
    
    if (fscanf(f, "%d", &ppm->max) != 1) {
        fprintf(stderr, "Error al leer el valor máximo de color\n");
        fclose(f);
        free(ppm->name);
        free(ppm);
        return NULL;
    }

    // Reservar memoria para la matriz de píxeles
    ppm->image = (rgbColor*)malloc(ppm->height * sizeof(rgbColor*));
    for (int i = 0; i < ppm->height; i++) {
        ppm->image[i] = (rgbColor*)malloc(ppm->width * sizeof(rgbColor));
    }

    // Leer los datos de la imagen
    for (int i = 0; i < ppm->height; i++) {
        for (int j = 0; j < ppm->width; j++) {
            if (fread(&ppm->image[i][j], sizeof(rgbColor), 1, f) != 1) {
                fprintf(stderr, "Error al leer datos de la imagen\n");
                fclose(f);
                ppmFile_destroy(ppm);
                return NULL;
            }
        }
    }

    // Cerrar el archivo
    fclose(f);
    return ppm;
}

// Función para liberar la memoria de una instancia de PPMFile
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

// Función para convertir la imagen a blanco y negro
void ppmFile_blackAndWhite(PPMFile pf) {
    if (pf != NULL) {
        for (int i = 0; i < pf->height; i++) {
            for (int j = 0; j < pf->width; j++) {
                // Calcular el promedio de los valores RGB
                unsigned char gray = (pf->image[i][j].r + pf->image[i][j].g + pf->image[i][j].b) / 3;
                // Asignar el mismo valor de gris a cada canal RGB
                pf->image[i][j].r = gray;
                pf->image[i][j].g = gray;
                pf->image[i][j].b = gray;
            }
        }
    }
}
