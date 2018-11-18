#include <stdio.h>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;

//Movimiento de un proyectil
//El metodo usado para resolver la ecuacion de movimiento es Leap-Frog
int main()
{
//Valores de las constantes
float cm=1.0; // porque,  c/masa=0.2/0.2
float gr = -10; // en el eje y negativo
float pi=3.141; //valor de la constante pi

//posicion inicial, pasos en el tiempo
float paso_tiempo = 0.002;

float vx0=300*cos(45/360*(2*pi));
float vy0=300*sin(45/360*(2*pi));

// posiciones en el presente y el futuro
float xpr, xfu;
float ypr, yfu;

// velocidades en el presente, el futuro y en el centro
float vxpr, vxc, vxfu;
float vypr, vyc, vyfu;

// derivadas de posiciones y velocidades
float dx, dy;
float dvx, dvy;
float Fr;

// asignar los valores iniciales al presente
xpr = 0.0;
ypr = 0.0;

//Cambio de paso, presente se convierte en el inicio para empezar a caminar
vxpr = vx0;
vypr = vy0;


//Almacenar los datos en un archivo llamado p45.txt donde estan todos los puntos a un angulo de 45 (no se realizo con ./a.out >> como en clase para indicar el paso en el .cpp
ofstream output("movimientoa45.txt");
//Inicializacion de la distancia que recorrera el proyectil
float distancia_recorrida=0.0;

//Ciclo para caminar 
for (int i = 0; i < 1000; ++i)
{	
	// Valor de Fr y derivadas de la velocidad en x y en y
	Fr = cm*pow(vxpr*vxpr + vypr*vypr, 0.5);
	dvx = -Fr*vxpr;
	dvy = gr -Fr*vypr;
		
	// Velocidades en el centro y en el futuro 
	vxc = vxpr + (1.0/2.0)*paso_tiempo*dvx;
	vxfu = vxpr + 1.0*paso_tiempo*dvx;
	vyc = vypr + (1.0/2.0)*paso_tiempo*dvy;
	vyfu = vypr + 1.0*paso_tiempo*dvy;

	// Derivada de la posicion actual
	dx = vxc;
	dy = vyc;

	// Avance, posiciones en el futuro Calcular las nuevas posiciones con la velocidad de medio paso adelante
	xfu = xpr + 1.0*paso_tiempo*dx;
	yfu = ypr + 1.0*paso_tiempo*dy;

	output << xfu << "\t" << yfu << "\t" << vxfu << "\t" << vyfu << "\t" << "\n";

	// cambiar de paso, presente se convierte en futuro en x y y, las velocidades tambien pasan de presente a futuro
	xpr = xfu;
	yfu = yfu;
	vxpr = vxfu;
	vypr = vyfu;
	//
	if (yfu<0 and distancia_recorrida==0.0)
		{
			distancia_recorrida = xfu;
		}


	

}

printf("La distancia recorrida es de %f\n", distancia_recorrida);
 
return 0;
}
