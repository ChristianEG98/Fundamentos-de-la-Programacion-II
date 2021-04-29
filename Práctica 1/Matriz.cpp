#include "Matriz.h"

bool cargar(tMatrizChar& mat, istream& ent) {
	bool cargado = false;
	ent >> mat.tam_matriz.x >> mat.tam_matriz.y; //guardamos el tamaño de la matriz

	for (int i = 0; i < mat.tam_matriz.x; i++)
		for (int j = 0; j < mat.tam_matriz.y; j++)
			ent >> mat.matriz[i][j]; //guardamos el color de cada casilla

	if (mat.tam_matriz.x > 0 && mat.tam_matriz.y > 0) { //si el tamaño de la matriz es mayor a 0 devolvemos true
		cargado = true;
	}

	return cargado;
}

bool operator == (tMatrizChar const& mat1, tMatrizChar const& mat2) {
	bool distintos = false;
	//primero comprobamos si los tamaños son iguales entre ambas matrices
	if (mat1.tam_matriz.x == mat2.tam_matriz.x && mat1.tam_matriz.y == mat2.tam_matriz.y) {
		//recorremos cada casilla
		for (int i = 0; i < mat1.tam_matriz.x; i++) {
			for (int j = 0; j < mat1.tam_matriz.y; j++) {
				//si una casilla es distinta con respecto a la de la otra matriz, distintos = true
				if (mat1.matriz[i][j] != mat2.matriz[i][j]) {
					distintos = true;
				}
			}
		}
	}
	//si los tamaños son distintos
	else {
		distintos = true;
	}

	return !distintos;
}

bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
	bool correcto = true;
	uint8 aux;
	if (pos1 != pos2) { //si son casillas diferentes comprobamos si las coordenadas se exceden de los límites de la matriz
		if (pos1.x < 0 || pos1.x >= mat.tam_matriz.x || pos1.y < 0 || pos1.y >= mat.tam_matriz.y || pos2.x < 0 || pos2.x >= mat.tam_matriz.x || pos2.y < 0 || pos2.y >= mat.tam_matriz.y) {
			correcto = false;
		}
		else { //intercambia las coordenadas
			aux = mat.matriz[pos1.x][pos1.y];
			mat.matriz[pos1.x][pos1.y] = mat.matriz[pos2.x][pos2.y];
			mat.matriz[pos2.x][pos2.y] = aux;
		}
	}
	return correcto;
}

//acciones del modo 1D

bool swapF(tMatrizChar& mat, int f1, int f2) {
	bool correcto = false;
	uint8 aux[DIM_MAX]; //array auxiliar
	if (f1 < mat.tam_matriz.x && f2 < mat.tam_matriz.x) { //comprobamos si las filas pertenecen a la matriz
		for (int a = 0; a < mat.tam_matriz.x; a++) {
			aux[a] = mat.matriz[f1][a]; //fila f1 almacenada
		}
		for (int b = 0; b < mat.tam_matriz.x; b++) {
			mat.matriz[f1][b] = mat.matriz[f2][b]; //fila f2 copiada en f1
		}
		for (int c = 0; c < mat.tam_matriz.x; c++) {
			mat.matriz[f2][c] = aux[c]; //fila aux (f1 original) copiada en f2
		}
		correcto = true;
	}
	return correcto;
}

bool swapC(tMatrizChar& mat, int c1, int c2) {
	bool correcto = false;
	uint8 aux[DIM_MAX]; //array auxiliar
	if (c1 < mat.tam_matriz.y && c2 < mat.tam_matriz.y) { //comprobamos si las columnas pertenecen a la matriz
		for (int a = 0; a < mat.tam_matriz.y; a++) {
			aux[a] = mat.matriz[a][c1]; //columna c1 almacenada
		}
		for (int b = 0; b < mat.tam_matriz.y; b++) {
			mat.matriz[b][c1] = mat.matriz[b][c2]; //columna c2 copiada en c1
		}
		for (int c = 0; c < mat.tam_matriz.y; c++) {
			mat.matriz[c][c2] = aux[c]; //columna aux (c1 original) copiada en c2
		}
		correcto = true;
	}
	return correcto;
}

bool swapD(tMatrizChar& mat, int d) {
	bool correcto = false;
	uint8 aux[DIM_MAX]; //array auxiliar
	if (mat.tam_matriz.x == mat.tam_matriz.y && d < mat.tam_matriz.x && d < mat.tam_matriz.y) { //comprobamos si la diagonal pertenece a la matriz y si es cuadrada
		for (int a = 0; a < mat.tam_matriz.x - d; a++) {
			aux[a] = mat.matriz[a][d + a];
		}
		for (int b = 0; b < mat.tam_matriz.x - d; b++) {
			mat.matriz[b][d + b] = mat.matriz[d + b][b] ;
		}
		for (int c = 0; c < mat.tam_matriz.y - d; c++) {
			mat.matriz[d + c][c] = aux[c];
		}
		correcto = true;
	}
	return correcto;
}

bool voltearF(tMatrizChar& mat, int f) {
	bool correcto = false;
	uint8 aux[DIM_MAX]; //array auxiliar
	if (f < mat.tam_matriz.x) { //comprobamos si la fila pertenece a la matriz
		for (int a = 0; a < mat.tam_matriz.y; a++) {
			aux[a] = mat.matriz[f][mat.tam_matriz.y - 1 - a]; //fila f almacenada en aux ya volteada
		}
		for (int c = 0; c < mat.tam_matriz.y; c++) {
			mat.matriz[f][c] = aux[c]; //volvemos a almacenarlo en la matriz original
		}
		correcto = true;
	}
	return correcto;
}

