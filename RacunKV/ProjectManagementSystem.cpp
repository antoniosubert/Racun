#include "pch.h"
#include "ProjectManagementSystem.h"
#include "TextTable.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;
using namespace tinyxml2;

ProjectManagementSystem::ProjectManagementSystem()
{
	UcitajKlijente();
	UcitajRacune();
	UcitajTransakcije();
	UcitajBankare();
}

void ProjectManagementSystem::DohvatiIzbornik() {
	system("CLS");
	cout << "Odaberite akciju: \n 1 - Pregled stanja svih racuna \n 2 - Transakcija \n 3 - Dodavanje racuna \n 4 - Dodavanje klijenta \n 5 - Azuriranje klijenta \n 6 - Brisanje klijenta \n 7 - Statistika";
	cout << endl;
	int odabir;
	cin >> odabir;
	switch (odabir)
	{
	case 1:
		IspisRacuna();
		cout << "\n";
		break;
	case 2:
		ObaviTransakciju();
		break;
	case 3:
		DodavanjeRacuna();
		break;
	case 4:
		DodajKlijenta();
		break;
	case 5:
		AzuriranjeKlijenta();
		break;
	case 6:
		BrisanjeIzbornik();
		break;
	case 7:
		Statistika();
		break;
	default:
		cout << "Unijeli ste nepostojecu opciju" << endl;
		break;
	}
}

bool ProjectManagementSystem::UcitajKlijente() {
	XMLDocument oDoc;
	XMLError oResult = oDoc.LoadFile("klijenti.xml");
	if (oResult != XML_SUCCESS)
	{
		cout << "Greška u XML datoteci!" << endl;
		return false;
	}
	XMLNode* oRoot = oDoc.FirstChildElement("data");
	if (oRoot == nullptr) return false;
	XMLElement* oKlijent = oRoot->FirstChildElement("klijenti");
	if (oKlijent == nullptr) return false;
	for (XMLElement* oElem = oKlijent->FirstChildElement("klijent"); oElem != NULL; oElem = oElem->NextSiblingElement())
	{
		string ime = oElem->Attribute("ime");
		string prezime = oElem->Attribute("prezime");
		string oib = oElem->Attribute("oib");
		string adresa = oElem->Attribute("adresa");
		int sifra = atoi(oElem->Attribute("sifra"));
		this->vKlijenti.push_back(new Klijent(ime, prezime, oib, adresa, sifra));
	}
	return true;

}

bool ProjectManagementSystem::UcitajBankare() {
	XMLDocument oDoc;
	XMLError oResult = oDoc.LoadFile("bankari.xml");
	if (oResult != XML_SUCCESS)
	{
		cout << "Greška u XML datoteci!" << endl;
		return false;
	}
	XMLNode* oRoot = oDoc.FirstChildElement("data");
	if (oRoot == nullptr) return false;
	XMLElement* oBankar = oRoot->FirstChildElement("bankari");
	if (oBankar == nullptr) return false;
	for (XMLElement* oElem = oBankar->FirstChildElement("bankar"); oElem != NULL; oElem = oElem->NextSiblingElement())
	{
		string ime = oElem->Attribute("ime");
		string prezime = oElem->Attribute("prezime");
		string oib = oElem->Attribute("oib");
		int sifra = atoi(oElem->Attribute("sifra"));
		this->vBankar.push_back(new Bankar(ime, prezime, oib, sifra));
	}
	return true;
}

bool ProjectManagementSystem::UcitajRacune() {

	XMLDocument oDoc;
	XMLError oResult = oDoc.LoadFile("racuni.xml");
	if (oResult != XML_SUCCESS)
	{
		cout << "Greška u XML datoteci!" << endl;
		return false;
	}
	XMLNode* oRoot = oDoc.FirstChildElement("data");
	if (oRoot == nullptr) return false;
	XMLElement* oRacun = oRoot->FirstChildElement("racuni");
	if (oRacun == nullptr) return false;
	for (XMLElement* oElem = oRacun->FirstChildElement("racun"); oElem != NULL; oElem = oElem->NextSiblingElement())
	{
		int sifra = atoi(oElem->Attribute("sifraKlij"));
		int stanje = atoi(oElem->Attribute("stanje"));
		string brojRac = oElem->Attribute("brojRac");
		this->vRacuni.push_back(new Racuni(sifra, stanje, brojRac));
	}
	return true;
}

