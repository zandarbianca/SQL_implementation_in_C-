#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<list>
using namespace std;

class Abstract {
protected:
	int dimenisune;
public:
	virtual int getDimensiune() = 0;
};

class Ajutor {
public:
	int dim;
	char** coloane;
	Ajutor(char* col)
	{
		setColoane(col);
	}
	void setColoane(char* col)
	{
		char* temp = new char[strlen(col) + 1];
		strcpy(temp, col);
		if (col != nullptr)
		{
			if (this->coloane != nullptr)
				delete[] this->coloane;
			const char s[7] = " ,()";
			char* cuv = nullptr;
			int nrcuv = 0;
			int dimensiune = 0;
			cuv = strtok(col, s);
			while (cuv != NULL)			//numaram cuvintele
			{
				dimensiune++;
				cuv = strtok(NULL, s);
			}
			this->coloane = new char* [dimensiune + 1];		//alocare spatiu vector de cuvinte
			strcpy(col, temp);
			if (temp != NULL)
			{
				delete[] temp;
			}
			cuv = strtok(col, s);
			while (cuv != NULL)									//copiem cuvintele in vector si le separam
			{
				this->coloane[nrcuv] = new char[strlen(cuv) + 1];
				strcpy(this->coloane[nrcuv], cuv);
				nrcuv++;
				cuv = strtok(NULL, s);
			}
			this->dim = dimensiune;
		}
	}
};

class CreateFisier//public Abstract
{
	string nume;
	char** coloane = nullptr;
	string* comenzi = nullptr; //"1"
	int dim = 0;
public:
	CreateFisier(char** coloane, int dimensiune, char* nume_tabel) {
		this->coloane = coloane;
		this->dim = dimensiune;
		this->nume = nume_tabel;
		//nume = nume + ".txt";
	}
	void transfer() {
		comenzi = new string[dim];
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < strlen(coloane[i]); j++)
			{
				comenzi[i] += coloane[i][j];
			}
		}
	}
	int getDimensiune()
	{
		return this->dim;
	}
	void creareFisier() {
		ofstream fisier;
		fisier.open(nume + ".txt", ios::out | ios::trunc);
		if (fisier.is_open()) {
			for (int i = 0; i < dim; i++)
			{
				fisier << comenzi[i] << endl;
			}
			fisier.close();
		}
		ofstream file;
		file.open(nume + "_date", ios::binary | ios::trunc);
		file.close();
	}
};

class VerificaNume {
	string numeTabel;
public:
	VerificaNume(char* numele) {
		this->numeTabel = numele;

	}

	int existaTabel() {
		string rand;
		int ok = 0;
		ifstream file("Tabele.txt");
		while (getline(file, rand)) {
			if (rand == numeTabel) ok = 1;
		}
		return ok;
	}


};

class PrimireARGV {
	string numeFisier = "";
	string* comanda = nullptr;
public:
	PrimireARGV(char* nume)
	{
		string temp(nume);
		this->numeFisier = temp;
	}
	void deschideFisier(int& i)
	{
		string x;
		i = 0;
		ifstream fin(this->numeFisier, ios::in);
		while (!fin.eof())
		{

			getline(fin, x);
			i++;
		}
		this->comanda = new string[i];
		fin.clear();
		fin.seekg(0);
		int j = 0;
		while (!fin.eof())
		{
			getline(fin, this->comanda[j]);
			j++;
		}
	}
	string getComanda(int index)
	{
		return comanda[index];
	}

};

class Verificare
{
	char* comanda = nullptr;
public:
	Verificare(char* com)
	{
		if (com != nullptr)
		{
			this->comanda = new char[strlen(com) + 2];
			int d = strlen(com);
			strcpy(this->comanda, com);
		}
	}

	int verif()
	{
		int d = strlen(this->comanda);
		int deschise = 0, ok = 0;
		string s;
		for (int i = 0; i < d; i++)
		{
			s = s + this->comanda[i];
		}
		for (int i = 0; i < d; i++)
		{
			if (s[i] == '(')
			{
				deschise++;
			}
			else if (s[i] == ')')
				deschise--;
		}
		if (deschise == 0)
			ok = 1;
		else ok = 0;
		return ok;
	}
	~Verificare()
	{
		if (this->comanda != NULL)
			delete[] this->comanda;
	}

};

class Produse {
private:
	char nume[50];
	int* stocuriMagazin = nullptr;
	int nrMagazine = 0;
public:
	Produse() {
		strcpy(this->nume, "Nume");
	}
	Produse(const char* nume, int* stocuri, int nrMagazine) {
		strcpy(this->nume, nume);
		this->nrMagazine = nrMagazine;
		this->stocuriMagazin = new int[this->nrMagazine];
		for (int i = 0; i < nrMagazine; i++) {
			this->stocuriMagazin[i] = stocuri[i];
		}
	}
	Produse(const Produse& p) {
		strcpy(this->nume, p.nume);
		this->nrMagazine = p.nrMagazine;
		if (this->stocuriMagazin != nullptr) delete[] this->stocuriMagazin;
		this->stocuriMagazin = new int[p.nrMagazine];
		for (int i = 0; i < p.nrMagazine; i++) {
			this->stocuriMagazin[i] = p.stocuriMagazin[i];
		}
	}
	~Produse() {
		if (this->stocuriMagazin != nullptr) delete[] this->stocuriMagazin;
	}
	int getTotalStoc() {
		int stocTotal = 0;
		for (int i = 0; i < this->nrMagazine; i++) stocTotal = stocTotal + this->stocuriMagazin[i];
		return stocTotal;
	}
	char* getNumeProdus() {
		return this->nume;
	}
	int getNrMag() {
		return this->nrMagazine;
	}
	int getStocMagazin(int index) {
		if (index < 0 || index > this->nrMagazine) cout << endl << "Index gresit!";
		else return this->stocuriMagazin[index];
	}
	void changeStoc(int index, int value) {
		if (index < 0 || index>this->nrMagazine) cout << endl << "Index gresit!";
		else {
			this->stocuriMagazin[index] = value;
		}
	}
	void schimbaNume(const char* numeNouMagazin) {
		if (strlen(numeNouMagazin) > 49) cout << "Nume prea lung";
		else strcpy(this->nume, numeNouMagazin);
	}
	Produse operator+(int valoare) {
		int* newStocuri = new int[this->nrMagazine + 1];
		for (int i = 0; i < this->nrMagazine; i++) {
			newStocuri[i] = this->stocuriMagazin[i];
		}
		newStocuri[this->nrMagazine] = valoare;
		if (this->stocuriMagazin != NULL) delete[] this->stocuriMagazin;
		this->stocuriMagazin = newStocuri;
		this->nrMagazine += 1;
		return *this;
	}
	Produse operator=(Produse fc) {
		strcpy(this->nume, fc.nume);
		if (this->stocuriMagazin != NULL) delete[] this->stocuriMagazin;
		this->stocuriMagazin = new int[fc.nrMagazine];
		for (int i = 0; i < fc.nrMagazine; i++)	this->stocuriMagazin[i] = fc.stocuriMagazin[i];
		this->nrMagazine = fc.nrMagazine;
		return *this;
	}

	explicit operator int() {
		return getTotalStoc();
	}

	int& operator[](int index) {
		if (index >= 0 && index <= this->nrMagazine)
			return this->stocuriMagazin[index];
		else
			cout << "Index gresit";
	}

	friend ostream& operator<<(ostream& consola, Produse& p) {
		consola << endl << "------------------------";
		consola << endl << "Nume: " << p.getNumeProdus();
		consola << endl << "Stocuri: " << p.getTotalStoc();
		consola << endl << "Nr Magazine  " << p.getNrMag();
		return consola;
	}

