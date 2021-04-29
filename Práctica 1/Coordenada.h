#ifndef COORDENADA_H
#define COORDENADA_H

using namespace std;

typedef struct{
	int x;
	int y;
} tCoor;

bool operator == (tCoor c1, tCoor c2); //compara si dos coordenadas son iguales
bool operator != (tCoor c1, tCoor c2); //compara si dos coordenadas son distintas
tCoor operator + (tCoor c1, tCoor c2); //devuelve la coordenada resultante de sumar otras dos

#endif