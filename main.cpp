#include "Card.h"
#include "Deck.h"
#include "SpiderGame.h"
#include "GolfGame.h"

using std::string;
using std::cin;
using std::getline;
using std::endl;
using std::stoi;


// Black magic
const bool ADMIN = true;
bool BYPASS = false;
static void clrscr() { cout << "\033[2J\033[1;1H"; };

static void waitForEnter() {
	cout << endl;
	cout << "[!] Presione enter para continuar";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	clrscr();
}

static int gameToPlay() {
	string Option;
	cout << "[*] Seleccione el juego de Solitario que desea jugar." << endl;
	cout << "[1] Solitario Golf" << endl;
	cout << "[2] Solitario Spider" << endl;
	cout << "[3] Salir del programa" << endl;
	if (ADMIN) cout << "[4] Activar Hacks" << endl;

	while (true) {
		cout << "[#] ";
		getline(cin, Option);
		if (Option == "4" && ADMIN) break;
		if (Option == "1" || Option == "2" || Option == "3") break;
		cout << "[!] Opción inválida, intente de nuevo." << endl;
	}
	clrscr();
	return stoi(Option);
}

static int golfGameOption() {
	string Option;
	cout << "[*] Seleccione la versión de Solitario Golf que desea jugar." << endl;
	cout << "[1] Una Ronda Única" << endl;
	cout << "[2] Juego Completo de 9 rondas" << endl;
	cout << "[3] Atras" << endl;

	while (true) {
		cout << "[#] ";
		getline(cin, Option);
		if (Option == "1" || Option == "2" || Option == "3") break;
		cout << "[!] Opción inválida, intente de nuevo." << endl;
	}
	clrscr();
	return stoi(Option);
}

static int golfGameActions() {
	string Option;
	cout << "[*] Seleccione el movimiento que desea intentar." << endl;
	cout << "[1] Descartar Carta" << endl;
	cout << "[2] Tomar Carta de la Mano" << endl;
	cout << "[3] Deshacer Movimiento" << endl;
	cout << "[4] Abandonar Juego" << endl;

	while (true) {
		cout << "[#] ";
		getline(cin, Option);
		if (Option == "1" || Option == "2" || Option == "3" || Option == "4") break;
		cout << "[!] Opción inválida, intente de nuevo." << endl;
	}
	clrscr();
	return stoi(Option);
}

static int readNumber() {
	int input;
	cout << "[#] ";
	cin >> input;
	while (!cin)
	{
		cout << "[!] Opción inválida, intente de nuevo." << endl;
		cout << "[#] ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> input;
	}
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return input;
}

bool jugarRondaGolf(GolfGame* game, int numeroRonda = 0) {
	int golfGameAction;
	game->inicializarJuego();
	while (!game->rondaTerminada()) { //Se debe implementar la condición de gane o pierde
		if (numeroRonda != 0) cout << "[*] Ronda: " << numeroRonda << endl;
		game->print();
		golfGameAction = golfGameActions();
		if (golfGameAction == 1) {
			if (numeroRonda != 0) cout << "[*] Ronda: " << numeroRonda << endl;
			game->print();
			cout << "[*] Seleccione la columna de la carta que desea descartar." << endl;
			if (!game->descartarCarta(readNumber()-1, BYPASS)) waitForEnter();
		}
		if (golfGameAction == 2) {
			game->voltearCarta();
		}
		if (golfGameAction == 3) {
			game->deshacer();
		}
		if (golfGameAction == 4) {
			return false;
		}

		clrscr();
	}
	return true;
}

void playGolf(GolfGame* game, int golfOption) {
	
	// Ronda Rápida
	if (golfOption == 1) {
		if (!jugarRondaGolf(game)) return;
		game->print();
		cout << "[*] Juego terminado. Puntaje: " << game->calcularPuntaje() << endl;
		waitForEnter();
	}

	// 9 Rondas
	if (golfOption == 2) {
		int rondasJugadas = 0;
		int puntaje = 0;
		while (rondasJugadas < 9){
			cout << "[*] Ronda " << rondasJugadas + 1 << " iniciada." << endl;
			if (!jugarRondaGolf(game, rondasJugadas + 1)) return;

			puntaje += game->calcularPuntaje();
			rondasJugadas++;
			game->print();
			cout << "[*] Ronda " << rondasJugadas << " terminada. Puntaje ronda: " << game->calcularPuntaje() << endl;
			waitForEnter();
		}
		clrscr();
		cout << "[*] Juego terminado. Puntaje total: " << puntaje << endl;
		waitForEnter();
	}
}

static int spiderGameActions() {
	string Option;
	cout << "[*] Seleccione el movimiento que desea intentar." << endl;
	cout << "[1] Mover Cartas" << endl;
	cout << "[2] Solicitar Cartas" << endl;
	cout << "[3] Deshacer Movimiento" << endl;
	cout << "[4] Abandonar Juego" << endl;

	while (true) {
		cout << "[#] ";
		getline(cin, Option);
		if (Option == "1" || Option == "2" || Option == "3" || Option == "4") break;
		cout << "[!] Opción inválida, intente de nuevo." << endl;
	}
	clrscr();
	return stoi(Option);
}

void playSpider(SpiderGame* game) {
	int spiderGameAction;
	game->inicializarJuego();
	while (!game->rondaTerminada()) { //Se debe implementar la condición de gane o pierde
		game->print();
		spiderGameAction = spiderGameActions();
		if (spiderGameAction == 1) {
			game->print();
			cout << "[*] Seleccione la columna de las carta que desea mover." << endl;
			int columna = readNumber() - 1;
			cout << "[*] Seleccione la cantidad de cartas que desea mover." << endl;
			int cantidad = readNumber();
			cout << "[*] Seleccione la columna destino." << endl;
			int destino = readNumber() - 1;
			if (!game->moverCartas(columna, cantidad, destino)) waitForEnter();
		}
		if (spiderGameAction == 2) {
			game->solicitarCartas();
		}
		if (spiderGameAction == 3) {
			game->deshacer();
		}
		if (spiderGameAction == 4) {
			break;
		}

		clrscr();
	}
	if (game->rondaTerminada()) cout << "[*] Felicidades, juego terminado." << endl;
	else cout << "[*] Juego abandonado. Pathetic." << endl;
	waitForEnter();
}

int main() {
	//SetConsoleOutputCP(65001);
	srand(time(NULL));
	SpiderGame* spiderGame = new SpiderGame();
	GolfGame* golfGame = new GolfGame();

	bool continuar = true;
	int gameOption;
	int golfOption;

	while ((gameOption = gameToPlay()) != 3) {
		//GOLF GAME
		if (gameOption == 1) playGolf(golfGame, golfGameOption());

		//SPIDER GAME
		if (gameOption == 2) playSpider(spiderGame);

		//HACKERMAN <- MATRIX
		if (gameOption == 4 && ADMIN) {
			BYPASS = !BYPASS;
			cout << "[*] Hacks " << (BYPASS ? "activados" : "desactivados") << endl;
		}
	}
}