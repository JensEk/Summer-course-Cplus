/*
Uppgift: Strängar och arrayer, del B
Av: Jens Ekenblad
Datum: 07/07-2022
*/

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

// Tips: Anv�nd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// ist�llet f�r v�rdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26; // A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP inneh�ller bokstavsfrekvensen i %
// f�r fyra spr�k. TOLK_HJALP[0][0] �r frekvensen av
// bokstaven a f�r engelska. TOLK_HJALP[0][25] �r frekvensen av
// bokstaven z f�r engelska.
// Arrayen �r en GLOBAL KONSTANT och skall allts� ej skickas
// som parameter till den funktion som beh�ver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER] =
    {{8.27, 1.48, 2.94, 4.03, 11.78, 2.22, 1.72, 6.77, // engelska
      7.39, 0.12, 0.81, 3.76, 2.85, 6.71, 7.79, 1.54,
      0.05, 5.95, 6.69, 9.07, 2.66, 1.13, 2.14, 0.19,
      1.89, 0.03},
     {7.97, 1.40, 3.55, 3.79, 16.89, 1.02, 1.00, 0.75, // franska
      7.08, 0.38, 0.04, 5.51, 2.82, 8.11, 5.19, 2.78,
      1.01, 6.69, 8.35, 7.22, 6.09, 1.35, 0.02, 0.54,
      0.30, 0.15},
     {9.50, 1.11, 1.53, 5.30, 8.94, 1.74, 3.57, 3.94, // svenska
      3.98, 0.89, 3.26, 4.93, 3.41, 8.46, 5.01, 1.77,
      0.00, 6.73, 5.56, 9.20, 1.94, 2.42, 0.00, 0.05,
      0.45, 0.00},
     {5.12, 1.95, 3.57, 5.07, 16.87, 1.35, 3.00, 5.79, // tyska
      8.63, 0.19, 1.14, 3.68, 3.12, 10.64, 1.74, 0.42,
      0.01, 6.30, 6.99, 5.19, 3.92, 0.77, 1.79, 0.01,
      0.69, 1.24}};

// Globala variabler �r ej till�tna

//--------------------------------------------------------
// Funktionsdeklarationer:

// Deklarationer av dina egna funktioner
// Anv�nd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
// denna skrevs i A-uppgiften och kan klippas in h�r
int berakna_histogram_abs(string rad, string alpha, int freq[]);

// Funktionen abs_till_rel
void abs_till_rel(int freq[], double rel[], int antal);

// Funktionen plotta_histogram_rel
void plotta_histogram_rel(string alpha, double rel[]);

// Funktionen tolkning
void tolkning(double rel[], int antal);

// Funktionen namn_pa_fil
string namn_pa_fil(string inputNamn);

// Funktionen inlasning
string inlasning(string filnamn);

//--------------------------------------------------------
// Huvudprogram:

/* Läser in angivet förslag på filnamn och letar sedan efter att öppna den filen i samma mapp som programmet körs från.
Sedan beräknas histogram och ger förslag på vilket språk texten är skriven i. */
int main()
{
  // Deklarera variabler
  string inputNamn;
  string filnamn;
  string text;
  string alpha = "abcdefghijklmnopqrstuvwxyz";
  int freq[ANTAL_BOKSTAVER] = {0};
  double rel[ANTAL_BOKSTAVER] = {0.0};

  cout << "Ange filnamn: " << endl;
  getline(cin, inputNamn);
  filnamn = namn_pa_fil(inputNamn);
  text = inlasning(filnamn);

  int antal = berakna_histogram_abs(text, alpha, freq);
  abs_till_rel(freq, rel, antal);
  plotta_histogram_rel(alpha, rel);
  tolkning(rel, antal);
  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:

// Tar in an angiven string med text, ett alfapet och en pekare till en array som uppdateras med varje bokstavs frekvens i stringen rad. Returnerar sedan totala antelt bokstäver.
int berakna_histogram_abs(string rad, string alpha, int freq[])
{
  int antal = 0;
  for (int i = 0; i < rad.length(); i++)
  {

    char c = rad.at(i);
    if (isalpha(c))
    {
      antal++;
      c = tolower(c);
      int index = alpha.find(c);
      if (index < 26)
        freq[index]++;
    }
  }
  return antal;
}

// Omvandlar frekvensen i absoluta tal till relativ frekvens i procent och sparar i arrayen rel.
void abs_till_rel(int freq[], double rel[], int antal)
{

  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    double f = (freq[i] / (double)antal) * 100;
    int s = (int)(f * 100 + 0.5);
    rel[i] = s / (double)100;
  }
}

// Skriver ut den relativen frekvensen av inlästa texten och ersätter procenten mot '*', där 2x * motsvarar 1%.
void plotta_histogram_rel(string alpha, double rel[])
{

  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    string ch;
    for (int j = 0; j < (int)(rel[i] / 0.5); j++)
    {
      ch.append("*");
    }

    cout << (char)(toupper(alpha.at(i))) << " " << ch << endl;
  }
}

/* Jämför den beräknade frekvensen av varje bokstav mot de 4 språken.
Sparar den som har lägst kvadratsumma dvs avviker minst mot de procentuella facit som är angivet och skriver ut vilken det är. */
void tolkning(double rel[], int antal)
{

  double closestSum = MAXFLOAT;
  string closestLang;
  string lang[4] = {"engelska", "franska", "svenska", "tyska"};
  double langSum[4] = {0.0};

  cout << "Totala antalet bokstäver: " << antal << endl;

  for (int i = 0; i < sizeof(TOLK_HJALP) / sizeof(TOLK_HJALP[0]); i++)
  {

    for (int j = 0; j < sizeof(TOLK_HJALP[i]) / sizeof(TOLK_HJALP[0][0]); j++)
    {
      langSum[i] += (TOLK_HJALP[i][j] - rel[j]) * (TOLK_HJALP[i][j] - rel[j]);
    }

    cout << lang[i] << " har kvadratsumma "
         << " = " << langSum[i] << endl;
    if (langSum[i] < closestSum)
    {
      closestSum = langSum[i];
      closestLang = lang[i];
    }
  }

  cout << "Det är mest troligt att språket är " << closestLang << endl;
}

// Tar in ett angivet filnamn och kontrollerar om det slutar på .txt annars läggs det tills i slutet och returneras.
string namn_pa_fil(string inputNamn)
{

  string filnamn;
  if (inputNamn.rfind(".txt") != (inputNamn.length() - 4))
  {
    filnamn = inputNamn.append(".txt");
  }
  else
  {
    filnamn = inputNamn;
  }

  return filnamn;
}

// Läser in filen från angivet filnamn och kontrollerar filen existerar, sedan läser in tecken varje tecken och returnerar kompletta stringen
string inlasning(string filnamn)
{

  string text;
  ifstream fin(filnamn.c_str());

  if (!fin)
  {
    cout << "Det finns ingen fil med namnet " << filnamn << endl;
    exit(EXIT_FAILURE);
  }

  char in;
  fin.get(in);
  while (!fin.eof())
  {
    text.push_back(in);
    fin.get(in);
  }
  return text;
}

// -------------------------------------------------------
// Rapport om uppgiften
