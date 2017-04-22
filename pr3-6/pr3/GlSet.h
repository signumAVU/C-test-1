///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

void resiz(void);
void posit(void);

void PrintOpenGLInfo(void);
void ValidateGLErrors(void);

void Setting(void);

void CloseCons(void); 
void OpenCons(void);

void CrOpenGLCont(int);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int GetStat(void)    // ��������� ������
{
	return StSysVar.Status;
}
void SetStat(unsigned int s)   // ���������� ������
{
	StSysVar.Status = s;
}
void ClrStat(void)            // �������� ������
{
	StSysVar.Status = 0;

}
void BitClrStat(unsigned int s) // �������� ����� ������� �����
{
	//�������������� ����������� ������
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	StSysVar.Status &= ~s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);
}
void BitSetStat(unsigned int s) // ���������� ����� ������� �����
{
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	StSysVar.Status |= s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);

}
bool InStat(unsigned int s)     // ������� �������� ������������ ���
{

	return StSysVar.Status & s ? true : false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int GetOptPr(void)    // ��������� ���������
{
	return StSysVar.OptionsPr;
}
void SetOptPr(unsigned int s)   // ���������� ���������
{
	StSysVar.OptionsPr = s;
}
void ClrOptPr(void)            // �������� ���������
{
	StSysVar.OptionsPr = 0;

}
void BitClrOptPr(unsigned int s) // �������� ����� ������� �����
{
	//�������������� ����������� ������
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	StSysVar.OptionsPr &= ~s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);
}
void BitSetOptPr(unsigned int s) // ���������� ����� ������� �����
{
	InitializeCriticalSection(&csStat);
	EnterCriticalSection(&csStat);
	StSysVar.OptionsPr |= s;
	LeaveCriticalSection(&csStat);
	DeleteCriticalSection(&csStat);

}
bool InOptPr(unsigned int s)     // ������� �������� ������������ ���
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
	/* ��������� ������� */
	if (InOptPr(OPT_CONSOLEDS) != false)
	{
		ShowWindow(StSysVar.hWnd, SW_HIDE); 
		BitClrStat(STAT_CONSEN); //���������� ������ ����� �������
	}
	else{
		setlocale(LC_ALL, "rus");                // ���������� ����������� ���������

		//system("mode con cp select=1251"); // -���������� ������� �������� ����� 1251 (Windows - ���������)
		system("mode con cp select=866");  // -���������� ������� �������� ����� 866 (DOS - ���������)
		//system("pause");
		system("cls");                           // ������� �������
		system("color 1A");                      // ���� �������
		//system("mode con cols=165 lines=56");  // ������ �������
		system("mode CON /STATUS");
		//cout << "������� " << endl;

		//system("pause");
	}
	
	//window.create(VideoMode(1, 1), "Default Window", Style::Fullscreen);
#ifdef MENU
	menu(window);//����� ����
