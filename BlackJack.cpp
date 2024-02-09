#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void shuffle(int* mazo, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        swap(mazo[i], mazo[j]);
    }
}

int getValorCarta(int carta) {
    int valor = carta % 13 + 1;
    if (valor > 10) {
        valor = 10; 
    }
    return valor;
}

int valorAs(int total) {
    int valor;
    cout << "¿Desea que el AS valga 1 o 11? ";
    do {
        cin >> valor;
    } while (valor != 1 && valor != 11);
    return valor;
}

int main() {
    const int TAM_MAZO = 52;
    int mazo[TAM_MAZO];
    for (int i = 0; i < TAM_MAZO; i++) {
        mazo[i] = i;
    }

    shuffle(mazo, TAM_MAZO);

    string nombreJugador;
    cout << "Bienvenido al juego de Blackjack!" << endl;
    cout << "Por favor, ingresa tu nombre: ";
    getline(cin, nombreJugador);

    int jugadorPuntos = 0;
    int bancaPuntos = 0;

    for (int i = 0; i < 2; i++) {
        int carta = mazo[i];
        cout << nombreJugador << " recibe carta: " << carta << endl;
        if (carta % 13 == 0) {
            jugadorPuntos += valorAs(jugadorPuntos);
        }
        else {
            jugadorPuntos += getValorCarta(carta);
        }
    }

    int cartaBanca = mazo[2];
    cout << "Banca recibe carta: " << cartaBanca << endl;
    bancaPuntos += getValorCarta(cartaBanca);

    char opcion;
    do {
        cout << "¿Desea otra carta? (s/n): ";
        cin >> opcion;
        if (opcion == 's') {
            int carta = mazo[3];
            cout << nombreJugador << " recibe carta: " << carta << endl;
            if (carta % 13 == 0) { 
                jugadorPuntos += valorAs(jugadorPuntos);
            }
            else {
                jugadorPuntos += getValorCarta(carta);
            }
        }
    } while (opcion == 's');

    while (bancaPuntos < 17) {
        int carta = mazo[4];
        cout << "Banca recibe carta: " << carta << endl;
        bancaPuntos += getValorCarta(carta);
    }

    cout << "Resultados:" << endl;
    if (jugadorPuntos > 21 || (bancaPuntos <= 21 && bancaPuntos > jugadorPuntos)) {
        cout << "El jugador pierde y la banca gana." << endl;
    }
    else if (bancaPuntos > 21 || jugadorPuntos > bancaPuntos) {
        cout << "El jugador gana y la banca pierde." << endl;
    }
    else {
        cout << "Empate. El jugador pierde y la banca gana." << endl;
    }

    return 0;
}