	friend void operator>>(istream& in, Produse& p) {
		cout << endl << "------------------------";
		cout << endl << "Nume Produs: ";
		in.getline(p.nume, 50);
		cout << endl << "Numar de magazine: ";
		in >> p.nrMagazine;
		p.stocuriMagazin = new int[p.nrMagazine];
		for (int i = 0; i < p.nrMagazine; i++) {
			cout << "Stocul magazinului " << i + 1 << " = ";
			in >> p.stocuriMagazin[i];
		}
	}

};
bool operator>(Produse p1, Produse p2) {
	if (p1.getTotalStoc() > p2.getTotalStoc())return true;
	else return false;
}

class Tabel {
	const int id;
	string numeTabela;
	static int nrTabela;
	int nrColoane;
public:

	Tabel() : id(nrTabela)
	{
		this->numeTabela = "";
		this->nrColoane = 0;
		nrTabela++;
	}

	Tabel(string nume) : id(nrTabela)
	{
		this->numeTabela = nume;
		nrTabela++;
	}

	Tabel(string nume, int numar_c) : id(nrTabela)
	{
		this->numeTabela = nume;
		this->nrColoane = numar_c;
		nrTabela++;
	}

	Tabel(const Tabel& t) : id(nrTabela)
	{
		this->numeTabela = t.numeTabela;
		this->nrColoane = t.nrColoane;
	}

	string getNumeTabel()
	{
		return this->numeTabela;
	}

	int getNrColoane()
	{
		return this->nrColoane;
	}

	void setNumeTabela(string numeT)
	{
		if (numeT != "")
			this->numeTabela = numeT;
	}

	void setNrColoane(int nr)
	{
		if (nr != 0)
			this->nrColoane = nr;
	}

	friend ostream& operator<<(ostream& consola, Tabel& tab)
	{

		consola << "Nume tabela: " << tab.numeTabela << endl;
		consola << "Numar tabela: " << tab.nrTabela << endl;
		consola << "Numar coloane: " << tab.nrColoane << endl;

		return consola;
	}

	friend istream& operator>>(istream& input, Tabel& tab)
	{

		cout << "Nume tabela: ";
		input >> tab.numeTabela;
		cout << "Numar tabela: ";
		input >> tab.nrTabela;
		cout << "Numar coloane: ";
		input >> tab.nrColoane;

		return input;
	}

	Tabel operator+(const Tabel& t)
	{
		this->nrColoane += t.nrColoane;
		return *this;
	}

	void operator=(Tabel& t)
	{
		this->numeTabela = t.numeTabela;
		this->nrTabela = t.nrTabela;
		this->nrColoane = t.nrColoane;
	}

	bool operator==(Tabel& t)
	{
		if (this->numeTabela == t.numeTabela && this->nrTabela == t.nrTabela && this->nrColoane == t.nrColoane)
			return true;
		else return false;
	}
};

class Coloana {
private:
	string denumireColoana;
	string* dateColoana;
	int nrInregistrari;
public:

	Coloana()
	{
		this->denumireColoana = "";
		this->dateColoana = nullptr;
		this->nrInregistrari = 0;
	}
	Coloana(string denumireColoana, int nrInregistrari, string* dateColoana)
	{
		if (denumireColoana.length() > 0)
			this->denumireColoana = denumireColoana;
		else cout << "Denumire coloana invalida";
		if (nrInregistrari > 0)
		{
			this->nrInregistrari = nrInregistrari;
			if (dateColoana != nullptr)
			{
				this->dateColoana = new string[nrInregistrari];
				for (int i = 0; i < nrInregistrari; i++)
					this->dateColoana[i] = dateColoana[i];
			}
			else cout << "Eroare la introducerea datelor din coloana";
		}
		else cout << "Numar inregistrari invalid";
	}

	Coloana(const Coloana& c)
	{
		if (denumireColoana.length() > 0)
			this->denumireColoana = c.denumireColoana;
		else cout << "Denumire coloana invalida";
		if (nrInregistrari > 0)
		{
			this->nrInregistrari = c.nrInregistrari;
			if (dateColoana != nullptr)
			{
				this->dateColoana = new string[c.nrInregistrari];
				for (int i = 0; i < c.nrInregistrari; i++)
					this->dateColoana[i] = c.dateColoana[i];
			}
			else cout << "Eroare la introducerea datelor din coloana";
		}
		else cout << "Numar inregistrari invalid";
	}

	~Coloana()
	{
		if (this->dateColoana != nullptr)
		{
			delete[]this->dateColoana;
		}
		this->dateColoana = nullptr;
	}

	friend ostream& operator<<(ostream& out, Coloana& coloana)
	{
		out << coloana.denumireColoana << endl;
		out << coloana.nrInregistrari << endl;
		for (int i = 0; i < coloana.nrInregistrari; i++)
		{
			out << coloana.dateColoana[i] << " ";
		}
		out << endl;
		return out;
	}

	string& operator[](int index) const
	{
		if (index >= 0 && index < this->nrInregistrari)
		{
			return this->dateColoana[index];
		}
	}

	const Coloana& operator=(const Coloana& coloana)
	{
		if (coloana.denumireColoana.length() > 0)
		{
			this->denumireColoana = coloana.denumireColoana;
		}
		else
			cout << "Denumire coloana invalida";

		if (coloana.nrInregistrari > 0)
		{
			this->nrInregistrari = coloana.nrInregistrari;
			if (dateColoana != nullptr)
			{
				if (this->dateColoana != nullptr)
				{
					delete[]this->dateColoana;
				}
				this->dateColoana = new string[coloana.nrInregistrari];
				for (int i = 0; i < coloana.nrInregistrari; i++)
				{
					this->dateColoana[i] = coloana.dateColoana[i];
				}
			}
			else {
				cout << "Eroare la introducerea datelor din coloana";
			}
		}
		else {
			cout << "Numar inregistrari invalid";
		}
		return *this;
	}
};

class Create : public Ajutor
{
	char* nume_tabel = nullptr;
public:
	Create(const char* nume_t, char* col) :Ajutor(col)
	{
		if (nume_t != nullptr)
		{
			if (this->nume_tabel != nullptr)
				delete[] this->nume_tabel;
			this->nume_tabel = new char[strlen(nume_t) + 1];
			strcpy(this->nume_tabel, nume_t);
		}
		else cout << "nu merge";
	}
	int getDimensiune()
	{
		return this->dim;
	}
	char getColoane()
	{
		for (int i = 0; i < dim; i++)
			for (int j = 0; j < strlen(coloane[i]); j++)
				return coloane[i][j];
	}
	int verificareTip()
	{
		int i = 1, ok = 1;
		int n = this->dim;
		while (ok == 1 && i < n)
		{
			for (i = 1; i < n; i = i + 4)
			{
				if (strcmp(this->coloane[i], "integer") != 0 && strcmp(this->coloane[i], "float") != 0 && strcmp(this->coloane[i], "text") != 0 && strcmp(this->coloane[i], "numeric") != 0)
				{
					cout << "Ati ales tipuri de date gresite " << "'" << coloane[i] << "'." << " Puteti alege doar INTEGER, NUMERIC, FLOAT sau TEXT.";
					ok = 0;
					break;
				}
			}
		}
		i = 2;
		while (ok == 1 && i < n)
		{
			for (i = 2; i < n; i = i + 4)
			{
				for (int j = 0; j < strlen(this->coloane[i]); j++)
				{
					if (!(isdigit(this->coloane[i][j])))
					{
						cout << "Ati ales dimensiuni gresite " << "'" << coloane[i] << "'." << " Dimensiunea trebuie sa fie un NUMAR.";
						ok = 0;
						break;
					}
				}
			}
		}
		i = 3;
		while (ok == 1 && i < n)
		{
			for (i = 3; i < n; i = i + 4)
			{
				for (int j = 1; j < strlen(this->coloane[i]) - 1; j++)
				{
					if (strcmp(coloane[i], "NULL") != 0 && strcmp(coloane[i], "''")!=0 && strcmp(coloane[i], "0.0") != 0)
					{
						if (!(isdigit(coloane[i][j])))
						{
							cout << "Ati ales valoare implicita gresita " << "'" << coloane[i] << "'." << " Valoarea implicita trebuie sa fie un NUMAR sau NULL.";
							ok = 0;
							break;
						}
					}
				}
			}
		}
		return ok;
	}

