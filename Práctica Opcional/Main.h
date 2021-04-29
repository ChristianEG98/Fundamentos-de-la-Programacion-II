#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <iostream>
using namespace std;

const int TAM_ARRAY = 10;

typedef struct {
	int* p; //puntero
	int tam; //tamaño del array
	int contador; //primera posición libre
} tConjunto;

//TAD
void crearConjuntoVacio(tConjunto& c); //crea un conjunto vacio.
bool pertenece(tConjunto c, int e); //determina si e pertenece a c o no.
bool conjuntoVacio(tConjunto c); //determina si c es vacio o no.
void insertar(tConjunto& c, int e); //inserta e en c.Importante: solo puede haber una aparicion de e.
void mostrar(tConjunto c); //muestra por pantalla el contenido de c.
void eliminar(tConjunto& c, int e); //elimina e en c. Importante : si no existe e no hace nada.
bool operator==(tConjunto a, tConjunto b); //determina si a y b son iguales o no.
tConjunto operator*(tConjunto a, tConjunto b);  //devuelve la interseccion de a y b.
tConjunto operator+(tConjunto a, tConjunto b); //devuelve la union de a y b.
tConjunto operator-(tConjunto a, tConjunto b); //devuelve la diferencia de a y b.
bool operator<<(tConjunto a, tConjunto b);  //determina si a esta contenido en b o no

void redimensionar(tConjunto& c, int num); //redimensiona el array según el num de posiciones que le pasamos

#endif