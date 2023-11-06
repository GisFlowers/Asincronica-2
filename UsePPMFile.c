#include <stdio.h>
#include "PPMFile.h"

int main(){
    PPMFile ppm = ppmFile_create("pruebaAsincronica.ppm");
    printf("%p\n", ppm);
    return 0;
}