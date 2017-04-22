///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRITICAL_SECTION csStat;

unsigned int GetStat(void);    // Прочитать статус
void SetStat(unsigned int );   // Установить статус
void ClrStat(void);            // Сбросить статус
void BitClrStat(unsigned int); // Сбросить через битовую маску
void BitSetStat(unsigned int); // Установить через битовую маску
bool InStat(unsigned int);     // Считать значения определенных бит

unsigned int GetOptPr(void);    // Прочитать настройки программы
void SetOptPr(unsigned int);   // Установить настройки
void ClrOptPr(void);            // Сбросить настройки
void BitClrOptPr(unsigned int); // Сбросить через битовую маску
void BitSetOptPr(unsigned int); // Установить через битовую маску
bool InOptPr(unsigned int);     // Считать значения определенных бит

bool IniPr(void);
bool IniCon(void);
bool IniGl(void);

void Comenttxt(void); 
void Defaulttxt(void);
void Errortxt(void);

void resiz(void);
void posit(void);

void PrintOpenGLInfo(void);
void ValidateGLErrors(void);

void Setting(void);

void CloseCons(void); 
void OpenCons(void);

void CrOpenGLCont(int);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int GetStat(void)    // Прочитать статус
{
	return StSysVar.Status;
}
void SetStat(unsigned int s)   // Установить статус
{
	StSysVar.Status = s;
}
void ClrStat(void)            // Сбросить статус
{
	StSysVar.Status = 0;

}
void BitClrStat(unsigned int s) // Сбросить через битовую маску
{
	//Инициализируем критическую секцию
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	StSysVar.Status &= ~s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);
}
void BitSetStat(unsigned int s) // Установить через битовую маску
{
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	StSysVar.Status |= s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);

}
bool InStat(unsigned int s)     // Считать значения определенных бит
{

	return StSysVar.Status & s ? true : false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int GetOptPr(void)    // Прочитать настройки
{
	return StSysVar.OptionsPr;
}
void SetOptPr(unsigned int s)   // Установить настройки
{
	StSysVar.OptionsPr = s;
}
void ClrOptPr(void)            // Сбросить настройки
{
	StSysVar.OptionsPr = 0;

}
void BitClrOptPr(unsigned int s) // Сбросить через битовую маску
{
	//Инициализируем критическую секцию
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	StSysVar.OptionsPr &= ~s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);
}
void BitSetOptPr(unsigned int s) // Установить через битовую маску
{
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	StSysVar.OptionsPr |= s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);

}
bool InOptPr(unsigned int s)     // Считать значения определенных бит
{
	return StSysVar.OptionsPr & s ? true : false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IniPr(void)
{
	
	Setting();
	
	if (InOptPr(OPT_DEFAULTSET) != false)
	{
		StSysVar.Title = "SFML window";
		StSysVar.SysHeight = HEIGHT;
		StSysVar.SysWidth = WIDTH;
		BitSetStat(STAT_INIPR);
		BitSetOptPr(OPT_COLORTXT | OPT_VERTICALSYN );//| OPT_STYLEWINFLS
		BitSetStat(STAT_DEFSETEN | STAT_CONSEN | STAT_VSYNCEN | STAT_TXTCOLREN);

		StSysVar.GLdepthBits = 24;
		StSysVar.GLstencilBits = 8;
		StSysVar.GLantialiasingLevel = 8;
		StSysVar.GLmajorVersion = 4;
		StSysVar.GLminorVersion = 2;

	}
	IniCon();
	IniGl();
	BitClrStat(STAT_INIPR);
	BitSetStat(STAT_READYPR);
	return 0;
}
bool IniCon(void)
{
	/* Настройки консоли */
	if (InOptPr(OPT_CONSOLEDS) != false)
	{
		ShowWindow(StSysVar.hWnd, SW_HIDE); 
		BitClrStat(STAT_CONSEN); //собственно прячем оконо консоли
	}
	else{
		setlocale(LC_ALL, "rus");                // Корректное отображение Кириллицы

		//system("mode con cp select=1251"); // -установить кодовую страницу номер 1251 (Windows - кодировка)
		system("mode con cp select=866");  // -установить кодовую страницу номер 866 (DOS - кодировка)
		//system("pause");
		system("cls");                           // Очистка консоли
		system("color 1A");                      // Цвет консоли
		//system("mode con cols=165 lines=56");  // Размер консоли
		system("mode CON /STATUS");
		//cout << "Русский " << endl;

		//system("pause");
	}
	
	//window.create(VideoMode(1, 1), "Default Window", Style::Fullscreen);
#ifdef MENU
	menu(window);//вызов меню
#endif	

	//if (FreeConsole() == false){MyMes(2, GetLastError());} // Выключить консоль	
	
	//if (AllocConsole() == false){MyMes(2, GetLastError());} // Включить консоль
	return 0;
}
bool IniGl(void)
{
	int Style_ = 0;
	
	CrOpenGLCont(42);
	ValidateGLErrors();
	//PrintOpenGLInfo();
	StSysVar.settings                   = window.getSettings();
	//Defaulttxt();
	//cout << " Version :            " << StSysVar.settings.majorVersion << "." << StSysVar.settings.minorVersion; Comenttxt(); cout << "  // MajorVersion и MinorVersion версия OpenGL" << endl << endl;
	//Defaulttxt();

	StSysVar.settings.depthBits         = StSysVar.GLdepthBits;             // количество битов на пиксель для использования в буфере глубины ( 0 , чтобы отключить его )
	StSysVar.settings.stencilBits       = StSysVar.GLstencilBits;           // количество бит на пиксель , чтобы использовать для буфера трафарета ( 0 , чтобы отключить его )
	StSysVar.settings.antialiasingLevel = StSysVar.GLantialiasingLevel;     // уровень мультисэмплинга
	StSysVar.settings.majorVersion      = StSysVar.GLmajorVersion;          // MajorVersion и MinorVersion содержат запрашиваемую версию OpenGL
	StSysVar.settings.minorVersion      = StSysVar.GLminorVersion;          //
	
	
	 // Полнэкранный режим
	if (InOptPr(OPT_STYLEWINFLS) != false){ Style_ = STFULLS;  BitSetStat(STAT_FLLSCREN); StSysVar.fullscreen = true; }
	else                                  { Style_ = STDEF;    BitClrStat(STAT_FLLSCREN); StSysVar.fullscreen = false; }
	// Создание окна
	window.create(VideoMode(StSysVar.SysWidth, StSysVar.SysHeight), "Default Window", Style_, StSysVar.settings);
	window.setSize(Vector2u(StSysVar.SysWidth, StSysVar.SysHeight));

	/* умножаем размер экрана на 2 с использованием sf::View и все картинки рисуются в 2 раза выше и шире. */
	//View view;
	//view.reset(FloatRect(0.0f, 0.0f, StSysVar.SysWidth, StSysVar.SysHeight));
	//view.setViewport(FloatRect(0.0f, 0.0f, 2.0f, 2.0f));
	
	StSysVar.handleWin = window.getSystemHandle(); // Получаем хендел окна, для разных нужд
	StSysVar.hInstance = (HINSTANCE)GetWindowLongPtr(StSysVar.handleWin, GWL_HINSTANCE);
	/*Функция GetClassName извлекает данные об имени класса, которому принадлежит указанное окно.*/
	if (!GetClassName(StSysVar.handleWin, StSysVar.lpClassName, 64)){ MyMes(2, GetLastError());}
	//cout <<" lpClassName : "<< StSysVar.lpClassName << endl;
	//GetModuleHandle(NULL);

	StSysVar.settings = window.getSettings();

	Comenttxt();
	cout << endl;
	cout << " Включенные функции OpenGL :" << endl
	                                       << endl;
	Defaulttxt();
	cout << " Depth Bits :         " << StSysVar.settings.depthBits; Comenttxt(); cout << "   // Количество бит на пиксель, буфера глубины" << endl;
	Defaulttxt();
	cout << " Stencil Bits :       " << StSysVar.settings.stencilBits; Comenttxt(); cout << "   // Количество бит на пиксель, буфера трафарета" << endl;
	Defaulttxt();
	cout << " Antialiasing Level : " << StSysVar.settings.antialiasingLevel; Comenttxt(); cout << "   // Уровень мультисэмплинга" << endl;
	Defaulttxt();
	cout << " Version :            " << StSysVar.settings.majorVersion << "." << StSysVar.settings.minorVersion; Comenttxt(); 
    cout << "  // MajorVersion и MinorVersion версия OpenGL" << endl << endl;
	Defaulttxt();

     // Вертикальная синхронизация, запускается один раз, после создания окна
	if (StSysVar.Framerat == 0){ StSysVar.Framerat = 60; }
	if (InOptPr(OPT_VERTICALSYN) != false){ window.setVerticalSyncEnabled(true);         BitSetStat(STAT_VSYNCEN); }
	else                                  { window.setFramerateLimit(StSysVar.Framerat); BitClrStat(STAT_VSYNCEN); } //Ограничение кадров в секунду, 
	
	// изменяет позиции окна(относительно рабочего стола)
	window.setPosition(Vector2i(StSysVar.SysPositWinX, StSysVar.SysPositWinX));
	
	// изменяет название окна
	window.setTitle(StSysVar.Title);
	//window.setSize();

		
	// теперь можно использовать handle со специфичными для операционной системы функциями
	//WindowHandle handle = /* отдельно для того что делаем и для библиотеки, которую используем */;
#if 0
	Window window(handle);
#endif	
	//MyMes(1, 0);
	//MyMes(3, 0);
	return 0;
}

void Comenttxt(void)
{
	if (InOptPr(OPT_COLORTXT) != false)
	{
		COMENTTXT;
	}
}

void Defaulttxt(void)
{
	if (InOptPr(OPT_COLORTXT) != false)
	{
		DEFAULTTXT;
	}
}

void Errortxt(void)
{
	if (InOptPr(OPT_COLORTXT) != false)
	{
		ERRORTXT;
	}
}
void resiz(void)
{
Vector2u size = window.getSize();
unsigned int width = size.x;
unsigned int height = size.y;

StSysVar.SysWidth = width;
StSysVar.SysHeight = height;

cout << " Размер окна изменен на: " << endl;
cout << " Ширина: " << width << endl;
cout << " Высота: "<< height << endl << endl;
}
void posit(void)
{
	Vector2i posit = window.getPosition();
	int x = posit.x;
	int y = posit.y;

	StSysVar.SysPositWinX = x;
	StSysVar.SysPositWinY = y;

	cout << " Позиция окна по х: " << x << " по y: " << y << endl << endl;

}

void ValidateGLErrors(void)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		string message;
		// с помощью switch превращаем GLenum в строковое описание
		// печатаем строку или делаем ещё что-то в целях отладки
		switch (error)
		{
		case GL_INVALID_ENUM:
			message = " Invalid enum passed to GL function: \n (GL_INVALID_ENUM) ";
			break;
		case GL_INVALID_VALUE:
			message = " Invalid parameter passed to GL function: \n (GL_INVALID_VALUE)";
			break;
		case GL_INVALID_OPERATION:
			message = " Cannot execute some of GL functions in current state: \n (GL_INVALID_OPERATION)";
			break;
		case GL_STACK_OVERFLOW:
			message = " Matrix stack overflow occured inside GL: \n (GL_STACK_OVERFLOW)";
			break;
		case GL_STACK_UNDERFLOW:
			message = " Matrix stack underflow occured inside GL: \n (GL_STACK_UNDERFLOW)";
			break;
		case GL_OUT_OF_MEMORY:
			message = " No enough memory to execute GL function: \n (GL_OUT_OF_MEMORY)";
			break;
		default:
			message = " Error in some GL extension: \n (framebuffers, shaders, etc)";
			break;
		}
		Errortxt();
		cout << " OpenGL error: " << message << endl;
		Defaulttxt();
		//std::cerr << "OpenGL error: " << message << std::endl;
		//std::abort();
	}else
	{
		//Comenttxt();
		//cout << " OpenGL no error: "  << endl;
		//Defaulttxt();
	}
}

