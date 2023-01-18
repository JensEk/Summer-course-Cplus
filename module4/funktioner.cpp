/*
Module4
Uppgift: Funktioner
Av: Jens Ekenblad
Datum: 20/06-2022
*/

#include <iostream>
using namespace std;

// Funktionsdeklaration
void skrivInfo();
int lasEttTal();
char lasOp();
void ordna(int &a, int &b);
int berakna(int undre, int ovre, char op);
void skrivResultat(int svar);

// Följer ordningen givet i uppgiftangivelsen
int main()
{
    int tal1, tal2, svar;
    char op;

    skrivInfo();

    tal1 = lasEttTal();

    tal2 = lasEttTal();

    op = lasOp();

    ordna(tal1, tal2);

    svar = berakna(tal1, tal2, op);

    skrivResultat(svar);

    return 0;
}

// Funktionsdefinitioner baserat på angivelserna i uppgiftbeskrivningen med egendefinierade ledtexter.

// Programbeskrivning
void skrivInfo()
{
    cout << "Programmet tar in två heltal och utför en aritmetisk operation på de båda talen beroende på angiven operation." << endl;
}

// Läser in input och returnerar talet.
int lasEttTal()
{
    int temp;
    cout << "Vänligen ange ett heltal att läsa in:" << endl;
    cin >> temp;

    return temp;
}

// Läser in vald operation och gör kontroll att endast tecknen a,m och k är giltiga som input.
char lasOp()
{
    char temp;
    cout << "Tillgängliga operationer: a = addition || m = multiplikation || k = kvadratsumma" << endl
         << "Vänligen ange vilken operation som ska utföras:" << endl;

    cin >> temp;
    while (temp != 'a' && temp != 'm' && temp != 'k')
    {
        cout << "Inte giltig operation vänligen ange ny operation: " << endl;
        cin.ignore();
        cin.clear();
        cin >> temp;
    }
    cout << "Vald operation är: " << temp << endl;
    return temp;
}

// Sorterar de båda inlästna talen så att tal1 blir minst och tal2 det större.
void ordna(int &a, int &b)
{

    int temp;
    if (b < a)
    {
        cout << "Tal2 är mindre än tal1, byter plats" << endl;
        temp = a;
        a = b;
        b = temp;
    }
    else
    {
        cout << "Tal1 är redan mindre eller lika stort som tal2, ingen sortering krävs" << endl;
    }
}

// Beroende på vilken operation som är angiven på op så utförs 3 olika aritmetiska operationer.
int berakna(int undre, int ovre, char op)
{

    int svar = 0;

    switch (op)
    {

    case 'a':
    {
        for (int i = undre; i <= ovre; i++)
        {
            svar += i;
        }
        break;
    }

    case 'm':
    {
        svar = 1;
        for (int i = undre; i <= ovre; i++)
        {
            svar *= i;
        }
        break;
    }

    case 'k':
    {
        for (int i = undre; i <= ovre; i++)
        {
            svar += i * i;
        }
        break;
    }

    default:
    {
        cout << "Ogiltig inmatning av operation, vänligen starta om programmet" << endl;
        svar = 0;
        break;
    }
    }

    return svar;
}

// Skriver ut resultatet av beräkningen som ges som argument
void skrivResultat(int svar)
{
    cout << "Svaret från beräkningen är: " << svar << endl;
}
