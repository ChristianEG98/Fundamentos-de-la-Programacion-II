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

void main(); //función principal
int menu(); //menu
bool iniciar(tJuegoPM& jpm); //inicia los parámetros necesarios y llama a cargar()
bool cargar(tJuegoPM& jpm); //abre el fichero correspondiente y llama a cargar() en el módulo Matriz
void mostrar(tJuegoPM const& jpm); //muestra el número de intentos y las imágenes
bool jugar(tJuegoPM& jpm); //realizar las acciones necesarias para jugar y controla el número de intentos
bool accion(tJuegoPM& jpm); //llama a la acción correspondiente en el módulo Matriz

#endif
