
/*
 *
 * Napisz program rysowania znakiem ASCII poni¿szej figury.
 * Program powinien umo¿liwiaæ:
 * -wybór znaku kodu ASCII
 * -wczytanie pocz¹tkowych rozmiarów figury
 * -zmian¹ wielkoœci figury klawiszami + i -
 * -przesuwanie figury za pomoc¹ kursorów
 * -ograniczenie przesuwania i rozmiarów figury do obszaru ekranu
 *
 * Created 07.01.2017
 *
 */


#include <iostream>
#include <windows.h>
#include "conio.h"

using namespace std;

void czytaj_dane(int &rozmiar, char &znak);   //funkcja wczytujaca dane od u¿ytkownika
void gotoxy(int x, int y);    // funkcja przeruniêcia elementu
void rysuj(int x, int y, int rozmiar, char znak);   // funkcja rysuj¹ca figurê
void przesun(int x, int y, int rozmiar, char znak);   //funkcja odczytuj¹ca kierunek przesuniêcia
void HideCursor();    //ukrycie kursora
void SetWindow(int Width, int Height);    // funcka ustawiaj¹ca rozmiar okna
void poczatek();    // funkcja wyœwietlaj¹ca informacje pocz¹tkowe

int main(){
  int rozmiar = 0;    // deklaracja zmiennej rozmaru
  char znak;    // deklaracja zmiennej znaku ktorym bêdzie rysowana figura
  int x = 60;   // ustawienie œrodka dla x
  int y = 8;    // ustawienie œrodka dla y


  poczatek();
  czytaj_dane(rozmiar, znak);
  SetWindow(124,35);    //ustawienie wielkoœci okna
  gotoxy(x, y);
  HideCursor();
  rysuj(x, y, rozmiar, znak);
  przesun(x, y, rozmiar, znak);
}

//================================================================================================//
void czytaj_dane(int &rozmiar, char &znak){

  system("CLS");

  cout << "Podaj rozmiar pocz¹tkowy obiektu (1-14)" << endl;
  do {
while(!(cin>>rozmiar)){ //dopóki strumieñ jest w stanie b³êdu -> dopóki podawane s¹ b³êdne dane

  cout << "Proszê podaæ wartoœæ liczbow¹ w zakresie 1-14" << endl;
  cin.clear(); //kasowanie flagi b³êdudu strumienia
  cin.sync(); //kasowanie zbêdnychh znaków z bufora
}
    if(rozmiar <= 0 || rozmiar > 14){
      cout << "Rozmiar nie moze byæ mniejszy niz 1, ani wiêkszy niz 14" << endl;
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

  for (int i = 0; i<rozmiar; i++){    //rysowanie gornej czeêœci figury
    gotoxy(x1, y1);
    x1--;
    y1++;
    cout << znak << endl;
  }
  for (int i = 0; i<rozmiar + 1; i++){  //rysowanie dolnej czêœci figury
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
    cout << "Klawisz Esc kokoñczy pracê programu";

    rysuj(x1, y1, rozmiar1, znak);

    //Ograniczenia ekranu
    int xmin = rozmiar1 + 1;
    int ymin = 1;
    int xmax = 123;
    int ymax = 33 - (rozmiar1*2);


    klawisz = _getch();
    switch (klawisz) {
      case '+' :{   //zwiêkszanie rozmiaru figory
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
      case 77:{  // Przesuniêcie w prawo
        if(x1 < xmax){
          x1++;
        }
        break;
      }
      case 75:{  // Przesuniêcie w lewo
        if(x1 >= xmin){
          x1--;
        }
        break;
      }
      case 72:{  // Przesuniêcie w gore
        if(y1 >= ymin){
          y1--;
        }
        break;
      }
      case 80:{  // Przesuniêcie w doÅ‚
        if(ymax >= y1){
          y1++;
        }
        break;
      }
    }

  } while(klawisz != 27);   //zakoñczenie pracy programu przez klawisz esc
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
  cout << " Napisz program rysowania znakiem ASCII poni¿szej figury. Program powinien umo¿liwia³" << endl;
  cout << "  -wybÃ³r znaku kodu ASCII;" << endl;
  cout << "  -wczytanie pocz¹tkowych rozmiarów figury;" << endl;
  cout << "  -zmian¹ wielkoœci figury klawiszami +² i -" << endl;
  cout << "  -przesuwanie figury za pomoc¹ kursorów “;" << endl;
  cout << "  -ograniczenie przesuwania i rozmiarów figury do obszaru ekranu;" << endl;
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
  cout << endl << endl << "S³awomir Pluciñski" << endl;
  cout << endl << endl << "Kliknij dowolny klawisz" << endl;

  _getch();
}
