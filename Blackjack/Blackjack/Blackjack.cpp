
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string.h>
#include <Windows.h>

using namespace std;

struct Jucator{
	char nume[20];
	int bani=0;
	int mana=0;
	int pariu=0;

};

Jucator totiJucatorii[1000];
int nrJucatori = 0;

char *tipuriCarti[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

int transformaCarte(int carte)
{
	if (carte <= 8)
		return carte + 2;
	else if (carte == 12)
		return 11;
	else return 10;
}

Jucator login()
{
realege:
	system("cls");
	cout << "----------ULTIMATE BLACKJACK----------" << endl << endl;
	cout << "LOGIN WITH A NEW USERNAME (1)" << endl << endl;
	cout << "LOGIN WITH A EXISTING USERNAME (2)" << endl << endl;
	cout << "SEE ALL FORMER PLAYERS (3)" << endl << endl;
	int x = 0,index;
	cin >> x;
	system("cls");
	if (x == 1)
	{
		cout << "Nume: ";
		cin >> totiJucatorii[++nrJucatori].nume;
		cout << endl << "Bani: ";
		cin >> totiJucatorii[nrJucatori].bani;
		system("cls");
		return totiJucatorii[nrJucatori];

	}
	else
	if (x == 2)
	{
		char numeNou[20];
		cout << "Nume: ";
		cin >> numeNou;
		for (index = 1; index <= nrJucatori; index++)
		if (strcmp(numeNou, totiJucatorii[index].nume) == 0)
			return totiJucatorii[index];
		cout << "Nu ati introdus un nume care sa fie deja folosit! Va rugam alegeti alta optiune!"<<endl;
		Sleep(3000);
		system("cls");
		goto realege;
	}
	else
	if (x == 3)
	{
		cout << "ALL FORMER PLAYERS" << endl << endl;
		if (nrJucatori == 0)
			cout << "Nu exista alti jucatori" << endl;
		else
		for (index = 1; index <= nrJucatori; index++)
			cout<<totiJucatorii[index].nume << " " << totiJucatorii[index].bani << endl;
		cout << endl<<endl;
		cout << "BACK(1)"<<endl;
		while (x != 1)
		{
			cin >> x;
			if (x==1)
				goto realege;
			cout << "Date de intrare gresite! Va rog incercati din nou!" << endl;
		}

	}
	else
	{
		cout << "Date de intrare gresite! Va rog incercati din nou!" << endl;
		cin >> x;
		goto realege;
	}
}

void jucatorVsJucator()
{
	Jucator jucator1, jucator2;
	jucator1 = login();
	jucator2 = login();
	system("cls");

}

void startJoc()
{
	cout << "Jucator vs Jucator (1)" << endl << endl;
	cout << "Jucator vs Calculator (2)" << endl << endl;
	int x;
	cin >> x;
	if (x == 1)
	{
		jucatorVsJucator();
	}
}

void joc()
{
	srand(time(0));
	int contor = 0;
	do
	{

		cout << "----------ULTIMATE BLACKJACK----------" << endl << endl;
		cout << "Ai cartile:" << endl;
		int primaCarte = (rand() % 13), aDouaCarte = (rand() % 13), suma = 0, apare = 0;
		if (primaCarte == 12)
			apare++;
		if (aDouaCarte == 12)
			apare++;
		suma = transformaCarte(primaCarte) + transformaCarte(aDouaCarte);
		cout << tipuriCarti[primaCarte] << " " << tipuriCarti[aDouaCarte] << endl;
		cout << "Apasati h pentru a primi o carte sau s pentru a sta" << endl;
		char tasta;
		cin >> tasta;
		while (tasta != 's')
		{
			int nouaCarte = (rand() % 13);
			if (nouaCarte == 12)
				apare++;
			suma = suma + transformaCarte(nouaCarte);
			cout << tipuriCarti[nouaCarte] << endl;
			if (suma == 21)
				tasta = 's';
			else if (suma > 21)
			{
				if (apare != 0)
				{
					suma = suma - 10;
					apare--;
					goto continuare;
				}
				else
				{
					cout << "Ai pierdut!" << endl;
					goto next;
				}
			}
			else {
			continuare:
				cout << "Apasati h pentru a primi o carte sau s pentru a sta" << endl;
				cin >> tasta;
			}
		}
		cout << endl;
		cout << "Casa are cartile:" << endl;
		int primaCarteCasa = (rand() % 13), aDouaCarteCasa = (rand() % 13), sumaCasa = 0, apareCasa = 0;
		if (primaCarteCasa == 12)
			apareCasa++;
		if (aDouaCarteCasa == 12)
			apareCasa++;
		sumaCasa = transformaCarte(primaCarteCasa) + transformaCarte(aDouaCarteCasa);
		cout << tipuriCarti[primaCarteCasa] << " " << tipuriCarti[aDouaCarteCasa] << endl;
		while (sumaCasa<17)
		{
			int nouaCarte = (rand() % 13);
			if (nouaCarte == 12)
				apareCasa++;
			sumaCasa = sumaCasa + transformaCarte(nouaCarte);
			cout << tipuriCarti[nouaCarte] << endl;
			if (sumaCasa>21)
			{
				if (apareCasa != 0)
				{
					sumaCasa = sumaCasa - 10;
					apareCasa--;
					goto continuareCasa;
				}
				else
				{
					cout << "Ai castigat!" << endl;
					goto next;
				}
			}
		continuareCasa:;
		}
		if (suma > sumaCasa)
			cout << "Ai castigat!" << endl;
		else
			cout << "Ai pierdut!" << endl;

	next:
		cout << "Pentru a mai juca un joc apasati 1 sau 2 in caz contrar" << endl;
		cin >> contor;
		system("cls");
	} while (contor == 1);
	
}

void reguli()
{
	cout << "----------ULTIMATE BLACKJACK----------" << endl << endl;
	cout << "Blackjack, cunoscut si sub numele de 21,  este un joc des intalnit in cazinouri. Jocul a castigat popularitate deoarece este usor de jucat, jucatorul ce are suma cartilor 21 sau cel mai aproape de 21 castiga. Jocul se va juca cu un numar   nelimitat de carti. "<<endl<<endl;
	cout << "Valoarea cartilor: cartile intre 2 si 10 au valoarea scrise pe ele, figurile au valoarea 10, asul poate fi 1 sau 11 dupa preferinta jucatorului." << endl<<endl;
	cout << "Derularea jocului: Calculatorul (casa) va primi 2 carti, dintre care se vede doar 1. Fiecare jucator primeste initial 2 carti ce vor fi afisate tuturor participantilor la joc. Dupa impartire fiecare jucator are sansa de a avea suma cartilor 21, sau cat mai aproape dupa cum urmeaza." << endl << endl;
	cout << "Decizia jucatorului: Dupa impartirea cartilor jucatorul poate alege intre 4 optiuni standard: hit, stand, split, double down. " << endl;
	cout << "HIT: mai iau o carte" << endl;
	cout << "STAND: nu mai iau carte" << endl;
	cout << "DOUBLE DOWN: dublez miza, iau doar 1 singura carte" << endl;
	cout << "SPLIT: optiune folosita cand jucatorul are cele 2 carti primite de aceeasi valoare, jucatorul formand cate o mana pe    fiecare carte, cele 2 maini se joaca apoi dupa regulile standard(se poate face doar pe cartile primite initial)" << endl<<endl;
	cout << "Decizia casei:" << endl;
	cout << "SOFT 17: Cand suma cartilor dealerului este sub 17, acesta trebuie sa mai traga o carte. Daca suma este 17 sau mai mare dealerul nu mai are voie la o alta carte." << endl;
	cout << "BLACKJACK: Daca un jucator are din impartirea cartilor suma 21 primeste de la casa (3:2)x valoarea pariului." << endl;
	cout << "In cazul in care jucatorul are valoare cartilor cat are casa,casa castiga!" << endl << endl;

}

void meniu()
{
	start:
	cout << "----------ULTIMATE BLACKJACK----------" << endl << endl;
	cout << "START GAME (1)"<<endl<<endl;
	cout << "REGULI (2)" << endl<<endl;
	cout << "EXIT (3)"<<endl<<endl;
	int x;
	cin >> x;
	incercareNoua:
	if (x == 1)
	{
		system("cls");
		joc();
		system("cls");
		cout << "BACK TO MAIN MENU (1)"<<endl;
		cout << "EXIT (2)" << endl;
		cin >> x;
		repetaCiclu:
		if (x == 1)
		{
			system("cls");
			goto start;
		}
		else
		if (x == 2)
			goto end;
		else
		{
			cout << "Date de intrare gresite! Va rog incercati din nou!" << endl;
			cin >> x;
			goto repetaCiclu;
		}

	}
	else
	if (x == 2)
	{
		system("cls");
		reguli();
		cout << "BACK (1)" << endl;
		cout << "EXIT (2)" << endl;
		int x;
		cin >> x;
		repeta:
		if (x == 1)
		{
			system("cls");
			goto start;
		}
		else
		if (x == 2)
			goto end;
		else
		{
			cout << "Date de intrare gresite! Va rog incercati din nou!" << endl;
			cin >> x;
			goto repeta;
		}
	}
	else
	if (x == 3)
	{
		system("cls");
		goto end;
	}
	else
	{
		cout << "Date de intrare gresite! Va rog incercati din nou!" << endl;
		cin >> x;
		goto incercareNoua;
	}
	end:
	system("cls");
	cout << "GAME OVER!" << endl;
}

int main()
{
	jucatorVsJucator();
	meniu();

}

