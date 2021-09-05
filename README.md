# automat_komorkowy

Zadanie: zaprogramuj jednowymiarowy automat komórkowy z binarnym stanem komórek (0,1) oraz sąsiedztwem r = 1 (dokładniej - automat elementarny) oraz sąsiedztwem "zapętlonym" (czyli sąsiad ostatniego elementu to element przedostatni oraz pierwszy, sąsiad pierwszego elementu to element ostatni oraz drugi). Projekt posiada dwa stopnie trudności:

1. Poziom podstawowy

Automat posiada pewne parametry jako stałe: ROZMIAR_POPULACJI, ILOSC_ITERACJI

Następnie użytkownikowi wyświetla się menu gdzie ma do wyboru:

Zainicjalizować populację (czyli wylosować ROZMIAR_POPULACJI osobników)

Wylosować regułę przejścia 

Wywołać automat komórkowy (próba wywołania automatu bez populacji i/lub reguły przejścia powinna skutkować informacją, czego jeszcze brakuje żeby wywołać automat).

Wyjść z programu

Po wywołaniu automatu komórkowego, wyrysowujemy początkową populację, a następnie ewoluujemy populację ILOSC_ITERACJI razy, po każdej udanej ewolucji wyrysowujemy populację.

Po zakończonym procesie program informuje o zakończeniu działania automatu i powraca do menu.

2. Poziom trudniejszy

Rozmiar populacji można wpisać samemu,

ilość iteracji można także wybrać samemu,

można samemu wybrać regułę przejścia (od 0 do 255),

napisany kod jest zoptymalizowany.

