#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <sstream>
#include <cstring> //do funkcji strcpy

void alokacjaPamieciChar2D(){

};

void alokacjaPamieciString(std::string *&tab, std::string *&wzorzec , int *&licznik){

    wzorzec = new std::string[1]; //pierwsza linia w pliku to wzorzec
    std::string odrzuc;


    std::ifstream plik("tekst.txt");
    if (!plik) {
        std::cerr << "Nie mozna otworzyc pliku!" << std::endl;
        return;
    }
    plik >> wzorzec[0];
    std::string linia;

    int licznik2 = 0;
    while (std::getline(plik, linia)) {
        (*licznik)++;
        licznik2++;
    }


    tab = new std::string[licznik2];

    plik.clear();
    plik.seekg(0, std::ios::beg);

    std::getline(plik, odrzuc); // Odrzucamy pierwsza linie bo to wzorzec
    for (int i = 0; i < licznik2; i++) {
        std::getline(plik, tab[i]);
    }

    plik.close();
};

void zamianaWzorcaNaChar(std::string *&wzorzec, char *&wzorzec2, int *&licznik){
    wzorzec2 = new char[wzorzec[0].length() + 1];
    strcpy(wzorzec2, wzorzec[0].c_str());

};

void zamianaTablicyStringNaChar(std::string *&tab, char **&tab2, int *&licznik){
    int licznik2 = *licznik;
    tab2 = new char*[licznik2];
    for (int i = 0; i < licznik2; i++) {
        tab2[i] = new char[tab[i].length() + 1];
        strcpy(tab2[i], tab[i].c_str()); //strstr - poszukiwanie podlancucha znakow
    }
};

void wyswietlTabliceS(std::string *tab, int *licznik){
    int licznik2 = *licznik;
    for (int i = 0; i < licznik2; i++) {
        std::cout << tab[i] << std::endl;
    }
};

void wyswietlTabliceC(char **tab, int *licznik){
    int licznik2 = *licznik;
    for (int i = 0; i < licznik2; i++) {
        std::cout << tab[i] << std::endl;
    }
};

void algortymNaiwny(char **tab2, char *wzorzec2, int *licznik){
    int licznik2 = *licznik;
    for (int i = 0; i < licznik2; i++) {
        if (strstr(tab2[i], wzorzec2) != nullptr) {
            std::cout << "Znaleziono wzorzec w linii " << i + 1 << ": " << tab2[i] << std::endl;
        }
    }
};

int algorytmKnuthaMorrisaPratta(char *wzorzec2, char *tab2, int dlugoscWzorca, int dlugoscTekstu, int *tablicaDopasowan){
int i=0, j=0;
while (i <dlugoscTekstu){
    if(wzorzec2[j]== tab2[i]){
        j++;
        i++;
    }

    if(j==dlugoscWzorca){
        return i-j;
    }
    else if(i<dlugoscTekstu && wzorzec2[j]!=tab2[i]){
        if(j!=0){
            j=tablicaDopasowan[j];
        }
        else
            i++;
    }
    }
    return -1;
};

void zbudujTabliceDopasowan(char *wzorzec2, int dlugoscWzorca, int *&tablicaDopasowan){
    tablicaDopasowan[0] = 0;
    tablicaDopasowan[1] = 0;
    int t = 0;
    int i = 1;
    while(i<dlugoscWzorca){
        while(t>0 && wzorzec2[t]!= wzorzec2[i]){
            t=tablicaDopasowan[t];
        }
        if(wzorzec2[t] == wzorzec2[i]){
            t=t+1;
        }
        tablicaDopasowan[i+1]=t;
        i=i+1;
        }
};

void tablicaPrzesuniec(char *wzorzec2, int dlugoscWzorca, int *&tablica, char pocz, char kon){
 
    int n_pocz = (int)pocz;
    int n_kon = (int)kon;
    int dlugosc = n_kon - n_pocz + 1;

    tablica = new int[dlugosc];
    for(int i = 0; i < dlugosc; i++){
        tablica[i] = -1;
    }

    for(int i = 0; i < dlugoscWzorca; i++){
        int index = (int)wzorzec2[i] - n_pocz;
        if(index >= 0 && index < dlugosc){
            tablica[index] = i;
        }
    }


};
int algorytmBoyerMoore(char *wzorzec, char *tekst, int dlW, int dlT, int *tablica, char pocz){
    int n_pocz = (int)pocz;
    int i = 0;

    while(i <= dlT - dlW) {
        int j = dlW -1;
        while(j >= 0 && wzorzec[j] == tekst[i + j]){
            j--;
        }
        if(i <0){
            return i; //znaleziono wzorzec
        }else{
            int index = (int)tekst[i + j] - n_pocz;
            int przesuniecie = j - (index >= 0 ? tablica[index] : -1);
            if(przesuniecie < 1)
                przesuniecie = 1;
            i = i + przesuniecie;
        }
    }
    return -1; //nie znaleziono wzorca

};



