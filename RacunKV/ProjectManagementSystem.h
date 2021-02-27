#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <conio.h>
#include <iomanip>
#include <chrono>

#include "Klijent.h"
#include "Racuni.h"
#include "Transakcije.h"
#include "Bankar.h"
#include "tinyxml2.h"

#include "TextTable.h"

using namespace std;
using namespace tinyxml2;

class ProjectManagementSystem
{
public:
	ProjectManagementSystem();
	~ProjectManagementSystem();

	vector<Klijent*> vKlijenti;
	vector<Racuni*> vRacuni;
	vector<Transakcije*> vTransakcije;
	vector<Bankar*> vBankar;

	XMLDocument oDocument;
	XMLDocument oDocument2;


	XMLElement *pChildBankar;
	XMLElement *pChildKlijent;
	XMLElement *pChildRacun;
	XMLElement *pChildTransakcija;
	XMLElement *m_pData;
	XMLElement* m_pData2;
	XMLElement* m_pBankari;
	XMLElement* m_pKlijenti;
	XMLElement* m_pRacuni;
	XMLElement* m_pTransakcije;
	

	void DohvatiIzbornik();
	bool UcitajKlijente();
	bool UcitajBankare();
	bool UcitajRacune();
	bool UcitajTransakcije();
	void IspisRacuna();
	void BrisanjeIzbornik();
	int BrisanjeKlijenta(int rbIzbor, int n2);
	void AzuriranjeKlijenta();
	void DodajKlijenta();
	void DodavanjeRacuna();
	void IspisiKlijente();
	void ObaviTransakciju();
	void Statistika();
	void ExitIzbornik();


	
};