#endif	

	//if (FreeConsole() == false){MyMes(2, GetLastError());} // ��������� �������	
	
	//if (AllocConsole() == false){MyMes(2, GetLastError());} // �������� �������
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
	//cout << " Version :            " << StSysVar.settings.majorVersion << "." << StSysVar.settings.minorVersion; Comenttxt(); cout << "  // MajorVersion � MinorVersion ������ OpenGL" << endl << endl;
	//Defaulttxt();

	StSysVar.settings.depthBits         = StSysVar.GLdepthBits;             // ���������� ����� �� ������� ��� ������������� � ������ ������� ( 0 , ����� ��������� ��� )
	StSysVar.settings.stencilBits       = StSysVar.GLstencilBits;           // ���������� ��� �� ������� , ����� ������������ ��� ������ ��������� ( 0 , ����� ��������� ��� )
	StSysVar.settings.antialiasingLevel = StSysVar.GLantialiasingLevel;     // ������� ���������������
	StSysVar.settings.majorVersion      = StSysVar.GLmajorVersion;          // MajorVersion � MinorVersion �������� ������������� ������ OpenGL
	StSysVar.settings.minorVersion      = StSysVar.GLminorVersion;          //
	
	
	 // ������������ �����
	if (InOptPr(OPT_STYLEWINFLS) != false){ Style_ = STFULLS;  BitSetStat(STAT_FLLSCREN); StSysVar.fullscreen = true; }
	else                                  { Style_ = STDEF;    BitClrStat(STAT_FLLSCREN); StSysVar.fullscreen = false; }
	// �������� ����
	window.create(VideoMode(StSysVar.SysWidth, StSysVar.SysHeight), "Default Window", Style_, StSysVar.settings);
	window.setSize(Vector2u(StSysVar.SysWidth, StSysVar.SysHeight));

	/* �������� ������ ������ �� 2 � �������������� sf::View � ��� �������� �������� � 2 ���� ���� � ����. */
	//View view;
	//view.reset(FloatRect(0.0f, 0.0f, StSysVar.SysWidth, StSysVar.SysHeight));
	//view.setViewport(FloatRect(0.0f, 0.0f, 2.0f, 2.0f));
	
	StSysVar.handleWin = window.getSystemHandle(); // �������� ������ ����, ��� ������ ����
	StSysVar.hInstance = (HINSTANCE)GetWindowLongPtr(StSysVar.handleWin, GWL_HINSTANCE);
	/*������� GetClassName ��������� ������ �� ����� ������, �������� ����������� ��������� ����.*/
	if (!GetClassName(StSysVar.handleWin, StSysVar.lpClassName, 64)){ MyMes(2, GetLastError());}
	//cout <<" lpClassName : "<< StSysVar.lpClassName << endl;
	//GetModuleHandle(NULL);

	StSysVar.settings = window.getSettings();

	Comenttxt();
	cout << endl;
	cout << " ���������� ������� OpenGL :" << endl
	                                       << endl;
	Defaulttxt();
	cout << " Depth Bits :         " << StSysVar.settings.depthBits; Comenttxt(); cout << "   // ���������� ��� �� �������, ������ �������" << endl;
	Defaulttxt();
	cout << " Stencil Bits :       " << StSysVar.settings.stencilBits; Comenttxt(); cout << "   // ���������� ��� �� �������, ������ ���������" << endl;
	Defaulttxt();
	cout << " Antialiasing Level : " << StSysVar.settings.antialiasingLevel; Comenttxt(); cout << "   // ������� ���������������" << endl;
	Defaulttxt();
	cout << " Version :            " << StSysVar.settings.majorVersion << "." << StSysVar.settings.minorVersion; Comenttxt(); 
    cout << "  // MajorVersion � MinorVersion ������ OpenGL" << endl << endl;
	Defaulttxt();

     // ������������ �������������, ����������� ���� ���, ����� �������� ����
	if (StSysVar.Framerat == 0){ StSysVar.Framerat = 60; }
	if (InOptPr(OPT_VERTICALSYN) != false){ window.setVerticalSyncEnabled(true);         BitSetStat(STAT_VSYNCEN); }
	else                                  { window.setFramerateLimit(StSysVar.Framerat); BitClrStat(STAT_VSYNCEN); } //����������� ������ � �������, 
	
	// �������� ������� ����(������������ �������� �����)
	window.setPosition(Vector2i(StSysVar.SysPositWinX, StSysVar.SysPositWinX));
	
	// �������� �������� ����
	window.setTitle(StSysVar.Title);
	//window.setSize();

		
	// ������ ����� ������������ handle �� ������������ ��� ������������ ������� ���������
	//WindowHandle handle = /* �������� ��� ���� ��� ������ � ��� ����������, ������� ���������� */;
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

cout << " ������ ���� ������� ��: " << endl;
cout << " ������: " << width << endl;
cout << " ������: "<< height << endl << endl;
}
void posit(void)
{
	Vector2i posit = window.getPosition();
	int x = posit.x;
	int y = posit.y;

	StSysVar.SysPositWinX = x;
	StSysVar.SysPositWinY = y;

	cout << " ������� ���� �� �: " << x << " �� y: " << y << endl << endl;

}

void ValidateGLErrors(void)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		string message;
		// � ������� switch ���������� GLenum � ��������� ��������
		// �������� ������ ��� ������ ��� ���-�� � ����� �������
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
	
	if (FreeConsole() == false){ MyMes(2, GetLastError()); } // ��������� �������
	BitClrStat(STAT_CONSEN);
}
void OpenCons(void)
{
	
	if (AllocConsole() == false){ MyMes(2, GetLastError()); } // �������� �������
	BitSetStat(STAT_CONSEN);
	
}



