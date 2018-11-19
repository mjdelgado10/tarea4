#include <stdio.h>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;

//Movimiento de un proyectil

//Funcion que modela varios proyectiles
void varios_proyectiles()
{
// definir las constantes
float cm=1.0; // relacion c/m=0.2/0.2
float gr = -10; // m/s^2
float pi=3.141;

// definir el paso
float paso_tiempo = 0.0002;
	

float direcciones_lanzamiento[7];
direcciones_lanzamiento[0] = 10.0/360.0*(2*pi);
direcciones_lanzamiento[1] = 20.0/360.0*(2*pi);
direcciones_lanzamiento[2] = 30.0/360.0*(2*pi);
direcciones_lanzamiento[3] = 40.0/360.0*(2*pi);
direcciones_lanzamiento[4] = 50.0/360.0*(2*pi);
direcciones_lanzamiento[5] = 60.0/360.0*(2*pi);
direcciones_lanzamiento[6] = 70.0/360.0*(2*pi);


//float vx_inicial=300*cos(45.0/360.0*(2*pi));
//float vy_inicial=300*sin(45.0/360.0*(2*pi));


// posiciones en el presente y el futuro
float xpr[7], xfu[7];
float ypr[7], yfu[7];

// velocidades en el presente, el futuro y en el centro
float vxpr[7], vxc[7], vxfu[7];
float vypr[7], vyc[7], vyfu[7];

// derivadas de posiciones y velocidades
float dx[7], dy[7];
float dvx[7], dvy[7];
float Fr[7];

float distancia_recorrida[7];

//encuentra los valores iniciales
for (int c = 0; c < 7; ++c)
{
	xpr[c] = 0.0;
	ypr[c] = 0.0;

	vxpr[c] = 300.0*cos(direcciones_lanzamiento[c]);
	vypr[c] = 300.0*sin(direcciones_lanzamiento[c]);

	distancia_recorrida[c] = 0.0;
}
	


ofstream output_x("trayectorias7.txt");
ofstream output_v("velocidades7.txt");



for (int i = 0; i < 100000; ++i)
{	
	for (int c = 0; c < 7; ++c)
	{
		
		// Calcular derivadas de la velocidad
		Fr[c] = cm*pow(vxpr[c]*vxpr[c] + vypr[c]*vypr[c], 0.5);
		dvx[c] = -Fr[c]*vxpr[c];
		dvy[c] = gr -Fr[c]*vypr[c];
	
		// calcular velocidad medio paso de tiempo adelante y un paso de tiempo adelante
		vxc[c] = vxpr[c] + (1.0/2.0)*paso_tiempo*dvx[c];
		vxfu[c] = vxpr[c] + 1.0*paso_tiempo*dvx[c];

		vyc[c] = vypr[c] + (1.0/2.0)*paso_tiempo*dvy[c];
		vyfu[c] = vypr[c] + 1.0*paso_tiempo*dvy[c];

		// Calcular derivadas de las posiciones
		dx[c] = vxc[c];
		dy[c] = vyc[c];

		// Calcular las nuevas posiciones con la velocidad de medio paso adelante
		xfu[c] = xpr[c] + 1.0*paso_tiempo*dx[c];
		yfu[c] = ypr[c] + 1.0*paso_tiempo*dy[c];


		output_x << xpr[c] << "\t" << ypr[c] << "\t";
		output_v << vxpr[c] << "\t" << vypr[c] << "\t";

		// cambiar las referencias de pasado y futuro
		xpr[c] = xfu[c];
		ypr[c] = yfu[c];
		vxpr[c] = vxfu[c];
		vypr[c] = vyfu[c];

		if (yfu[c]<0 and distancia_recorrida[c]==0.0)
		{
			distancia_recorrida[c] = xfu[c];
		}

	}
	output_x << "\n";
	output_v << "\n";
}


// encontrar la mayor distancia recorrida
int maxI=3;
float maxDist = distancia_recorrida[maxI];

for (int c = 0; c < 7; ++c)
{
	if (maxDist < distancia_recorrida[c])
	{
		maxI = c;
		maxDist = distancia_recorrida[c];
		//cout << c << "--";
	}
	//cout << distancia_recorrida[c] << "**";
}

//cout << maxI << endl; 
printf("La distancia maxima recorrida es de %f y se da a los %f grados de lanzamiento del proyectil\n", distancia_recorrida[maxI], direcciones_lanzamiento[maxI]/(2.0*pi)*360);

}

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
 
varios_proyectiles();


return 0;
}