void PrintOpenGLInfo(void)
{
	
	//ValidateGLErrors();
}
void Setting(void)
{
	ClrStat();
	ClrOptPr();
	BitSetOptPr(OPT_DEFAULTSET);
}

void CloseCons(void)
{
	
	if (FreeConsole() == false){ MyMes(2, GetLastError()); } // Выключить консоль
	BitClrStat(STAT_CONSEN);
}
void OpenCons(void)
{
	
	if (AllocConsole() == false){ MyMes(2, GetLastError()); } // Включить консоль
	BitSetStat(STAT_CONSEN);
	
}



void CrOpenGLCont(int ver) // Создание контекста
{
	int format;
	int major, mj, mi;
	int minor;
	MyMes(2, -1);
	if (ver == 30){ mj = 3; mi = 0;}else
	if (ver == 32){ mj = 3; mi = 2;}else
	if (ver == 33){ mj = 3; mi = 3;}else
    if (ver == 40){ mj = 4; mi = 0;}else
	if (ver == 42){ mj = 4; mi = 2;}else{ mj = 2; mi = 0; }
	//StSysVar.hWnd = GetConsoleWindow();       //Если компилятор старый заменить на GetForegroundWindow(), если прятать консоль нам понадобится

	StSysVar.hWnd = StSysVar.handleWin;
	
	StSysVar.hDC = GetDC(StSysVar.hWnd);
	
	if (!StSysVar.hDC)
	{
		MyMes(2, GetLastError());
		Errortxt();
		cout << " GetDC fail" << endl;
		Defaulttxt();
		return;
	}
	/* обнулим структуру с описанием формата пикселей и сохраним ее размер */
	memset(&StSysVar.GlPFDescript, 0, sizeof(StSysVar.GlPFDescript));
	StSysVar.GlPFDescript.nSize     = sizeof(StSysVar.GlPFDescript);

	
	StSysVar.GlPFDescript.nVersion = 1; // согласно MSDN версия всегда равна 1

	/* нас интересует поддержка окном OpenGL и двойного буфера */
	StSysVar.GlPFDescript.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;	
	StSysVar.GlPFDescript.iPixelType = PFD_TYPE_RGBA; // пиксель с цветовыми компонентами RGBA	
	StSysVar.GlPFDescript.cColorBits = 32; // 32 бита на цвет, по 8 на каждую компоненту	
	StSysVar.GlPFDescript.cDepthBits = StSysVar.GLdepthBits; //24 разрядность буфера глубины определяет его точность

	// попробуем выбрать формат один из системных форматов пикселей
	format = ChoosePixelFormat(StSysVar.hDC, &StSysVar.GlPFDescript);
	if (!format || !SetPixelFormat(StSysVar.hDC, format, &StSysVar.GlPFDescript))
	{
		MyMes(2, GetLastError());
		Errortxt();
		cout << " Setting pixel format fail" << endl;
		Defaulttxt();
		return;
	}
	// создадим временный контекст OpenGL
	HGLRC hRCTemp = wglCreateContext(StSysVar.hDC);

	// если не получилось создать контекст или контекст не устанавливается для нашего окна
	if (!hRCTemp || !wglMakeCurrent(StSysVar.hDC, hRCTemp))
	{
		MyMes(2, GetLastError());
		Errortxt();
		cout << " Сreating temp render context fail " << endl;
		Defaulttxt();
		return ;
	}
	else{
		   
	    }

	// определим указатель на функцию создания расширенного контекста OpenGL 3....
	// PFNWGLCREATECONTEXTATTRIBSARBPROC берется из файла wglext.h

	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

	// получим адрес функции создания расширенного контекста OpenGL
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	// временный контекст OpenGL нам больше не нужен, удаляем его
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRCTemp);

	// если драйвер видеокарты не предоставил нам адрес этой функции
	if (!wglCreateContextAttribsARB)
	{
		MyMes(2, GetLastError());
		Errortxt();
		cout << " wglCreateContextAttribsARB fail "  << endl;
		Defaulttxt();
		return ;
	}
	// укажем атрибуты для создания расширенного контекста OpenGL 3...
	// атрибуты установлены согласно спецификации расширения:

	// WGL_CONTEXT_MAJOR_VERSION_ARB - старшая цифра необходимой версии

	// WGL_CONTEXT_MINOR_VERSION_ARB - младшая цифра необходимой версии

	// WGL_CONTEXT_FLAGS_ARB - флаги контекста, для нас это контекст с поддержкой
	//    нового функционала WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB

	// WGL_CONTEXT_PROFILE_MASK_ARB - профиль создаваемого контекста, выбираем
	//    WGL_CONTEXT_CORE_PROFILE_BIT_ARB, все устройства с OpenGL 3.2 и старше
	//    должны поддерживать профиль CORE, этот профиль позволяет получить доступ
	//    к новому функционалу и говорит об отказе от устаревшего функционала

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, mj,
		WGL_CONTEXT_MINOR_VERSION_ARB, mi,
		WGL_CONTEXT_FLAGS_ARB, 
		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, 
		WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	// пробуем создать контекст с поддержкой OpenGL 3...
	StSysVar.hRC = wglCreateContextAttribsARB(StSysVar.hDC, 0, attribs);

	// если создать контекст не получилось или он не устанавливается для нашего окна
	if (!StSysVar.hRC || !wglMakeCurrent(StSysVar.hDC, StSysVar.hRC))
	{
		MyMes(2, GetLastError());
		Errortxt();
		cout << " Creating render context fail " << endl;
		Defaulttxt();
		return ;
	}
	
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << " После создания контекста : " << endl;
	cout << " Major и Minor версия VersionOpenGL : " 
		 << major << '.' <<  minor << endl;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 
	Интерфейс IOperation предназначен для выполнения операции в одном потоке, 
	интерфейс IOperationC может выполняться в нескольких потоках. 
	Функция Do() выполняет операцию, после чего обращений к этой операции не будет, 
	поэтому в функции необходимо освободить все данные. 
	Функция Free() предназначена для освобождения данных, если не удалось добавить операцию в очередь потока. 
	Функция SetCounter(int) передает количество потоков в которые добавлена эта операция, 
	при вызове функции Do() необходимо уменьшать счетчик на 1, а когда счетчик будет равен 0 - освободить данные. */
class IOperation
{
public:
	virtual void Do() = 0;
	virtual void Free() = 0;
};

class IOperationC : public IOperation
{
public:
	virtual void SetCounter(int) = 0;
};


