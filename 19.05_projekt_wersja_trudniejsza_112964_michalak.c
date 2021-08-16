#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//funkcja czyszczaca bufor
void czyszczenie_bufora() {
	while (getchar() != '\n');
}

//funkcja wczytujaca i zwracajaca liczbe calkowita z zadanego zakresu
int wczytaj_int_z_zakresu(int min, int max) {
	int liczba;
	while (scanf_s("%d", &liczba) != 1 || liczba < min || liczba > max || getchar() != '\n')
	{
		czyszczenie_bufora();
		printf("Bledne dane. Popraw: ");
	}
	return liczba;
}

//funkcja wczywujaca i zwracajaca liczbe calkowita wieksza od zera
int wczytaj_liczbe_calkowita_dodatnia() {
	int liczba;
	while (!scanf_s("%d", &liczba) || liczba < 1 || getchar() != '\n') {
		czyszczenie_bufora();
		printf("Niepoprawna liczba, podaj jeszcze raz: ");
	}
	return liczba;
}

//funkcja rysujaca ciagi zer i jedynek za pomoca bialych i czarnych kwadratow
void rysowanie_populacji(int znak[], int rozmiar) {
	int k;
	for (k = 0; k < rozmiar; ++k) {
		if (znak[k] == 1) {
			printf("  ");
		}
		else {
			printf("%c%c", 219, 219);
		}
	}
	putchar('\n');
}

