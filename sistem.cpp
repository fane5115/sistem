#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

using namespace std;

class Nod;

typedef vector<Nod> Strat;

class Nod {

private:
    double iesireNod;
    vector<double> pondereNod;
    static double alocarePondere();
    unsigned indexNod;
    static double func(double val);

public:
    Nod(unsigned nrIesiri, unsigned nrNod);
    void setIesireNod(double val);
    double getIesireNod();
    vector<double> getPondere();
    void legatura( Strat stratAnterior);

};

void Nod::setIesireNod(double val) {
    iesireNod = val; 
}

double Nod::getIesireNod() {
    return iesireNod; 
}

vector<double> Nod::getPondere() {
    return pondereNod; 
}

Nod::Nod(unsigned nrIesiri, unsigned nrNod) {
    for (unsigned c = 0; c < nrIesiri; c++) {
        pondereNod.push_back(alocarePondere()); //adaug o pondere aleatoare pentru fiecare legatura
    }

    this->indexNod = nrNod; //memorez indexul nodului pentru a sti ce pondere folosesc
}

void Nod::legatura( Strat stratAnterior) {
    double sum = 0.0;

    for (unsigned n = 0; n < stratAnterior.size(); n++) {
        sum += stratAnterior[n].getIesireNod() * stratAnterior[n].pondereNod[indexNod]; //calculez iesirea nodului
    }

    setIesireNod(Nod::func(sum)); //trec iesirea prin filtrul functiei apoi o atribui
}

double Nod::alocarePondere() {
    return (double(rand()) / double(RAND_MAX)) * (2.0) - 1.0; //returneaza un numar aleator intre (-1.0, 1.0)
}

double Nod::func(double val) {
    return (val >= 1) ? 1.0 : 0.0;
}

class Sistem {

private:
    vector<Strat> straturi; //declaram un vector de straturi fiecare strat avand un numar variabil de noduri

public:
    Sistem( vector<unsigned> info_straturi);
    void legatura( vector<double> intrari);
    void informatii_sistem();

};

Sistem::Sistem( vector<unsigned> info_straturi) {
    unsigned numarStraturi = info_straturi.size();

    for (unsigned nrStrat = 0; nrStrat < numarStraturi; nrStrat++) {
        straturi.push_back(Strat()); //adaug in vector un strat
        unsigned nrIesiri = nrStrat == info_straturi.size() - 1 ? 0 : info_straturi[nrStrat + 1]; // verific cate iesiri o sa am in functie de numarul de noduri din stratul urmator

        for (unsigned nrNod = 0; nrNod < info_straturi[nrStrat]; nrNod++) {
            straturi.back().push_back(Nod(nrIesiri, nrNod)); //creez pe ultimul strat adaugat noduri 
        }
    }
}

void Sistem::legatura( vector<double> intrari) {

    for (unsigned i = 0; i < intrari.size(); i++) {
        straturi[0][i].setIesireNod(intrari[i]); //pentru primul strat setez iesirea nodurilor cu o valoare cunoscuta
    }

    for (unsigned nrStrat = 1; nrStrat < straturi.size(); nrStrat++) {
        Strat& stratAnterior = straturi[nrStrat - 1];

        for (unsigned n = 0; n < straturi[nrStrat].size(); n++) {
            straturi[nrStrat][n].legatura(stratAnterior); //calculez iesirea nodului in functie de stratul anterior
        }
    }
}

void Sistem::informatii_sistem() {
    cout << "\n\nSistemul are " << straturi.size() << " straturi. \n";

    cout << "---------------------------------------------------------------";
    cout << "\nStratul de intrare are " << straturi[0].size() << " noduri.\n";
    for (unsigned i = 0; i < straturi[0].size(); i++) {
        cout << "\nNodul " << i + 1 << " are: \n";
        cout << "Iesire: " << straturi[0][i].getIesireNod() << "\n";
        for (unsigned j = 0; j < straturi[0][i].getPondere().size(); j++) {
            cout << "Pondere" << j + 1 << ": " << straturi[0][i].getPondere()[j] << "\n";
        }
    }
    
    for (unsigned i = 1; i < straturi.size() - 1; i++) {
        cout << "---------------------------------------------------------------";
        cout << "\nStratul " << i << " ascuns are " << straturi[i].size() << " noduri.\n";
        for (unsigned j = 0; j < straturi[i].size(); j++) {
            cout << "\nNodul " << j + 1 << " are: \n";
            cout << "Iesire: " << straturi[i][j].getIesireNod() << "\n";
            for (unsigned k = 0; k < straturi[i][j].getPondere().size(); k++) {
                cout << "Pondere" << k + 1 << ": " << straturi[i][j].getPondere()[k] << "\n";
            }
        }
    }

    cout << "---------------------------------------------------------------";
    cout << "\nStratul de iesire are " << straturi[straturi.size() - 1].size() << " noduri.\n";
    for (unsigned i = 0; i < straturi[straturi.size() - 1].size(); i++) {
        cout << "\nNodul " << i + 1 << " are: \n";
        cout << "Iesire: " << straturi[straturi.size() - 1][i].getIesireNod() << "\n";
        for (unsigned j = 0; j < straturi[straturi.size() - 1][i].getPondere().size(); j++) {
            cout << "Pondere" << j + 1 << ": " << straturi[straturi.size() - 1][i].getPondere()[j] << "\n";
        }
    }
}

int main() {
    unsigned Q, P;
    vector<unsigned> info_straturi;
    cout << "Introduceti numarul de straturi: ";
    cin >> Q;
    int nr = 1;
    while (Q--) {
        cout << "Introduceti numarul de noduri de pe stratul " << nr << " : ";
        cin >> P;
        info_straturi.push_back(P);
        nr++;
    }

        
    Sistem sist(info_straturi);


    vector<double> intrari(info_straturi[0]);
    cout << "Introduceti valori pentru intrari: \n";
    for (unsigned i = 0; i < info_straturi[0]; i++) {
        cout << "Intrarea " << i + 1 << ": ";
        cin >> intrari[i];
    }

    sist.legatura(intrari);
    
    sist.informatii_sistem();
}