	friend void operator<<(ostream& output, Create& f)
	{
		output << "\n Ati ales comanda CREATE TABLE cu numele: ";
		output << f.nume_tabel << " ";
		output << "si parametrii: ";
		for (int i = 0; i < f.dim - 1; i++)
		{
			output << f.coloane[i] << ", ";
		}
		output << f.coloane[f.dim - 1] << ". ";

	}
	~Create()
	{
		for (int i = 0; i < this->dim; i++) {
			if (this->coloane[i]) delete[] this->coloane[i];
		}
		delete[] this->coloane;

		if (this->nume_tabel != NULL)
			delete[] this->nume_tabel;
	}
};


class Drop
{
	char* nume_tabel = nullptr;
public:
	void setTable(const char* nume) {
		if (nume != nullptr)
		{
			if (this->nume_tabel != nullptr)
				delete[] this->nume_tabel;
			this->nume_tabel = new char[strlen(nume) + 1];
			strcpy(this->nume_tabel, nume);
		}
	}
	Drop(const char* nume)
	{
		setTable(nume);
	}
	friend void operator<<(ostream& output, Drop& f);
	~Drop()
	{
		if (this->nume_tabel != NULL)
			delete[] this->nume_tabel;
	}
};
void operator<<(ostream& output, Drop& f) {
	output << endl << "Ati ales comanda DROP TABLE. Vom sterge tabela " << f.nume_tabel << " daca aceasta exista." << endl;
}

class StergeFisier {
	string nume;
public:
	StergeFisier(char* nume_tabel) {
		this->nume = nume_tabel;
	}
	void verificaDacaSterge()
	{
		if (remove((nume + ".txt").c_str()) != 0)
			cout << endl << "Eroare la stergerea fisierului .txt";
		else
			cout << endl << "Stergerea fisierului .txt a fost facuta.";
		if (remove((nume + "_date").c_str()) != 0)
			cout << endl << "Eroare la stergerea fisierului binar";
		else
			cout << endl << "Stergerea fisierului binar a fost facuta.";
	}
	void stergereNume() {
		ifstream f1;
		string temporar;
		f1.open("Tabele.txt");
		if (f1.is_open()) {
			ofstream temp;
			temp.open("temp.txt", ios::trunc);
			while (getline(f1, temporar)) {
				if (temporar != nume) temp << temporar << endl;
			}
			temp.close();
			f1.close();
			remove("Tabele.txt");
			rename("temp.txt", "Tabele.txt");
		}
		else cout << "Eroare la deschiderea fisierului Tabele.txt";
	}
};

class Display
{
	char* nume_tabel = nullptr;
public:

	void setTable(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->nume_tabel != nullptr)
				delete[] this->nume_tabel;
			this->nume_tabel = new char[strlen(nume) + 1];
			strcpy(this->nume_tabel, nume);
		}
	}
	Display(const char* nume)
	{
		setTable(nume);
	}
	friend void operator<<(ostream& output, Display& f);

	~Display()
	{
		if (this->nume_tabel != NULL)
			delete[] this->nume_tabel;
	}
};
void operator<<(ostream& output, Display& f) {
	output << endl << "Ati ales comanda DISPLAY TABLE. Vom afisa tabela " << f.nume_tabel << " daca aceasta exista." << endl;
}

class BazaDeDate {
	Coloana c[10];
	Produse p[10];
	Tabel* t[10];
};

class Insert :public Ajutor {
	char* nume_tabel = nullptr;
public:
	void setTable(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->nume_tabel != nullptr)
				delete[] this->nume_tabel;
			this->nume_tabel = new char[strlen(nume) + 1];
			strcpy(this->nume_tabel, nume);
		}
	}
	int getDimensiune()
	{
		return this->dim;
	}
	bool ver(int dim)
	{
		if (dim == 0)
			return false;
		else return true;
	}
	Insert(char* nume, char* comanda) :Ajutor(comanda)
	{
		setTable(nume);
	}

	friend void operator<<(ostream& output, Insert& f)
	{
		if (f.ver(f.dim))
		{
			output << "\n Ati ales comanda INSERT INTO pentru tabela cu numele: ";
			output << f.nume_tabel << " ";
			output << "si parametrii: ";
			for (int i = 0; i < f.dim - 1; i++)
			{
				output << f.coloane[i] << ", ";
			}
			output << f.coloane[f.dim - 1];
		}
		else cout << "Ati introdus nume de coloana GRESIT.";
	}
	~Insert()
	{
		for (int i = 0; i < this->dim; i++) {
			if (this->coloane[i]) delete[] this->coloane[i];
		}
		delete[] this->coloane;

		if (this->nume_tabel != NULL)
			delete[] this->nume_tabel;
	}
};

class VerificareInsert {
	string numeTabel;
	char** datele;
	string* comenzi;
	string* citire;
	int dimensiune;
	int contor;
public:
	VerificareInsert(char* nume, char** date, int dim) {
		this->numeTabel = nume;
		this->datele = date;
		this->dimensiune = dim;
	}
	void transfer() {
		comenzi = new string[this->dimensiune];
		for (int i = 0; i < this->dimensiune; i++) {
			for (int j = 0; j < strlen(this->datele[i]); j++)
			{
				this->comenzi[i] += this->datele[i][j];

			}
		}
	}
	void getRanduri() {
		int contor = 0;
		string randuri;
		ifstream file(numeTabel + ".txt");
		if (file.is_open()) {
			while (getline(file, randuri)) {
				contor++;
			}
		}
		else cout << endl << endl << " A aparut o eroare la deschiderea fisierului!" << endl << endl;
		file.close();
		this->contor = contor / 4;
	}

	int verificareCorect() {
		int ok = 1;
		if (this->dimensiune % this->contor != 0) ok = 0;
		return ok;
	}
	void scrieDate() {
		int dim = 0;
		ofstream file1(numeTabel + "_date", ios::binary | ios::app);
		for (int i = 0; i < this->dimensiune; i++) {
			dim = comenzi[i].size() + 1;
			file1.write((char*)&dim, sizeof(int));
			file1.write(comenzi[i].c_str(), dim * sizeof(char));     //aici se lasa un spatiu, grija!
		}
		file1.close();
	}
	/*void citimDate() {
		string* citire = new string[dimensiune];
		char buffer[10];
		int dim;
		ifstream file(numeTabel + "_date", ios::binary);
		for (int i = 0; i < this->dimensiune; i++) {
			file.read((char*)&dim, sizeof(int));
			file.read(buffer, dim* sizeof(char));
			citire[i] = string(buffer);
			cout << endl << dim;
			cout << endl << citire[i];
		}
		file.close();
	}*/

	int verificareTip() {

	}

};

class AfisareDisplay
{
	string numeTabel;
	string* caracteristici;
public:
	AfisareDisplay(char* nume) {
		numeTabel = nume;
	}
	void afisareFisier() {
		string rand;
		ifstream file2(numeTabel + ".txt");
		int contor = 0;
		while (getline(file2, rand)) {
			contor++;
		}
		file2.close();
		ifstream file3(numeTabel + ".txt");
		int j = 0;
		caracteristici = new string[contor];
		while (getline(file3, rand)) {
			caracteristici[j] = rand;
			j++;
		}
		file3.close();
		cout << endl << "Ati ales comanda DISPLAY pentru tabel " << numeTabel << " cu caracteristicile: ";
		for (int i = 0; i < contor; i++) {
			if (i % 4 == 0) cout << "Denumirea coloanei este " << caracteristici[i] << endl;
			else if (i % 4 == 1) cout << "Tipul datei este " << caracteristici[i] << endl;
			else if (i % 4 == 2) cout << "Marimea datei este " << caracteristici[i] << endl;
			else if (i % 4 == 3) cout << "Valoarea default este " << caracteristici[i] << endl;
		}
	}
};

