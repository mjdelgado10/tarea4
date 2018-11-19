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
