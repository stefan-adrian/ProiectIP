
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

char *tipuriCarti[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };


int transformaCarte(int carte)
{
	if (carte <= 8)
		return carte + 2;
	else if (carte == 12)
		return 11;
	else return 10;
}

void joc()
{
	srand(time(0));
	int contor = 0;
	do
	{

		cout << "----------BLACKJACK----------" << endl << endl;
		cout << "Ai cartile:" << endl;
		int primaCarte = 12, aDouaCarte = (rand() % 13), suma = 0, apare = 0;
		if (primaCarte == 12 || aDouaCarte == 12)
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
		if (primaCarteCasa == 12 || aDouaCarteCasa == 12)
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

int main()
{
	joc();
	cout << "GAME OVER" << endl;

}