bool ProjectManagementSystem::UcitajTransakcije() {
	XMLDocument oDoc;
	XMLError oResult = oDoc.LoadFile("transakcije.xml");
	if (oResult != XML_SUCCESS)
	{
		cout << "Greška u XML datoteci!" << endl;
		return false;
	}
	XMLNode* oRoot = oDoc.FirstChildElement("data");
	if (oRoot == nullptr) return false;
	XMLElement* oTransakcija = oRoot->FirstChildElement("transakcije");
	if (oTransakcija == nullptr) return false;
	for (XMLElement* oElem = oTransakcija->FirstChildElement("transakcija"); oElem != NULL; oElem = oElem->NextSiblingElement())
	{
		int sifra = atoi(oElem->Attribute("sifra"));
		int iznos = atoi(oElem->Attribute("iznos"));
		string brojRacPrim = oElem->Attribute("brojRacPrim");
		string brojRacPos = oElem->Attribute("brojRacPos");
		this->vTransakcije.push_back(new Transakcije(sifra, iznos, brojRacPrim, brojRacPos));
	}
	return true;
}

void ProjectManagementSystem::IspisRacuna() {
	system("CLS");

	vector<Racuni*>vRacuniTemp;

	for (int i = 0; i < vRacuni.size(); i++) {
		for (int j = i + 1; j < vRacuni.size(); j++) {
			if (vRacuni[i]->stanje < vRacuni[j]->stanje) {
				vRacuniTemp.push_back(vRacuni[i]);
				vRacuni[i] = vRacuni[j];
				vRacuni[j] = vRacuniTemp[0];
				vRacuniTemp.clear();
			}
		}
	}

	int brojac = 1;
	TextTable t('-', '|', '+');
	t.add("R.br.");
	t.add("Broj racuna");
	t.add("OIB");
	t.add("Naziv klijenta");
	t.add("Mjesto");
	t.add("Saldo");
	t.endOfRow();
	for (int i = 0; i < vRacuni.size(); i++)
	{
		int serijski = 0;
		for (int j = 0; j < vKlijenti.size(); j++)
		{
			if (vRacuni[i]->sifra == vKlijenti[j]->sifra)
			{
				t.add(to_string(brojac++));
				t.add(vRacuni[i]->brojRac);
				t.add(vKlijenti[j]->oib);
				t.add((vKlijenti[j]->ime) + " " + (vKlijenti[j]->prezime));
				t.add(vKlijenti[j]->adresa);
				t.add(to_string(vRacuni[i]->stanje));
				t.endOfRow();
			}
		}
	}
	cout << t;

	ExitIzbornik();
}
void ProjectManagementSystem::ObaviTransakciju() {
	int sifraBankara,n;
	cout << "\nOdaberite bankara (redni broj)" << endl;
	
	for (int i = 0; i < vBankar.size(); i++) {
		cout << i + 1 << ". Ime: " << vBankar[i]->ime << " Prezime: " << vBankar[i]->prezime << endl;
	}
	cin >> n;
	while (n > vBankar.size() || n < 1) {
		cout << "\nPogresan unos, pokusajte ponovo--> ";
		cin >> n;
	}
	sifraBankara = vBankar[n-1]->sifra;
	cout << "\nOdaberite posiljatelja (redni broj)" << endl;
	int n1, n2;
	string brojRacuna1, brojRacuna2;
	vector<Racuni*>vRacuni2;
	for (int i = 0; i < vRacuni.size(); i++)
	{
		cout << "-->" << (i + 1) << ".   " << vRacuni[i]->brojRac << "  " <<vRacuni[i]->stanje << endl;
	}
	cout << "\n\n-->";
	cin >> n1;
	while (n1 > vRacuni.size() || n1 < 1) {
		cout << "\nPogresan unos, pokusajte ponovo--> ";
		cin >> n1;
	}
	brojRacuna1 = vRacuni[n1-1]->brojRac;
	
	cout << "\nOdaberite primatelja (redni broj)" << endl;
	for (int i = 0; i < vRacuni.size(); i++)
	{
		if (vRacuni[i]->brojRac!= brojRacuna1) {
			vRacuni2.push_back(vRacuni[i]);
		}
	}
	for (int i = 0; i < vRacuni2.size(); i++)
	{
		cout << "-->" << (i + 1) << ".   " << vRacuni2[i]->brojRac << "  " << vRacuni2[i]->stanje << endl;

	}
	cout << "\n\n-->";
	cin >> n2;
	while (n2 > vRacuni2.size() || n2<1) {
		cout << "\nPogresan unos, pokusajte ponovo--> ";
		cin >> n2;
	}
	
	brojRacuna2 = vRacuni2[n2 - 1]->brojRac;

	cout << "\nPrvi" << brojRacuna1 << endl;
	cout << "\nDrugi" << brojRacuna2 << endl;
	int svotaTransakcije;
	cout << "\n\nUnesite svotu koju zelite prenijeti sa prvog na drugi racun: ";
	cin >> svotaTransakcije;
	vRacuni[n1 - 1]->stanje = vRacuni[n1 - 1]->stanje - svotaTransakcije;
	for (int i = 0; i < vRacuni.size(); i++) {
		if (vRacuni[i]->brojRac == brojRacuna2) {
			vRacuni[i]->stanje = vRacuni[i]->stanje + svotaTransakcije;
		}
	}
	for (int i = 0; i < vRacuni.size(); i++)
	{
		cout << "-->" << (i + 1) << ".   " << vRacuni[i]->brojRac << "  " << vRacuni[i]->stanje << endl;
	}

	oDocument.LoadFile("transakcije.xml");
	m_pData = oDocument.FirstChildElement("data");
	XMLElement* m_pDataTransakcije = m_pData->FirstChildElement("transakcije");
	XMLElement* pElementTransakcija = oDocument.NewElement("transakcija");

	pElementTransakcija->SetAttribute("sifra", sifraBankara);
	pElementTransakcija->SetAttribute("iznos", svotaTransakcije);
	pElementTransakcija->SetAttribute("brojRacPrim", brojRacuna1.data());
	pElementTransakcija->SetAttribute("brojRacPos", brojRacuna2.data());

	m_pDataTransakcije->InsertEndChild(pElementTransakcija);
	oDocument.SaveFile("transakcije.xml");

}
void ProjectManagementSystem::AzuriranjeKlijenta() {
	IspisiKlijente();
	int n;
	string str;
	cout << "\nOdaberite redni broj klijenta cije podatke zelite azurirati: ";
	cin >> n;
	cout << "Odabrali ste klijenta: " << vKlijenti[n - 1]->sifra << " Ime: " << vKlijenti[n - 1]->ime;
	
	string nime;
	string nprezime;
	string nadresa;
	int noib;
	int nsifra;


	while (str != "d") {
		cout << "\nSto zelite azurirati kod klijenta?" << endl;
		cout << "\n1 Ime / 2 prezime / 3 oib / 4 adresa";
		int m;
		cin >> m;
		switch (m) {
			case 1:
				cout << "\nUnesite novo ime-->";
				cin >> nime;
				vKlijenti[n - 1]->ime = nime;
				break;
			case 2:
				cout << "\nUnesite novo prezime-->";
				cin >> nprezime;
				vKlijenti[n - 1]->prezime = nprezime;
				break;
			case 3:			
				cout << "\nUnesite novo adresa-->";
				cin >> nadresa;
				vKlijenti[n - 1]->adresa = nadresa;
				break;
			case 4:			
				cout << "\nUnesite novo oib-->";
				cin >> noib;
				vKlijenti[n - 1]->oib = noib;
				break;
			default:
				cout << "\nKriva vrijednost, pokusajte ponovno";
				break;
		}
		
		cout <<"\n"<< vKlijenti[n-1]->ime;
		cout <<"\n"<< vKlijenti[n-1]->prezime;
		cout << "\n" << vKlijenti[n - 1]->oib;
		cout <<"\n"<< vKlijenti[n-1]->adresa;
		cout <<"\n"<< vKlijenti[n-1]->sifra;
		cout <<"\n\nJeste li zadovoljni sa promjenama? pritisnite d za da ili bilo sto drugo za ne-->";
		cin >> str;
	}
	int br = BrisanjeKlijenta(n, 1);

	oDocument.LoadFile("klijenti.xml");
	m_pData = oDocument.FirstChildElement("data");
	XMLElement* m_pDataKlijenti = m_pData->FirstChildElement("klijenti");
	XMLElement* pElementKlijent = oDocument.NewElement("klijent");

	pElementKlijent->SetAttribute("ime", (vKlijenti[n - 1]->ime).data());
	pElementKlijent->SetAttribute("prezime", (vKlijenti[n - 1]->prezime).data());
	pElementKlijent->SetAttribute("oib", (vKlijenti[n - 1]->oib).data());
	pElementKlijent->SetAttribute("adresa", (vKlijenti[n - 1]->adresa).data());
	pElementKlijent->SetAttribute("sifra", (vKlijenti[n - 1]->sifra));

	m_pDataKlijenti->InsertEndChild(pElementKlijent);
	oDocument.SaveFile("klijenti.xml");

	cout << "\n\nKLIJENT JE USPJESNO AZURIRAN" << endl;
	ExitIzbornik();
}
void ProjectManagementSystem::Statistika() {
	int ukupanSaldo=0;
	int najvecaUplata;
	vector<int>vSifre;
	for (int i = 0; i < vRacuni.size(); i++) {
		ukupanSaldo += vRacuni[i]->stanje;
	}
	
	cout << "\n\n";
	for (int i = 0; i < vSifre.size(); i++) {
		cout << "\n sifra-->" << vSifre[i];
	}
	cout << "\nUkupan broj racuna: " << vRacuni.size();
	cout << "\nUkupan saldo svih racuna: " << ukupanSaldo;


	cout << "\n\n";
	
}
void ProjectManagementSystem::DodajKlijenta()
{
	system("CLS");
	UcitajKlijente();
	UcitajRacune();

	oDocument.LoadFile("klijenti.xml");
	m_pData = oDocument.FirstChildElement("data");
	XMLElement* m_pDataKlijenti = m_pData->FirstChildElement("klijenti");
	XMLElement* pElementKlijent = oDocument.NewElement("klijent");

	string dpime = "";
	string dpprezime = "";
	string dpoib = "";
	string dpadresa = "";
	string dpiban = "";
	long long ibangen;
	
	int dpsifra;
	int dpsifk;
	int dpstanje = 0;

	string unos = "";

	cout << "\nOdabrali ste opciju dodaj klijenta\n" << endl;
ponovno3:
	system("CLS");
	cout << "\nUpisite ime." << endl;
	cout << "----->";
	cin >> dpime;
	
	if (dpime == "")
	{
		cout << "Polje ne moze biti prazno, molimo pokusajte ponovno!";
		goto ponovno3;
	}
	ponovno4:
	system("CLS");
	cout << "\nUpisite prezime." << endl;
	cout << "----->";
	cin >> dpprezime;

	if (dpprezime == "")
	{
		cout << "Polje ne moze biti prazno, molimo pokusajte ponovno!";
		goto ponovno4;
	}
ponovno1:
	system("CLS");
	cout << "\nUpisite OIB." << endl;
	cout << "----->";
	cin >> dpoib;

	if (dpoib.size() != 11)
	{
		cout << "Neispravan OIB, unesite ponovno!";
		goto ponovno1;
	}

	for (int i = 0; i < vKlijenti.size(); i++) {
		if (vKlijenti[i]->oib == dpoib)
		{
			cout << "OIB postoji, unesite ponovno!";
			goto ponovno1;
		}
	}
	system("CLS");
	cout << "\nUpisite grad." << endl;
	cout << "----->";
	cin >> dpadresa;

	ponovno2:

	srand(time(NULL)); //randomizes the seat
	dpsifra = rand() % 10000;

	for (int i = 0; i < vKlijenti.size(); i++) {
		if (vKlijenti[i]->sifra == dpsifra)
		{
			goto ponovno2;
		}
	}

	

	random_device rd;

	/* Random number generator */
	default_random_engine generator(rd());

	/* Distribution on which to apply the generator */
	uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFFFFFFF);

	for (int i = 0; i < 19; i++) {
		ibangen = distribution(generator);
		if (ibangen < 0)
		{
			 ibangen = ibangen * -1;
		}
	}
	
	dpiban = "HR" + to_string(ibangen);
	dpsifk = dpsifra;

	pElementKlijent->SetAttribute("ime", dpime.data());
	pElementKlijent->SetAttribute("prezime", dpprezime.data());
	pElementKlijent->SetAttribute("oib", dpoib.data());
	pElementKlijent->SetAttribute("adresa", dpadresa.data());
	pElementKlijent->SetAttribute("sifra", dpsifra);

	m_pDataKlijenti->InsertEndChild(pElementKlijent);
	oDocument.SaveFile("klijenti.xml");

	oDocument.Clear();

	oDocument.LoadFile("racuni.xml");
	m_pData = oDocument.FirstChildElement("data");
	XMLElement* m_pDataRacuni = m_pData->FirstChildElement("racuni");
	XMLElement* pElementRacun = oDocument.NewElement("racun");


	pElementRacun->SetAttribute("sifraKlij", dpsifk);
	pElementRacun->SetAttribute("stanje", dpstanje);
	pElementRacun->SetAttribute("brojRac", dpiban.data());


	m_pDataRacuni->InsertEndChild(pElementRacun);
	oDocument.SaveFile("racuni.xml");

	system("CLS");
	cout << "\n\n----------KLIJENT I RACUN SU USPJESNO POHRANJENI U BAZU PODATAKA----------" << endl;
	cout << "\n-----------------------ODABERITE OPCIJU ZA NASTAVAK-----------------------" << endl;

	ExitIzbornik();
}

