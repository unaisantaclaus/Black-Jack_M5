#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Funció per barrejar el mazo
void barrejar(int* mazo, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        swap(mazo[i], mazo[j]);
    }
}

// funció per obtenir el valor d'una carta
int valorCarta(int carta) {
    int valor = carta % 13 + 1;
    if (valor > 10) {
        valor = 10; // Les figures valen 10
    }
    return valor;
}

// funció per determinar el valor de l'as pel jugador
int valorAsJugador() {
    int valor;
    cout << "Vols que el valor de l'AS valgui 1 o 11? ";
    do {
        cin >> valor;
    } while (valor != 1 && valor != 11);
    return valor;
}

// funció per mostrar carta rebuda
void mostrarCarta(int carta) {
    string palos[4] = { "Piques", "Cors", "Rombs", "Trèvols" };
    string figures[13] = { "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jota", "Reina", "Rei" };

    cout << figures[carta % 13] << " de " << palos[carta / 13] << endl;
}

int main() {
    const int TAM_MAZO = 52;
    int mazo[TAM_MAZO];
    for (int i = 0; i < TAM_MAZO; i++) {
        mazo[i] = i;
    }

    barrejar(mazo, TAM_MAZO);

    string nomJugador;
    cout << "Benvingut al joc de Blackjack!" << endl;
    cout << "Introdueix el teu nom: ";
    getline(cin, nomJugador);

    int puntsJugador = 0;
    int puntsBanca = 0;

    // entrega de les dues primeres cartes al jugador
    cout << nomJugador << " rep les següents cartes:" << endl;
    for (int i = 0; i < 2; i++) {
        int carta = mazo[i];
        mostrarCarta(carta);
        if (carta % 13 == 0) { // és un AS
            puntsJugador += valorAsJugador();
        }
        else {
            puntsJugador += valorCarta(carta);
        }
    }

    // entrega de la primera carta a la banca
    cout << "La banca rep la següent carta:" << endl;
    int cartaBanca = mazo[2];
    mostrarCarta(cartaBanca);
    puntsBanca += valorCarta(cartaBanca);

    // torn del jugador
    char opcio;
    do {
        cout << "Voleu una altra carta? (s/n): ";
        cin >> opcio;
        if (opcio == 's') {
            int carta = mazo[3];
            cout << nomJugador << " rep la següent carta:" << endl;
            mostrarCarta(carta);
            if (carta % 13 == 0) { // és un AS
                puntsJugador += valorAsJugador();
            }
            else {
                puntsJugador += valorCarta(carta);
            }
        }
    } while (opcio == 's' && puntsJugador < 21);

    // if per la banca
    if (puntsJugador <= 21) {
        cout << "Torn de la banca:" << endl;
        while (puntsBanca < puntsJugador && puntsBanca < 17) {
            int carta = mazo[4];
            cout << "La banca rep la següent carta:" << endl;
            mostrarCarta(carta);
            puntsBanca += valorCarta(carta);
            if (puntsBanca > 21) {
                break;
            }
        }
    }

