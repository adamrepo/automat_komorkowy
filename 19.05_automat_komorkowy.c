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

//funkcja rysujaca ciagi zer i jedynek za pomoca bialych i czarnych kwadratow
void rysowanie(int znak[100],int rozmiar) {
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

void automat()
{
	int populacja[100], rozmiar_populacji = 0;//oryginalnie wylosowana populacja
	int	ewolucja1[100], ewolucja2[100];//kolejne ewolucje oryginalnej populacji
	int regula_przejscia = 256, regula[8], reg; //wylosowana regula przejscia kolejno w postaci dziesiatnej i dwojkowej, reg-zmienna pomocnicza do obliczenia postaci dwojkowej
	int ilosc_iteracji=100;
	int wybor;//wybor w menu
	int i, j;
	int konfiguracja;//zmienna obliczajaca konfiguracje komorek w sasiedztwie
	printf("Autor - Adam Michalak\n");
	printf("Program to automat komorkowy jedno-wymiarowy.\n");
	do {
		printf("\n1. Zainicjuj populacje\n");
		printf("2. Wylosuj regule przejscia\n");
		printf("3. Wywolaj automat komorkowy\n");
		printf("0. Zakoncz program\n");
		wybor = wczytaj_int_z_zakresu(0, 3);
		//przypadki w zaleznosci od wyboru urzytkownika
		switch (wybor) {
		case 0://koniec programu
			continue;
			break;
		case 1://Zainicjuj populacje
			rozmiar_populacji = rand() % 51 + 50;//losowanie rozmiaru populacji z zakresu [50,100]
			printf("Wylosowany rozmiar populacji wynosi: %d.\n",rozmiar_populacji);
			//losowanie ciagu zer i jedynek
			for (i = 0; i < rozmiar_populacji-2; ++i) {
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
		case 2://Wylosuj regule przejscia
			regula_przejscia = rand() % 256;//losowanie reguly przejscia z zakresu [0,255] w postaci dziesietnej
			reg = regula_przejscia;
			printf("Wylosowana regula przejscia wynosi: %d.\n", regula_przejscia);//wypisanie wylosowanej reguly
			//przeksztalcenie reguly na postac dwojkowa
			for (i = 0; i <=7; ++i) {
				regula[i] = reg % 2;
				reg = reg / 2;
			}
			printf("Regula przejscia w postaci dwojkowej: ");
			for (i = 7; i >= 0; i--) {
				printf("%d", regula[i]);
			}
			break;
		case 3://Wywolaj automat komorkowy
			//warukni przy probie wywolania automatu bez zainicjowania populacji lub reguly
			if (rozmiar_populacji == 0) {
				printf("\nBrak zainicjowanej populacji. Wybierz jeszcze raz..\n");
			}
			if (regula_przejscia == 256) {
				printf("Brak reguly przejscia. Wybierz jeszcze raz..\n");
			}
			//algorytm liczacy i wypisujacy kolejne ewolucje
			if (regula_przejscia != 256 && rozmiar_populacji != 0) {
				rysowanie(populacja, rozmiar_populacji);//rysowanie poczatkowej populacji
				//przepisanie populacji do tablicy na ktorej beda wykonywanie dzialania
				for (i = 0; i < rozmiar_populacji; ++i) {
					ewolucja1[i] = populacja[i];
				}
				for (i = 0; i <= ilosc_iteracji; ++i) {
					//ewolucja kolejnych komorek
					for (j = 1; j <= rozmiar_populacji - 2; ++j) {
						konfiguracja = ewolucja1[j - 1] * 4 + ewolucja1[j] * 2 + ewolucja1[j + 1];
						ewolucja2[j] = regula[konfiguracja];
					}
					//sasiedztwo "zapetlone"
					ewolucja2[0] = ewolucja2[rozmiar_populacji - 2];
					ewolucja2[rozmiar_populacji - 1] = ewolucja2[1];
					//przepisanie nowej ewolucji jako poczatkowej do kolejnej ewolucji
					for (j = 0; j < rozmiar_populacji; ++j) {
						ewolucja1[j] = ewolucja2[j];
					}
					//rysowanie nowej ewolucji
					rysowanie(ewolucja2, rozmiar_populacji);
				}
			}
			break;
		}
	} while (wybor != 0);
	printf("\n\nKoniec.\n\n");
}

void main() {
	automat();
}