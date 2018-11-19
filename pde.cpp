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


	
}
int main()
{

return 0;
}
