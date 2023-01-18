/*
Uppgift 6 Alpresa del B
Av: Jens Ekenblad
Datum: 28/07-2022
*/

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:
const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

// Klassdeklarationer:

// Lagrar värden som hör ihop med ett enda kvitto, används av klassen TransaktionsLista
class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int antal_kompisar;
    string *kompisar;

public:
    Transaktion();
    ~Transaktion();
    Transaktion(const Transaktion &t);
    Transaktion &operator=(const Transaktion &t);
    string hamtaNamn() const;
    double hamtaBelopp() const;
    int hamtaAntalKompisar() const;
    bool finnsKompis(const string &namnet) const;
    bool lasIn(istream &is);
    void skrivUt(ostream &os) const;
    void skrivTitel(ostream &os) const;
};

// Lagrar en persons sammanslagna transaktionsdata
class Person
{
private:
    string namn;
    double betalat_andras; // ligger ute med totalt
    double skyldig;        // skyldig totalt

public:
    Person();
    Person(const string &namn, double betalat_andras, double skyldig);
    string hamtaNamn();
    double hamtaBetalat();
    double hamtaSkyldig();
    void skrivUt(ostream &os);
};

// Ska hålla ordning på unika personer som är med i sammanhanget med dess namn och transaktionsdata.
class PersonLista
{
private:
    int antal_personer;
    Person *personer;

public:
    PersonLista();
    ~PersonLista();
    PersonLista(const PersonLista &p);
    PersonLista &operator=(const PersonLista &perslista);
    void laggTill(Person ny_person);
    void skrivUtOchFixa(ostream &os);
    double summaSkyldig() const;
    double summaBetalat() const;
    bool finnsPerson(const string &namn);
};

// Ska lagra data om många kvitton
class TransaktionsLista
{
private:
    int antal_transaktioner;
    Transaktion *transaktioner;

public:
    TransaktionsLista();
    ~TransaktionsLista();
    TransaktionsLista(const TransaktionsLista &t);
    TransaktionsLista &operator=(const TransaktionsLista &translista);
    void lasIn(istream &is);
    void skrivUt(ostream &os);
    void laggTill(Transaktion &t);
    double totalKostnad() const;
    double liggerUteMed(const string &namnet);
    double arSkyldig(const string &namnet);
    PersonLista FixaPersoner();
};

// Huvudprogram:

int main()
{

    cout << "Startar med att läsa från en fil." << endl;

    TransaktionsLista transaktioner;
    std::ifstream is("resa.txt");
    transaktioner.lasIn(is);

    int operation = 1;
    while (operation != 0)
    {
        cout << endl;
        cout << "Välj i menyn nedan:" << endl;
        cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
        cout << "1. Skriv ut information om alla transaktioner." << endl;
        cout << "2. Läs in en transaktion från tangentbordet." << endl;
        cout << "3. Beräkna totala kostnaden." << endl;
        cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA" << endl;

        cin >> operation;
        cout << endl;

        switch (operation)
        {
        case 1:
        {
            transaktioner.skrivUt(cout);
            break;
        }
        case 2:
        {
            Transaktion transaktion;
            cout << "Ange transaktion i följande format" << endl;
            transaktion.skrivTitel(cout);
            transaktion.lasIn(cin);
            transaktioner.laggTill(transaktion);
            break;
        }
        case 3:
        {
            cout << "Den totala kostnanden för resan var "
                 << transaktioner.totalKostnad() << endl;
            break;
        }
        case 4:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ar_skyldig = transaktioner.arSkyldig(namn);
            if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
            else
                cout << namn << " är skyldig " << ar_skyldig << endl;
            break;
        }
        case 5:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ligger_ute_med = transaktioner.liggerUteMed(namn);
            if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
            else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
            break;
        }
        case 6:
        {
            cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
            PersonLista lista = transaktioner.FixaPersoner();
            lista.skrivUtOchFixa(cout);
            break;
        }
        }
    }

    std::ofstream os("transaktioner.txt");
    transaktioner.skrivUt(os);

    return 0;
}

// Klassimplementationer:
Transaktion::Transaktion()
{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0.0;
    antal_kompisar = 0;
    kompisar = 0;
}

Transaktion::~Transaktion()
{
    delete[] kompisar;
}

// kopieringskonstruktor
Transaktion::Transaktion(const Transaktion &t)
{
    datum = t.datum;
    typ = t.typ;
    namn = t.namn;
    belopp = t.belopp;
    antal_kompisar = t.antal_kompisar;

    if (antal_kompisar > 0)
    {
        kompisar = new string[antal_kompisar];

        for (int i = 0; i < antal_kompisar; i++)
        {
            kompisar[i] = kompisar[i];
        }
    }
    else
    {
        kompisar = 0; // Nullpointer
    }
}