void wykonaj1(std::string *&tab, char **&tab2, std::string *&wzorzec , char *&wzorzec2, int *licznik){
alokacjaPamieciString(tab, wzorzec, licznik);
    std::cout<< "Licznik: "<< *licznik-1 << std::endl;
    std::cout << "Wczytano dane z pliku." << std::endl;
    std::cout << "Wzorzec: " << wzorzec[0] << std::endl;
    wyswietlTabliceS(tab, licznik);
    zamianaWzorcaNaChar(wzorzec, wzorzec2, licznik);
    std::cout << "Wzorzec po zamianie na char: " << wzorzec2 << std::endl;
    zamianaTablicyStringNaChar(tab, tab2, licznik);
    std::cout << "Tablica po zamianie na char: " << std::endl;
    wyswietlTabliceC(tab2, licznik);

};

void wykonaj2(char **tab2, char *wzorzec2, int *licznik){
    algortymNaiwny(tab2, wzorzec2, licznik);
};

void wykonaj3(std::string *wzorzec, char *wzorzec2, int *licznik, char **tab2){
    int dlugoscWzorca = wzorzec[0].length();
    int *tablicaDopasowan = new int[dlugoscWzorca];
    zbudujTabliceDopasowan(wzorzec2, dlugoscWzorca, tablicaDopasowan);
    int *dlugoscTekstow = new int[*licznik];
    for (int i = 0; i < *licznik; i++) {
        dlugoscTekstow[i] = strlen(tab2[i]-1);
    }
    for(int i=0; i<*licznik; i++){
        int k=-1;
        k=algorytmKnuthaMorrisaPratta(wzorzec2, tab2[i], dlugoscWzorca, dlugoscTekstow[i], tablicaDopasowan);
        if(k!=-1){
            std::cout << "Znaleziono wzorzec w linii " << i + 1 << ": " << tab2[i] << std::endl;
        }
    }
};

void wykonaj4(std::string *wzorzec, char *wzorzec2, int *licznik, char **tab2){
    char pocz='a';
    char kon='z';
    int dlugoscWzorca = wzorzec[0].length();

    int *tablicaPrzesuniecBM = nullptr;
    tablicaPrzesuniec(wzorzec2,dlugoscWzorca,tablicaPrzesuniecBM, pocz, kon);
    for(int i = 0; i < *licznik; i++) {

        int k = algorytmBoyerMoore(wzorzec2, tab2[i], dlugoscWzorca, strlen(tab2[i]), tablicaPrzesuniecBM, pocz);
        if (k != -1) {
            std::cout << "Znaleziono wzorzec w linii " << i + 1 << ": " << tab2[i] << std::endl;
        }
    }
};

void zwolnijPamiecChar2D( char **&tab2, int *&licznik){
    int licznik2 = *licznik;
    for (int i = 0; i < licznik2; i++) {
        delete[] tab2[i];
    }
    delete[] tab2;
    delete licznik;

};

void zwolnijPamiecChar(char *&wzorzec2){
    delete[] wzorzec2;
};

void zwolnijPamiecString(std::string *&tab, std::string *&wzorzec, int *&licznik){
    delete[] tab;
    delete[] wzorzec;
    delete licznik;
};

int main(){
    int wybor;
    std::string *tab = nullptr;
    char **tab2 = nullptr;
    std::string *wzorzec = nullptr;
    char *wzorzec2 = nullptr;
    int *licznik = new int(0);
    do{
        std::cout << "Wybierz opcje:" << std::endl;
        std::cout << "1. Wczytanie danych z pliku" << std::endl;
        std::cout << "2. Algorytm Naiwny" << std::endl;
        std::cout << "3. Algorytm Knutha-Morrisa-Pratta" << std::endl;
        std::cout << "4. Algorytm Boyer'a-Moore'a" << std::endl;
        std::cout << "5. Zakoncz program" << std::endl;
        std::cin >> wybor;
        if (wybor==1){
            wykonaj1(tab,tab2,wzorzec,wzorzec2, licznik);
        }
        else if(wybor==2){
            wykonaj2(tab2, wzorzec2, licznik);
        }
        else if(wybor==3){
            wykonaj3(wzorzec,wzorzec2,licznik,tab2);
        }
        else if(wybor==4){
            wykonaj4(wzorzec,wzorzec2,licznik,tab2);
        }
        else if(wybor==5){
            std::cout << "Koniec programu" << std::endl;
            zwolnijPamiecString(tab, wzorzec, licznik);
            zwolnijPamiecChar(wzorzec2);
            zwolnijPamiecChar2D(tab2, licznik);
            std::cout << "Pamiec zwolniona." << std::endl;
            break;
        }
        else{
            std::cout << "Niepoprawny wybor, sprobuj ponownie." << std::endl;
        }

    }while(wybor!=5);
    delete licznik;
return 0;}