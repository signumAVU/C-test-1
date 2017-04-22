#pragma once

 

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;
using namespace sf;


sf::RenderWindow window;

#pragma comment(lib,"glut.lib")
#pragma comment(lib,"glut32.lib")

unsigned int Status = 0;
unsigned int OptionsPr = 0; 
signed int ErrCode = 0;
int Framerat = 60;

// ������� ���� ������� ����� � ������� ��� ���������
//LCID langId = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);	 
// LCID langId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
LCID langId = MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA);

#define LANGID langId

#define STDEF   Style::Default
#define STFULLS Style::Fullscreen

#define WIDTH  800U
#define HEIGHT  600U

#define ERRORTXT   SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY) // ������� ������ � ���� ����� ���
#define COMENTTXT  SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | 0x000E | FOREGROUND_INTENSITY) // ������� ������ � ���� ����� ���	
#define DEFAULTTXT SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | 0x000A | FOREGROUND_INTENSITY) // ������� ������ � ���� ����� ���

#define COLORTXT    0x0001UL // ������������ ����� 
#define STYLEWINFLS 0x0002UL // ������������� �����
#define VERTICALSYN 0x0004UL // ������������ �������������
