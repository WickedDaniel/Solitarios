#include "Card.h"
#include "Deck.h"
#include "GolfGame.h"

int main() {
	srand(time(NULL));

	Deck deck = Deck(1);
	deck.shuffle();

	Card drawnCard = Card(Card::ACE, true);
	//cout << drawnCard << endl;

	GolfGame game = GolfGame();
	game.inicializarJuego();
	game.imprimirStacks();
	game.imprimirDescartes();
	game.imprimirMano();
	
	game.voltearCarta();
	game.voltearCarta();
	game.voltearCarta();
	game.voltearCarta();
	game.voltearCarta();
	game.imprimirStacks();
	game.imprimirDescartes();
	game.imprimirMano();


	//cout << "Deck size: " << deck.getSize() << endl;
}