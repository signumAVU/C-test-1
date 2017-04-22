#pragma once

#ifndef CDS_FULLSCREEN        // CDS_FULLSCREEN не определяется некоторыми
#define CDS_FULLSCREEN 4      // компиляторами. Определяем эту константу
#endif                        // Таким образом мы можем избежать ошибок


#define SFML 

//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;
using namespace sf;


sf::RenderWindow window;

GLfloat xrot;         // X вращение
GLfloat yrot;         // Y вращение
GLfloat zrot;         // Y вращение
GLfloat zspeed;       // X скорость вращения
GLfloat xspeed;       // X скорость вращения
GLfloat yspeed;       // Y скорость вращения
GLuint filter;         // Какой фильтр использовать
GLfloat z = -5.0f;      // Сдвиг вглубь экрана


struct SysVar
{

unsigned int Status;	    // Статус программы
unsigned int OptionsPr;     // Настройки программы
signed   int ErrCode;	    // Коды ошибок
int          Framerat;	    // Кадров в секунду

unsigned int SysWidth;	    // Ширина окна
unsigned int SysHeight;  	// Высота окна
unsigned int SysPositWinX;	// Позиция окна X
unsigned int SysPositWinY;	// Позиция окна Y

unsigned int SysWidthCons;	// Ширина консоли
unsigned int SysHeightCons;	// Высота консоли
unsigned int SysPositConsX;	// Позиция консоли X
unsigned int SysPositConsY;	// Позиция консоли Y

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


// Выбрать свой вариант языка и локации для сообщений
//LCID langId = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);	 
// LCID langId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
LCID langId = MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA);

HANDLE			hConsole  = GetStdHandle(STD_OUTPUT_HANDLE);
HINSTANCE       hInstance = NULL;
HWND			hWnd = NULL;
WindowHandle	handleWin = NULL; // SFML окно
LPTSTR lpClassName;
HGLRC hRC = NULL;
HDC hDC = NULL;

bool fullscreen = TRUE; // Флаг полноэкранного режима (по умолчанию: полноэкранное)
ContextSettings settings; // настройки OpenGL 
string Title;

}StSysVar;









/**/
#define LANGID StSysVar.langId
/**/
#define STDEF   Style::Default
#define STFULLS Style::Fullscreen

/* Для включения меню, разкоментировать определение "MENU"  */
//#define MENU
/**/
#define WIDTH   800U
#define HEIGHT  600U
/**/
#define ERRORTXT   SetConsoleTextAttribute(StSysVar.hConsole, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY) // окраска текста и фона перед ним
#define COMENTTXT  SetConsoleTextAttribute(StSysVar.hConsole, BACKGROUND_BLUE | 0x000E | FOREGROUND_INTENSITY) // окраска текста и фона перед ним	
#define DEFAULTTXT SetConsoleTextAttribute(StSysVar.hConsole, BACKGROUND_BLUE | 0x000A | FOREGROUND_INTENSITY) // окраска текста и фона перед ним
/* флаги настроек */
#define OPT_COLORTXT    0x0001UL // Подкрашивать текст 
#define OPT_STYLEWINFLS 0x0002UL // Полноэкранный режим
#define OPT_VERTICALSYN 0x0004UL // Вертикальная синхронизация
#define OPT_CONSOLEDS   0x0008UL // 
#define OPT_DEFAULTSET  0x0010UL //

/* Флаги статуса */
#define STAT_ERRORPR		 0x0001UL // Ошибка
#define STAT_INIPR		 0x0002UL // Инициализация
#define STAT_READYPR		 0x0004UL // Готовность
#define STAT_SETPR		 0x0008UL // Установки
#define STAT_RUNPR		 0x0010UL // Выполнение

#define STAT_TXTCOLREN    0x0100UL // Подкрашивать текст в консоли
#define STAT_FLLSCREN     0x0200UL // Полноэкранный режим
#define STAT_VSYNCEN      0x0400UL // Вертикальная синхронизация
#define STAT_CONSEN       0x0800UL // Консоль разрешенна
#define STAT_DEFSETEN     0x1000UL // 
#define STAT_FOCUSWIN     0x2000UL // 




