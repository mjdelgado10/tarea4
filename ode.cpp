#include <stdio.h>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;

//Movimiento de un proyectil
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
float friccionMag;

// asignar los valores iniciales
xpr = 0.0;
ypr = 0.0;

//Cambio de paso, presente se convierte en el inicio para empezar a caminar
vxpr = vx0;
vypr = vy0;

//Almacenar los datos en un archivo llamado p45.txt donde estan todos los puntos a un angulo de 45 (no se realizo con ./a.out >> como en clase para indicar el paso en el .cpp
ofstream output("p45.txt");

return 0;
}
