
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int GetStat(void)    // Прочитать статус
{
	return Status;
}
void SetStat(unsigned int s)   // Установить статус
{
	Status = s;
}
void ClrStat(void)            // Сбросить статус
{
	Status = 0;

}
void BitClrStat(unsigned int s) // Сбросить через битовую маску
{
	//Инициализируем критическую секцию
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	Status &= ~s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);
}
void BitSetStat(unsigned int s) // Установить через битовую маску
{
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	Status |= s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);

}
bool InStat(unsigned int s)     // Считать значения определенных бит
{

	return Status & s ? true : false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int GetOptPr(void)    // Прочитать настройки
{
	return OptionsPr;
}
void SetOptPr(unsigned int s)   // Установить настройки
{
	OptionsPr = s;
}
void ClrOptPr(void)            // Сбросить настройки
{
	OptionsPr = 0;

}
void BitClrOptPr(unsigned int s) // Сбросить через битовую маску
{
	//Инициализируем критическую секцию
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	OptionsPr &= ~s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);
}
void BitSetOptPr(unsigned int s) // Установить через битовую маску
{
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	OptionsPr |= s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);

}
bool InOptPr(unsigned int s)     // Считать значения определенных бит
{
	return OptionsPr & s ? true : false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IniPr(void)
{
	ClrStat();
	ClrOptPr();
	BitSetOptPr(COLORTXT | VERTICALSYN);
	IniCon();
	IniGl();
	return 0;
}
bool IniCon(void)
{
	/* Настройки консоли */
	setlocale(LC_ALL, "rus");              // Корректное отображение Кириллицы
	//SetConsoleOutputCP(1251);			   //
	//SetConsoleCP(1251);					   //

	system("cls");                         // Очистка консоли
	system("color 1A");                    // Цвет консоли
	//system("mode con cols=165 lines=56");  // Размер консоли

	//HWND hConsole = GetConsoleWindow();//Если компилятор старый заменить на GetForegroundWindow()
	//ShowWindow(hConsole, SW_HIDE);//собственно прячем оконо консоли

	//if (FreeConsole() == false){MyMes(2, GetLastError());} // Выключить консоль	
	//if (AllocConsole() == false){MyMes(2, GetLastError());} // Включить консоль
	return 0;
}
bool IniGl(void)
{
	int Style_ = 0;
	ContextSettings settings; // настройки OpenGL 
	
	settings = window.getSettings();
	settings.depthBits = 24;             // количество битов на пиксель для использования в буфере глубины ( 0 , чтобы отключить его )
	settings.stencilBits = 8;            // количество бит на пиксель , чтобы использовать для буфера трафарета ( 0 , чтобы отключить его )
	settings.antialiasingLevel = 4;      // уровень мультисэмплинга
	settings.majorVersion = 3;           // MajorVersion и MinorVersion содержат запрашиваемую версию OpenGL
	settings.minorVersion = 0;           //


	 // Полнэкранный режим
	if (InOptPr(STYLEWINFLS) != false){ Style_ = STFULLS;  }
	else                              { Style_ = STDEF;  }
	// Создание окна
	window.create(VideoMode(1, 1), "Default Window", Style_, settings);
	window.setSize(Vector2u(WIDTH, HEIGHT));
	settings = window.getSettings();
	Comenttxt();
	cout << endl;
	cout << " Включенные функции OpenGL :" << endl
	                                       << endl;
	Defaulttxt();
	cout << " Depth Bits :         " << settings.depthBits; Comenttxt(); cout << "   // Количество бит на пиксель, буфера глубины" << endl;
	Defaulttxt();
	cout << " Stencil Bits :       " << settings.stencilBits; Comenttxt(); cout << "   // Количество бит на пиксель, буфера трафарета" << endl;
	Defaulttxt();
	cout << " Antialiasing Level : " << settings.antialiasingLevel; Comenttxt(); cout << "   // Уровень мультисэмплинга" << endl;
	Defaulttxt();
	cout << " Version :            " << settings.majorVersion << "." << settings.minorVersion; Comenttxt(); cout << "  // MajorVersion и MinorVersion версия OpenGL" << endl << endl;
	Defaulttxt();
     // Вертикальная синхронизация, запускается один раз, после создания окна
	if (Framerat == 0){ Framerat = 60; }
	if (InOptPr(VERTICALSYN) != false){ window.setVerticalSyncEnabled(true);   }
	else                              { window.setFramerateLimit(Framerat);  } //Ограничение кадров в секунду, 
	
	// изменяет позиции окна(относительно рабочего стола)
	window.setPosition(Vector2i(0, 0));

	// изменяет название окна
	window.setTitle("SFML window");
	//window.setSize();

	// получаем размер окна
	Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;
	//cout << "Width X Height : " << width << " X " << height << endl;

	WindowHandle handle = window.getSystemHandle(); // Получаем хендел окна, для разных нужд 
	// теперь можно использовать handle со специфичными для операционной системы функциями
	//WindowHandle handle = /* отдельно для того что делаем и для библиотеки, которую используем */;
#if 0
	Window window(handle);
#endif	
	MyMes(1, 0);
	MyMes(3, 0);
	return 0;
}

void Comenttxt(void)
{
	if (InOptPr(COLORTXT) != false)
	{
		COMENTTXT;
	}
}

void Defaulttxt(void)
{
	if (InOptPr(COLORTXT) != false)
	{
		DEFAULTTXT;
	}
}

void Errortxt(void)
{
	if (InOptPr(COLORTXT) != false)
	{
		ERRORTXT;
	}
}