class Select : public Ajutor
{
	char* nume_tabel = nullptr;
	char* cond = nullptr;
	char* param = nullptr;
	char* valoare = nullptr;
	int v = 0;
public:
	void setTable(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->nume_tabel != nullptr)
				delete[] this->nume_tabel;
			this->nume_tabel = new char[strlen(nume) + 1];
			strcpy(this->nume_tabel, nume);
		}
	}
	int verificareParametru(char* param1)
	{
		int ok = 1;
		if (strcmp(param1, "="))
			ok = 0;
		return ok;
	}
	void setParametru(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->param != nullptr)
				delete[] this->param;
			this->param = new char[strlen(nume) + 1];
			strcpy(this->param, nume);
		}
	}
	void setValoare(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->valoare != nullptr)
				delete[] this->valoare;
			this->valoare = new char[strlen(nume) + 1];
			strcpy(this->valoare, nume);
		}
	}
	void setConditie(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->cond != nullptr)
				delete[] this->cond;
			this->cond = new char[strlen(nume) + 1];
			strcpy(this->cond, nume);
		}
	}
	int getDimensiune()
	{
		return this->dim;
	}
	bool ver(int dim)
	{
		if (dim == 0)
			return false;
		else return true;
	}
	void afisare()
	{
		cout << nume_tabel << " " << cond;
	}
	Select(char* nume, char* c) :Ajutor(c)
	{
		setTable(nume);
	}
	Select(char* nume, char* c, char* conditie, char* parametru, char* val) :Ajutor(c)
	{
		setTable(nume);
		setConditie(conditie);
		setParametru(parametru);
		setValoare(val);
	}
	friend void operator<<(ostream& output, Select& f)
	{
		if (f.ver(f.dim))
		{
			if (f.cond != nullptr && f.param != nullptr && f.valoare != nullptr)
			{
				if (f.verificareParametru(f.param) == 0)
				{
					output << "Ati introdus gresit semnul.";
				}
				else
				{
					output << "\n Ati ales comanda SELECT pentru tabela cu numele: ";
					output << f.nume_tabel << " ";
					if (f.dim == 1 && f.v == 0)
					{
						output << ". Ati afisat toate coloanele ";
						output << " si conditia: ";
						output << f.cond << " " << f.param << " " << f.valoare;
					}
					else
					{
						output << ". Coloanele sunt:";
						for (int i = 0; i < f.dim - 1; i++)
						{
							output << f.coloane[i] << " , ";
						}
						output << f.coloane[f.dim - 1];
						output << " si conditia: ";
						output << f.cond << " " << f.param << " " << f.valoare;
					}
				}
			}
			else
			{
				output << "\n Ati ales comanda SELECT pentru tabela cu numele: ";
				output << f.nume_tabel << " ";
				if (f.dim == 1 && f.v == 0)
				{
					output << ". Ati afisat toate coloanele ";
				}
				else
				{
					output << ". Coloanele sunt:";
					for (int i = 0; i < f.dim; i++)
					{
						output << f.coloane[i] << " ";
					}
				}
			}
		}
		else cout << "Ati introdus numele de coloana GRESIT.";
	}
	char* operator[](int index)
	{
		if (index >= 0 && index <= this->dim)
		{
			return this->coloane[index];
		}
		else cout << "Ati ales index gresit!";

	}
};

class SelectFaraWhere {
	string* comenzi = nullptr;   //din _date binar
	int dimensiune = 0;  //cate coloane sunt in select (id,nume)
	string nume_tabel;
	string* dinBinar = nullptr;
public:
	SelectFaraWhere(char** col, int dim, char* nume)
	{
		this->dimensiune = dim;
		if (col != nullptr)
		{
			this->comenzi = new string[this->dimensiune];
			for (int i = 0; i < this->dimensiune; i++) {
				for (int j = 0; j < strlen(col[i]); j++)
				{
					comenzi[i] += col[i][j];
				}
			}
		}
		else {
			comenzi = new string[1];
			comenzi[0] = "ALL";
		}
		this->nume_tabel = nume;
	}
	void binaryToString()
	{
		char buffer[100];
		int dim = 0;
		int co = 0;
		ifstream fil(nume_tabel + "_date", ios::binary);
		while (fil.read((char*)&dim, sizeof(int)))
		{
			fil.read(buffer, dim * sizeof(char));
			co++;
		}
		fil.close();
		dinBinar = new string[co];
		ifstream fic(nume_tabel + "_date", ios::binary);
		for (int i = 0; i < co; i++)
		{
			fic.read((char*)&dim, sizeof(int));
			fic.read(buffer, dim * sizeof(char));
			dinBinar[i] = string(buffer);
		}
		fic.close();
	}
	void afisare()
	{
		int co = 0;
		string* caracteristici = nullptr;
		if (comenzi[0] == "ALL")
		{
			string rand;
			ifstream fit(nume_tabel + ".txt");
			int contor = 0;
			while (getline(fit, rand)) {
				contor++;
			}
			fit.close();
			ifstream fit1(nume_tabel + ".txt");
			int j = 0;
			caracteristici = new string[contor / 4];
			int i = 0;
			while (getline(fit1, rand)) {
				if (j % 4 == 0)
				{
					caracteristici[i++] = rand;
					j++;
				}
				else j++;
			}
			fit1.close();

			ifstream fib(nume_tabel + "_date", ios::binary);
			char buffer[100];
			int dim = 0;
			i = 0;

			while (!fib.eof())
			{
				fib.read((char*)&dim, sizeof(int));
				fib.read(buffer, dim * sizeof(char));
				co++;
			}
			fib.close();
			ofstream fib3("ComenziSelect.txt", ios::app);
			ifstream fib2(nume_tabel + "_date", ios::binary);
			for (int k = 0; k < co - 1; k++)
			{
				if (i == contor / 4) i = 0;
				fib2.read((char*)&dim, sizeof(int));
				fib2.read(buffer, dim * sizeof(char));
				fib3 << caracteristici[i] + " = " << string(buffer) << endl;
				cout << endl << caracteristici[i] + " = " << string(buffer);
				i++;
			}
			fib3 << "--------------------------------------------" << endl;
			fib3.close();
			fib2.close();
		}
		else {
			ifstream fib(nume_tabel + "_date", ios::binary);
			char buffer[100];
			int dim = 0;
			while (!fib.eof())
			{
				fib.read((char*)&dim, sizeof(int));
				fib.read(buffer, dim * sizeof(char));
				co++;
			}
			fib.close();
			co = co - 1;
			string rand;
			ifstream fit(nume_tabel + ".txt");
			int contor = 0;
			while (getline(fit, rand)) {
				contor++;
			}
			fit.close();
			ifstream fit1(nume_tabel + ".txt");
			int j = 0;
			caracteristici = new string[contor / 4];
			int i = 0;
			while (getline(fit1, rand)) {
				if (j % 4 == 0)
				{

					caracteristici[i] = rand;    //din txt luate
					i++;
					j++;
				}
				else j++;
			}
			fit1.close();
			i = contor / 4;
			int m = 0, n = 0, l = 0;
			const int x = this->dimensiune;
			int* b = nullptr; int* copieB = nullptr;
			b = new int[dimensiune];
			copieB = new int[dimensiune];

			for (int k = 0; k < i; k++)
			{
				int ok = 0;
				for (int g = 0; g < dimensiune && ok == 0; g++)
				{
					if (comenzi[g] == caracteristici[k])
					{
						ok = 1;
						b[l] = g;
						copieB[l] = g;
						l++;
					}
				}
			}

			int u = 0;
			int f = 0;
			int h = 0;
			int d = 0;
			//co=cate sunt in binar
			//contor= cate sunt in txt
			while (h < co / dimensiune) {
				while (f < co)
				{
					u = 0;
					while (u < l)
					{
						d = copieB[u];
						cout << endl << caracteristici[b[u]] << " = " << dinBinar[d];
						copieB[u] = copieB[u] + dimensiune;
						d = copieB[u];
						u++;
						f++;
					}
					h++;
				}
			}
		}
	}
};

