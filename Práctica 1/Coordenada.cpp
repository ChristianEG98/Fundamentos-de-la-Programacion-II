#include "Coordenada.h"

bool operator == (tCoor c1, tCoor c2){
	return (c1.x == c2.x && c1.y == c2.y);
}
bool operator != (tCoor c1, tCoor c2){
	return !(c1 == c2);
}
tCoor operator + (tCoor c1, tCoor c2){
	tCoor c3;
	c3.x = c1.x + c2.x;
	c3.y = c1.y + c2.y;
	return c3;
}