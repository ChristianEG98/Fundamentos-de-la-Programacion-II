#include "ListaPuzzles.h"
bool buscar(tListaPuzzles const& lista, tPuzzle* puzzle, int& pos); //busca un puzzle en la lista y devuelve si existe o no (pos contiene la posición donde se inserta)

void inicializar(tPuzzlesReunidos& jr) {
	for (int i = 0; i < NUM_MODOS; i++) {
		for (int j = 0; i < MAX_PUZZLES; j++) {
			jr[i].puzzles[j] = NULL; //inicializamos a null todos las direcciones de los punteros
		}
		jr[i].contador = 0; //ponemos el contador de puzzles a 0
	}
}

bool cargar(tPuzzlesReunidos& jr) {
	int num;
	string nombre;
	bool cargado = false;
	ifstream archivo;
	archivo.open("datosPuzzles.txt");
	if (archivo.is_open()) {
		cargado = true;
		for (int i = 0; i < NUM_MODOS; i++) {
			archivo >> num;
			jr[i].contador = num; //guardamos el numero de puzzles de cada modo
			archivo.ignore();
			for (int j = 0; j < num; j++) {
				jr[i].puzzles[j] = new tPuzzle; //nuevo tPuzzle
				getline(archivo, nombre);
				jr[i].puzzles[j]->nombre = nombre; //guardamos el nombre del puzzle
				getline(archivo, nombre);
				jr[i].puzzles[j]->fichero = nombre; //guardamos el nombre del fichero del puzzle
				jr[i].puzzles[j]->modo = i; //guardamos el modo del puzzle (0 - 1D, 1 - 2D)

				//cargamos el numero de movimientos y la matrices de cada puzzle de los txt
				if (!cargar(*jr[i].puzzles[j])) cout << "Problema al carga el puzzle: " << jr[i].puzzles[j]->nombre << endl;
			}
		}
	}
	archivo.close();
	return cargado;
}

void guardar(tPuzzlesReunidos const& listas) {
	ofstream archivo;
	archivo.open("datosPuzzles.txt");
	if (archivo.is_open()) {
		for (int i = 0; i < NUM_MODOS; i++) { //para los dos modos posibles
			archivo << listas[i].contador << endl; //guardamos en el fichero el numero de puzzles
			for (int j = 0; j < listas[i].contador; j++) { //para cada puzzle de cada lista
				archivo << listas[i].puzzles[j]->nombre << endl; //guardamos en el fichero el nombre del puzzle
				archivo << listas[i].puzzles[j]->fichero << endl; //guardamos en el fichero el nombre del fichero txt
				delete listas[i].puzzles[j]; //devolvemos la memoria dinámica usada para cada puzzle
			}
		}
	}
	else {
		cout << "No se ha podido guardar en el fichero la lista de los puzzles" << endl;
	}
	archivo.close();
}

int elegirPuzzle(tListaPuzzles& lp) {
	int op;
	do {
		cout << "  En esta version estan disponibles los siguientes retos:" << endl << endl;
		mostrarListaPuzzles(lp);
		cout << "  0 Salir" << endl;
		cout << "  -1 Ordenar la lista de mayor a menor" << endl;
		cout << "  -2 Ordenar la lista de menor a mayor" << endl;

		cout << endl << "  Elige un reto: ";
		cin >> op;
		//si elige una de las dos opciones de ordenar, no termina el bucle, sino que vuelve a ejecutarse
		if (op == -1) ordenarMayorMenor(lp);
		else if (op == -2) ordenarMenorMayor(lp);

	} while (op < 0 || op > lp.contador); //tiene que elegir alguna opción entre el 0 y el numero de puzzles de la lista

	return op;
}

void mostrarListaPuzzles(tListaPuzzles const& lp) {
	for (int i = 0; i < lp.contador; i++) {
		cout << "  " << i + 1 << " " << lp.puzzles[i]->nombre << " con un maximo de " << lp.puzzles[i]->max_acciones << " movimientos" << endl;
	}
}

bool insertarOrdenado(tListaPuzzles& l, tPuzzle* p) {
	bool insertado = false;
	int pos = 0;
	if (!buscar(l, p, pos)) { //si devuelve true es que lo ha encontrado
		insertado = true;
		l.contador++; //aumentamos en uno la capacidad de la lista
		for (int i = l.contador - 1; i > pos; i--) { //desde el final de la lista hasta la posición donde se inserta el nuevo puzzle, se desplazan uno a la derecha
			l.puzzles[i] = l.puzzles[i - 1];
		}
		l.puzzles[pos] = p; //en la posición devuelta por buscar() se inserta el nuevo puzzle
	}
	return insertado;
}

bool buscar(tListaPuzzles const& lista, tPuzzle* puzzle, int& pos) {
	bool encontrado = false;
	int i = 0;
	while((*lista.puzzles[i] < *puzzle) && (i < lista.contador)){ //se recorre la lista desde el principio hasta encontrar un puzzle mayor al que se quiere insertar
		i++;
	}
	if (lista.puzzles[i]->fichero == puzzle->fichero) { //si el puzzle a insertar ya existe en la lista
		encontrado = true;
	}
	else {
		pos = i; //si el puzzle no existe en la lista se pasa la posición donde deber de insertarse
	}
	return encontrado;
}

void ordenarMayorMenor(tListaPuzzles& lp) {
	//por el método de la burbuja
	for (int i = 0; i < lp.contador - 1; i++) { //se recorre la lista del primero al último
		for (int j = lp.contador - 1; j > i; j--) { //se recorre la lista desde el último hasta el siguiente a i
			if (*lp.puzzles[j] > *lp.puzzles[j - 1]) { //si el ultimo es mayor al anterior, se intercambian
				tPtrPuzzle puzzle = lp.puzzles[j];
				lp.puzzles[j] = lp.puzzles[j - 1];
				lp.puzzles[j - 1] = puzzle;
			}
		}
	}
}

void ordenarMenorMayor(tListaPuzzles& lp) {
	//por el método de la burbuja
	for (int i = 0; i < lp.contador - 1; i++) { //se recorre la lista del primero al último
		for (int j = lp.contador - 1; j > i; j--) { //se recorre la lista desde el último hasta el siguiente a i
			if (*lp.puzzles[j] < *lp.puzzles[j - 1]) { //si el ultimo es menor al anterior, se intercambian
				tPtrPuzzle puzzle = lp.puzzles[j];
				lp.puzzles[j] = lp.puzzles[j - 1];
				lp.puzzles[j - 1] = puzzle;
			}
		}
	}
}