import numpy as np
import matplotlib.pyplot as plt

#obtiene los datos del archivo de movimiento a 45 generado en el punto ODE.cpp
[x,y,vx,vy] = np.genfromtxt('movimientoa45.txt', unpack=True)

#se crea la figura
fig,ax = plt.subplots()
ax.plot(x,y)
ax.set_ylim([0,np.max(y)])
fig.savefig('movimientoa45.png')


#obtiene los datos del archivo de trayectorias7 generado en el punto ODE.cpp
XY = np.genfromtxt("trayectorias7.txt", unpack=False)

fig = plt.figure()
ax = fig.gca()
#se crean las siete trayectorias
for i in range(7):
	ax.plot(XY[:,i*2], XY[:,i*2+1], label=str(10+i*10))
ax.legend()
ax.set_ylim([0,5])
fig.savefig('trayectorias.png')


#obtiene los datos de los archivos generados por los tres casos de condiciones de frontera generados en el punto PDE.cpp
Imagen1 = np.genfromtxt("fronterasfijas.txt")
Imagen2 = np.genfromtxt("fronterasabiertas.txt")
Imagen3 = np.genfromtxt("fronterasperiodicas.txt")

n0,n1 = np.shape(Imagen1)
pasos = int(n0/n1);
 

#forma de las imagenes
Imagen1 = np.reshape(Imagen1, (pasos,n1,n1))
Imagen2 = np.reshape(Imagen2, (pasos,n1,n1))
Imagen3 = np.reshape(Imagen3, (pasos,n1,n1))

x = np.arange(0,n1)/n1*50.0
X,Y = np.meshgrid(x,x)
i0 = 0
i1 = int(pasos*0.4)
i2 = int(pasos*0.8)
i3 = -1

# calcular promedios
promedio1 = np.sum(np.sum(Imagen1,1),1)/(n1**2)
promedio2 = np.sum(np.sum(Imagen2,1),1)/(n1**2)
promedio3 = np.sum(np.sum(Imagen3,1),1)/(n1**2)

print(np.shape(promedio1))

#graficas de los promedios
fig = plt.figure()
ax = fig.gca()
ax.plot(promedio1, label='Fijas')
ax.plot(promedio2, label='Abiertas')
ax.plot(promedio3, label='Periodicas')
ax.legend()
fig.savefig('tm.png')


#grafica del CASO 1, condiciones de frontera fijas

fig = plt.figure(figsize=(12,4))
ax = fig.add_subplot(1,3,1, projection='3d')
ax.plot_surface(X,Y,Imagen1[i0,:,:])
ax.set_title('Fronteras Fijas')
ax.set_zlim([0,100])

#grafica del CASO 2, condiciones de frontera abiertas
ax = fig.add_subplot(1,3,2, projection='3d')
ax.plot_surface(X,Y,Imagen2[i0,:,:])
ax.set_title('Fronteras Abiertas')
ax.set_xlabel('tiempo inicial')
ax.set_zlim([0,100])

#grafica del CASO 3, condiciones de frontera periodicas
ax = fig.add_subplot(1,3,3, projection='3d')
ax.plot_surface(X,Y,Imagen3[i0,:,:])
ax.set_title('Fronteras Periodicas')
ax.set_zlim([0,100])

#Almacena las graficas en un solo archivo png
fig.savefig("t0.png")


#grafica del CASO 1, condiciones de frontera fijas
fig = plt.figure(figsize=(12,4))
ax = fig.add_subplot(1,3,1, projection='3d')
ax.plot_surface(X,Y,Imagen1[i1,:,:])
ax.set_title('Fronteras Fijas')
ax.set_zlim([0,100])

#grafica del CASO 2, condiciones de frontera abiertas
ax = fig.add_subplot(1,3,2, projection='3d')
ax.plot_surface(X,Y,Imagen2[i1,:,:])
ax.set_title('Fronteras Abiertas')
ax.set_xlabel('40% tiempo')
ax.set_zlim([0,100])

#grafica del CASO 3, condiciones de frontera periodicas
ax = fig.add_subplot(1,3,3, projection='3d')
ax.plot_surface(X,Y,Imagen3[i1,:,:])
ax.set_title('Fronteras Periodicas')
ax.set_zlim([0,100])

#Almacena las graficas en un solo archivo png transcurrido tiempo
fig.savefig("t1.png")


#grafica del CASO 1, condiciones de frontera fijas
fig = plt.figure(figsize=(12,4))
ax = fig.add_subplot(1,3,1, projection='3d')
ax.plot_surface(X,Y,Imagen1[i2,:,:])
ax.set_title('Fronteras Fijas')
ax.set_zlim([0,100])


#grafica del CASO 2, condiciones de frontera abiertas
ax = fig.add_subplot(1,3,2, projection='3d')
ax.plot_surface(X,Y,Imagen2[i2,:,:])
ax.set_title('Fronteras Abiertas')
ax.set_xlabel('80% tiempo')
ax.set_zlim([0,100])


#grafica del CASO 3, condiciones de frontera periodicas
ax = fig.add_subplot(1,3,3, projection='3d')
ax.plot_surface(X,Y,Imagen3[i2,:,:])
ax.set_title('Fronteras Periodicas')
ax.set_zlim([0,100])


#Almacena las graficas en un solo archivo png transcurrido tiempo
fig.savefig("t2.png")




#grafica del CASO 1, condiciones de frontera fijas
fig = plt.figure(figsize=(12,4))
ax = fig.add_subplot(1,3,1, projection='3d')
ax.plot_surface(X,Y,Imagen1[i3,:,:])
ax.set_title('Fronteras Fijas')
ax.set_zlim([0,100])


#grafica del CASO 2, condiciones de frontera abiertas
ax = fig.add_subplot(1,3,2, projection='3d')
ax.plot_surface(X,Y,Imagen2[i3,:,:])
ax.set_title('Fronteras Abiertas')
ax.set_xlabel('Tiempo final')
ax.set_zlim([0,100])

#grafica del CASO 3, condiciones de frontera periodicas
ax = fig.add_subplot(1,3,3, projection='3d')
ax.plot_surface(X,Y,Imagen3[i3,:,:])
ax.set_title('Fronteras Periodicas')
ax.set_zlim([0,100])

#Almacena las graficas en un solo archivo png en el tiempo final 
fig.savefig("t3.png")