class SelectCuWhere {
	//aici facem sa fie all
	string* coloane = nullptr;    //numele coloanelor din select
	string numeTabel;
	int nrColoane = 0;      //numarul coloanelor din select
	string conditie1;   //de ex id
	string conditie2;   //de ex 1
	string* dinBinar = nullptr;  //datele din binar
	string* caracteristici = nullptr;   //datele din txt
	int indice = 0;    //indicele pe care se gaseste conditie 1 in txt
	int* b = nullptr; int* copieB = nullptr;   //salvare indici pentru select (id,grupa,nume)==> 0,2,1
public:
	SelectCuWhere(char** col, char* nume, int dim, char* cond1, char* cond2)
	{
		this->numeTabel = nume;
		this->nrColoane = dim;
		if (col != nullptr)
		{
			this->coloane = new string[this->nrColoane];
			for (int i = 0; i < this->nrColoane; i++) {
				for (int j = 0; j < strlen(col[i]); j++)
				{
					this->coloane[i] += col[i][j];
				}
			}
		}
		else {
			this->coloane = new string[1];
			this->coloane[0] = "ALL";
		}
		this->conditie1 = cond1;
		this->conditie2 = cond2;
	}
	void binaryToString()
	{
		char buffer[100];
		int dim = 0;
		int co = 0;
		ifstream fil(this->numeTabel + "_date", ios::binary);
		while (fil.read((char*)&dim, sizeof(int)))
		{
			fil.read(buffer, dim * sizeof(char));
			co++;
		}
		fil.close();
		dinBinar = new string[co];
		ifstream fic(this->numeTabel + "_date", ios::binary);
		for (int i = 0; i < co; i++)
		{
			fic.read((char*)&dim, sizeof(int));
			fic.read(buffer, dim * sizeof(char));
			dinBinar[i] = string(buffer);
		}
		fic.close();
	}
	void txtToString()
	{
		string rand;
		ifstream fit(this->numeTabel + ".txt");
		int contor = 0;
		while (getline(fit, rand)) {
			contor++;
		}
		fit.close();
		ifstream fit1(this->numeTabel + ".txt");
		int j = 0;
		caracteristici = new string[contor / 4];
		int i = 0;
		while (getline(fit1, rand)) {
			if (j % 4 == 0)
			{
				caracteristici[i++] = rand;
				j++;
			}
			else j++;
		}
		fit1.close();
	}
	void salvareIndice()
	{
		string rand;
		ifstream fit(this->numeTabel + ".txt");
		int contor = 0;
		while (getline(fit, rand)) {
			contor++;
		}
		fit.close();
		int ok = 0;
		for (int k = 0; k < (contor / 4) && ok == 0; k++)
		{
			if (this->conditie1 == caracteristici[k])
			{
				ok = 1;
				this->indice = k;
			}
		}
	}
	void verificareExistentaInBinar()
	{
		string rand;
		ifstream fit(this->numeTabel + ".txt");
		int contor = 0;
		while (getline(fit, rand)) {
			contor++;
		}
		fit.close();
		contor = contor / 4;     //cate date avem in txt
		if (this->coloane[0] == "ALL") {
			char buffer[100];
			int dim = 0;
			int co = 0;
			ifstream fil(this->numeTabel + "_date", ios::binary);
			while (fil.read((char*)&dim, sizeof(int)))
			{
				fil.read(buffer, dim * sizeof(char));
				co++;
			}
			fil.close();
			int copieIndice = this->indice;
			int k = 0, j = 0;
			while (this->indice < co) {
				if (this->dinBinar[indice] == this->conditie2)
				{
					k = indice - copieIndice;
					int d = contor / indice;
					j = k;
					for (int i = 0; i < contor; i++) {
						cout << endl << caracteristici[i] << " = " << dinBinar[j];
						j = j + 1;
					}
				}
				k = indice - copieIndice;
				this->indice = this->indice + contor;

			}
		}
		else {

			b = new int[this->nrColoane];    //vector de indici din select
			copieB = new int[this->nrColoane];
			int l = 0;

			for (int k = 0; k < this->nrColoane; k++)
			{
				int ok = 0;
				for (int g = 0; g < contor && ok == 0; g++)
					for (int g = 0; g < contor && ok == 0; g++)
					{
						if (this->coloane[k] == caracteristici[g])
						{
							ok = 1;
							b[l] = g;
							copieB[l] = g;
							l++;
						}
					}
			}
			for (int i = 0; i < l; i++)
				cout << endl << b[i] << " " << copieB[i] << endl;
			char buffer[100];
			int dim = 0;
			int co = 0;
			ifstream fil(this->numeTabel + "_date", ios::binary);
			while (fil.read((char*)&dim, sizeof(int)))
			{
				fil.read(buffer, dim * sizeof(char));
				co++;
			}
			fil.close();
			int u = 0;
			int d = 0;
			cout << contor;
			while (this->indice < co)
			{
				if (this->dinBinar[indice] == this->conditie2)
				{
					u = 0;
					d = indice - (indice / contor) + 1;
					while (u < l)
					{
						cout << endl << caracteristici[b[u]] << " = " << dinBinar[d];
						u++; d = d + (copieB[u] - copieB[u - 1]);
					}
				}
				indice = indice + contor;
			}
		}
	}
};

class UpdateBun {
	string numeTabel;
	string conditieSet1;
	string conditieSet2;
	string conditieWhere1;
	string conditieWhere2;
	string* dinBinar = nullptr;  //datele din binar
	string* caracteristici = nullptr; //datele din txt
	int indiceWhere = 0;
	int indiceSet = 0;
	int dimensiuneBinar;
	int dimensiuneText;
public:
	UpdateBun(char* nume, char* conditieset1, char* conditieset2, char* conditiewhere1, char* conditiewhere2) {
		this->numeTabel = nume;
		this->conditieSet1 = conditieset1;
		this->conditieSet2 = conditieset2;
		this->conditieWhere1 = conditiewhere1;
		this->conditieWhere2 = conditiewhere2;
	}
	void binaryToString()
	{
		char buffer[100];
		int dim = 0;
		dimensiuneBinar = 0;
		ifstream fil(this->numeTabel + "_date", ios::binary);
		while (fil.read((char*)&dim, sizeof(int)))
		{
			fil.read(buffer, dim * sizeof(char));
			dimensiuneBinar++;
		}
		fil.close();
		dinBinar = new string[dimensiuneBinar];
		ifstream fic(this->numeTabel + "_date", ios::binary);
		for (int i = 0; i < dimensiuneBinar; i++)
		{
			fic.read((char*)&dim, sizeof(int));
			fic.read(buffer, dim * sizeof(char));
			dinBinar[i] = string(buffer);
		}
		fic.close();
	}
	void txtToString()
	{
		string rand;
		ifstream fit(this->numeTabel + ".txt");
		dimensiuneText = 0;
		while (getline(fit, rand)) {
			dimensiuneText++;
		}
		fit.close();
		ifstream fit1(this->numeTabel + ".txt");
		int j = 0;
		caracteristici = new string[dimensiuneText / 4];
		int i = 0;
		while (getline(fit1, rand)) {
			if (j % 4 == 0)
			{
				caracteristici[i++] = rand;
				j++;
			}
			else j++;
		}
		fit1.close();
	}
	void salvareIndice()
	{
		int ok = 0;
		for (int k = 0; k < (dimensiuneText / 4) && ok == 0; k++)
		{
			if (this->conditieWhere1 == caracteristici[k])
			{
				ok = 1;
				this->indiceWhere = k;
			}
		}
		ok = 0;
		for (int k = 0; k < (dimensiuneText / 4) && ok == 0; k++)
		{
			if (this->conditieSet1 == caracteristici[k])
			{
				ok = 1;
				this->indiceSet = k;
			}
		}
	}
	void schimbariFisier() {
		while (this->indiceWhere < dimensiuneBinar) {
			if (dinBinar[indiceWhere] == this->conditieWhere2) {
				dinBinar[indiceSet] = conditieSet2;
			}
			indiceWhere = indiceWhere + dimensiuneText / 4;
			indiceSet = indiceSet + dimensiuneText / 4;
		}
		cout << endl;
	}
	void scrieDate() {
		int dim = 0;
		ofstream file1(numeTabel + "_date", ios::binary | ios::trunc);
		for (int i = 0; i < this->dimensiuneBinar; i++) {
			dim = dinBinar[i].size() + 1;
			file1.write((char*)&dim, sizeof(int));
			file1.write(dinBinar[i].c_str(), dim * sizeof(char));     //aici se lasa un spatiu, grija!
		}
		file1.close();
	}

};

