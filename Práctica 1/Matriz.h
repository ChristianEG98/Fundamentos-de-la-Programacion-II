#ifndef MATRIZ_H
#define MATRIZ_H
#include <iostream>
#include <string>
#include "UtilidadesSYS.h"
#include "Coordenada.h"

using namespace std;

const int DIM_MAX = 64;

typedef struct {
	uint8 matriz[DIM_MAX][DIM_MAX];
	tCoor tam_matriz;
} tMatrizChar;

bool cargar(tMatrizChar& mat, istream& ent); //carga en la matriz los datos por flujo de entrada
bool operator == (tMatrizChar const& mat1, tMatrizChar const& mat2); //compara si dos matrices son iguales
bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2); //intercambia las coordenadas pos1 y pos2
//Modo de juego - 1D
bool swapF(tMatrizChar& mat, int f1, int f2); //intercambia las filas f1 y f2
bool swapC(tMatrizChar& mat, int c1, int c2); //intercambia las columnas c1 y c2
bool swapD(tMatrizChar& mat, int d); //intercambia las diagonales d y -d
bool voltearF(tMatrizChar& mat, int f); //voltea la fila f
bool voltearC(tMatrizChar& mat, int c); //voltea la columna c
bool voltearD(tMatrizChar& mat, int d); //voltea la diagonal d
//Modo de juego - 2D
void voltearV(tMatrizChar& mat); //voltea la imagen con respecto al eje vertical
void voltearH(tMatrizChar& mat); //voltea la imagen con respecto al eje horizontal
void rotarD(tMatrizChar& mat); //rota la imagen 90 grados a la derecha
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2); //intercambia las celdas adyacentes de pos1 y pos2
bool voltearID(tMatrizChar& mat); //voltea la imagen con respecto a la diagonal principal
#endif
