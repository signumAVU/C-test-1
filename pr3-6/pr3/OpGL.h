bool keys[256];       // ������, �������������� ��� ���������� ��������� ����������
bool active = TRUE;     // ���� ��������� ���������� ���������� (�� ���������: TRUE)



BOOL light;      // ���� ��� / ����
BOOL lp;         // L ������?
BOOL fp;         // F ������?




GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // �������� �������� ����� 
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // �������� ���������� ����� 
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };     // ������� ����� 


GLuint texture[3];     // ����� ��� �������� 3 �������
//bool fullscreen = TRUE; // ���� �������������� ������ (�� ���������: �������������)

int InitGL(GLsizei, GLsizei);           // ��� ��������� ������� OpenGL ���������� �����
int DrawGLScene(GLvoid);      // ����� ����� ����������� ��� ����������
GLvoid KillGLWindow(GLvoid);  // ���������� ���������� ����

AUX_RGBImageRec *LoadBMP(char);     // �������� ��������
int LoadGLTextures();                      // �������� �������� � ��������������� � ��������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int InitGL(GLsizei Width, GLsizei Height)                // ��� ��������� ������� OpenGL ���������� �����
{
	if (!LoadGLTextures())        // ������� �� ��������� �������� ��������
	{
		return false;                // ���� �������� �� ��������� ���������� FALSE
	}

	glEnable(GL_TEXTURE_2D);      // ��������� ��������� ��������
	glShadeModel(GL_SMOOTH);      // ���������� ����������� ������������
	glClearColor(0.0f, 0.0f, 0.5f, 0.5f); // ������ ���
	glClearDepth(1.0f);           // ��������� ������ �������
	glEnable(GL_DEPTH_TEST);      // ��������� ���� �������
	glDepthFunc(GL_LEQUAL);       // ��� ����� �������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // ���������� ���������� �����������


	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    // ��������� �������� �����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    // ��������� ���������� �����
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   // ������� �����

	glEnable(GL_LIGHT1); // ���������� ��������� ����� ����� ����

	glMatrixMode(GL_PROJECTION);// ����� ������� ��������
	glLoadIdentity();		// ����� ������� ��������
	gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);
	// ��������� ����������� �������������� �������� ��� ����
	glMatrixMode(GL_MODELVIEW);// ����� ������� ��������� ������
	return true;         // ������������� ������ OK
}

