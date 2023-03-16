// cups.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include "TSubstance.h"
#include "TCups.h"

int main()
{
    /*
    for (int i = 0; i < 4; i++)
    {
        std::cout << substancje[i].get_name() << ": " << substancje[i].get_Ro() << "kg/m3\n";
    }

    std::cout << std::endl;*/

    TCups kubek1, kubek2;
    kubek1.add(substancje[0], 100);
    kubek1.add(substancje[1], 50);
    kubek1.add(substancje[2], 150);
    kubek1.add(substancje[3], 10);
    kubek1.add("woda", 30);
    kubek1.add("kwas", 50);
    kubek1.add("krew", 300);
    kubek1.add("oliwa", 1300);
    
    kubek1.add_2("woda", 90);

    //kubek1.show();
    std::cout << "\n";

    kubek2.add_2("oliwa", 90, "mass");
    //kubek2.show();

    kubek1.mixup(kubek2); //dlaczego drugi raz wywołując ten kubek się to psuje
    kubek1.show();
    kubek2.show();
}






// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
