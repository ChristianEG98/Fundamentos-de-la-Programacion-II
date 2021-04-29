#pragma once
#ifndef JUEGOPM_H
#define JUEGOPM_H
#include <fstream>
#include <iomanip>
#include "Matriz.h"
using namespace std;

typedef struct {
	tMatrizChar modelo;
	tMatrizChar objetivo;
	int max_acciones;
	int modo;
} tJuegoPM;

void main(); //funci�n principal
int menu(); //menu
bool iniciar(tJuegoPM& jpm); //inicia los par�metros necesarios y llama a cargar()
bool cargar(tJuegoPM& jpm); //abre el fichero correspondiente y llama a cargar() en el m�dulo Matriz
void mostrar(tJuegoPM const& jpm); //muestra el n�mero de intentos y las im�genes
bool jugar(tJuegoPM& jpm); //realizar las acciones necesarias para jugar y controla el n�mero de intentos
bool accion(tJuegoPM& jpm); //llama a la acci�n correspondiente en el m�dulo Matriz

#endif
