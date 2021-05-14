#include <iostream>
#include <iomanip>
using namespace std;

#define N 8

int rozwiazPKSDodatk(int x, int y, int ruchi, int rozw[N][N],
                     int xRuch[], int yRuch[]);

/* Dodatkowa funkcja do sprawdzenia, czy i, j są
poprawnymi indeksami dla szachownicy N*N */
int jestPoprawne(int x, int y, int rozw[N][N])
{
    return (x >= 0 && x < N && y >= 0 && y < N && rozw[x][y] == -1);
}

/* Dodatkowa funkcja do drukowania
macierzy rozwiązania rozw[N][N] */
void drukujRozwiazanie(int rozw[N][N])
{
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
            cout << " " << setw(2) << rozw[x][y] << " ";
        cout << endl;
    }
}

/* Ta funckja rozwiązuje problem konika szachowego poprzez cofanie się.
Ta funkcja korzysta głównie z rozwiazPKSDodatk() aby rozwiązać problem.
Zwraca false jeżeli żadna pełna ścieżka nie jest dostępna, w innym
przypadku zwraca true i drukuje ścieżkę. Należy zwrócić uwagę na to
że możliwe są inne rozwiązania, funkcja ta wypisuje tylko jedną z możliwych.*/
int rozwiazPKS()
{
    int rozw[N][N];

    /* Wstępne ładowanie macierzy rozwiązań */
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            rozw[x][y] = -1;

    /* xRuch[] i yRuch[] definiują kolejny ruch konika.
    xRuch[] jest dla na następnej wartości współrzędnej x
    yRuch[] jest dla na następnej wartości współrzędnej y */
    int xRuch[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yRuch[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    // Skoro konik początkowo jest na pierwszym polu
    rozw[0][0] = 0;

    /* Zacznij od 0,0 i sprawdź wszystkie ścieżki przy użyciu
    rozwiazPKSDodatk() */
    if (rozwiazPKSDodatk(0, 0, 1, rozw, xRuch, yRuch) == 0)
    {
        cout << "rozwution does not exist";
        return 0;
    }
    else
        drukujRozwiazanie(rozw);

    return 1;
}

/* Rekursywna funkcja dodatkowa dla rozwiązania problemu konika szachowego */
int rozwiazPKSDodatk(int x, int y, int ruchi, int rozw[N][N],
                     int xRuch[N], int yRuch[N])
{
    int k, nast_x, nast_y;
    if (ruchi == N * N)
        return 1;

    /* Wypróbuj wszystkie ruchy z
    obecnej pozycji x, y */
    for (k = 0; k < 8; k++)
    {
        nast_x = x + xRuch[k];
        nast_y = y + yRuch[k];
        if (jestPoprawne(nast_x, nast_y, rozw))
        {
            rozw[nast_x][nast_y] = ruchi;
            if (rozwiazPKSDodatk(nast_x, nast_y, ruchi + 1, rozw,
                                 xRuch, yRuch) == 1)
                return 1;
            else

                // backtracking
                rozw[nast_x][nast_y] = -1;
        }
    }
    return 0;
}

// Główna funkcja
int main()
{
    // Wezwanie funkcji
    rozwiazPKS();
    system("pause");
    return 0;
}
