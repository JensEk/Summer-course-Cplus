/*
Module3
Uppgift: Styrande satsar
Av: Jens Ekenblad
Datum: 20/06-2022
*/

#include <iostream>
#include <climits>

using namespace std;

int main()
{

    int antal, startNummer, startTim, startMin, startSek, malTim, malMin, malSek, slutTim, slutMin, slutSek = 0;
    int bestTime = INT_MAX;
    int bestNummer = -1;

    // Kör så länge inte -1 matas in som startNummer annars breakar ut
    while (true)
    {

        cout << "Startnummer?" << endl;
        cin >> startNummer;

        if (startNummer < 1)
        {
            break;
        }
        else
        {
            antal++;

            cout << "Starttid? (Ange 3 tal för timme, minut och sekund)" << endl;
            cin >> startTim >> startMin >> startSek;

            cout << "Måltid? (Ange 3 tal för timme, minut och sekund)" << endl;
            cin >> malTim >> malMin >> malSek;

            // Kontroll om ett nytt dygn har startats och omvanldar till 24+ timmar isåfall
            if (malTim < startTim)
            {
                malTim = startTim + malTim + 1;
            }

            // Omvandlar uppmätt tid till endast sekunder för att lättare jämföra
            malMin += (malTim - startTim) * 60;
            malSek += (malMin - startMin) * 60;

            // Kontroll om måltid kmr in på nytt dygn men tidigare än starttid
            if (malSek <= startSek)
            {
                malSek += 60 * 60 * 24;
            }
            malSek -= startSek;

            // Behåller den kortaste tiden och anger startnummer
            if (malSek < bestTime)
            {
                bestTime = malSek;
                bestNummer = startNummer;
            }
        }
    }

    // Om minst 1 tid har angivits så omvanldas bestTime i sekunder till motsvarande timme:minut:sekund och skriver ut
    if (antal > 0)
    {
        cout << "Vinner är startnr: " << bestNummer << endl;

        slutTim = bestTime / (60 * 60);
        slutMin = (bestTime - (slutTim * 60 * 60)) / 60;
        slutSek = bestTime % 60;

        cout << "Tim: " << slutTim << " Min: " << slutMin << " Sek: " << slutSek << endl;
        cout << "Antal tävlande: " << antal << endl;
    }
    else
    {
        cout << "Inga tävlande" << endl;
    }

    cout << "Programmet avslutas" << endl;
    return 0;
}
