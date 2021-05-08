#include<iostream>
#include <string>
#include <vector>
#include "Header.h"
#include <map>

int main(int argc, char* argv[])
{
    cout << "Introduceti de la tastatura numele dvs. de utilizator: ";
    string nume;
    getline(cin, nume);
    Nume n(nume);
    n.txtToString();
    if (n.verificare() == 1)  n.scriere();
    else {
        ListaTabele lt;
        lt.countTables();
        lt.txtToString();
    }
    cout << "Doriti sa scrieti comenzile de la tastatura? Daca da, scrieti 1 si dati enter. Daca nu, scrieti orice si dati enter.";
    string opt;
    cin >> opt;
    if (opt != "1") {
        PrimireARGV a(argv[1]);
        int i = 0;
        a.deschideFisier(i);
        int count = 0;
        for (int j = 0; j < i; j++)
        {
            SeparareComanda i1(a.getComanda(j));
            i1.impartireCuvinte();
            count++;
        }
    }
    else {
        while (1) {
            SeparareComanda i2;
            cin >> i2;
            i2.impartireCuvinte();
        }
    }

    ListaComenzi a1("1","Comanda 1"), a2("2","Comanda 2"), a3("3","Comanda 3");

    map<string, ListaComenzi> LC; map<string, ListaComenzi>::iterator itm;
    LC.insert(pair<string, ListaComenzi>(a1.getId(), a1));
    LC.insert(pair<string, ListaComenzi>(a2.getId(), a2));
   LC.insert(pair<string, ListaComenzi>(a3.getId(), a3));
    for (itm = LC.begin(); itm != LC.end(); itm++)
        cout << "\n" << itm->first << "----" << (*itm).second;

    ListaTabele listat;
    Nume* pNume[2];
    ListaComenzi lista;
    pNume[0] = &listat;
    pNume[1] = &lista;
    
}