void ProjectManagementSystem::IspisiKlijente()
{
	system("CLS");
	vKlijenti.clear();
	vRacuni.clear();

	UcitajKlijente();
	UcitajRacune();

	int rbr = 1;
	cout << "\nPrikaz imena i prezimena:" << endl;
	for (int i = 0; i < vKlijenti.size(); i++) {
		cout << "\n" << rbr++ << ". " << vKlijenti[i]->ime << " " << vKlijenti[i]->prezime << endl;
	}
	cout << "\n\n";
}

void ProjectManagementSystem::DodavanjeRacuna()
{
	system("CLS");

	oDocument.LoadFile("racuni.xml");
	m_pData = oDocument.FirstChildElement("data");
	XMLElement* m_pDataRacuni = m_pData->FirstChildElement("racuni");
	XMLElement* pElementRacun = oDocument.NewElement("racun");

	string dpiban = "";
	int dpsifra;
	int dpsifk;
	int dpstanje;
	long long ibangen;

	string unos = "";

	cout << "\nOdabrali ste opciju dodaj racun\n" << endl;

	int sifraKlijenta, n;
	cout << "\nOdaberite klijenta (redni broj)" << endl;

	for (int i = 0; i < vKlijenti.size(); i++) {
		cout << i + 1 << " " << vKlijenti[i]->ime << " " << vKlijenti[i]->prezime << endl;
	}
	cin >> n;
	while (n > vKlijenti.size() || n < 1) {
		cout << "\nPogresan unos, pokusajte ponovo--> ";
		cin >> n;
	}
	sifraKlijenta = vKlijenti[n - 1]->sifra;

	
	random_device rd;

	/* Random number generator */
	default_random_engine generator(rd());

	/* Distribution on which to apply the generator */
	uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFFFFFFF);

	for (int i = 0; i < 19; i++) {
		ibangen = distribution(generator);
		if (ibangen < 0)
		{
			ibangen = ibangen * -1;
		}
	}

	dpiban = "HR" + to_string(ibangen);

	ponovno1:
	cout << "Upisite pocetno stanje racuna." << endl;
	cout << "----->";
	cin >> dpstanje;

	if (dpstanje < 0)
	{
		cout << "Pocetno stanje nije moguce da bude u minusu! Pokusajte ponovno unos!";
		goto ponovno1;
	}

	pElementRacun->SetAttribute("sifraKlij", sifraKlijenta);
	pElementRacun->SetAttribute("stanje", dpstanje);
	pElementRacun->SetAttribute("brojRac", dpiban.data());


	m_pDataRacuni->InsertEndChild(pElementRacun);
	oDocument.SaveFile("racuni.xml");

	system("CLS");
	cout << "\n\n----------RACUN JE USPJESNO POHRANJEN U BAZU PODATAKA----------" << endl;
	cout << "\n--------------------ODABERITE OPCIJU ZA NASTAVAK-----------------" << endl;

	ExitIzbornik();


}
void ProjectManagementSystem::BrisanjeIzbornik() {
		system("CLS");

		m_pData = oDocument.FirstChildElement("data");

		int rbIzbor;

		cout << "\nOdabrali ste opciju izbrisi klijenta." << endl;
		IspisiKlijente();
		cout << "\nNapomena- kod brisanja klijenta brisu se i svi njegovi racuni" << endl;
		cout << "\nUpisite redni broj klijenta kojeg zelite izbrisati" << endl;
		cout << "----->";
		cin >> rbIzbor;
		int obrisano=BrisanjeKlijenta(rbIzbor, 2);
		if (obrisano == 1) {
			cout << "\n\n---------------KLIJENT I NJEGOVI RACUNI SU USPJESNO UKLONJENI IZ BAZE PODATAKA---------------\n\n";

			cout << "\n\n";
			ExitIzbornik();
		}
}

