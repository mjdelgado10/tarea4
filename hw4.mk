all: *.png


*.png: ode pde
	################################################################
	################################################################
	python plots.py

ode:
	################################################################
	################################################################
	g++ ode.cpp -o punto2.x
	./punto2.x
	

pde:
	################################################################
	################################################################
	g++ pde.cpp -o punto3.x
	./punto3.x

clean:
	rm *.png *.txt *.x