class Update {
	char* nume_tabel = nullptr;
	char* col1 = nullptr;
	char* param1 = nullptr;
	char* valoare1 = nullptr;
	char* col2 = nullptr;
	char* param2 = nullptr;
	char* valoare2 = nullptr;
public:
	void setTable(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->nume_tabel != nullptr)
				delete[] this->nume_tabel;
			this->nume_tabel = new char[strlen(nume) + 1];
			strcpy(this->nume_tabel, nume);
		}
	}
	void setColoana1(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->col1 != nullptr)
				delete[] this->col1;
			this->col1 = new char[strlen(nume) + 1];
			strcpy(this->col1, nume);
		}
	}
	int verificareParametru(char* param1)
	{
		int ok = 1;
		if (strcmp(param1, "!=") != 0 && strcmp(param1, "=") != 0 && strcmp(param1, ">") != 0 &&
			strcmp(param1, ">=") != 0 && strcmp(param1, "<") != 0 && strcmp(param1, "<=") != 0)
			ok = 0;
		return ok;
	}
	void setParametru1(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->param1 != nullptr)
				delete[] this->param1;
			this->param1 = new char[strlen(nume) + 1];
			strcpy(this->param1, nume);
		}
	}
	void setValoare1(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->valoare1 != nullptr)
				delete[] this->valoare1;
			this->valoare1 = new char[strlen(nume) + 1];
			strcpy(this->valoare1, nume);
		}
	}
	void setColoana2(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->col2 != nullptr)
				delete[] this->col2;
			this->col2 = new char[strlen(nume) + 1];
			strcpy(this->col2, nume);
		}
	}
	void setParametru2(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->param2 != nullptr)
				delete[] this->param2;
			this->param2 = new char[strlen(nume) + 1];
			strcpy(this->param2, nume);
		}
	}
	void setValoare2(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->valoare2 != nullptr)
				delete[] this->valoare2;
			this->valoare2 = new char[strlen(nume) + 1];
			strcpy(this->valoare2, nume);
		}
	}
	Update(char* nume, char* c1, char* p1, char* v1, char* c2, char* p2, char* v2)
	{
		setTable(nume);
		setColoana1(c1);
		setParametru1(p1);
		setValoare1(v1);
		setColoana2(c2);
		setParametru2(p2);
		setValoare2(v2);
	}
	friend void operator<<(ostream& output, Update& f)
	{
		if (f.verificareParametru(f.param1) == 0 && f.verificareParametru(f.param2) == 0)
		{
			output << "Ati introdus gresit semnul.";
		}
		else
		{
			output << "\n Ati ales comanda UPDATE TABLE cu numele: ";
			output << f.nume_tabel;
			output << ". Faceti update la: ";
			output << f.col1 << " " << f.param1 << " " << f.valoare1 << " ";
			output << "si conditia: ";
			output << f.col2 << " " << f.param2 << " " << f.valoare2;
		}
	}

	~Update()
	{
		if (this->nume_tabel != NULL)
			delete[] this->nume_tabel;
		if (this->col1 != NULL)
			delete[] this->col1;
		if (this->col2 != NULL)
			delete[] this->col2;
		if (this->param1 != NULL)
			delete[] this->param1;
		if (this->param2 != NULL)
			delete[] this->param2;
		if (this->valoare1 != NULL)
			delete[] this->valoare1;
		if (this->valoare2 != NULL)
			delete[] this->valoare2;
	}
};

class Delete {
	char* nume_tabel = nullptr;
	char* col = nullptr;
	char* param = nullptr;
	char* valoare = nullptr;
public:
	void setTable(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->nume_tabel != nullptr)
				delete[] this->nume_tabel;
			this->nume_tabel = new char[strlen(nume) + 1];
			strcpy(this->nume_tabel, nume);
		}
	}
	void setColoana1(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->col != nullptr)
				delete[] this->col;
			this->col = new char[strlen(nume) + 1];
			strcpy(this->col, nume);
		}
	}
	int verificareParametru()
	{
		int ok = 1;
		if (strcmp(this->param, "!=") != 0 && strcmp(this->param, "=") != 0 && strcmp(this->param, ">") != 0 &&
			strcmp(this->param, ">=") != 0 && strcmp(this->param, "<") != 0 && strcmp(this->param, "<=") != 0)
			ok = 0;
		return ok;
	}
	void setParametru(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->param != nullptr)
				delete[] this->param;
			this->param = new char[strlen(nume) + 1];
			strcpy(this->param, nume);
		}
	}
	void setValoare(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->valoare != nullptr)
				delete[] this->valoare;
			this->valoare = new char[strlen(nume) + 1];
			strcpy(this->valoare, nume);
		}
	}
	Delete(char* nume, char* coloana, char* parametru, char* val)
	{
		setTable(nume);
		setColoana1(coloana);
		setParametru(parametru);
		setValoare(val);
	}
	friend void operator<<(ostream& output, Delete& f)
	{
		if (f.verificareParametru() == 0)
		{
			output << "Ati introdus gresit semnul.";
		}
		else
		{
			output << "\n Ati ales comanda DELETE TABLE cu numele: ";
			output << f.nume_tabel << " ";

			output << "si conditia: ";
			output << f.col << " " << f.param << " " << f.valoare;
		}
	}
	~Delete()
	{
		if (this->nume_tabel != NULL)
			delete[] this->nume_tabel;
		if (this->col != NULL)
			delete[] this->col;
		if (this->param != NULL)
			delete[] this->param;
		if (this->valoare != NULL)
			delete[] this->valoare;
	}
};

