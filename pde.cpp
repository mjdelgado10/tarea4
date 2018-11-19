#include <stdio.h>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;

//Condiciones iniciales
//Numero de pasos
int N=20;
//Valor de un lado de la Calcita en metros
float lado=0.5;
//Distancia entre punto y punto
float delta_x=lado/N;
//Diametro de la varilla en metros
float dm=0.1;
//Constante de la estabilidad 
float ce=0.2;
// Funcion de la temperatura inicial de la calcita y la varilla
void tempinicial(float temperatura[20][20])
{ 
	int i, j;
	float radio;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			// calcular el radio de la varilla en mi posicion presente (i)
			// Se empezo a contar los puntos en el centro de la Calcita
			radio = pow( pow(delta_x*(j-N/2),2) + pow(delta_x*(i-N/2),2) , 0.5);
			// Si el radio es mayor que el diametro, anade el valor de la temperatura como 0
			if (radio>dm/2.0)
			{
				temperatura[i][j]=0.0; // temperatura incial de la calcita
			}else
			{
				temperatura[i][j]=100.0; // temperatura inicial de la varilla
			}
		}
	}



	// Probar un caso asimetrico para verificar diferencias en condiciones de frontera
	//for (i = 16; i < N; i++)
	//{
		//for (j = 16; j < N; j++)
		//{
			//temperatura[i][j]=1000;
		//}
	//}

	
}


//por esquemas de diferencias finitas se calcula la nueva temperatura en todos los puntos de la calcita.
void temperatura(float puntos[20][20], float calcita[20][20])
{

// Guarda el nuevo momento del tiempo en calcita a partir de los datos de puntos

//Declaracion de variable 
	int i, j;
//radio de la esfera
	float radio;
// guarda las posiciones de temperatura los puntos vecinos
	float tfu;
// guarda los puntos  de la temperatura(posiciones) pasados
	float tpa;

// empiezo en 1 y termino en <N-1 para evitar los nodos exteriores

	for (i = 1; i < N-1; i++) 
	{
		for (j = 1; j < N-1; j++)
		{
			// calcular el radio del punto que estoy viendo
			// el origen lo ubico en la mitad del rectangulo
			radio = pow( pow(delta_x*(j-N/2),2) + pow(delta_x*(i-N/2),2) , 0.5);
			if (radio>dm/2.0) // nodo de calcita
			{
				tfu = ce*( puntos[i-1][j] + puntos[i+1][j] + puntos[i][j-1] + puntos[i][j+1]);
				tpa = puntos[i][j] - ce*4*puntos[i][j];

				calcita[i][j] = tpa + tfu;
			}
		}
	}

}

//CASO 1; Condiciones de fronte fijas a 10 grados centigrados

void condiciones_fronteras_fijas(float puntos[20][20])
{
// Se almacena las condiciones de frontera fijas en la Matriz

for (int i = 0; i < N; i++)
{
	puntos[i][0] = 10.0;
	puntos[0][i] = 10.0;
	puntos[i][N-1] = 10.0;
	puntos[N-1][i] = 10.0;
}
}

//CASO 2; Condiciones de frontera abiertas

void condiciones_fronteras_abiertas(float puntos[20][20])
{// Almacena las condiciones de frontera fijas en la Matriz

for (int i = 0; i < N; i++)
{
	puntos[i][0] = puntos[i][1];
	puntos[0][i] = puntos[1][i];
	puntos[i][N-1] = puntos[i][N-2];
	puntos[N-1][i] = puntos[N-2][i];
}
}

