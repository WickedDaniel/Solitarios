#include "Card.h"
#include "Deck.h"
#include "SpiderGame.h"
#include "windows.h"

int main() {
	SetConsoleOutputCP(65001);
	srand(time(NULL));
	SpiderGame game = SpiderGame();

	game.inicializarJuego();
	game.imprimirStacks();
	game.imprimirCardReserve();

	game.solicitarCartas();
	game.imprimirStacks();
	game.imprimirCardReserve();


	//cout << "=== Testing LinkedList slice() ===" << endl << endl;

	// Test 1: Basic slice with integers
	/*
	cout << "Test 1: Basic slice with integers" << endl;
	LinkedList<int>* list1 = new LinkedList<int>();
	for (int i = 0; i < 10; i++) {
		list1->append(i);
	}
	cout << "Original list: ";
	list1->print();

	LinkedList<int>* sliced1 = list1->slice(0, 6);
	cout << "Slice(2, 5): ";
	sliced1->print();
	cout << "Expected: [ 2 3 4 ]" << endl << endl;

	list1->append(sliced1);
	list1->print();
	*/

	/*
	// Si son las 9 rondas
	GolfGame game = GolfGame();
	game.inicializarJuego();
	int puntaje = 0;
	while (ronda != 9 || abandonar) {
		game.print();
		imprimirMenu();
		int opcion = usuarioSeleccion();

		if (game.rondaTerminada) {
			puntaje += game.calcularPuntajeRonda();
			game.inicializarJuego();
			ejecutarOpcion(opcion, game);
		}
	}

	/* Si es una ronda
	* 
	while (!game.rondaTerminada) {
		game.print();
		imprimirMenu();
		int opcion = usuarioSeleccion();
		ejecutarOpcion(opcion, game);
	}
	*/


	//cout << "Deck size: " << deck.getSize() << endl;
}