int ProjectManagementSystem::BrisanjeKlijenta(int rbIzbor, int n2)
{
	int obrisano = 0;
	int counter = 1;

	XMLDocument oDoc;
	XMLError oResult = oDoc.LoadFile("klijenti.xml");
	XMLNode* oRoot = oDoc.FirstChildElement("data");
	int idsifra = vKlijenti[rbIzbor - 1]->sifra;

	XMLElement* oKlijent = oRoot->FirstChildElement("klijenti");

	for (XMLElement* oElem = oKlijent->FirstChildElement("klijent"); oElem != NULL; oElem = oElem->NextSiblingElement())
	{
		if (counter == rbIzbor) {
			
			oKlijent->DeleteChild(oElem);
			obrisano = 1;
			break;
		}
		counter++;
	}

	oDoc.SaveFile("klijenti.xml");

	if (n2 == 2) {
		oDocument.LoadFile("racuni.xml");
		m_pData = oDocument.FirstChildElement("data");
		m_pRacuni = m_pData->FirstChildElement("racuni");

		string ssid = to_string(idsifra);

		for (int i = 0; i < 4; i++) {
			for (pChildRacun = m_pRacuni->FirstChildElement("racun"); pChildRacun != NULL;
				pChildRacun = pChildRacun->NextSiblingElement()) {
				if (pChildRacun->Attribute("sifraKlij") == ssid) {
					m_pRacuni->DeleteChild(pChildRacun);
					break;
				}
			}
		}
		oDocument.SaveFile("racuni.xml");
	}
	return obrisano;
	
}

void ProjectManagementSystem::ExitIzbornik() {

	cin.clear();

	int izbor;

	cout << "\n\nDa li zelite:" << endl;
	cout << "          1-----> Vratiti se na pocetni izbornik." << endl;
	cout << "          2-----> Zatvoriti program." << endl;
	cout << "\nUnesite broj zeljene opcije koji zelite provesti." << endl;
	cout << "----->";
	cin >> izbor;
	switch (izbor)
	{
	case 1:
		DohvatiIzbornik();
		break;
	case 2:
		break;
	default:
		cout << "\nUNIJELI STE POGRESAN BROJ OPCIJE, POKUSAJTE OPET" << endl;
		ExitIzbornik();
		break;
	}
}
ProjectManagementSystem::~ProjectManagementSystem()
{
}