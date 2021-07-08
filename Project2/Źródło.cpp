#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
using namespace std;
int rozmiar;
int max_poziom;

struct Drzewo {
    int zawartosc;
    Drzewo* ojciec;
    Drzewo* syn_P;
    Drzewo* syn_L;
    int poziom;
};

void Wyswietl_Lewy_wezel(Drzewo* wezel) {
    while (wezel) {
        if (wezel->poziom) {
            cout << "      ojciec -";
            cout << wezel->ojciec->zawartosc << endl;
        }
        if (wezel->syn_L) {
            cout << "   lewy -";
            cout << wezel->syn_L->zawartosc;
        }

        if (wezel->syn_P) {
            cout << "   prawy -";
            cout << wezel->syn_P->zawartosc << endl;
        }
        wezel = wezel->syn_L;
        cout << endl;
    }return;
}

void Wyswietl_Prawy_wezel(Drzewo* wezel) {
    while (wezel) {
        if (wezel->poziom) {
            cout << "      ojciec -";
            cout << wezel->ojciec->zawartosc << endl;
        }
        if (wezel->syn_L) {
            cout << "   lewy -";
            cout << wezel->syn_L->zawartosc;
        }

        if (wezel->syn_P) {
            cout << "   prawy -";
            cout << wezel->syn_P->zawartosc << endl;
        }
        wezel = wezel->syn_P;
        cout << endl;
    }return;
}

void Wyswietl(Drzewo* drzewo) {
    if (rozmiar == 0) return;
    cout << " Ilosc poziomow " << max_poziom << endl;
    cout << " KORZEN " << endl;  // WYSWIETLA KORZEN
    cout << "    ojciec -"; cout << drzewo->ojciec->zawartosc << endl;
    if (drzewo->syn_L) { cout << "Lewy - "; cout << drzewo->syn_L->zawartosc; }
    if (drzewo->syn_P) { cout << " Prawy - "; cout << drzewo->syn_P->zawartosc << endl << endl; }

    cout << endl << " Lewy wezel " << endl; Wyswietl_Lewy_wezel(drzewo->syn_L);
    cout << endl << endl << " Prawy wezel " << endl; Wyswietl_Prawy_wezel(drzewo->syn_P);
    return;
}


void IN_order(Drzewo* drzewo) {
    if (rozmiar == 0) return;
    Drzewo* lewe = drzewo->syn_L;
    Drzewo* prawe = drzewo->syn_P;
    while (lewe) {
        if (lewe->syn_L) {
            cout << "," << lewe->syn_L->zawartosc;
        }
        if (lewe->syn_P) {
            cout << "," << lewe->syn_P->zawartosc;
        }
        lewe = lewe->syn_P;
    }
    cout << "," << drzewo->syn_L->zawartosc;
    cout << "," << drzewo->ojciec->zawartosc;
    cout << "," << drzewo->syn_P->zawartosc << endl;
    while (prawe) {
        if (prawe->syn_L) {
            cout << "," << prawe->syn_L->zawartosc;
        }
        if (prawe->syn_P) {
            cout << "," << prawe->syn_P->zawartosc;
        }
        prawe = prawe->syn_P;
    }
    return;
}

void IN_ORDER(Drzewo* wezel)
{
    if (wezel->syn_L) IN_ORDER(wezel->syn_L);
    if (wezel->zawartosc != 0)cout << wezel->zawartosc << ",";
    if (wezel->syn_P) IN_ORDER(wezel->syn_P);
}
void POST_ORDER(Drzewo* wezel)
{
    if (wezel->syn_L) POST_ORDER(wezel->syn_L);
    if (wezel->syn_P) POST_ORDER(wezel->syn_P);
    if (wezel->zawartosc != 0)cout << wezel->zawartosc << ",";
}




void Wezel_lewy(Drzewo* wezel, Drzewo* nowy_wezel, int poz) {
    wezel->syn_L = nowy_wezel;
    wezel->poziom = poz;
    wezel->syn_L->ojciec = nowy_wezel;
    wezel->syn_L->syn_L = nullptr;
    wezel->syn_L->syn_P = nullptr;
    return;
}

void Wezel_prawy(Drzewo* wezel, Drzewo* nowy_wezel, int poz) {
    wezel->syn_P = nowy_wezel;
    wezel->poziom = poz;
    wezel->syn_P->ojciec = nowy_wezel;
    wezel->syn_P->syn_L = nullptr;
    wezel->syn_P->syn_P = nullptr;
    return;
}

void Dodaj(Drzewo* wezel) {
    int x, poz = 0;
    Drzewo* nowy_wezel = new Drzewo;
    cout << "podaj liczbe "; cin >> x;
    nowy_wezel->zawartosc = x;
    if (rozmiar == 0) {
        nowy_wezel->ojciec = nullptr;
        wezel->ojciec = nowy_wezel;
        return;
    }
    while (wezel) {
        if (max_poziom < poz) max_poziom = poz;
        if (x > wezel->ojciec->zawartosc) {
            if (x > wezel->ojciec->zawartosc && wezel->syn_P == nullptr) {
                Wezel_prawy(wezel, nowy_wezel, poz);
                return;
            }
            wezel = wezel->syn_P;
        }
        else if (x <= wezel->ojciec->zawartosc) {
            if (x <= wezel->ojciec->zawartosc && wezel->syn_L == nullptr) {
                Wezel_lewy(wezel, nowy_wezel, poz); return;
            }
            wezel = wezel->syn_L;

        }
        poz++;
    }
}



int main() {
    int user = 1; char x;
    rozmiar = 0;
    Drzewo* wezel = new Drzewo;
    wezel->ojciec = nullptr;
    wezel->zawartosc = 0;
    wezel->syn_L = nullptr;
    wezel->syn_P = nullptr;
    while (user != 0) {
        system("CLS");
        Wyswietl(wezel); cout << endl;
        cout << "//////////////////////////////////////////////" << endl;
        cout << " Dodaj liczbe  - 1" << endl;
        cout << " IN_ORDER  - 2" << endl;
        cout << " POST_ORDER  - 3" << endl;
        cout << " Wyjscie  - 0" << endl;
        cout << "Wpisz " << endl; cin >> user;
        switch (user) {
        case 1: Dodaj(wezel); rozmiar += 1;   break;
        case 2: IN_ORDER(wezel); cout << endl << "wcisnij cos aby zakonczyc"; cin >> x; break;
        case 3: POST_ORDER(wezel); cout << endl << "wcisnij cos aby zakonczyc"; cin >> x; break;
        }
    }



    return 0;
}
