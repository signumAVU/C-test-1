
CRITICAL_SECTION csStat;

unsigned int GetStat(void);    // ��������� ������
void SetStat(unsigned int );   // ���������� ������
void ClrStat(void);            // �������� ������
void BitClrStat(unsigned int); // �������� ����� ������� �����
void BitSetStat(unsigned int); // ���������� ����� ������� �����
bool InStat(unsigned int);     // ������� �������� ������������ ���

unsigned int GetOptPr(void);    // ��������� ��������� ���������
void SetOptPr(unsigned int);   // ���������� ���������
void ClrOptPr(void);            // �������� ���������
void BitClrOptPr(unsigned int); // �������� ����� ������� �����
void BitSetOptPr(unsigned int); // ���������� ����� ������� �����
bool InOptPr(unsigned int);     // ������� �������� ������������ ���

bool IniPr(void);
bool IniCon(void);
bool IniGl(void);

void Comenttxt(void); 
void Defaulttxt(void);
void Errortxt(void);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int GetStat(void)    // ��������� ������
{
	return Status;
}
void SetStat(unsigned int s)   // ���������� ������
{
	Status = s;
}
void ClrStat(void)            // �������� ������
{
	Status = 0;

}
void BitClrStat(unsigned int s) // �������� ����� ������� �����
{
	//�������������� ����������� ������
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	Status &= ~s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);
}
void BitSetStat(unsigned int s) // ���������� ����� ������� �����
{
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	Status |= s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);

}
bool InStat(unsigned int s)     // ������� �������� ������������ ���
{

	return Status & s ? true : false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int GetOptPr(void)    // ��������� ���������
{
	return OptionsPr;
}
void SetOptPr(unsigned int s)   // ���������� ���������
{
	OptionsPr = s;
}
void ClrOptPr(void)            // �������� ���������
{
	OptionsPr = 0;

}
void BitClrOptPr(unsigned int s) // �������� ����� ������� �����
{
	//�������������� ����������� ������
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	OptionsPr &= ~s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);
}
void BitSetOptPr(unsigned int s) // ���������� ����� ������� �����
{
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	OptionsPr |= s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);

}
bool InOptPr(unsigned int s)     // ������� �������� ������������ ���
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
	/* ��������� ������� */
	setlocale(LC_ALL, "rus");              // ���������� ����������� ���������
	//SetConsoleOutputCP(1251);			   //
	//SetConsoleCP(1251);					   //

	system("cls");                         // ������� �������
	system("color 1A");                    // ���� �������
	//system("mode con cols=165 lines=56");  // ������ �������

	//HWND hConsole = GetConsoleWindow();//���� ���������� ������ �������� �� GetForegroundWindow()
	//ShowWindow(hConsole, SW_HIDE);//���������� ������ ����� �������

	//if (FreeConsole() == false){MyMes(2, GetLastError());} // ��������� �������	
	//if (AllocConsole() == false){MyMes(2, GetLastError());} // �������� �������
	return 0;
}
bool IniGl(void)
{
	int Style_ = 0;
	ContextSettings settings; // ��������� OpenGL 
	
	settings = window.getSettings();
	settings.depthBits = 24;             // ���������� ����� �� ������� ��� ������������� � ������ ������� ( 0 , ����� ��������� ��� )
	settings.stencilBits = 8;            // ���������� ��� �� ������� , ����� ������������ ��� ������ ��������� ( 0 , ����� ��������� ��� )
	settings.antialiasingLevel = 4;      // ������� ���������������
	settings.majorVersion = 3;           // MajorVersion � MinorVersion �������� ������������� ������ OpenGL
	settings.minorVersion = 0;           //


	 // ������������ �����
	if (InOptPr(STYLEWINFLS) != false){ Style_ = STFULLS;  }
	else                              { Style_ = STDEF;  }
	// �������� ����
	window.create(VideoMode(1, 1), "Default Window", Style_, settings);
	window.setSize(Vector2u(WIDTH, HEIGHT));
	settings = window.getSettings();
	Comenttxt();
	cout << endl;
	cout << " ���������� ������� OpenGL :" << endl
	                                       << endl;
	Defaulttxt();
	cout << " Depth Bits :         " << settings.depthBits; Comenttxt(); cout << "   // ���������� ��� �� �������, ������ �������" << endl;
	Defaulttxt();
	cout << " Stencil Bits :       " << settings.stencilBits; Comenttxt(); cout << "   // ���������� ��� �� �������, ������ ���������" << endl;
	Defaulttxt();
	cout << " Antialiasing Level : " << settings.antialiasingLevel; Comenttxt(); cout << "   // ������� ���������������" << endl;
	Defaulttxt();
	cout << " Version :            " << settings.majorVersion << "." << settings.minorVersion; Comenttxt(); cout << "  // MajorVersion � MinorVersion ������ OpenGL" << endl << endl;
	Defaulttxt();
     // ������������ �������������, ����������� ���� ���, ����� �������� ����
	if (Framerat == 0){ Framerat = 60; }
	if (InOptPr(VERTICALSYN) != false){ window.setVerticalSyncEnabled(true);   }
	else                              { window.setFramerateLimit(Framerat);  } //����������� ������ � �������, 
	
	// �������� ������� ����(������������ �������� �����)
	window.setPosition(Vector2i(0, 0));

	// �������� �������� ����
	window.setTitle("SFML window");
	//window.setSize();

	// �������� ������ ����
	Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;
	//cout << "Width X Height : " << width << " X " << height << endl;

	WindowHandle handle = window.getSystemHandle(); // �������� ������ ����, ��� ������ ���� 
	// ������ ����� ������������ handle �� ������������ ��� ������������ ������� ���������
	//WindowHandle handle = /* �������� ��� ���� ��� ������ � ��� ����������, ������� ���������� */;
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