class DeleteBun {
	string numeTabel;
	string conditieWhere1;
	string conditieWhere2;
	string* dinBinar = nullptr;  //datele din binar
	string* caracteristici = nullptr; //datele din txt
	int dimensiuneText = 0;
	int dimensiuneBinar = 0;
	int indice = 0;
public:
	DeleteBun(char* nume, char* conditieWhere1, char* conditieWhere2) {
		this->numeTabel = nume;
		this->conditieWhere1 = conditieWhere1;
		this->conditieWhere2 = conditieWhere2;
	}
	void binaryToString()
	{
		char buffer[100];
		int dim = 0;
		dimensiuneBinar = 0;
		ifstream fil(this->numeTabel + "_date", ios::binary);
		while (fil.read((char*)&dim, sizeof(int)))
		{
			fil.read(buffer, dim * sizeof(char));
			dimensiuneBinar++;
		}
		fil.close();
		dinBinar = new string[dimensiuneBinar];
		ifstream fic(this->numeTabel + "_date", ios::binary);
		for (int i = 0; i < dimensiuneBinar; i++)
		{
			fic.read((char*)&dim, sizeof(int));
			fic.read(buffer, dim * sizeof(char));
			dinBinar[i] = string(buffer);
		}
		fic.close();
	}
	void txtToString()
	{
		string rand;
		ifstream fit(this->numeTabel + ".txt");
		dimensiuneText = 0;
		while (getline(fit, rand)) {
			dimensiuneText++;
		}
		fit.close();
		ifstream fit1(this->numeTabel + ".txt");
		int j = 0;
		caracteristici = new string[dimensiuneText / 4];
		int i = 0;
		while (getline(fit1, rand)) {
			if (j % 4 == 0)
			{
				caracteristici[i++] = rand;
				j++;
			}
			else j++;
		}
		fit1.close();
	}
	void salvareIndice()
	{
		int ok = 0;
		for (int k = 0; k < (dimensiuneText / 4) && ok == 0; k++)
		{
			if (this->conditieWhere1 == caracteristici[k])
			{
				ok = 1;
				this->indice = k;
			}
		}
	}
	void schimbariString() {
		int ok = 0;
		while (this->indice < this->dimensiuneBinar)
		{
			if (this->dinBinar[this->indice] == this->conditieWhere2)
			{
				int catePozitiiInSpate = this->indice % (this->dimensiuneText / 4);
				int i = this->indice;
				i = i - catePozitiiInSpate;
				for (int j = i; j < i + (this->dimensiuneText / 4); j++)
				{
					this->dinBinar[j] = "~";
				}
				this->indice = this->indice + (this->dimensiuneText / 4);
				ok = 1;
			}
			else this->indice = this->indice + (this->dimensiuneText / 4);
		}
		if (ok == 0)
		{
			cout << "Nu au fost gasite elemente cu conditia data";
		}
	}
	void scrieDate() {
		int dim = 0;
		ofstream file1(numeTabel + "_date", ios::binary | ios::trunc);
		for (int i = 0; i < this->dimensiuneBinar; i++) {
			if (dinBinar[i] != "~") {
				dim = dinBinar[i].size() + 1;
				file1.write((char*)&dim, sizeof(int));
				file1.write(dinBinar[i].c_str(), dim * sizeof(char));     //aici se lasa un spatiu, grija!
			}
		}
		file1.close();
	}
};

class Import {
	string numeTabel;
	string numeFisier;
	string* comenzi;
	int dimensiuneComenzi = 0;
	char* numeChar;
	char* comanda;
	char* numeTabelChar;
public:
	Import(char* numeTabel, char* numeFisier) {
		this->numeTabel = numeFisier;
		this->numeFisier = numeTabel;
	}
	void transferChar() {
		numeChar = new char[numeTabel.size() + 1];
		strcpy(numeChar, numeTabel.c_str());
		numeTabelChar = new char[numeFisier.size() + 1];
		strcpy(numeTabelChar, numeFisier.c_str());
	}
	void citireDateDinFisier() {
		string rand;
		ifstream f1(this->numeTabel);
		while (getline(f1, rand)) {
			dimensiuneComenzi++;
		}
		f1.close();
		comenzi = new string[dimensiuneComenzi];
		ifstream f2(this->numeTabel);
		int i = 0;
		while (getline(f2, rand)) {
			comenzi[i++] = rand;
		}
		f2.close();
		for (i = 0; i < dimensiuneComenzi; i++) {
			cout << endl << comenzi[i];
		}
	}
	void folosireInsert() {
		for (int i = 0; i < dimensiuneComenzi; i++) {
			comanda = new char[comenzi[i].size() + 1];
			strcpy(comanda, comenzi[i].c_str());
			Insert i1(numeTabelChar, comanda);
			VerificareInsert vi(numeTabelChar, i1.coloane, i1.getDimensiune());
			vi.getRanduri();
			vi.transfer();
			if (vi.verificareCorect() == 1) {
				vi.scrieDate();
			}
		}
	}
};

class SeparareComanda {
	string denumire = "";
public:
	SeparareComanda() {
		this->denumire = "";
	}

	SeparareComanda(string comanda) {
		this->denumire = comanda;
	}

