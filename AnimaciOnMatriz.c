#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 20

char m[HEIGHT][WIDTH];
char buffer[HEIGHT*WIDTH + HEIGHT + 1];

void display();
void delay(int msLimit);

int main(void) {

	int i, j;

	//limpiamos la matriz llenAndola de espacios
	for(i=0; i<HEIGHT; i++)
		for(j=0; j<WIDTH; j++)
			m[i][j] = ' ';
		
		
	for(i = 0; i <  HEIGHT; i++)
	{	
		for(j = 0; j < WIDTH; j++)
		{
			m[i][j] = 'X';
			m[HEIGHT -1 -i][WIDTH -1 -j] = 'Y';
			//esperamos unos 50 ms
			delay(50);
			//limpiamos la pantalla
			system("cls");
			//dibujamos la matriz
			display();
		}
	}
	
	//para que no se cierre la consola
	getchar();

	return 0;


}


void display() {
	//metemos todos los caracteres de la matriz...
	//...en un buffer
	//para hacer un solo printf
	//porque serIa demasiado costoso hacer un printf por cada caracter
	int i, j, k = 0;
	for(i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
			buffer[k++] = m[i][j];
		buffer[k++] = '\n';
	}

	buffer[k] = '\0';
	printf("%s", buffer);
}


void delay(int msLimit)
{
	clock_t begin = clock();

	clock_t end, difference;
	do
	{
		end = clock();
		difference = (end - begin) * 1000 / CLOCKS_PER_SEC;
	}while(difference < msLimit);
}





