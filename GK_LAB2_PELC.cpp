//*********************************************************************
//
//  PLIK �R�D�OWY:		GK_LAB2_PELC.cpp
//
//  OPIS:				Program s�u�y do tworzenia dywanu sierpinskiego z perturbacjami
//
//  AUTOR:				Janusz Pelc
//
//  DATA				14.10.2021
//	MODYFIKACJI:
//
//  PLATFORMA:			Kompilator:         Microsoft Visual studio 19.
//
//  MATERIA�Y			Instrukcja �wiczenie 2 - OpenGL podstawy
//	�R�D�OWE:			
//		
//  U�YTE BIBLIOTEKI	Nie u�ywano.
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
bool white; //1 = bia�y bez perturbacji

//-----------------------------------------------------------------
//funkcja rysuje kwadrat
//-----------------------------------------------------------------

void Kwadrat(double a, double x, double y) { 
	double 	v;
	glBegin(GL_POLYGON);
	
	if (white) {
		glColor3f(1, 1, 1);	//ustawienie bia�ego koloru wierzcho�ka
		glVertex2f(x - a / 2, y - a / 2);	//wyznaczenie wierzcho�k�w kwadratu ze �rodkiem w [x,y]

		glColor3f(1, 1, 1);
		glVertex2f(x - a / 2, y + a / 2);

		glColor3f(1, 1, 1);
		glVertex2f(x + a / 2, y + a / 2);

		glColor3f(1, 1, 1);
		glVertex2f(x + a / 2, y - a / 2);
	}
	else {
		v = a * (rand() % 10 + 1) / 100 * per;  //losowe przesuni�cie kwadratu zale�ne od nat�enia i proporcjonalne do wielko�ci
		glColor3f(float(rand() % 2), float(rand() % 2), float(rand() % 2));		//ustwienie losowego koloru wierzcho�ka
		glVertex2f(x - a / 2 + v, y - a / 2 + v);	//wyznaczenie wierzcho�k�w kwadratu ze �rodkiem w [x,y]

		v = a * (rand() % 10 + 1) / 100 * per;  //losowe przesuni�cie kwadratu zale�ne od nat�enia i proporcjonalne do wielko�ci
		glColor3f(float(rand() % 2), float(rand() % 2), float(rand() % 2));
		glVertex2f(x - a / 2 + v, y + a / 2 + v);

		v = a * (rand() % 10 + 1) / 100 * per;  //losowe przesuni�cie kwadratu zale�ne od nat�enia i proporcjonalne do wielko�ci
		glColor3f(float(rand() % 2), float(rand() % 2), float(rand() % 2));
		glVertex2f(x + a / 2 + v, y + a / 2 + v);

		v = a * (rand() % 10 + 1) / 100 * per;  //losowe przesuni�cie kwadratu zale�ne od nat�enia i proporcjonalne do wielko�ci
		glColor3f(float(rand() % 2), float(rand() % 2), float(rand() % 2));
		glVertex2f(x + a / 2 + v, y - a / 2 + v);
	}

	glEnd();
}

//-----------------------------------------------------------------
//funkcja rysuje dywan Sierpinskiego
//-----------------------------------------------------------------

void Dywan(int n,double bok, double x, double y) { 
	double a[2]; //wsp�rzedne wierzcho�ka kwadratu
	double b[2];
	double c[2];
	double d[2];

	if (n > 0) {

		//wyznaczenie wierzcho�k�w kwadratu ze �rodkiem w [x,y]
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
		//W miejscach kwadrat�w, z kt�rych jest zbudowany aktualny dywan, rysuje 8 nowych
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
// Funkcja ustalaj�ca stan renderowania
//-----------------------------------------------------------------

void MyInit(void){

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	// Kolor okna wn�trza okna
}

//-----------------------------------------------------------------
// Funkcja s�u��ca do kontroli zachowania proporcji rysowanych obiekt�w
// niezale�nie od rozmiar�w okna graficznego
//-----------------------------------------------------------------

void ChangeSize(GLsizei horizontal, GLsizei vertical){

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora

	glLoadIdentity();
	// Okre�lenie przestrzeni ograniczaj�cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// okre�lenie okna obserwatora.
	// Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
	// Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)

	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych    

	glLoadIdentity();

}

//-----------------------------------------------------------------
// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli
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
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB

	glutCreateWindow("Dywan Sierpi�skiego");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
	// trzeba b�dzie przerysowa� okno

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie 
	// inicjalizacje konieczneprzed przyst�pieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

