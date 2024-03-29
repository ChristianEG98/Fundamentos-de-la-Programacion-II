#include "JuegoPM.h"

void main(){
	chcp1252();
	int op;
	tJuegoPM jpm;
	do {
		op = menu();
		if (op == 0) { //opcion 0 para salir del juego
			cout << endl << "  Saliendo del juego... hasta la proxima!" << endl;
		}
		else { //opcion 1 o 2 para elegir el modo de juego
			if (op == 1) jpm.modo = 1;
			else jpm.modo = 2;

			if (!iniciar(jpm)) { //llama a iniciar y si devuelve falso imprime que ha habido un error
				cout << "  Fallo al intentar iniciar el juego, vuelva a intentarlo." << endl;
			}
		}
	} while (op != 0); //el bucle se ejecuta hasta que se elige la opci�n 0 de salir
}

int menu(){
	int op;
	do {
		cout << endl << "  1. Version del juego - 1D" << endl;
		cout << "  2. Version del juego - 2D" << endl;
		cout << "  0. Salir" << endl;
		cout << endl << "  Elija una opcion: ";
		cin >> op;
	} while (op < 0 || op > 2); //comprobamos que no elige una de las opciones disponibles

	return op;
}

bool iniciar(tJuegoPM& jpm){
	bool correcto = false;
	//iniciamos a 0 los tama�os de ambas imagenes y el max de acciones
	jpm.modelo.tam_matriz.x = 0;
	jpm.modelo.tam_matriz.y = 0;
	jpm.objetivo.tam_matriz.x = 0;
	jpm.objetivo.tam_matriz.y = 0;
	jpm.max_acciones = 0;

	if (cargar(jpm)) { //llamamos a cargar, si consigue cargarlo correctamente, devuelve true y se llama a jugar
		correcto = true;
		jugar(jpm);
	}
	return correcto;
}

bool cargar(tJuegoPM& jpm){
	bool cargado = false;
	string nombre, nombreFinal;
	//introduce el nombre del archivo
	cout << endl << "  Introduce el nombre del archivo: ";
	cin >> nombre;
	ifstream archivo;
	//a�adimos la extensi�n al nombre del archivo seg�n el modo elegido
	if(jpm.modo == 1)
		nombreFinal = nombre + "_1D.txt";
	else
		nombreFinal = nombre + "_2D.txt";
	//abrimos el archivo
	archivo.open(nombreFinal);
	//comprobamos si se ha abierto correctamente, si es as�, llamamos a cargar del m�dulo Matriz y cargamos ambas matrices
	if (archivo.is_open()) {
		if (cargar(jpm.modelo, archivo) && cargar(jpm.objetivo, archivo))
			cargado = true;
		archivo >> jpm.max_acciones; //almacenamos el n�mero de acciones m�ximas
		archivo.close(); //cerramos el archivo
	}
	else
		cout << endl << "  No se ha podido cargar el archivo" << endl;
	return cargado;
}

void mostrar(tJuegoPM const& jpm){
	//mostramos el numero de intentos restantes
	cout << endl << "  Intentos restantes: " << jpm.max_acciones << endl << endl;
	//mostramos la imagen modelo
	cout << "    ";
	for (int c = 0; c < jpm.modelo.tam_matriz.y; c++) {
		cout << setw(2) << c << "";
	}
	cout << endl;
	for (int i = 0; i < jpm.modelo.tam_matriz.x; i++) {
		cout << " " << setw(2) << i << " ";
		for (int j = 0; j < jpm.modelo.tam_matriz.y; j++) {
			colorCTA(15, int(jpm.modelo.matriz[i][j]) - int('0'));
			cout << setw(2) << " ";
		}
		colorCTA(15, 0);
		cout << endl;
	}
	cout << endl;
	//mostramos la imagen objetivo
	cout << "    ";
	for (int c = 0; c < jpm.objetivo.tam_matriz.y; c++) {
		cout << setw(2) << c << "";
	}
	cout << endl;
	for (int i = 0; i < jpm.objetivo.tam_matriz.x; i++) {
		cout << " " << setw(2) << i << " ";
		for (int j = 0; j < jpm.objetivo.tam_matriz.y; j++) {
			colorCTA(15, int(jpm.objetivo.matriz[i][j]) - int('0'));
			cout << setw(2) << " ";
		}
		colorCTA(15, 0);
		cout << endl;
	}
}

