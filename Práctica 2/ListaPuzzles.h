#pragma once
#ifndef LISTAPUZZLES
#define LISTAPUZZLES
#include "Puzzle.h"

const int MAX_PUZZLES = 100;
const int NUM_MODOS = 2;

typedef tPuzzle *tPtrPuzzle; //puntero a variables de tipo tPuzzle

typedef struct {
	tPtrPuzzle puzzles[MAX_PUZZLES];
	int contador;
} tListaPuzzles;

typedef tListaPuzzles tPuzzlesReunidos[NUM_MODOS];

void inicializar(tPuzzlesReunidos& jr); //inicializa las dos listas de puzzles
bool cargar(tPuzzlesReunidos& jr); //carga el fichero datosPuzzles.txt
void guardar(tPuzzlesReunidos const& listas); //guarda la lista de puzzles en datosPuzzles.txt
int elegirPuzzle(tListaPuzzles& lp); //muestra el menu para elegir puzzle u ordenarlos
void mostrarListaPuzzles(tListaPuzzles const& lp); //muestra la lista de puzzles
bool insertarOrdenado(tListaPuzzles& l, tPuzzle* p); //inserta ordenado un nuevo puzzle en la lista
void ordenarMayorMenor(tListaPuzzles& lp); //ordena la lista de mayor a menor
void ordenarMenorMayor(tListaPuzzles& lp); //ordena la lista de menor a mayor
#endif