// Överlagrad tilldelningsoperator
Transaktion &Transaktion::operator=(const Transaktion &t)
{
    if (this != &t)
    {
        delete[] kompisar;
        datum = t.datum;
        typ = t.typ;
        namn = t.namn;
        belopp = t.belopp;
        antal_kompisar = t.antal_kompisar;
        kompisar = new string[antal_kompisar];
        for (int i = 0; i < antal_kompisar; i++)
            kompisar[i] = t.kompisar[i];
    }
    return *this;
}

string Transaktion::hamtaNamn() const
{
    return namn;
}

double Transaktion::hamtaBelopp() const
{
    return belopp;
}

int Transaktion::hamtaAntalKompisar() const
{
    return antal_kompisar;
}

bool Transaktion::finnsKompis(const string &namnet) const
{

    for (int i = 0; i < antal_kompisar; i++)
    {

        if (kompisar[i].compare(namnet) == 0)
        {
            return true;
        }
    }

    return false;
}

bool Transaktion::lasIn(istream &is)
{

    delete[] kompisar;
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;
    kompisar = new string[antal_kompisar];

    for (int i = 0; i < antal_kompisar; i++)
    {
        is >> kompisar[i];
    }

    return !is.eof();
}

void Transaktion::skrivUt(ostream &os) const
{
    os << datum << '\t' << typ << '\t' << namn << '\t' << belopp << '\t' << antal_kompisar << '\t';
    for (int i = 0; i < antal_kompisar; i++)
    {
        os << kompisar[i] << '\t';
    }

    os << endl;
}

void Transaktion::skrivTitel(ostream &os) const
{
    os << "Datum" << '\t' << "Typ" << '\t' << "Namn" << '\t' << "Belopp" << '\t' << "Antal och lista av kompisar" << endl;
}

Person::Person()
{
    namn = "";
    betalat_andras = 0.0;
    skyldig = 0.0;
}

Person::Person(const string &namn, double betalat_andras, double skyldig)
{
    this->namn = namn;
    this->betalat_andras = betalat_andras;
    this->skyldig = skyldig;
}

string Person::hamtaNamn()
{
    return namn;
}

double Person::hamtaBetalat()
{
    return betalat_andras;
}

double Person::hamtaSkyldig()
{
    return skyldig;
}

void Person::skrivUt(ostream &os)
{
    os << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig << ".";
    if (betalat_andras > skyldig)
        os << " Skall ha " << (betalat_andras - skyldig) << " från potten!" << endl;
    else
        os << " Skall lägga " << (skyldig - betalat_andras) << " till potten!" << endl;
}

PersonLista::PersonLista()
{
    antal_personer = 0;
    personer = 0;
}

PersonLista::~PersonLista()
{
    delete[] personer;
}

// Kopieringskonstruktor
PersonLista::PersonLista(const PersonLista &p)
{
    antal_personer = p.antal_personer;

    if (antal_personer > 0)
    {
        personer = new Person[antal_personer];

        for (int i = 0; i < antal_personer; i++)
        {
            personer[i] = p.personer[i];
        }
    }
    else
    {
        personer = 0; // NUllpointer
    }
}

// Överlagrad tilldelningsoperator
PersonLista &PersonLista::operator=(const PersonLista &perslista)
{
    if (this != &perslista)
    {
        delete[] personer;
        antal_personer = perslista.antal_personer;
        personer = new Person[antal_personer];
        for (int i = 0; i < antal_personer; i++)
        {
            personer[i] = perslista.personer[i];
        }
    }

    return *this;
}

void PersonLista::laggTill(Person ny_person)
{
    Person *p = 0;
    p = new Person[antal_personer + 1];
    for (int i = 0; i < antal_personer; i++)
    {
        p[i] = personer[i];
    }
    p[antal_personer] = ny_person;
    antal_personer++;
    delete[] personer;
    personer = p;
}

// Gör kontroll om avrundning ligger inom 1kr och isåfall bedöms summorna skyldig och betalat stämma.
void PersonLista::skrivUtOchFixa(ostream &os)
{

    for (int i = 0; i < antal_personer; i++)
    {
        personer[i].skrivUt(os);
    }

    double kontrollSumma = summaSkyldig() - summaBetalat();

    if ((kontrollSumma >= 0.0 && kontrollSumma < 1.0) || (kontrollSumma < 0.0 && kontrollSumma > -1.0))
        cout << "Summor stämmer" << endl;
    else
        cout << "Summor stämmer inte" << endl;
}