bool jugar(tJuegoPM& jpm){
	bool fin = false;
	mostrar(jpm); //mostramos el estado actual del puzzle
	do {
		//llamamos a accion(), si consigue ejecutarla correctamente, restamos uno al n�mero de intentos y llamamos a mostrar()
		if (accion(jpm)) {
			jpm.max_acciones--;
			mostrar(jpm);
		}
		//si accion() no consigue ejecutarse, mostramos que esa acci�n elegida no es v�lida
		else {
			cout << endl << "  Accion no valida!" << endl;
		}
		//comprobamos si se ha llegado a la matriz objetivo, y si es as�, fin = true y salimos del bucle
		if (jpm.modelo == jpm.objetivo) {
			fin = true;
			cout << endl << "  Has conseguido resolver el puzzle!" << endl;
		}
	} while (!fin && jpm.max_acciones > 0);

	if (jpm.max_acciones == 0 && fin != true) { //si no se ha llegado a resolver el puzzle y se ha quedado sin intentos
		cout << endl << "  No has conseguido resolver el puzzle, mejor suerte la proxima vez!" << endl;
	}

	return true;
}

bool accion(tJuegoPM& jpm){
	bool exito = false;
	string accion;
	int ac1 = 0, ac2 = 0;
	cout << endl << "  Introduzca la accion a realizar: ";
	cin >> accion;
	//todas las acciones del modo 1D
	if (jpm.modo == 1) {
		//voltear la fila ac1
		if (accion == "VF") {
			cin >> ac1;
			if (voltearF(jpm.modelo, ac1))
				exito = true;
			else
				cout << endl << "  La fila elegida se pasa del rango de la matriz" << endl;
		}
		//voltear la columna ac1
		else if (accion == "VC") {
			cin >> ac1;
			if (voltearC(jpm.modelo, ac1))
				exito = true;
			else
				cout << endl << "  La columna elegida se pasa del rango de la matriz" << endl;
		}
		//intercambiar las filas ac1 y ac2
		else if (accion == "SF") {
			cin >> ac1 >> ac2;
			if (swapF(jpm.modelo, ac1, ac2))
				exito = true;
			else
				cout << endl << "  La o las filas elegidas se pasan del rango de la matriz" << endl;
		}
		//intercambiar las columnas ac1 y ac2
		else if (accion == "SC") {
			cin >> ac1 >> ac2;
			if (swapC(jpm.modelo, ac1, ac2))
				exito = true;
			else
				cout << endl << "  La o las columnas elegidas se pasan del rango de la matriz" << endl;
		}
		//intercambiar la diagonal ac1
		else if (accion == "SD") {
			cin >> ac1;
			if (swapD(jpm.modelo, ac1))
				exito = true;
			else
				cout << endl << "  La diagonal elegida se pasa del rango de la matriz o la matriz no es cuadrada" << endl;
		}
		//voltear la diagonal ac1
		else if (accion == "VD") {
			cin >> ac1;
			if (voltearD(jpm.modelo, ac1))
				exito = true;
			else
				cout << endl << "  La diagonal elegida se pasa del rango de la matriz o la matriz no es cuadrada" << endl;
		}
	}
	//todas las acciones del modo 2D
	else {
		//voltear respecto a la vertical
		if (accion == "VV") {
			voltearV(jpm.modelo);
			exito = true;
		}
		//voltear respecto a la horizontal
		else if (accion == "VH") {
			voltearH(jpm.modelo);
			exito = true;
		}
		//rotar 90 grados a la derecha
		else if (accion == "RD") {
			rotarD(jpm.modelo);
			exito = true;
		}
		//intercambiar las casillas adyacentes de num1 y num2
		else if (accion == "SA") {
			tCoor num1, num2; //swapAdy usa par�metros de tipo tCoor
			cin >> num1.x >> num1.y >> num2.x >> num2.y;
			if (swapAdy(jpm.modelo, num1, num2)) {
				exito = true;
			}
			else {
				cout << endl << "  La casillas adyacentes se pasan de los limites del tablero" << endl;
			}
		}
		//voltear respecto a la diagonal
		else if (accion == "VD") {
			if (voltearID(jpm.modelo)) {
				exito = true;
			}
			else {
				cout << endl << "  La matriz no es cuadrada" << endl;
			}
		}
	}
	cin.ignore(10000, '\n'); //elimina los datos de entrada que no sirven
	return exito;
}