//CASO 3.Condiciones de frontera periodicas
void condiciones_fronteras_periodicas(float puntos[20][20], float calcita[20][20])
{// Almacena las condiciones de frontera fijas en la matriz de calcita

// las posiciones de temperatura los puntos vecinos
float tfu;
// puntos  de la temperatura(posiciones) pasados
float tpa;

int j_borde;
int i_borde;
int i, j;

//ciclo cuando  j borde es 0
j_borde = 0;
for (i = 1; i < N-1; i++)
{
	tpa = puntos[i][j_borde] - ce*4*puntos[i][j_borde];
	tfu = ce*( puntos[i-1][j_borde] + puntos[i+1][j_borde] + puntos[i][N-1] + puntos[i][j_borde+1]);
	calcita[i][j_borde] = tpa + tfu;
}

//ciclo cuando j borde es 19
j_borde = N-1;
for (i = 1; i < N-1; i++)
{
	tpa = puntos[i][j_borde] - ce*4*puntos[i][j_borde];
	tfu = ce*( puntos[i-1][j_borde] + puntos[i+1][j_borde] + puntos[i][j_borde-1] + puntos[i][0]);
	calcita[i][j_borde] = tpa + tfu;
}

//ciclo cuando i borde es 0
i_borde = 0;
for (j = 1; i < N-1; j++)
{
	tpa = puntos[i_borde][j] - ce*4*puntos[i_borde][j];
	tfu = ce*( puntos[N-1][j] + puntos[i_borde+1][j] + puntos[i_borde][j-1] + puntos[i_borde][j+1]);
	calcita[i_borde][j] = tpa + tfu;
}

//ciclo cuando i borde es 19
i_borde = N-1;
for (j = 1; i < N-1; j++)
{
	tpa = puntos[i_borde][j] - ce*4*puntos[i_borde][j];
	tfu = ce*( puntos[i_borde-1][j] + puntos[0][j] + puntos[i_borde][j-1] + puntos[i_borde][j+1]);
	calcita[i_borde][j] = tpa + tfu;
}

// esquina
i=0;
j=0;
tpa = puntos[i][j] - ce*4*puntos[i][j];
tfu = ce*( puntos[N-1][j] + puntos[i+1][j] + puntos[i][N-1] + puntos[i][j+1]);
calcita[i][j] = tpa + tfu;

// esquina
i=0;
j=N-1;
tpa = puntos[i][j] - ce*4*puntos[i][j];
tfu = ce*( puntos[N-1][j] + puntos[i+1][j] + puntos[i][j-1] + puntos[i][0]);
calcita[i][j] = tpa + tfu;

// esquina
i=N-1;
j=0;
tpa = puntos[i][j] - ce*4*puntos[i][j];
tfu = ce*( puntos[i-1][j] + puntos[0][j] + puntos[i][N-1] + puntos[i][j+1]);
calcita[i][j] = tpa + tfu;

// esquina
i=N-1;
j=N-1;
tpa = puntos[i][j] - ce*4*puntos[i][j];
tfu = ce*( puntos[i-1][j] + puntos[0][j] + puntos[i][j-1] + puntos[i][0]);
calcita[i][j] = tpa + tfu;
}

//guardar los tres archivos, uno por cada condicion de frontera
void imprimir_datos(float puntos[20][20], char *nombre_archivo)
{
int i, j;
ofstream imprimir_archivo(nombre_archivo);

for (i = 0; i < N; i++)
{
	for (j = 0; j < N; j++)
	{
		imprimir_archivo << puntos[i][j] << " ";
	}
	imprimir_archivo << "\n";
}

}

int main()
{


//Condiciones de fontera fijas
float fronfijas[20][20];
float fronfijas_1[20][20];
//condiciones de fontera abiertas
float fronabiertas[20][20];
float fronabiertas_1[20][20];
//condiciones de fontera periodicas
float fronperiodicas[20][20];
float fronperiodicas_1[20][20];
// difusion de los puntos
float v=1.62/(820*2.71*1000); 
float dtt=pow(delta_x,2)*ce/v;
	
// Solucion para condiciones de frontera fijas
int i, j, n;
int nmax=50;


// Incializar sistemas
tempinicial(fronfijas);
tempinicial(fronfijas_1);
// Para las condiciones de frontera fijas, inicializar los valores de las fronteras
condiciones_fronteras_fijas(fronfijas); 
condiciones_fronteras_fijas(fronfijas_1);
// Para las condiciones de frontera abiertas, inicializar los valores de las fronteras
tempinicial(fronabiertas);
tempinicial(fronabiertas_1);
// Para las condiciones de frontera periodicas, inicializar los valores de las fronteras
tempinicial(fronperiodicas);
tempinicial(fronperiodicas_1);

for (n = 0; n < nmax; ++n)
{
	temperatura(fronfijas, fronfijas_1);
	temperatura(fronabiertas, fronabiertas_1);
	temperatura(fronperiodicas, fronperiodicas_1);

	// Calcular condiciones de frontera
	condiciones_fronteras_fijas(fronfijas_1);
	condiciones_fronteras_abiertas(fronabiertas_1);
	condiciones_fronteras_periodicas(fronperiodicas , fronperiodicas_1);

	// Guardar los valores nuevos en el arreglo 0
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			fronfijas[i][j] = fronfijas_1[i][j];
			fronabiertas[i][j] = fronabiertas_1[i][j];
			fronperiodicas[i][j] = fronperiodicas_1[i][j];
		}
	}

	}

//imprime los archivos por cada condicion de frontera
imprimir_datos(fronfijas_1, "fronterasfijas.txt");
imprimir_datos(fronabiertas_1, "fronterasabiertas.txt");
imprimir_datos(fronperiodicas_1, "fronterasperiodicas.txt");
	
	

cout << "Finalizar" << endl;

return 0;
}