// Räknar ihop alla personers totala summa som de är skyldiga
double PersonLista::summaSkyldig() const
{
    double skyldig = 0.0;

    for (int i = 0; i < antal_personer; i++)
    {
        skyldig += personer[i].hamtaSkyldig();
    }

    return skyldig;
}
// Räknar ihop alla personers totala summa som de har betalat
double PersonLista::summaBetalat() const
{
    double betalat = 0.0;

    for (int i = 0; i < antal_personer; i++)
    {
        betalat += personer[i].hamtaBetalat();
    }

    return betalat;
}

bool PersonLista::finnsPerson(const string &namn)
{

    for (int i = 0; i < antal_personer; i++)
    {
        if (personer[i].hamtaNamn().compare(namn) == 0)
            return true;
    }

    return false;
}

TransaktionsLista::TransaktionsLista()
{
    antal_transaktioner = 0;
    transaktioner = 0;
}

TransaktionsLista::~TransaktionsLista()
{
    delete[] transaktioner;
}

// Kopieringskonstruktor
TransaktionsLista::TransaktionsLista(const TransaktionsLista &t)
{
    antal_transaktioner = t.antal_transaktioner;

    if (antal_transaktioner > 0)
    {

        transaktioner = new Transaktion[antal_transaktioner];

        for (int i = 0; i < antal_transaktioner; i++)
        {
            transaktioner[i] = t.transaktioner[i];
        }
    }
    else
    {
        transaktioner = 0; // Nullpointer
    }
}

// överlagrad tilldelningsoperator
TransaktionsLista &TransaktionsLista::operator=(const TransaktionsLista &translista)
{
    if (this != &translista)
    {
        delete[] transaktioner;
        antal_transaktioner = translista.antal_transaktioner;
        transaktioner = new Transaktion[antal_transaktioner];
        for (int i = 0; i < antal_transaktioner; i++)
        {
            transaktioner[i] = translista.transaktioner[i];
        }
    }
    return *this;
}

// Från uppgiftsbeskrivningen
void TransaktionsLista::lasIn(istream &is)
{

    Transaktion t;

    while (t.lasIn(is))
    {
        laggTill(t);
    }
}

void TransaktionsLista::skrivUt(ostream &os)
{

    os << "Antal trans = " << antal_transaktioner << endl;
    transaktioner->skrivTitel(os);

    for (int i = 0; i < antal_transaktioner; i++)
    {
        transaktioner[i].skrivUt(os);
    }
}

// Angivelse given i uppgiften
void TransaktionsLista::laggTill(Transaktion &t)
{

    Transaktion *trans = 0;
    trans = new Transaktion[antal_transaktioner + 1];
    for (int i = 0; i < antal_transaktioner; i++)
    {
        trans[i] = transaktioner[i];
    }
    trans[antal_transaktioner] = t;
    antal_transaktioner++;
    delete[] transaktioner;
    transaktioner = trans;
}

// Räknar ihop den totala kostnaden alla betalat
double TransaktionsLista::totalKostnad() const
{
    double totalKostnad = 0.0;

    for (int i = 0; i < antal_transaktioner; i++)
    {
        totalKostnad += transaktioner[i].hamtaBelopp();
    }

    return totalKostnad;
}

// Från instruktionen
double TransaktionsLista::liggerUteMed(const string &namn)
{
    double summa = 0.;
    for (int i = 0; i < antal_transaktioner; i++)
        if (transaktioner[i].hamtaNamn() == namn)
        {
            summa += transaktioner[i].hamtaBelopp() * (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
        }
    return summa;
}

double TransaktionsLista::arSkyldig(const string &namnet)
{
    double skyldig = 0.0;

    for (int i = 0; i < antal_transaktioner; i++)
    {
        if (transaktioner[i].finnsKompis(namnet))
        {
            skyldig += (transaktioner[i].hamtaBelopp() / (transaktioner[i].hamtaAntalKompisar() + 1));
        }
    }
    return skyldig;
}

// Räknar ihop varje unika persons totala belopp för inkassering och som ska betalas.
PersonLista TransaktionsLista::FixaPersoner()
{
    PersonLista personLista;
    string namn;
    double inkassera = 0.0;
    double skyldig = 0.0;

    for (int i = 0; i < antal_transaktioner; i++)
    {
        namn = transaktioner[i].hamtaNamn();

        if (!personLista.finnsPerson(namn))
        {
            inkassera = liggerUteMed(namn);
            skyldig = arSkyldig(namn);

            Person ny_pers(namn, inkassera, skyldig);
            personLista.laggTill(ny_pers);
        }
    }
    return personLista;
}
