#pragma once
#ifndef PUZZLE
#define PUZZLE
#include <fstream>
#include <string>
#include <iomanip>
#include "Matriz.h"

typedef struct {
	string nombre;
	string fichero;
	int max_acciones;
	int modo;
	tMatrizChar modelo;
	tMatrizChar objetivo;
} tPuzzle;

void mainPuzzle(tPuzzle& jpm); //llama a jugar() y muestra si lo ha conseguido resolver o no
bool iniciar(tPuzzle& jpm); //inicia los par�metros necesarios y llama a cargar()
bool cargar(tPuzzle& jpm); //abre el fichero correspondiente y llama a cargar() en el m�dulo Matriz
void mostrar(tPuzzle const& jpm); //muestra el n�mero de intentos y las im�genes
bool jugar(tPuzzle& jpm); //realizar las acciones necesarias para jugar y controla el n�mero de intentos
bool accion(tPuzzle& jpm); //llama a la acci�n correspondiente en el m�dulo Matriz
bool operator <(tPuzzle const& p1, tPuzzle const& p2); //compara y devuelve si el puzzle p1 es menor que el puzzle p2
bool operator >(tPuzzle const& p1, tPuzzle const& p2); //compara y devuelve si el puzzle p1 es mayor que el puzzle p2
#endif