void CrOpenGLCont(int ver) // �������� ���������
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
	//StSysVar.hWnd = GetConsoleWindow();       //���� ���������� ������ �������� �� GetForegroundWindow(), ���� ������� ������� ��� �����������

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
	/* ������� ��������� � ��������� ������� �������� � �������� �� ������ */
	memset(&StSysVar.GlPFDescript, 0, sizeof(StSysVar.GlPFDescript));
	StSysVar.GlPFDescript.nSize     = sizeof(StSysVar.GlPFDescript);

	
	StSysVar.GlPFDescript.nVersion = 1; // �������� MSDN ������ ������ ����� 1

	/* ��� ���������� ��������� ����� OpenGL � �������� ������ */
	StSysVar.GlPFDescript.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;	
	StSysVar.GlPFDescript.iPixelType = PFD_TYPE_RGBA; // ������� � ��������� ������������ RGBA	
	StSysVar.GlPFDescript.cColorBits = 32; // 32 ���� �� ����, �� 8 �� ������ ����������	
	StSysVar.GlPFDescript.cDepthBits = StSysVar.GLdepthBits; //24 ����������� ������ ������� ���������� ��� ��������

	// ��������� ������� ������ ���� �� ��������� �������� ��������
	format = ChoosePixelFormat(StSysVar.hDC, &StSysVar.GlPFDescript);
	if (!format || !SetPixelFormat(StSysVar.hDC, format, &StSysVar.GlPFDescript))
	{
		MyMes(2, GetLastError());
		Errortxt();
		cout << " Setting pixel format fail" << endl;
		Defaulttxt();
		return;
	}
	// �������� ��������� �������� OpenGL
	HGLRC hRCTemp = wglCreateContext(StSysVar.hDC);

	// ���� �� ���������� ������� �������� ��� �������� �� ��������������� ��� ������ ����
	if (!hRCTemp || !wglMakeCurrent(StSysVar.hDC, hRCTemp))
	{
		MyMes(2, GetLastError());
		Errortxt();
		cout << " �reating temp render context fail " << endl;
		Defaulttxt();
		return ;
	}
	else{
		   
	    }

	// ��������� ��������� �� ������� �������� ������������ ��������� OpenGL 3....
	// PFNWGLCREATECONTEXTATTRIBSARBPROC ������� �� ����� wglext.h

	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

	// ������� ����� ������� �������� ������������ ��������� OpenGL
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	// ��������� �������� OpenGL ��� ������ �� �����, ������� ���
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRCTemp);

	// ���� ������� ���������� �� ����������� ��� ����� ���� �������
	if (!wglCreateContextAttribsARB)
	{
		MyMes(2, GetLastError());
		Errortxt();
		cout << " wglCreateContextAttribsARB fail "  << endl;
		Defaulttxt();
		return ;
	}
	// ������ �������� ��� �������� ������������ ��������� OpenGL 3...
	// �������� ����������� �������� ������������ ����������:

	// WGL_CONTEXT_MAJOR_VERSION_ARB - ������� ����� ����������� ������

	// WGL_CONTEXT_MINOR_VERSION_ARB - ������� ����� ����������� ������

	// WGL_CONTEXT_FLAGS_ARB - ����� ���������, ��� ��� ��� �������� � ����������
	//    ������ ����������� WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB

	// WGL_CONTEXT_PROFILE_MASK_ARB - ������� ������������ ���������, ��������
	//    WGL_CONTEXT_CORE_PROFILE_BIT_ARB, ��� ���������� � OpenGL 3.2 � ������
	//    ������ ������������ ������� CORE, ���� ������� ��������� �������� ������
	//    � ������ ����������� � ������� �� ������ �� ����������� �����������

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

	// ������� ������� �������� � ���������� OpenGL 3...
	StSysVar.hRC = wglCreateContextAttribsARB(StSysVar.hDC, 0, attribs);

	// ���� ������� �������� �� ���������� ��� �� �� ��������������� ��� ������ ����
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
	cout << " ����� �������� ��������� : " << endl;
	cout << " Major � Minor ������ VersionOpenGL : " 
		 << major << '.' <<  minor << endl;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 
	��������� IOperation ������������ ��� ���������� �������� � ����� ������, 
	��������� IOperationC ����� ����������� � ���������� �������. 
	������� Do() ��������� ��������, ����� ���� ��������� � ���� �������� �� �����, 
	������� � ������� ���������� ���������� ��� ������. 
	������� Free() ������������� ��� ������������ ������, ���� �� ������� �������� �������� � ������� ������. 
	������� SetCounter(int) �������� ���������� ������� � ������� ��������� ��� ��������, 
	��� ������ ������� Do() ���������� ��������� ������� �� 1, � ����� ������� ����� ����� 0 - ���������� ������. */
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


