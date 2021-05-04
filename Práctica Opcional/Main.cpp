#include "Main.h"

int main() { 
	//para pruebas, creamos tres conjuntos vacios e insertamos enteros en a y en b
	tConjunto a, b, c;
	crearConjuntoVacio(a);
	crearConjuntoVacio(b);
	crearConjuntoVacio(c);
	insertar(a, 8);
	for (int i = 0; i < 4; i++) {
		insertar(a, i);
	}
	for (int i = 3; i < 10; i++) {
		insertar(b, i);
	}
	insertar(b, 1);
	//contenido de los conjuntos a y b
	cout << "Conjunto a: ";
	mostrar(a); // { 8 0 1 2 3 }
	cout << "Conjunto b: ";
	mostrar(b); // { 3 4 5 6 7 8 9 1 }
	c = b * a;
	cout << "Interseccion de a y b: ";
	mostrar(c);
	c = b + a;
	cout << "Union de a y b: ";
	mostrar(c);
	c = b - a;
	cout << "Diferencia de a y b: ";
	mostrar(c);
	a << b ? cout << "a esta contenido en b" : cout << "a no esta contenido en b";
	delete[] a.p; delete[] b.p; delete[] c.p;
	return 0;
}

void crearConjuntoVacio(tConjunto& c) {
	c.p = new int[TAM_ARRAY]; //array de 10 enteros
	c.contador = 0;
	c.tam = TAM_ARRAY;
}

bool pertenece(tConjunto c, int e) {
	bool pertenece = false;
	for (int i = 0; i < c.contador; i++) {
		if (c.p[i] == e) pertenece = true; //buscamos si e ya se encuentra en alguna posición ocupada del array
	}
	return pertenece;
}

bool conjuntoVacio(tConjunto c) {
	return (c.contador == 0);
}

void insertar(tConjunto& c, int e) {
	if (c.contador < c.tam) { //si aún queda espacio para insertar
		if (!pertenece(c, e)) { //si e no pertenece ya a c lo añadimos
			c.p[c.contador] = e;
			c.contador++;
		}
	}
	else { //si no queda espacio para insertar, redimensionamos y lo insertamos
		redimensionar(c, 10);
		insertar(c, e);
	}
}

void mostrar(tConjunto c) {
	cout << "{ ";
	for (int i = 0; i < c.contador; i++) {
		cout << c.p[i] << " ";
	}
	cout << "}" << endl;
}

void eliminar(tConjunto& c, int e) {
	int pos = 0;
	if (pertenece(c, e)) { //si e pertenece a c
		while (c.p[pos] != e) {
			pos++; //posición en el array del numero e
		}
		for (int i = pos; i < c.contador; i++) { //eliminamos e
			c.p[i] = c.p[i + 1];
		}
		c.contador--;
		//si ya ha sido redimensionado al menos una vez (tam > 10) y la infomación es < 25% redimensionamos el array para que tenga 10 casillas menos
		if (c.tam > 10 && ((double)c.contador / (double)c.tam < 0.25)) { 
			redimensionar(c, -10);
		}
	}
}

bool operator==(tConjunto a, tConjunto b) {
	int contador = 0;
	bool iguales = false;
	if (a.contador == b.contador) { //si el numero de numeros en ambos conjunto es igual comprueba que son los mismos
		for (int i = 0; i < a.contador; i++) { //números del conjunto a
			for (int j = 0; j < b.contador; j++) { //números del conjunto b
				if (a.p[i] == b.p[j]) { //para cada número de a buscamos en todo el conjunto b si existe
					contador++;
				}
			}
		}
	}
	//si ha encontrado la misma cantidad de numeros que los que hay en a (también valdría b), es que pertenece
	if (contador == a.contador) iguales = true;
	return iguales;
}

tConjunto operator*(tConjunto a, tConjunto b) {
	tConjunto c;
	crearConjuntoVacio(c);
	for (int i = 0; i < a.contador; i++) {
		for (int j = 0; j < b.contador; j++) {
			if (a.p[i] == b.p[j]) { //si se encuentra un entero del conjunto a en el conjunto b, este se inserta en el conjunto c
				insertar(c, a.p[i]); //insertar comprueba si un numero ya pertenece, por lo que no hay enteros repetidos
			}
		}
	}
	return c;
}

tConjunto operator+(tConjunto a, tConjunto b) {
	tConjunto c;
	crearConjuntoVacio(c);
	for (int i = 0; i < a.contador; i++) {
		insertar(c, a.p[i]); //insertamos todos los enteros del conjunto a en c
	}
	for (int i = 0; i < b.contador; i++) {
		insertar(c, b.p[i]); //insertamos todos los enteros del conjunto b en c
		//la función insertar comprueba que un entero no pertenezca ya al conjunto, entonces si un entero de b ya existe en c, no se vuelve a insertar
	}
	return c;
}

tConjunto operator-(tConjunto a, tConjunto b) {
	tConjunto c;
	crearConjuntoVacio(c);
	for (int i = 0; i < a.contador; i++) {
		insertar(c, a.p[i]); //insertamos todos los enteros del conjunto a en c
	}
	for (int i = 0; i < b.contador; i++) {
		eliminar(c, b.p[i]); //eliminamos los enteros del conjunto b que se encuentren en el conjunto c
	}
	return c;
}

bool operator<<(tConjunto a, tConjunto b) {
	int contador = 0;
	bool contenido = false;
	for (int i = 0; i < a.contador; i++) { //números del conjunto a
		for (int j = 0; j < b.contador; j++) { //números del conjunto b
			if (a.p[i] == b.p[j]) { //para cada número de a buscamos en todo el conjunto b si existe
				contador++;
			}
		}
	}
	//si ha encontrado la misma cantidad de numeros que los que hay en a, es que pertenece
	if (contador == a.contador) contenido = true;
	return contenido;
}

void redimensionar(tConjunto& c, int num) {
	int* copiaC = new int[c.tam]; //nuevo array dinámico copiaC
	for (int i = 0; i < c.tam; i++) { //copiamos el array de enteros de c al array copiaC
		copiaC[i] = c.p[i];
	}
	delete[] c.p; //borramos el array de enteros de c
	c.p = new int[TAM_ARRAY + num]; //creamos un nuevo array dinámico con el nuevo tamaño
	for (int i = 0; i < c.tam; i++) { //copiamos de nuevo los enteros en el array copiaC al array de c 
		c.p[i] = copiaC[i];
	}
	delete[] copiaC; //borramos el array copiaC
	c.tam += num; //aumentamos el tamaño en la variable destinada a guardalo
} 