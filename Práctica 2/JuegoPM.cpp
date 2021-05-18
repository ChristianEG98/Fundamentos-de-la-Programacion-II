#include "JuegoPM.h"

int main() {
	mainPuzzlesReunidos();
	return 0;
}

void mainPuzzlesReunidos(){
	chcp1252();
	int numOpc, modo, opPuzzle;
	tPuzzlesReunidos jr;
	cargar(jr);
	do {
		numOpc = menu();
		//opcion 0 para salir del juego
		if (numOpc == 0) {
			cout << endl << "  Saliendo del juego... hasta la proxima!" << endl;
			guardar(jr); //guardamos las listas de nuevo en el fichero
		}
		//opcion 1 o 2 para resolver un puzzle
		else if (numOpc == 1 || numOpc == 2) {
			if (numOpc == 1) modo = 0;
			else modo = 1;

			opPuzzle = elegirPuzzle(jr[modo]); //opPuzzle guarda el puzzle elegido para ser jugado

			if (opPuzzle > 0) { //si ha elegido algun puzzle de la lista y no la opción 0 Salir
				if (!iniciar(*jr[modo].puzzles[opPuzzle - 1])) { //llama a iniciar y si devuelve falso imprime que ha habido un error
					cout << "  Fallo al intentar iniciar el juego, vuelva a intentarlo." << endl;
				}
			}
			ordenarMenorMayor(jr[modo]); //ordenamos la lista seleccionada de menor a mayor por si ha cambiado
		}
		//opcion 3 para añadir un nuevo puzzle al catálogo
		else if (numOpc == 3) {
			for (int i = 0; i < NUM_MODOS; i++) { //mostramos las listas con los puzzles ordenadas en orden creciente
				cout << endl << "  Juegos " << to_string(i + 1) << "D" << endl;
				mostrarListaPuzzles(jr[i]);
			}
			//cogemos la información acerca del nuevo puzzle
			string nombre;
			tPtrPuzzle p = new tPuzzle;
			cout << endl << "  Escriba el nombre del puzzle: ";
			cin.ignore();
			getline(cin, nombre); //cogemos el nombre del puzzle
			p->nombre = nombre;
			cout << endl << "  Escriba el nombre del fichero en que se encuentra: ";
			cin >> nombre; //cogemos el nombre del fichero
			p->fichero = nombre;

			if (cargar(*p)) { //si consigue cargar el fichero txt con la información del puzzle
				if (nombre[nombre.length() - 6] == '1') modo = 0; //nombre[nombre.lenght() - 6] nos permite acceder al caracter del nombre del fichero que tiene el modo de juego
				else modo = 1;
				if (!insertarOrdenado(jr[modo], p)) { //guardamos en la lista el nuevo puzzle si no existe ya
					cout << endl << "  Este puzzle ya existe en el catalogo" << endl;
				}
				cout << endl << "  Juegos " << to_string(modo + 1) << "D" << endl;
				mostrarListaPuzzles(jr[modo]); //mostramos la lista con el nuevo puzzle insertado
			}
		}
	} while (numOpc != 0); //el bucle se ejecuta hasta que se elige la opción 0 de salir

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //muestra si queda memoria dinámica sin devolver al sistema
}

int menu(){
	int op;
	do {
		cout << endl << "  1. Resolver un puzzle - 1D" << endl;
		cout << "  2. Resolver un puzzle - 2D" << endl;
		cout << "  3. Añadir un puzzle al catálogo" << endl;
		cout << "  0. Salir" << endl;
		cout << endl << "  Elija una opcion: ";
		cin >> op;
	} while (op < 0 || op > 3); //comprobamos que no elige una de las opciones disponibles

	return op;
}