bool voltearC(tMatrizChar& mat, int c) {
	bool correcto = false;
	uint8 aux[DIM_MAX]; //array auxiliar
	if (c < mat.tam_matriz.y) { //comprobamos si la columna pertenece a la matriz
		for (int a = 0; a < mat.tam_matriz.x; a++) {
			aux[a] = mat.matriz[mat.tam_matriz.x - 1 - a][c]; //columna c almacenada en axu ya volteada
		}
		for (int i = 0; i < mat.tam_matriz.x; i++) {
			mat.matriz[i][c] = aux[i]; //volvemos a almacenarlo en la matriz original
		}
		correcto = true;
	}
	return correcto;
}

bool voltearD(tMatrizChar& mat, int d) {
	bool correcto = false;
	uint8 aux[DIM_MAX]; //array auxiliar
	//comprobamos que la diagonal pertenece a la matriz y que esta es cuadrada
	if (mat.tam_matriz.x == mat.tam_matriz.y && d < mat.tam_matriz.x && d < mat.tam_matriz.y) {
		for (int a = 0; a < mat.tam_matriz.x - d; a++) {
			aux[a] = mat.matriz[mat.tam_matriz.x - 1 - d - a][mat.tam_matriz.y - 1 - a]; //guardamos en aux la diagonal ya volteada
		}
		for (int b = 0; b < mat.tam_matriz.x - d; b++) {
			mat.matriz[b][b + d] = aux[b]; //copiamos en la matriz original lo almacenado en aux
		}
		correcto = true;
	}
	return correcto;
}

//acciones del modo 2D

void voltearV(tMatrizChar& mat) {
	//para cada fila de la matriz llama a voltearF()
	for (int i = 0; i < mat.tam_matriz.x; i++) {
		voltearF(mat, i);
	}
}

void voltearH(tMatrizChar& mat) {
	//para cada columna de la matriz llama a voltearC()
	for (int i = 0; i < mat.tam_matriz.y; i++) {
		voltearC(mat, i);
	}
}

void rotarD(tMatrizChar& mat) {
	tMatrizChar aux; //matriz auxiliar
	for (int i = 0; i < mat.tam_matriz.x; i++) {
		for (int j = mat.tam_matriz.y; j >= 0 ; j--) {
			//almacenamos el valor de la matriz original en la matriz auxiliar de forma inversa (las filas de mat pasan a ser columnas en aux y las columnas pasan a ser las filas)
			aux.matriz[j][i] = mat.matriz[i][j];
		}
	}
	//intercambiamos los tamaños de alto y ancho de la matriz
	aux.tam_matriz.x = mat.tam_matriz.y;
	aux.tam_matriz.y = mat.tam_matriz.x;
	mat.tam_matriz.x = aux.tam_matriz.x;
	mat.tam_matriz.y = aux.tam_matriz.y;

	for (int k = 0; k < mat.tam_matriz.x; k++) {
		for (int l = 0; l < mat.tam_matriz.y; l++) {
			mat.matriz[k][mat.tam_matriz.y - 1 - l] = aux.matriz[k][l]; //guardamos en la matriz original lo almacenado en aux pero invertimos las filas
		}
	}
}

bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
	bool exito = true, pasaLimites = false;
	tCoor vec, aux1, aux2;
	//diferencias de las coordenadas adyacentes con respecto a la central
	int numsAdy = 8;
	int incF[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int incC[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	//primero comprobamos que todas las casillas adyacentes están dentro de los límites de la matriz
	for (int i = 0; i < numsAdy; i++) {
		//guardamos la combinación en el tCoor vec
		vec.x = incF[i];
		vec.y = incC[i];
		aux1 = pos1 + vec; //guardamos en aux1 la suma de pos1 y vec
		aux2 = pos2 + vec; //guardamos en aux2 la suma de pos2 y vec
		if (aux1.x < 0 || aux1.x >= mat.tam_matriz.x || aux1.y < 0 || aux1.y >= mat.tam_matriz.y || aux2.x < 0 || aux2.x >= mat.tam_matriz.x || aux2.y < 0 || aux2.y >= mat.tam_matriz.y) {
			pasaLimites = true;
		}
	}
	//si ninguna casilla se pasa de los límites de la matriz las intercambiamos
	if (!pasaLimites) {
		//para cada una de las ocho coordenadas adyacentes
		for (int i = 0; i < numsAdy; i++) {
			//guardamos la combinación en el tCoor vec
			vec.x = incF[i];
			vec.y = incC[i];
			aux1 = pos1 + vec; //guardamos en aux1 la suma de pos1 y vec
			aux2 = pos2 + vec; //guardamos en aux2 la suma de pos2 y vec
			//llamamos a la función swap()
			if (!swap(mat, aux1, aux2)) {
				exito = false;
			}
		}
	}
	else {
		exito = false;
	}

	return exito;
}

bool voltearID(tMatrizChar& mat) {
	bool exito = true;
	//para cada fila llamamos a swapD()
	for (int i = 0; i < mat.tam_matriz.x; i++) {
		if (!swapD(mat, i)) {
			exito = false;
		}
	}
	return exito;
}