int DrawGLScene(GLvoid)                // ����� ����� ����������� ��� ����������
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // �������� ����� � ����� �������
	/*
		����� ������� gLoadIdentity() ������������� ������ ������� ��������� � ����� ������, 
		������ ��� X ���� ����� �������, ��� Y ����� � ����, � ��� Z � � �� �����������. 
		����� OpenGL ������ ��������� � ����� 0, 0, 0. ����������, ������������� �����, 
		����� � ������ �� ����, ����� ������������� ��������, ������������� ������, 
		������ � �� ����������� � ����������� � �������������.
	*/
	glLoadIdentity();           // ����� ���������

	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glTranslatef(0.0f, 0.0f, z);      // ������� �/��� ������ �� z
	glRotatef(xrot, 1.0f, 0.0f, 0.0f); // �������� �� ��� X �� xrot
	glRotatef(yrot, 0.0f, 1.0f, 0.0f); // �������� �� ��� Y �� yrot
	glRotatef(zrot, 0.0f, 0.0f, 1.0f); // �������� �� ��� Y �� yrot

	glBindTexture(GL_TEXTURE_2D, texture[filter]);    // ����� �������� ����������� �� filter

	glBegin(GL_QUADS);       // ������ ��������� �����������������

	// �������� �����
	glNormal3f(0.0f, 0.0f, 1.0f);     // ������� ��������� �� �����������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ����� 1 (�����)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ����� 2 (�����)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ����� 3 (�����)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ����� 4 (�����)

	// ������ �����
	glNormal3f(0.0f, 0.0f, -1.0f);     // ������� ��������� �� �����������
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ����� 1 (���)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ����� 2 (���)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ����� 3 (���)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ����� 4 (���)

	// ������� �����
	glNormal3f(0.0f, 1.0f, 0.0f);     // ������� ��������� �����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ����� 1 (����)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ����� 2 (����)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ����� 3 (����)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ����� 4 (����)

	// ������ �����
	glNormal3f(0.0f, -1.0f, 0.0f);     // ������� ��������� ����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ����� 1 (���)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ����� 2 (���)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ����� 3 (���)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ����� 4 (���)

	// ������ �����
	glNormal3f(1.0f, 0.0f, 0.0f);     // ������� ��������� ������
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ����� 1 (�����)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ����� 2 (�����)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ����� 3 (�����)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ����� 4 (�����)

	// ����� �����
	glNormal3f(-1.0f, 0.0f, 0.0f);     // ������� ��������� �����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ����� 1 (����)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ����� 2 (����)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ����� 3 (����)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ����� 4 (����)
	glEnd();        // ������� �������� ���������������

	xrot += xspeed;        // �������� � xspeed �������� xrot
	yrot += yspeed;        // �������� � yspeed �������� yrot
	zrot += zspeed;        // �������� � yspeed �������� yrot
	
	
	
	return true;                // ���������� ������ �������
}
#if 1
GLvoid KillGLWindow(GLvoid)              // ���������� ���������� ����
{
	
	 
	/*
	    ���������, ��������� �� �� � ������������� ������.
		���� ��� ���, �� ������������� ����� �� ������� ����.
		�� ������ ���������� ���� �������������� ����� �� �������������� ������
     */
		if (StSysVar.fullscreen)              // �� � ������������� ������?
		{
			/*
			   �� ���������� ChangeDisplaySettings(NULL, 0) ��� �������� ������ �������� ����� � �������������� ���������.
			   �������� NULL � ������ ��������� � 0 �� ������ ���������� ���� ������������ ���������, 
			   ���������� � �������� ����(������������ ����������, 
			   ������� �������, ������� ���������� ������ � ������ �� ���������), 
			   ������������� �������������� �������������� ��������� �������� �����.
			   ����� ������������ ������� � �������� ������ �� ������ ������� ������ �������.
           */
			ChangeDisplaySettings(NULL, 0);    // ���� ��, �� ������������� ������� � ������� �����
			ShowCursor(true);                  // �������� ������ �����
		}
		/*
	        ��� ���������� ���� ���������, ���������� �� �������� ����������(hRC).
			���� ��� ���, �� ��������� ��������� �� ������ ����, 
			������������� ���� � ����������� ���������� �� �������� ����������(hDC).
         */
		if (StSysVar.hRC)                // ���������� �� �������� ����������?
		{
			/*
			���� �� ����������, ��� ���� ��������, 
			�������� �� ���������� ���(����������� RC �� DC).
			� ������� ��������� ����� ��������� ������.�� ������ ��������� ���������� 
			�������� ����������(� ������� ������ wglMakeCurrent(NULL, NULL)), ����� ���������, 
			������������ �� ��������� ��� �������� ��� ���.
            */
				if (!wglMakeCurrent(NULL, NULL))        // �������� �� ���������� RC � DC?
				{
					/*
					���� ���������� ���������� ��������� RC � DC, 
					�������� ��������� �� ������, ��� �������� ������, ��� ��������� �� ����������.
					NULL � ������� MessageBox() ��������, ��� � ��������� �� ����� ������������� ����.
					����� ������ �� NULL - �����, ������� ����� ��������� ���������. 
					"SHUTDOWN ERROR" - �����, ������� ����� ����������� � ��������� ���� - ���������.
					������ �� ����� MB_OK, ��� ��������, ��� ���� - ��������� ����� � ����� ������� 
					���������� "��".MB_ICONINFORMATION ������ ������ � ������� ���� - ���������(��� ���������� �������� �� ���� ��������).
                    */
						MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				}
				/*
			       ����� �� �������� ������� �������� ����������.
				   ���� ��� �� �������� �������� ��������������� ���������.
                */
				if (!wglDeleteContext(StSysVar.hRC))        // �������� �� ������� RC?
				{
					/*
					  ���� ���������� ������� �������� ���������� ���, ���������� ����, 
					  ������� ���� - ��������� ����������� ������, ��� ��� �������� - ����������.
					  hRC ����� ����������� � NULL.
                    */
						MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				}
				StSysVar.hRC = NULL;              // ���������� RC � NULL
		}
		/*
	      ������ �� ��������, ����� �� ��������� �������� ����������, � ���� ��� ���, 
		  �� �� ��������� ��� ����������.���� ��� ���������� ���� - ��������� ������� ��������������� ��������� � hDC ����� ���������� � NULL.
        */
		if (StSysVar.hDC && !ReleaseDC(StSysVar.hWnd, StSysVar.hDC))          // �������� �� ���������� DC?
		{
			MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			StSysVar.hDC = NULL;                // ���������� DC � NULL
		}
		    /*
	           ������ ��������, ���� �� ���������� ����, � ���� ����, �� ��������� ���������� ����, 
			   ��������� DestroyWindow(hWnd).
			   ���� ��� ���������� ���� - ��������� ������� ��������������� ��������� � hWnd ����� ���������� � NULL.
            */
		
		if (StSysVar.hWnd && !DestroyWindow(StSysVar.hWnd))            // �������� �� ���������� ����?
		{
			MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			StSysVar.hWnd = NULL;                // ���������� hWnd � NULL
		}
		/*
	          ���������, ��� ��� ���������� ������� ��� ��� �����������������(��������, �������� �����������) ����� ����.
			  ��� ��������� ��� ���������� ������� ���������� ���� � ������� ������ ��� ��������� 
			  ��������� �� ������ "Windows Class already registered" (����� ���� ��� ���������������).
        */
#ifndef SFML
		if (!UnregisterClass(StSysVar.lpClassName, StSysVar.hInstance))        // �������� �� ����������������� �����
		{
			MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			StSysVar.hInstance = NULL;                // ���������� hInstance � NULL
		}
#endif
}
#endif