	void setDenumire(string nouaDenumire) {
		this->denumire = nouaDenumire;
	}
	string getDenumire()
	{
		return this->denumire;
	}
	void impartireCuvinte()  //functia de verificare/interpretare a comenzii
	{
		const char s[] = " ";    //elementele de separare a cuvintelor
		char* comanda = new char[this->denumire.size() + 1];  //alocare dimensiune comanda intreaga 
		strcpy(comanda, denumire.c_str());   //denumire devine char din string si o copiem in comanda
		char* cuv = nullptr;
		int nrcuv = 0;
		int dimensiune = 0;
		cuv = strtok(comanda, " ");
		while (cuv != NULL)			//numaram cuvintele
		{
			dimensiune++;
			cuv = strtok(NULL, s);
		}

		char** cuvinte = new char* [dimensiune + 1];		//alocare spatiu vector de cuvinte
		strcpy(comanda, denumire.c_str());					//recopiere comanda
		cuv = strtok(comanda, " ");

		while (cuv != NULL)									//copiem cuvintele in vector si le separam
		{
			cuvinte[nrcuv] = new char[strlen(cuv) + 1];
			strcpy(cuvinte[nrcuv], cuv);
			nrcuv++;
			cuv = strtok(NULL, s);
		}
		ofstream fis;
		if (dimensiune == 4 && strcmp(cuvinte[0], "SELECT") == 0 && strcmp(cuvinte[2], "FROM") == 0)
		{
			Verificare v1(cuvinte[1]);
			VerificaNume vn(cuvinte[3]);
			if (vn.existaTabel() == 1) {
				if (v1.verif() == 1)
				{
					Select s1(cuvinte[3], cuvinte[1]);
					SelectFaraWhere sfw(s1.coloane, s1.getDimensiune(), cuvinte[3]);
					sfw.binaryToString();
					sfw.afisare();
					cout << s1;
				}
				else cout << "Numar de paranteze gresite!";
			}
			else cout << endl << "Tabelul nu exista" << endl;
		}
		else if (dimensiune == 8 && strcmp(cuvinte[0], "SELECT") == 0 && strcmp(cuvinte[2], "FROM") == 0 && strcmp(cuvinte[4], "WHERE") == 0)
		{
			Verificare v1(cuvinte[1]);
			VerificaNume vn(cuvinte[3]);
			if (vn.existaTabel() == 1) {
				if (v1.verif() == 1)
				{
					Select s2(cuvinte[3], cuvinte[1], cuvinte[5], cuvinte[6], cuvinte[7]);
					s2.verificareParametru(cuvinte[6]);
					SelectCuWhere scw(s2.coloane, cuvinte[3], s2.getDimensiune(), cuvinte[5], cuvinte[7]);
					scw.binaryToString();
					scw.txtToString();
					scw.salvareIndice();
					scw.verificareExistentaInBinar();
					cout << s2;
				}
				else cout << "Numar de paranteze gresite!" << endl;
			}
			else cout << endl << "Tabelul nu exista" << endl;
		}
		else if (dimensiune == 5 && strcmp(cuvinte[0], "INSERT") == 0 && strcmp(cuvinte[1], "INTO") == 0 && strcmp(cuvinte[3], "VALUES") == 0)
		{
			VerificaNume vn(cuvinte[2]);
			if (vn.existaTabel() != 0) {
				Verificare v1(cuvinte[4]);

				if (v1.verif() == 1)
				{
					Insert i1(cuvinte[2], cuvinte[4]);
					VerificareInsert vi(cuvinte[2], i1.coloane, i1.getDimensiune());
					vi.getRanduri();
					vi.transfer();
					if (vi.verificareCorect() == 1) {
						vi.scrieDate();
					}
					cout << i1;
				}
				else cout << "Numar de paranteze gresite!" << endl;
			}
			else cout << endl << "Tabelul nu exista" << endl;
		}
		else if (dimensiune == 7 && strcmp(cuvinte[0], "DELETE") == 0 && strcmp(cuvinte[1], "FROM") == 0 && strcmp(cuvinte[3], "WHERE") == 0)
		{
			VerificaNume vn(cuvinte[2]);
			if (vn.existaTabel() == 1) {
				Delete d1(cuvinte[2], cuvinte[4], cuvinte[5], cuvinte[6]);
				DeleteBun db(cuvinte[2], cuvinte[4], cuvinte[6]);
				db.binaryToString();
				db.txtToString();
				db.salvareIndice();
				db.schimbariString();
				db.scrieDate();
				cout << d1;
			}
			else cout << "Tabelul nu exista!" << endl;
		}
		else if (dimensiune == 10 && strcmp(cuvinte[0], "UPDATE") == 0 && strcmp(cuvinte[2], "SET") == 0 && strcmp(cuvinte[6], "WHERE") == 0)
		{
			VerificaNume vn(cuvinte[1]);
			if (vn.existaTabel() == 1) {
				Update u1(cuvinte[1], cuvinte[3], cuvinte[4], cuvinte[5], cuvinte[7], cuvinte[8], cuvinte[9]);
				UpdateBun ub(cuvinte[1], cuvinte[3], cuvinte[5], cuvinte[7], cuvinte[9]);
				ub.binaryToString();
				ub.txtToString();
				ub.salvareIndice();
				ub.schimbariFisier();
				ub.scrieDate();
				cout << u1;
			}
			else cout << endl << "Tabelul nu exista!" << endl;
		}
		else if (dimensiune == 4 && strcmp(cuvinte[0], "CREATE") == 0 && (strcmp(cuvinte[1], "TABLE") == 0))
		{
			VerificaNume vn(cuvinte[2]);
			Verificare v1(cuvinte[3]);
			if (vn.existaTabel() == 0) {
				if (v1.verif() == 1)
				{
					Create c1(cuvinte[2], cuvinte[3]);
					if (c1.verificareTip() == 1)
					{
						fis.open("Tabele.txt", ios::out | ios::app);
						if (fis.tellp() == 0)
							fis << cuvinte[2] << endl;
						else {
							fis << endl << cuvinte[2];

						}
						fis.close();
						CreateFisier cf(c1.coloane, c1.getDimensiune(), cuvinte[2]);
						cf.transfer();
						cf.creareFisier();
						cout << c1;
					}
				}
				else cout << "Numar de paranteze gresite!";
			}
			else cout << "Acest tabel exista deja!" << endl;
		}
		else if (dimensiune == 7 && strcmp(cuvinte[0], "CREATE") == 0 && (strcmp(cuvinte[1], "TABLE") == 0) && (strcmp(cuvinte[3], "IF") == 0) && (strcmp(cuvinte[4], "NOT") == 0) && (strcmp(cuvinte[5], "EXISTS") == 0))
		{
			VerificaNume vn(cuvinte[2]);
			Verificare v1(cuvinte[6]);
			if (vn.existaTabel() == 0) {
				if (v1.verif() == 1)
				{
					Create c1(cuvinte[2], cuvinte[6]);
					if (c1.verificareTip() == 1)
					{

						fis.open("Tabele.txt", ios::out | ios::app);
						if (fis.tellp() == 0)
							fis << cuvinte[2] << endl;
						else {
							fis << endl << cuvinte[2];

						}
						fis.close();
						CreateFisier cf(c1.coloane, c1.getDimensiune(), cuvinte[2]);
						cf.transfer();
						cf.creareFisier();
						cout << c1;
					}
				}
				else cout << "Numar de paranteze gresite!";
			}
			else cout << "Acest tabel exista deja!" << endl;
		}
		else if (dimensiune == 3 && strcmp(cuvinte[0], "DROP") == 0 && (strcmp(cuvinte[1], "TABLE") == 0))
		{

			VerificaNume vn(cuvinte[2]);
			if (vn.existaTabel() == 1) {
				Drop d1(cuvinte[2]);
				StergeFisier sf(cuvinte[2]);
				sf.verificaDacaSterge();
				sf.stergereNume();
			}
			else cout << endl << "Acest tabel nu exista" << endl;
		}
		else if (dimensiune == 3 && strcmp(cuvinte[0], "DISPLAY") == 0 && (strcmp(cuvinte[1], "TABLE") == 0))
		{
			VerificaNume vn(cuvinte[2]);
			if (vn.existaTabel() == 1) {
				Display m1(cuvinte[2]);
				AfisareDisplay ad(cuvinte[2]);
				ad.afisareFisier();
			}
			else cout << endl << "Acest tabel nu exista!" << endl;

		}
		else if (dimensiune == 3 && strcmp(cuvinte[0], "IMPORT") == 0)
		{
			cout << endl << "Pentru comanda IMPORT separatorul ales este virgula iar inregistrarile diferite sunt puse pe randuri diferite." << endl;
			VerificaNume vn(cuvinte[1]);
			if (vn.existaTabel() == 1) {
				Import i(cuvinte[1], cuvinte[2]);
				i.citireDateDinFisier();
				i.transferChar();
				i.folosireInsert();
			}
			else cout << endl << "Tabelul nu exista!";
		}
		else cout << endl << "Comanda introdusa gresit!" << endl;

	}

	friend void operator<<(ostream& consola, SeparareComanda f);
	friend void operator>>(istream&, SeparareComanda& f);
};

void operator>>(istream& input, SeparareComanda& f)
{
	cout << endl << "Introduceti comanda:  ";
	getline(input, f.denumire);
}
class Nume {
	vector<string> listaNume;
	string input = "";
public:
	Nume() {

	}
	Nume(string input) {
		this->input = input;
	}

	virtual void txtToString()
	{
		string rand;
		ifstream fit1("Nume.txt");
		while (getline(fit1, rand)) {
			listaNume.push_back(rand);
		}
		fit1.close();
	}
	void scriere() {
		fstream f;
		f.open("Nume.txt", ios::in | ios::out | ios::app);
		f << input << endl;
		f.close();
	}

	int verificare() {
		if (find(listaNume.begin(), listaNume.end(), input) != listaNume.end())
		{
			cout << "Ati mai folosit programul, bine ati revenit!" << endl;
			return 0;
		}
		else cout << "Bine ai venit!" << endl;
		return 1;
	}
	string getInput() {
		return this->input;
	}


};

class ListaTabele : public Nume {
	int nrTabele = 0;
	list<string> a;

public:
	ListaTabele() {
	}
	
	void countTables() {
		string rand;
		ifstream fit("Tabele.txt");
		int contor = 0;
		while (getline(fit, rand)) {
			contor++;
		}
		fit.close();
		this->nrTabele = contor;
	}

	void showlist(list <string> g)
	{
		list <string> ::iterator it;
		for (it = g.begin(); it != g.end(); ++it)
			cout << *it << " ";
		cout << '\n';
	}

	void txtToString()
	{
		string rand;
		ifstream fit1("Tabele.txt");
		while (getline(fit1, rand)) {
			a.push_front(rand);
		}
		fit1.close();
		cout << "Tabelele existente sunt: ";
		showlist(a);
	}
};

class ListaComenzi : public ListaTabele {
	string id;
	string denumire="";
public:
	ListaComenzi() {
		
	}

	ListaComenzi(string id, string denumire) {
		this->id = id;
		this->denumire = denumire;
	}

	string getId() {
		return this->id;
	}

	friend ostream& operator<<(ostream& ost, ListaComenzi& a)
	{
		ost << a.id << " --- " << a.denumire;  return ost;
	}

};