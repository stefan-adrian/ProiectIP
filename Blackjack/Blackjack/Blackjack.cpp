
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string.h>
#include <Windows.h>
#include <fstream>
#include <cmath>

using namespace std;

struct Jucator{
	char nume[100];
	int bani=0;
	int sumaCarti=0;
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

int verificareInput(char sir[], char c)
{
	if (sir[0] == c&&strlen(sir) == 1)
		return 1;
	return 0;
}


int convertFromCharToInt(char sir[])
{
	int numar = 0,index;
	for (index = 0; index < strlen(sir);index++)
		numar = numar + (sir[index] - 48)*pow(10,strlen(sir)-index-1);
	return numar;
	
}

int isDigit(char c)
{
	if (c >= '0'&&c <= '9')
		return 1;
	return 0;
}

int checkIfNumber(char sir[])
{
	int index;
	for (index = 0; index < strlen(sir);index++)
		if (isDigit(sir[index]) == 0)
			return 0;
	return 1;
}

int login()
{
realege:
	system("cls");
	cout << "----------ULTIMATE BLACKJACK----------" << endl << endl;
	cout << "LOGIN WITH A NEW USERNAME (1)" << endl << endl;
	cout << "LOGIN WITH A EXISTING USERNAME (2)" << endl << endl;
	cout << "SEE ALL FORMER PLAYERS (3)" << endl << endl;
	char x[100];
	int index;
	cin >> x;
	if (verificareInput(x,'1'))
	{
		system("cls");
		cout << "Nume: ";
		cin >> totiJucatorii[++nrJucatori].nume;
		char bani[100];
		alegeBani:
		cout << endl << "Bani: ";
		cin >> bani;
		if (checkIfNumber(bani) == 0)
		{
			cout << "Nu ati introdus un numar valid!Va rugam incercati din nou!" << endl;
			goto alegeBani;
		}
		else
		if (strlen(bani) > 6)
		{
			cout << "Valoare de bani introdusa este prea mare!Va rugam incercati din nou!" << endl;
			goto alegeBani;
		}
		else
		{
			totiJucatorii[nrJucatori].bani = convertFromCharToInt(bani);
		}
		
		system("cls");
		return nrJucatori;

	}
	else
	if (verificareInput(x, '2'))
	{
		system("cls");
		char numeNou[20];
		cout << "Nume: ";
		cin >> numeNou;
		for (index = 1; index <= nrJucatori; index++)
		if (strcmp(numeNou, totiJucatorii[index].nume) == 0)
			return index;
		cout << "Nu ati introdus un nume care sa fie deja folosit! Va rugam alegeti alta optiune!"<<endl;
		Sleep(3000);
		system("cls");
		goto realege;
	}
	else
	if (verificareInput(x, '3'))
	{
		system("cls");
		cout << "ALL FORMER PLAYERS" << endl << endl;
		if (nrJucatori == 0)
			cout << "Nu exista alti jucatori" << endl;
		else
		for (index = 1; index <= nrJucatori; index++)
			cout<<totiJucatorii[index].nume << " " << totiJucatorii[index].bani << endl;
		cout << endl<<endl;
		cout << "BACK(1)"<<endl;
		while (verificareInput(x, '1')==0)
		{
			cin >> x;
			if (verificareInput(x, '1'))
				goto realege;
			cout << "Date de intrare gresite! Va rog incercati din nou!" << endl;
		}

	}
	else
	{
		cout << "Date de intrare gresite! Va rog incercati din nou!" << endl;
		Sleep(2000);
		goto realege;
	}
}

void jucatorVsJucator()
{
	int jucator1, jucator2;
	jucator1 = login();
	jucator2 = login();
	system("cls");
	int pariu;
	cout << "Valoarea pentru care vreti sa jucati = ";
	char bani[100];
alegeBani:
	cin >> bani;
	if (checkIfNumber(bani) == 0)
	{
		cout << "Nu ati introdus un numar valid!Va rugam incercati din nou!" << endl;
		goto alegeBani;
	}
	else
	if (strlen(bani) > 6)
	{
		cout << "Valoare de bani introdusa este prea mare!Va rugam incercati din nou!" << endl;
		goto alegeBani;
	}
	else
	{
		pariu = convertFromCharToInt(bani);
	}
	system("cls");
	srand(time(0));
	char contor[100];
	do
	{
		cout << "----------ULTIMATE BLACKJACK----------" << endl << endl;
		cout << totiJucatorii[jucator1].nume << "'s turn" << endl << endl;
		int primaCarte = (rand() % 13), aDouaCarte = (rand() % 13), as = 0;
		if (primaCarte == 12)
			as++;
		if (aDouaCarte == 12)
			as++;
		totiJucatorii[jucator1].sumaCarti = transformaCarte(primaCarte) + transformaCarte(aDouaCarte);
		if (as == 2)
		{
			totiJucatorii[jucator1].sumaCarti -= 10;
			as--;
		}
		char *cartiJucator1[50];
		int nr = -1;
		cartiJucator1[++nr] = tipuriCarti[primaCarte];
		cartiJucator1[++nr] = tipuriCarti[aDouaCarte];
		cout << "INFO : Hit (h), Stand (s), Double (d) " << endl;
		cout << totiJucatorii[jucator1].nume << "'s hand" << endl;
		int index;
		for (index = 0; index <= nr; index++)
			cout << cartiJucator1[index] << " ";
		cout << "   Suma carti = " << totiJucatorii[jucator1].sumaCarti << "  Bani = " << totiJucatorii[jucator1].bani<< endl;
		char tasta[100];
		int nouaCarte;
		int bust1 = 0, bust2 = 0;
		continuare:
		cin >> tasta;
		if (verificareInput(tasta,'d'))
		{
			nouaCarte = (rand() % 13);
			if (nouaCarte == 12)
				as++;
			totiJucatorii[jucator1].sumaCarti += transformaCarte(nouaCarte);
			cartiJucator1[++nr] = tipuriCarti[nouaCarte];
			while (totiJucatorii[jucator1].sumaCarti > 21 && as > 0)
			{
				totiJucatorii[jucator1].sumaCarti -= 10;
				as--;
			}
			for (index = 0; index <= nr; index++)
				cout << cartiJucator1[index] << " ";
			cout << "   Suma carti = " << totiJucatorii[jucator1].sumaCarti << "  Bani = " << totiJucatorii[jucator1].bani << endl;
		}
		else
		if (verificareInput(tasta, 'h'))
		{
			nouaCarte = (rand() % 13);
			if (nouaCarte == 12)
				as++;
			totiJucatorii[jucator1].sumaCarti += transformaCarte(nouaCarte);
			cartiJucator1[++nr] = tipuriCarti[nouaCarte];
			while (totiJucatorii[jucator1].sumaCarti > 21 && as > 0)
			{
				totiJucatorii[jucator1].sumaCarti -= 10;
				as--;
			}
			for (index = 0; index <= nr; index++)
				cout << cartiJucator1[index] << " ";
			cout << "   Suma carti = " << totiJucatorii[jucator1].sumaCarti << "  Bani = " << totiJucatorii[jucator1].bani << endl;
			if (totiJucatorii[jucator1].sumaCarti > 21)
			{
				bust1 = 1;
				goto end;
			}
			goto continuare;

		}
		else
		if (verificareInput(tasta, 's'))
		{
			goto end;
		}
		else
		{
			cout << "Ati introdus o valoare incorecta! Va rog incercati din nou! " << endl;
			goto continuare;
		}
		end:
		Sleep(1500);
		system("cls");
		cout << "----------ULTIMATE BLACKJACK----------" << endl << endl;
		cout << totiJucatorii[jucator2].nume << "'s turn" << endl << endl;
		primaCarte = (rand() % 13);
		aDouaCarte = (rand() % 13);
		as = 0;
		if (primaCarte == 12)
			as++;
		if (aDouaCarte == 12)
			as++;
		totiJucatorii[jucator2].sumaCarti = transformaCarte(primaCarte) + transformaCarte(aDouaCarte);
		if (as == 2)
		{
			totiJucatorii[jucator2].sumaCarti -= 10;
			as--;
		}
		char *cartiJucator2[50];
		nr = -1;
		cartiJucator2[++nr] = tipuriCarti[primaCarte];
		cartiJucator2[++nr] = tipuriCarti[aDouaCarte];
		cout << "INFO : Hit (h), Stand (s), Double (d) " << endl;
		cout << totiJucatorii[jucator2].nume << "'s hand" << endl;
		for (index = 0; index <= nr; index++)
			cout << cartiJucator2[index] << " ";
		cout << "   Suma carti = " << totiJucatorii[jucator2].sumaCarti << "  Bani = " << totiJucatorii[jucator2].bani << endl;
		continuare2:
		cin >> tasta;
		if (verificareInput(tasta, 'd'))
		{
			nouaCarte = (rand() % 13);
			if (nouaCarte == 12)
				as++;
			totiJucatorii[jucator2].sumaCarti += transformaCarte(nouaCarte);
			cartiJucator2[++nr] = tipuriCarti[nouaCarte];
			while (totiJucatorii[jucator2].sumaCarti > 21 && as > 0)
			{
				totiJucatorii[jucator2].sumaCarti -= 10;
				as--;
			}
			for (index = 0; index <= nr; index++)
				cout << cartiJucator2[index] << " ";
			cout << "   Suma carti = " << totiJucatorii[jucator2].sumaCarti << "  Bani = " << totiJucatorii[jucator2].bani << endl;
		}
		else
		if (verificareInput(tasta, 'h'))
		{
			nouaCarte = (rand() % 13);
			if (nouaCarte == 12)
				as++;
			totiJucatorii[jucator2].sumaCarti += transformaCarte(nouaCarte);
			cartiJucator2[++nr] = tipuriCarti[nouaCarte];
			while (totiJucatorii[jucator2].sumaCarti > 21 && as > 0)
			{
				totiJucatorii[jucator2].sumaCarti -= 10;
				as--;
			}
			for (index = 0; index <= nr; index++)
				cout << cartiJucator2[index] << " ";
			cout << "   Suma carti = " << totiJucatorii[jucator2].sumaCarti << "  Bani = " << totiJucatorii[jucator2].bani << endl;
			if (totiJucatorii[jucator2].sumaCarti > 21)
			{
				bust2 = 1;
				goto end2;
			}
			goto continuare2;

		}
		else
		if (verificareInput(tasta, 's'))
		{
			goto end2;
		}
		else
		{
			cout << "Ati introdus o valoare incorecta! Va rog incercati din nou! " << endl;
			goto continuare2;
		}
	end2:
		Sleep(1500);
		system("cls");
		cout << totiJucatorii[jucator1].nume << " are scorul " << totiJucatorii[jucator1].sumaCarti << " si " << totiJucatorii[jucator2].nume << " are scorul " << totiJucatorii[jucator2].sumaCarti << endl << endl;
		if (bust1 == 1 && bust2 == 1 )
			cout << "Ambii jucatori au trecut de 21 deci este egalitate!" << endl << endl;
		else
		if (totiJucatorii[jucator1].sumaCarti == totiJucatorii[jucator2].sumaCarti)
			cout << "Ambii jucatori au acelasi scor deci este egalitate!" << endl << endl;
		else
		if ((bust1 == 0 && bust2 == 1) || totiJucatorii[jucator1].sumaCarti > totiJucatorii[jucator2].sumaCarti)
		{
			cout << totiJucatorii[jucator1].nume << " a castigat!" << endl << endl;
			totiJucatorii[jucator1].bani = totiJucatorii[jucator1].bani + pariu;
			totiJucatorii[jucator2].bani = totiJucatorii[jucator2].bani - pariu;
		}
		else
		if ((bust1 == 1 && bust2 == 0) || totiJucatorii[jucator1].sumaCarti < totiJucatorii[jucator2].sumaCarti)
		{
			cout << totiJucatorii[jucator2].nume << " a castigat!" << endl << endl;
			totiJucatorii[jucator1].bani = totiJucatorii[jucator1].bani - pariu;
			totiJucatorii[jucator2].bani = totiJucatorii[jucator2].bani + pariu;
		}

		cout << "PLAY AGAIN (1)" << endl;
		cout << "END THIS GAME (2)" << endl;
		cin >> contor;
		system("cls");
	} while ((verificareInput(contor, '1')));

}

void jucatorVsCalculator()
{
	int jucator;
	jucator = login();
	system("cls");
	srand(time(0));
	char contor[100];
	do
	{
		cout << "----------ULTIMATE BLACKJACK----------" << endl << endl;
		int primaCarteCasa = (rand() % 13);
		cout << "Cartea pe fata a casei este : " << tipuriCarti[primaCarteCasa] << endl<<endl;
		cout << totiJucatorii[jucator].nume << "'s turn" << endl << endl;
		cout << "Bani= " << totiJucatorii[jucator].bani << "   " << "Pariu= ";
		char bani[100];
	alegeBani:
		cin >> bani;
		if (checkIfNumber(bani) == 0)
		{
			cout << "Nu ati introdus un numar valid!Va rugam incercati din nou!" << endl;
			goto alegeBani;
		}
		else
		if (strlen(bani) > 6)
		{
			cout << "Valoare de bani introdusa este prea mare!Va rugam incercati din nou!" << endl;
			goto alegeBani;
		}
		else
		{
			totiJucatorii[jucator].pariu = convertFromCharToInt(bani);
		}
		totiJucatorii[jucator].bani -= totiJucatorii[jucator].pariu;
		cout << endl;
		int primaCarte = (rand() % 13), aDouaCarte = (rand() % 13), as = 0;
		if (primaCarte == 12)
			as++;
		if (aDouaCarte == 12)
			as++;
		totiJucatorii[jucator].sumaCarti = transformaCarte(primaCarte) + transformaCarte(aDouaCarte);
		if (totiJucatorii[jucator].sumaCarti > 21 && as != 0)
		{
			totiJucatorii[jucator].sumaCarti -= 10;
			as--;
		}
		char *cartiJucator[50];
		int nr = -1;
		cartiJucator[++nr] = tipuriCarti[primaCarte];
		cartiJucator[++nr] = tipuriCarti[aDouaCarte];
		cout << "INFO : Hit (h), Stand (s), Double (d) " << endl;
		cout << totiJucatorii[jucator].nume << "'s hand" << endl;
		int index;
		for (index = 0; index <= nr; index++)
			cout << cartiJucator[index] << " ";
		cout << "   Suma carti = " << totiJucatorii[jucator].sumaCarti << "  Bani = " << totiJucatorii[jucator].bani <<"   Pariu= "<<totiJucatorii[jucator].pariu<< endl;
		if (totiJucatorii[jucator].sumaCarti == 21)
		{
			cout << "BLACKJACK! Ai castigat!" << endl;
			totiJucatorii[jucator].bani += (totiJucatorii[jucator].pariu + totiJucatorii[jucator].pariu / 2);
			goto sfarsit;
		}
		char tasta[100];
		int nouaCarte;
		int ok = 0;
	continuare:
		cin >> tasta;
		if (verificareInput(tasta,'d')&&ok==0)
		{
			nouaCarte = (rand() % 13);
			if (nouaCarte == 12)
				as++;
			totiJucatorii[jucator].sumaCarti += transformaCarte(nouaCarte);
			cartiJucator[++nr] = tipuriCarti[nouaCarte];
			while (totiJucatorii[jucator].sumaCarti > 21 && as > 0)
			{
				totiJucatorii[jucator].sumaCarti -= 10;
				as--;
			}
			for (index = 0; index <= nr; index++)
				cout << cartiJucator[index] << " ";
			totiJucatorii[jucator].bani -= totiJucatorii[jucator].pariu;
			totiJucatorii[jucator].pariu *= 2;
			cout << "   Suma carti = " << totiJucatorii[jucator].sumaCarti << "  Bani = " << totiJucatorii[jucator].bani << "   Pariu= " << totiJucatorii[jucator].pariu << endl;
			ok = 1;
		}
		else
		if (verificareInput(tasta, 'h'))
		{
			nouaCarte = (rand() % 13);
			if (nouaCarte == 12)
				as++;
			totiJucatorii[jucator].sumaCarti += transformaCarte(nouaCarte);
			cartiJucator[++nr] = tipuriCarti[nouaCarte];
			while (totiJucatorii[jucator].sumaCarti > 21 && as > 0)
			{
				totiJucatorii[jucator].sumaCarti -= 10;
				as--;
			}
			for (index = 0; index <= nr; index++)
				cout << cartiJucator[index] << " ";
			cout << "   Suma carti = " << totiJucatorii[jucator].sumaCarti << "  Bani = " << totiJucatorii[jucator].bani << "   Pariu= " << totiJucatorii[jucator].pariu << endl;
			if (totiJucatorii[jucator].sumaCarti > 21)
			{
				goto end;
			}
			goto continuare;

		}
		else
		if (verificareInput(tasta, 's'))
		{
			goto end;
		}
		else
		{
			cout << "Ati introdus o valoare incorecta! Va rog incercati din nou! " << endl;
			goto continuare;
		}
	end:
		if (totiJucatorii[jucator].sumaCarti > 21)
		{
			cout << "BUSTED! Ai pierdut!"<<endl;
			goto sfarsit;
		}


		cout << "Casa are cartile:" << endl;
		int aDouaCarteCasa = (rand() % 13), sumaCasa = 0, apareCasa = 0;
		if (primaCarteCasa == 12)
			apareCasa++;
		if (aDouaCarteCasa == 12)
			apareCasa++;
		sumaCasa = transformaCarte(primaCarteCasa) + transformaCarte(aDouaCarteCasa);
		if (apareCasa != 0 && sumaCasa>21)
		{
			sumaCasa = sumaCasa - 10;
			apareCasa--;
		}
		char *cartiCasa[50];
		int nrCarti = -1;
		cartiCasa[++nrCarti] = tipuriCarti[primaCarteCasa];
		cartiCasa[++nrCarti] = tipuriCarti[aDouaCarteCasa];
		for (index = 0; index <= nrCarti; index++)
			cout << cartiCasa[index] << " ";
		cout << "   Suma casa="<<sumaCasa<<endl;
		while (sumaCasa<17)
		{
			int nouaCarte = (rand() % 13);
			if (nouaCarte == 12)
				apareCasa++;
			sumaCasa = sumaCasa + transformaCarte(nouaCarte);
			cartiCasa[++nrCarti] = tipuriCarti[nouaCarte];
			if (apareCasa != 0)
			{
				while (apareCasa != 0 && sumaCasa>21)
				{
					sumaCasa = sumaCasa - 10;
					apareCasa--;
					if (sumaCasa <= 21)
					{
						for (index = 0; index <= nrCarti; index++)
							cout << cartiCasa[index] << " ";
						cout << "   Suma casa=" << sumaCasa << endl;
						goto continuareCasa;
					}
				}
			}
			for (index = 0; index <= nrCarti; index++)
				cout << cartiCasa[index] << " ";
			cout << "   Suma casa=" << sumaCasa << endl;
			if (sumaCasa>21)
			{
				if (apareCasa != 0)
				{
					while (apareCasa != 0 && sumaCasa>21)
					{
						sumaCasa = sumaCasa - 10;
						apareCasa--;
						if (sumaCasa<=21)
						goto continuareCasa;
					}
				}
				else
				{
					cout << "Casa a depasit 21! Ai castigat!" << endl;
					totiJucatorii[jucator].bani += totiJucatorii[jucator].pariu * 2;
					goto sfarsit;
				}
			}
		continuareCasa:;
		}
		if (totiJucatorii[jucator].sumaCarti > sumaCasa)
		{
			cout << "Ai castigat!" << endl;
			totiJucatorii[jucator].bani += totiJucatorii[jucator].pariu * 2;
		}
		else
		{
			cout << "Ai pierdut!" << endl;

		}

	sfarsit:
		cout << "PLAY AGAIN (1)" << endl;
		cout << "END THIS GAME (2)" << endl;
		cin >> contor;
		system("cls");

	} while (verificareInput(contor,'1'));
}

void startJoc()
{
	cout << "----------ULTIMATE BLACKJACK----------" << endl << endl;
	cout << "Jucator vs Jucator (1)" << endl << endl;
	cout << "Jucator vs Calculator (2)" << endl << endl;
	char x[100];
	inceput:
	cin >> x;
	if (verificareInput(x,'1'))
	{
		jucatorVsJucator();
	}
	else
	if (verificareInput(x, '2'))
	{
		jucatorVsCalculator();
	}
	else
	{
		cout << "Ati introdus o valoare incorecta! Va rugam incercati din nou! " << endl;
		goto inceput;
	}
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
	char x[100];
	cin >> x;
	incercareNoua:
	if (verificareInput(x, '1'))
	{
		system("cls");
		startJoc();
		system("cls");
		cout << "BACK TO MAIN MENU (1)"<<endl;
		cout << "EXIT (2)" << endl;
		cin >> x;
	repetaCiclu:
		if (verificareInput(x, '1'))
		{
			system("cls");
			goto start;
		}
		else
		if (verificareInput(x, '2'))
			goto end;
		else
		{
			cout << "Date de intrare gresite! Va rog incercati din nou!" << endl;
			cin >> x;
			goto repetaCiclu;
		}

	}
	else
	if (verificareInput(x, '2'))
	{
		system("cls");
		reguli();
		cout << "BACK (1)" << endl;
		cout << "EXIT (2)" << endl;
		char x[100];
		cin >> x;
		repeta:
		if (verificareInput(x, '1'))
		{
			system("cls");
			goto start;
		}
		else
		if (verificareInput(x, '2'))
			goto end;
		else
		{
			cout << "Date de intrare gresite! Va rog incercati din nou!" << endl;
			cin >> x;
			goto repeta;
		}
	}
	else
	if (verificareInput(x, '3'))
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
	ofstream afiseaza("Jucatori.txt");
	int index;
	for (index = 1; index <= nrJucatori; index++)
		afiseaza << totiJucatorii[index].nume << " " << totiJucatorii[index].bani << endl;
	afiseaza.close();
	system("cls");
	cout << "GAME OVER!" << endl;
}

int main()
{
	meniu();
}