void automat_wersja_trudniejsza()
{
	int rozmiar_populacji = 0;
	int* populacja = 0;//oryginalna populacja zer i jedynek
	int* ewolucja1 = 0, * ewolucja2 = 0;//kolejne ewolucje oryginalnej populacji
	int regula_przejscia = 256, regula[8], reg; //regula przejscia kolejno w postaci dziesiatnej i dwojkowej, reg-zmienna pomocnicza do obliczenia postaci dwojkowej
	int ilosc_iteracji = 0;
	int wybor;//wybor w menu
	int i, j;
	int konfiguracja;//zmienna obliczajaca konfiguracje komorek w sasiedztwie
	printf("Autor - Adam Michalak\n");
	printf("Program to automat komorkowy jedno-wymiarowy.\n");
	do {
		printf("\n\n1. Zainicjuj populacje.\n");
		printf("2. Podaj regule przejscia.\n");
		printf("3. Podaj ilosc iteracji.\n");
		printf("4. Wywolaj automat komorkowy.\n");
		printf("0. Zakoncz program.\n");
		wybor = wczytaj_int_z_zakresu(0, 4);
		//przypadki w zaleznosci od wyboru uzytkownika
		switch (wybor) {
		case 0://koniec programu
			continue;
			break;
		case 1://Zainicjuj populacje
			printf("\n1. Zainicjuj populacje losowo.\n");
			printf("2. Zainicjuj populacje recznie.\n");
			printf("0. Powroc do glownego menu.\n");
			wybor = wczytaj_int_z_zakresu(0, 2);
			switch (wybor) {
			case 0://Powroc do glownego menu
				wybor = 1;//wybor rozny od zera aby nie konczyc programu
				break;
			case 1://Zainicjuj populacje losowo
				rozmiar_populacji = rand() % 51 + 50;//losowanie rozmiaru populacji z zakresu dla dobrej widocznosci automatu [50,100]
				printf("Wylosowany rozmiar populacji wynosi: %d.\n", rozmiar_populacji);
				//dynamiczna alokacja rozmiaru tablicy
				free(populacja);//uwolnienie zmiennej przed ponownym zainicjowaniem rozmiaru tablicy
				populacja = (int*)malloc(rozmiar_populacji * sizeof(*populacja));
				//losowanie ciagu zer i jedynek
				for (i = 0; i < rozmiar_populacji - 2; ++i) {
					populacja[i] = rand() % 2;
				}
				//sasiedztwo "zapetlone"
				populacja[rozmiar_populacji - 2] = populacja[0];
				populacja[rozmiar_populacji - 1] = populacja[1];
				//wypisanie pocz¹tkowej populacji
				printf("Populacja poczatkowa wyglada nastepujaco:\n");
				for (i = 0; i < rozmiar_populacji; ++i) {
					printf("%d", populacja[i]);
				}
				break;
			case 2://Zainicjuj populacje recznie
				printf("\nPodaj rozmiar populacji (zalecane od 50 do 100 dla lepszej widocznosci dzialania automatu), wieksza od 3: ");
				//dynamiczna alokacja rozmiaru tablicy
				do {
					while (!scanf_s("%d", &rozmiar_populacji) || rozmiar_populacji < 4 || getchar() != '\n') {
						czyszczenie_bufora();
						printf("Niepoprawna liczba, podaj jeszcze raz: ");
					}
					free(populacja);//uwolnienie zmiennej przed ponownym zainicjowaniem rozmiaru tablicy
					populacja = (int*)malloc(rozmiar_populacji * sizeof(*populacja));
					if (populacja == NULL) {
						printf("Nastapilo przepelnienie pamieci. Sprobuj jeszcze raz: ");
					}
				} while (populacja == NULL);
				//inicjowanie ciagu zer i jedynek
				printf("\n1. Wylosuj populacje zer i jedynek.\n");
				printf("2. Podaj populacje zer i jedynek.\n");
				wybor = wczytaj_int_z_zakresu(0, 2);
				switch (wybor) {
				case 1://Wylosuj populacje zer i jedynek
					for (i = 0; i < rozmiar_populacji - 2; ++i) {
						populacja[i] = rand() % 2;
					}
					break;
				case 2://Podaj populacje zer i jedynek recznie
					for (i = 0; i < rozmiar_populacji - 2; ++i) {
						printf("\nPodaj %d element populacji: ", i + 1);
						populacja[i] = wczytaj_int_z_zakresu(0, 1);
					}
					break;
				}
				//sasiedztwo "zapetlone"
				populacja[rozmiar_populacji - 2] = populacja[0];
				populacja[rozmiar_populacji - 1] = populacja[1];
				//wypisanie pocz¹tkowej populacji
				printf("Populacja poczatkowa wyglada nastepujaco:\n");
				for (i = 0; i < rozmiar_populacji; ++i) {
					printf("%d", populacja[i]);
				}
				break;
			}
			break;
		case 2://Podaj regule przejscia
			printf("\nPodaj regule przejscia (od 0 do 255): ");
			regula_przejscia = wczytaj_int_z_zakresu(0, 255);
			//przeksztalcenie reguly na postac dwojkowa
			reg = regula_przejscia;
			for (i = 0; i <= 7; ++i) {
				regula[i] = reg % 2;
				reg = reg / 2;
			}
			printf("Regula przejscia w postaci dwojkowej: ");
			for (i = 7; i >= 0; i--) {
				printf("%d", regula[i]);
			}
			break;
		case 3://Podaj ilosc iteracji
			printf("\nPodaj ilosc iteracji: ");
			ilosc_iteracji = wczytaj_liczbe_calkowita_dodatnia();
			break;
		case 4://Wywolaj automat komorkowy
			//dynamiczna alokacja rozmiaru tablic
			free(ewolucja1);//uwolnienie zmiennej przed ponownym zainicjowaniem rozmiaru tablicy
			free(ewolucja2);
			ewolucja1 = (int*)malloc(rozmiar_populacji * sizeof(*ewolucja1));
			ewolucja2 = (int*)malloc(rozmiar_populacji * sizeof(*ewolucja2));
			//warukni przy probie wywolania automatu bez zainicjowania populacji, reguly przejscia lub liczby iteracji
			if (rozmiar_populacji == 0) {
				printf("Brak zainicjowanego rozmiaru populacji. Wybierz jeszcze raz..\n");
			}
			if (regula_przejscia == 256) {
				printf("Brak reguly przejscia. Wybierz jeszcze raz..\n");
			}
			if (ilosc_iteracji == 0) {
				printf("Brak ilosci iteracji. Wybierz jeszcze raz..\n");
			}
			//algorytm liczacy i wypisujacy kolejne ewolucje
			if (regula_przejscia != 256 && rozmiar_populacji != 0 && ilosc_iteracji != 0) {
				rysowanie_populacji(populacja, rozmiar_populacji);//rysowanie poczatkowej populacji
				//przepisanie populacji do tablicy na ktorej beda wykonywanie dzialania w celu zachowanie populacji oryginalnej
				for (i = 0; i < rozmiar_populacji; ++i) {
					ewolucja1[i] = populacja[i];
				}
				for (i = 0; i < ilosc_iteracji; ++i) {
					//ewolucja kolejnych komorek
					for (j = 1; j < rozmiar_populacji - 1; ++j) {
						konfiguracja = ewolucja1[j - 1] * 4 + ewolucja1[j] * 2 + ewolucja1[j + 1];//zakres konfiguracji od 0 do 7
						ewolucja2[j] = regula[konfiguracja];
					}
					ewolucja2[0] = ewolucja2[rozmiar_populacji - 2];
					ewolucja2[rozmiar_populacji - 1] = ewolucja2[1];
					//przepisanie nowej ewolucji jako poczatkowej do kolejnej ewolucji
					for (j = 0; j < rozmiar_populacji; ++j) {
						ewolucja1[j] = ewolucja2[j];
					}
					//rysowanie nowej ewolucji
					rysowanie_populacji(ewolucja2, rozmiar_populacji);
				}
			}
			printf("\nAutomat zakonczyl swoje dzialane.\n");
			break;
		}
	} while (wybor != 0);
	printf("\n\nKoniec.\n\n");
}

void main() {
	automat_wersja_trudniejsza();
}