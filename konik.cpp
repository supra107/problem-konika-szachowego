#include <iostream>
#include <bits/stdc++.h>
#include <chrono>

#define N 8

//// xRuch[] i yRuch[] definiuj¹ kolejny ruch konika.
//// xRuch[] jest dla na nastêpnej wartoœci wspó³rzêdnej x
//// yRuch[] jest dla na nastêpnej wartoœci wspó³rzêdnej y
//// @note test note
static int mozliweRuchyOsX[N] = {1, 1, 2, 2, -1, -1, -2, -2};
static int mozliweRuchyOsY[N] = {2, -2, 1, -1, 2, -2, 1, -1};


/*
 Metoda sprawdza czy konik nie wyszedł poza szachownice, na osi x i y nie moga to byc wartosci wieksze od 8 i mniejsze od zera
 */
bool limity(int x, int y) {
    return ((x >= 0 && y >= 0) && (x < N && y < N));
}

/*
 Metoda sprawdza czy pole na ktore skacze konik:
 - nie bylo wczesniej wybrane,
 - nie jest poza szachownica
 */
bool jestPusty(int *a, int x, int y) {
    return (limity(x, y)) && (a[y * N + x] < 0);
}

/*
 Zwraca liczbe pol ktore nie zostaly odwiedzone przez konika.
 */
int zwrocStopien(int *a, int x, int y) {
    int count = 0;
    for (int i = 0; i < N; ++i)
        if (jestPusty(a, (x + mozliweRuchyOsX[i]), (y + mozliweRuchyOsY[i])))
            count++;

    return count;
}

/*
 * Zwroci true jesli wylosowany ruch nie byl uczesczany i nie znajduje sie poza plansza
 */
bool nastepnyRuch(int *a, int *x, int *y) {
    int min_deg_idx = -1;
    int c;
    int min_deg = (N + 1);
    int nx;
    int ny;


    int start = rand() % N;
    for (int count = 0; count < N; ++count) {
        int i = (start + count) % N;
        nx = *x + mozliweRuchyOsX[i];
        ny = *y + mozliweRuchyOsY[i];
        if ((jestPusty(a, nx, ny)) &&
            (c = zwrocStopien(a, nx, ny)) < min_deg) {
            min_deg_idx = i;
            min_deg = c;
        }
    }

    if (min_deg_idx == -1)
        return false;

    nx = *x + mozliweRuchyOsX[min_deg_idx];
    ny = *y + mozliweRuchyOsY[min_deg_idx];

    a[ny * N + nx] = a[(*y) * N + (*x)] + 1;

    *x = nx;
    *y = ny;

    return true;
}

/* Dodatkowa funkcja do drukowania
macierzy rozwi¹zania rozw[N][N] */
void drukuj(int *a) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            std::cout << a[j * N + i] << "\t";
        std::cout << "\n";
    }
}

/*
 * Sprawdza czy kolejny ruch konika sasiaduje z poprzednim
 */
bool sasiedni(int x, int y, int xx, int yy) {
    for (int i = 0; i < N; ++i)
        if (((x + mozliweRuchyOsX[i]) == xx) && ((y + mozliweRuchyOsY[i]) == yy))
            return true;

    return false;
}

/*
Glowna metoda, wyszukuje najblizszy mozliwy ruch konika z uwzglednieniem poprzednich ruchow,
konik odwiedza tylko raz kazde pole.
 */

bool ZnajdzNablizszyRuch(int zmiennaX, int zmiennaY) {

    int a[N * N];
    for (int i = 0; i < N * N; ++i)
        a[i] = -1;


    int sx = zmiennaX;
    int sy = zmiennaY;

    int x = sx, y = sy;
    a[y * N + x] = 1;

    for (int i = 0; i < N * N - 1; ++i)
        if (nastepnyRuch(a, &x, &y) == 0)
            return false;

    if (!sasiedni(x, y, sx, sy))
        return false;

    drukuj(a);
    return true;
}


/*
 * Metoda main, w niej wykonuje sie caly algorytm.
 */

int main() {

    /*
     * Biblioteki wykorzystane do obliczania czasu trwania algorytmu.
     */
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    int zmiennaX = 0;
    int zmiennaY = 0;
    std::cout << "Podaj startowa pozycje konika.\n";
    std::cout << "y - wartosci szachownicy na osi y, dozwolone 1-8\n";
    std::cout << "x - wartosci szachownicy na osi x, dozwolone 1-8\n";
    std::cout << "Podaj wartosc x\n";
    std::cin >> zmiennaX;
    std::cout << "Podaj wartosc y\n";
    std::cin >> zmiennaY;
    auto t1 = std::chrono::high_resolution_clock::now();
    zmiennaX--;
    zmiennaY--;
    if (zmiennaX < 8 && zmiennaX >= 0 && zmiennaY < 8 && zmiennaY >= 0) {
        bool znajdzRozwiazanie = false;
        while (!znajdzRozwiazanie) {
            znajdzRozwiazanie = ZnajdzNablizszyRuch(zmiennaX, zmiennaY);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << " \nCzas dzialania algorytmu: " << ms_int.count() << " milisekund\n";
    } else {
        std::cout << "Wartosci poza tablica";
    }
    return 0;
}