
/*
 *
 * Napisz program rysowania znakiem ASCII poni�szej figury.
 * Program powinien umo�liwia�:
 * -wyb�r znaku kodu ASCII
 * -wczytanie pocz�tkowych rozmiar�w figury
 * -zmian� wielko�ci figury klawiszami + i -
 * -przesuwanie figury za pomoc� kursor�w
 * -ograniczenie przesuwania i rozmiar�w figury do obszaru ekranu
 *
 * Created 07.01.2017
 *
 */


#include <iostream>
#include <windows.h>
#include "conio.h"

using namespace std;

void czytaj_dane(int &rozmiar, char &znak);   //funkcja wczytujaca dane od u�ytkownika
void gotoxy(int x, int y);    // funkcja przeruni�cia elementu
void rysuj(int x, int y, int rozmiar, char znak);   // funkcja rysuj�ca figur�
void przesun(int x, int y, int rozmiar, char znak);   //funkcja odczytuj�ca kierunek przesuni�cia
void HideCursor();    //ukrycie kursora
void SetWindow(int Width, int Height);    // funcka ustawiaj�ca rozmiar okna
void poczatek();    // funkcja wy�wietlaj�ca informacje pocz�tkowe

int main(){
  int rozmiar = 0;    // deklaracja zmiennej rozmaru
  char znak;    // deklaracja zmiennej znaku ktorym b�dzie rysowana figura
  int x = 60;   // ustawienie �rodka dla x
  int y = 8;    // ustawienie �rodka dla y


  poczatek();
  czytaj_dane(rozmiar, znak);
  SetWindow(124,35);    //ustawienie wielko�ci okna
  gotoxy(x, y);
  HideCursor();
  rysuj(x, y, rozmiar, znak);
  przesun(x, y, rozmiar, znak);
}

//================================================================================================//
void czytaj_dane(int &rozmiar, char &znak){

  system("CLS");

  cout << "Podaj rozmiar pocz�tkowy obiektu (1-14)" << endl;
  do {
while(!(cin>>rozmiar)){ //dop�ki strumie� jest w stanie b��du -> dop�ki podawane s� b��dne dane

  cout << "Prosz� poda� warto�� liczbow� w zakresie 1-14" << endl;
  cin.clear(); //kasowanie flagi b��dudu strumienia
  cin.sync(); //kasowanie zb�dnychh znak�w z bufora
}
    if(rozmiar <= 0 || rozmiar > 14){
      cout << "Rozmiar nie moze by� mniejszy niz 1, ani wi�kszy niz 14" << endl;
    }
  } while(rozmiar <= 0 || rozmiar > 14);

  cout << "Podaj znak"<< endl;
  cin >> znak;
}

void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void rysuj(int x, int y, int rozmiar, char znak){
  int x1 = x;
  int y1 = y;
  int rozmiar1 = rozmiar;

  system("cls");
  gotoxy(x, y); // Ustawienie punktu zaczepienia

  for (int i = 0; i<rozmiar; i++){    //rysowanie gornej cze�ci figury
    gotoxy(x1, y1);
    x1--;
    y1++;
    cout << znak << endl;
  }
  for (int i = 0; i<rozmiar + 1; i++){  //rysowanie dolnej cz�ci figury
    gotoxy(x1, y1);
    x1++;
    y1++;
    cout << znak << endl;
  }
}
void przesun(int x, int y, int rozmiar, char znak){   //definicja funkcji odpowiedzialna za ruch figory

  int rozmiar1 = rozmiar;
  int x1 = x;
  int y1 = y;


  char klawisz;
  do {
    gotoxy(0,0);
    cout << "Klawisz Esc koko�czy prac� programu";

    rysuj(x1, y1, rozmiar1, znak);

    //Ograniczenia ekranu
    int xmin = rozmiar1 + 1;
    int ymin = 1;
    int xmax = 123;
    int ymax = 33 - (rozmiar1*2);


    klawisz = _getch();
    switch (klawisz) {
      case '+' :{   //zwi�kszanie rozmiaru figory
        if(rozmiar1 < 14){
          rozmiar1++;
        }
        break;
      }
      case '-' :{   //zmniejszanie rozmiaru figory
        if(rozmiar1 > 1){
        rozmiar1--;
      }
        break;
      }
      case 77:{  // Przesuni�cie w prawo
        if(x1 < xmax){
          x1++;
        }
        break;
      }
      case 75:{  // Przesuni�cie w lewo
        if(x1 >= xmin){
          x1--;
        }
        break;
      }
      case 72:{  // Przesuni�cie w gore
        if(y1 >= ymin){
          y1--;
        }
        break;
      }
      case 80:{  // Przesuni�cie w doł
        if(ymax >= y1){
          y1++;
        }
        break;
      }
    }

  } while(klawisz != 27);   //zako�czenie pracy programu przez klawisz esc
}

void HideCursor(){  //definicja funkcji na ukrycie kursora

    ::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    ::CONSOLE_CURSOR_INFO hCCI;
    ::GetConsoleCursorInfo(hConsoleOut, &hCCI);
    hCCI.bVisible = FALSE;
    ::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

void SetWindow(int Width, int Height){  // definicja funkcji ustawienia rozmiaru okna
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Hak
    SetConsoleScreenBufferSize(Handle, coord);            // Ustawienie rozmiaru bufora
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Ustawienie rozmiaru okna
}

void poczatek(){  // definicja funkcji ekranu poczatkowego

  cout << endl << endl << endl;
  cout << " Napisz program rysowania znakiem ASCII poni�szej figury. Program powinien umo�liwia�" << endl;
  cout << "  -wybór znaku kodu ASCII;" << endl;
  cout << "  -wczytanie pocz�tkowych rozmiar�w figury;" << endl;
  cout << "  -zmian� wielko�ci figury klawiszami +� i -" << endl;
  cout << "  -przesuwanie figury za pomoc� kursor�w �;" << endl;
  cout << "  -ograniczenie przesuwania i rozmiar�w figury do obszaru ekranu;" << endl;
  cout << endl << endl << endl;
  cout << "                         *" << endl;
  cout << "                       *" << endl;
  cout << "                     *" << endl;
  cout << "                   *" << endl;
  cout << "                 *" << endl;
  cout << "                   *" << endl;
  cout << "                     *" << endl;
  cout << "                       *" << endl;
  cout << "                         *" << endl;
  cout << endl << endl << "S�awomir Pluci�ski" << endl;
  cout << endl << endl << "Kliknij dowolny klawisz" << endl;

  _getch();
}