int LoadGLTextures()                      // �������� �������� � ��������������� � ��������
{
	int Status = FALSE;                        // ��������� ���������

	AUX_RGBImageRec *TextureImage[1];        // ������� ����� ��� ��������

	memset(TextureImage, 0, sizeof(void *) * 1); // ���������� ��������� � NULL

	
	
	// �������� ��������, �������� �� ������, ���� �������� �� ������� - �����
	TextureImage[0] = auxDIBImageLoad("Data/metal.bmp"); //CRATE.BMPLoadBMP("Data/CRATE1.BMP");
	if (TextureImage[0] != false)
	{
		Status = TRUE;       // ��������� Status � TRUE
		glGenTextures(3, &texture[0]);     // �������� ���� �������

		// �������� �������� � �������� �� �������� ��������
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// �������� �������� � �������� �����������
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// �������� �������� � ���-����������
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); // 

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY,
			GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); //
	}


	if (TextureImage[0])           // ���� �������� ����������
	{
		if (TextureImage[0]->data)    // ���� ����������� �������� ����������
		{
			free(TextureImage[0]->data); // ������������ ������ ����������� ��������
		}

		free(TextureImage[0]);        // ������������ ������ ��� ���������
	}

	return Status;        // ���������� ������
}

AUX_RGBImageRec *LoadBMP(char *Filename)     // �������� ��������
{
#if 0
	FILE *File=NULL;          // ������ �����
	if (!Filename)            // �������� ����� �����
	{
		return NULL;             // ���� ��� ������ NULL
	}

	File=fopen(Filename,"r"); // �������� ���������� �� ����

	if (File)                 // ���� ����������?
	{
		fclose(File);            // ������� ����
		return auxDIBImageLoad(Filename); // �������� �������� � ������ �� ��� ���������
	}
#endif
	return NULL;              // ���� �������� �� ������� ������ NULL
}
#if 0
// �������� �������� � ��������������� � ��������
GLvoid LoadGLTextures()
{
	// �������� ��������
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad("Data/CRATE.BMP");
	// �������� ��������
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		4, 
		texture1->sizeX, 
		texture1->sizeY, 
		0,
		GL_RGB, GL_UNSIGNED_BYTE, 
		texture1->data
		);
}
void gets_utf8(char*buf)
{
	wchar_t tbuf[buf_len];
	gets(buf);
	MultiByteToWideChar(1251, 0, buf, -1, tbuf, buf_len);
	WideCharToMultiByte(CP_UTF8, 0, tbuf, -1, buf, buf_len, NULL, NULL);
}



#endif

