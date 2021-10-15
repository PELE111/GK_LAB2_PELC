//*********************************************************************
//
//  PLIK èR”D£OWY:		GK_LAB2_PELC.cpp
//
//  OPIS:				Program s≥uøy do tworzenia dywanu sierpinskiego z perturbacjami
//
//  AUTOR:				Janusz Pelc
//
//  DATA				14.10.2021
//	MODYFIKACJI:
//
//  PLATFORMA:			Kompilator:         Microsoft Visual studio 19.
//
//  MATERIA£Y			Instrukcja Êwiczenie 2 - OpenGL podstawy
//	èR”D£OWE:			
//		
//  UØYTE BIBLIOTEKI	Nie uøywano.
//  NIESTANDARDOWE
//		
//*********************************************************************

#include <windows.h>
#include <iostream>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cstdlib>
#include <time.h>

using namespace std;

double per; //natezenie perturbacji
double def_bok = 200; //wielkosc dywanu
int stopien; //stopien dywanu
bool white; //1 = bia≥y bez perturbacji

//-----------------------------------------------------------------
//funkcja rysuje kwadrat
//-----------------------------------------------------------------

void Kwadrat(double a, double x, double y) { 
	double 	v;
	glBegin(GL_POLYGON);
	
	if (white) {
		glColor3f(1, 1, 1);	//ustawienie bia≥ego koloru wierzcho≥ka
		glVertex2f(x - a / 2, y - a / 2);	//wyznaczenie wierzcho≥kÛw kwadratu ze úrodkiem w [x,y]

		glColor3f(1, 1, 1);
		glVertex2f(x - a / 2, y + a / 2);

		glColor3f(1, 1, 1);
		glVertex2f(x + a / 2, y + a / 2);

		glColor3f(1, 1, 1);
		glVertex2f(x + a / 2, y - a / 2);
	}
	else {
		v = a * (rand() % 10 + 1) / 100 * per;  //losowe przesuniÍcie kwadratu zaleøne od natÍøenia i proporcjonalne do wielkoúci
		glColor3f(float(rand() % 2), float(rand() % 2), float(rand() % 2));		//ustwienie losowego koloru wierzcho≥ka
		glVertex2f(x - a / 2 + v, y - a / 2 + v);	//wyznaczenie wierzcho≥kÛw kwadratu ze úrodkiem w [x,y]

		v = a * (rand() % 10 + 1) / 100 * per;  //losowe przesuniÍcie kwadratu zaleøne od natÍøenia i proporcjonalne do wielkoúci
		glColor3f(float(rand() % 2), float(rand() % 2), float(rand() % 2));
		glVertex2f(x - a / 2 + v, y + a / 2 + v);

		v = a * (rand() % 10 + 1) / 100 * per;  //losowe przesuniÍcie kwadratu zaleøne od natÍøenia i proporcjonalne do wielkoúci
		glColor3f(float(rand() % 2), float(rand() % 2), float(rand() % 2));
		glVertex2f(x + a / 2 + v, y + a / 2 + v);

		v = a * (rand() % 10 + 1) / 100 * per;  //losowe przesuniÍcie kwadratu zaleøne od natÍøenia i proporcjonalne do wielkoúci
		glColor3f(float(rand() % 2), float(rand() % 2), float(rand() % 2));
		glVertex2f(x + a / 2 + v, y - a / 2 + v);
	}

	glEnd();
}

//-----------------------------------------------------------------
//funkcja rysuje dywan Sierpinskiego
//-----------------------------------------------------------------

void Dywan(int n,double bok, double x, double y) { 
	double a[2]; //wspÛ≥rzedne wierzcho≥ka kwadratu
	double b[2];
	double c[2];
	double d[2];

	if (n > 0) {

		//wyznaczenie wierzcho≥kÛw kwadratu ze úrodkiem w [x,y]
		a[0] = x + bok / 6;	
		a[1] = y - bok / 6;

		b[0] = x - bok / 6;
		b[1] = y - bok / 6;

		c[0] = x - bok / 6;
		c[1] = y - bok / 6;

		d[0] = x - bok / 6;
		d[1] = y - bok / 6;

		n--;
		bok /= 3;
		//W miejscach kwadratÛw, z ktÛrych jest zbudowany aktualny dywan, rysuje 8 nowych
		Dywan(n, bok, x - bok, y - bok);
		Dywan(n, bok, x - bok, y);
		Dywan(n, bok, x - bok, y + bok);
		Dywan(n, bok, x, y + bok);
		Dywan(n, bok, x + bok, y + bok);
		Dywan(n, bok, x + bok, y);
		Dywan(n, bok, x + bok, y - bok);
		Dywan(n, bok, x, y - bok);
	}
	else {
		Kwadrat(bok, x, y);
	}
}

void RenderScene(void){
	glClear(GL_COLOR_BUFFER_BIT);

	Dywan(stopien,def_bok,0,0);

	glFlush();
}

//-----------------------------------------------------------------
// Funkcja ustalajπca stan renderowania
//-----------------------------------------------------------------

void MyInit(void){

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	// Kolor okna wnÍtrza okna
}

//-----------------------------------------------------------------
// Funkcja s≥uøπca do kontroli zachowania proporcji rysowanych obiektÛw
// niezaleønie od rozmiarÛw okna graficznego
//-----------------------------------------------------------------

void ChangeSize(GLsizei horizontal, GLsizei vertical){

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio okreúlajπcej proporcjÍ wymiarÛw okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoúciokna okna urzπdzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okreúlenie uk≥adu wspÛ≥rzÍdnych obserwatora

	glLoadIdentity();
	// Okreúlenie przestrzeni ograniczajπcej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspÛ≥czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// okreúlenie okna obserwatora.
	// Pozwala to zachowaÊ w≥aúciwe proporcje rysowanego obiektu
	// Do okreúlenia okna obserwatora s≥uøy funkcja glOrtho(...)

	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okreúlenie uk≥adu wspÛ≥rzÍdnych    

	glLoadIdentity();

}

//-----------------------------------------------------------------
// G≥Ûwny punkt wejúcia programu. Program dzia≥a w trybie konsoli
//-----------------------------------------------------------------

void main(void)

{
	cout << "Podaj stopien dywanu: ";
	cin >> stopien;

	cout << "Czy wersja biala bez perturbacji?: (t/n)";
	
	char x;
	do {
		cin >> x;
		if (x == 't') white = true;
		else if (x == 'n') {
			white = false;
			cout << "Podaj natezenie perturbacji (zalecane 0-10): ";
			cin >> per;
		}
	} while (x != 't' && x != 'n');


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyúwietlania
	// GLUT_SINGLE - pojedynczy bufor wyúwietlania
	// GLUT_RGBA - model kolorÛw RGB

	glutCreateWindow("Dywan SierpiÒskiego");
	// Utworzenie okna i okreúlenie treúci napisu w nag≥Ûwku okna

	glutDisplayFunc(RenderScene);
	// Okreúlenie, øe funkcja RenderScene bÍdzie funkcjπ zwrotnπ (callback)
	// Biblioteka GLUT bÍdzie wywo≥ywa≥a tπ funkcjÍ za kaødym razem, gdy
	// trzeba bÍdzie przerysowaÊ okno

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjÍ zwrotnπ odpowiedzialnπ za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powyøej) wykonuje wszelkie 
	// inicjalizacje konieczneprzed przystπpieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

