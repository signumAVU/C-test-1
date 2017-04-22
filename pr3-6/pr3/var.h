#pragma once

#ifndef CDS_FULLSCREEN        // CDS_FULLSCREEN �� ������������ ����������
#define CDS_FULLSCREEN 4      // �������������. ���������� ��� ���������
#endif                        // ����� ������� �� ����� �������� ������


#define SFML 

//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;
using namespace sf;


sf::RenderWindow window;

GLfloat xrot;         // X ��������
GLfloat yrot;         // Y ��������
GLfloat zrot;         // Y ��������
GLfloat zspeed;       // X �������� ��������
GLfloat xspeed;       // X �������� ��������
GLfloat yspeed;       // Y �������� ��������
GLuint filter;         // ����� ������ ������������
GLfloat z = -5.0f;      // ����� ������ ������


struct SysVar
{

unsigned int Status;	    // ������ ���������
unsigned int OptionsPr;     // ��������� ���������
signed   int ErrCode;	    // ���� ������
int          Framerat;	    // ������ � �������

unsigned int SysWidth;	    // ������ ����
unsigned int SysHeight;  	// ������ ����
unsigned int SysPositWinX;	// ������� ���� X
unsigned int SysPositWinY;	// ������� ���� Y

unsigned int SysWidthCons;	// ������ �������
unsigned int SysHeightCons;	// ������ �������
unsigned int SysPositConsX;	// ������� ������� X
unsigned int SysPositConsY;	// ������� ������� Y

unsigned int GLdepthBits;         //< Bits of the depth buffer
unsigned int GLstencilBits;       //< Bits of the stencil buffer
unsigned int GLantialiasingLevel; //< Level of antialiasing
unsigned int GLmajorVersion;      //< Major number of the context version to create
unsigned int GLminorVersion;      //< Minor number of the context version to create
Uint32       GLattributeFlags;    //< The attribute flags to create the context with
bool         GLsRgbCapable;       //< Whether the context framebuffer is sRGB capable


PIXELFORMATDESCRIPTOR GlPFDescript;
int GlFormat;

Vector3f ColorWin;
string   ColorCons;


// ������� ���� ������� ����� � ������� ��� ���������
//LCID langId = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);	 
// LCID langId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
LCID langId = MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA);

HANDLE			hConsole  = GetStdHandle(STD_OUTPUT_HANDLE);
HINSTANCE       hInstance = NULL;
HWND			hWnd = NULL;
WindowHandle	handleWin = NULL; // SFML ����
LPTSTR lpClassName;
HGLRC hRC = NULL;
HDC hDC = NULL;

bool fullscreen = TRUE; // ���� �������������� ������ (�� ���������: �������������)
ContextSettings settings; // ��������� OpenGL 
string Title;

}StSysVar;









/**/
#define LANGID StSysVar.langId
/**/
#define STDEF   Style::Default
#define STFULLS Style::Fullscreen

/* ��� ��������� ����, ���������������� ����������� "MENU"  */
//#define MENU
/**/
#define WIDTH   800U
#define HEIGHT  600U
/**/
#define ERRORTXT   SetConsoleTextAttribute(StSysVar.hConsole, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY) // ������� ������ � ���� ����� ���
#define COMENTTXT  SetConsoleTextAttribute(StSysVar.hConsole, BACKGROUND_BLUE | 0x000E | FOREGROUND_INTENSITY) // ������� ������ � ���� ����� ���	
#define DEFAULTTXT SetConsoleTextAttribute(StSysVar.hConsole, BACKGROUND_BLUE | 0x000A | FOREGROUND_INTENSITY) // ������� ������ � ���� ����� ���
/* ����� �������� */
#define OPT_COLORTXT    0x0001UL // ������������ ����� 
#define OPT_STYLEWINFLS 0x0002UL // ������������� �����
#define OPT_VERTICALSYN 0x0004UL // ������������ �������������
#define OPT_CONSOLEDS   0x0008UL // 
#define OPT_DEFAULTSET  0x0010UL //

/* ����� ������� */
#define STAT_ERRORPR		 0x0001UL // ������
#define STAT_INIPR		 0x0002UL // �������������
#define STAT_READYPR		 0x0004UL // ����������
#define STAT_SETPR		 0x0008UL // ���������
#define STAT_RUNPR		 0x0010UL // ����������

#define STAT_TXTCOLREN    0x0100UL // ������������ ����� � �������
#define STAT_FLLSCREN     0x0200UL // ������������� �����
#define STAT_VSYNCEN      0x0400UL // ������������ �������������
#define STAT_CONSEN       0x0800UL // ������� ����������
#define STAT_DEFSETEN     0x1000UL // 
#define STAT_FOCUSWIN     0x2000UL // 




