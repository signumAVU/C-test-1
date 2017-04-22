bool keys[256];       // Массив, использующийся для сохранения состояния клавиатуры
bool active = TRUE;     // Флаг состояния активности приложения (по умолчанию: TRUE)



BOOL light;      // Свет ВКЛ / ВЫКЛ
BOOL lp;         // L нажата?
BOOL fp;         // F нажата?




GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Значения фонового света 
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света 
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };     // Позиция света 


GLuint texture[3];     // Место для хранения 3 текстур
//bool fullscreen = TRUE; // Флаг полноэкранного режима (по умолчанию: полноэкранное)

int InitGL(GLsizei, GLsizei);           // Все установки касаемо OpenGL происходят здесь
int DrawGLScene(GLvoid);      // Здесь будет происходить вся прорисовка
GLvoid KillGLWindow(GLvoid);  // Корректное разрушение окна

AUX_RGBImageRec *LoadBMP(char);     // Загрузка картинки
int LoadGLTextures();                      // Загрузка картинки и конвертирование в текстуру
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int InitGL(GLsizei Width, GLsizei Height)                // Все установки касаемо OpenGL происходят здесь
{
	if (!LoadGLTextures())        // Переход на процедуру загрузки текстуры
	{
		return false;                // Если текстура не загружена возвращаем FALSE
	}

	glEnable(GL_TEXTURE_2D);      // Разрешить наложение текстуры
	glShadeModel(GL_SMOOTH);      // Разрешение сглаженного закрашивания
	glClearColor(0.0f, 0.0f, 0.5f, 0.5f); // Черный фон
	glClearDepth(1.0f);           // Установка буфера глубины
	glEnable(GL_DEPTH_TEST);      // Разрешить тест глубины
	glDepthFunc(GL_LEQUAL);       // Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Улучшенные вычисления перспективы


	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    // Установка Фонового Света
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    // Установка Диффузного Света
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   // Позиция света

	glEnable(GL_LIGHT1); // Разрешение источника света номер один

	glMatrixMode(GL_PROJECTION);// Выбор матрицы проекции
	glLoadIdentity();		// Сброс матрицы проекции
	gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);
	// Вычислить соотношение геометрических размеров для окна
	glMatrixMode(GL_MODELVIEW);// Выбор матрицы просмотра модели
	return true;         // Инициализация прошла OK
}

int DrawGLScene(GLvoid)                // Здесь будет происходить вся прорисовка
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // Очистить экран и буфер глубины
	/*
		Вызов функции gLoadIdentity() устанавливает начало системы координат в центр экрана, 
		причем ось X идет слева направо, ось Y вверх и вниз, а ось Z к и от наблюдателя. 
		Центр OpenGL экрана находится в точке 0, 0, 0. Координаты, расположенные слева, 
		снизу и вглубь от него, имеют отрицательное значение, расположенные справа, 
		сверху и по направлению к наблюдателю – положительное.
	*/
	glLoadIdentity();           // Сброс просмотра

	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glTranslatef(0.0f, 0.0f, z);      // Перенос В/Вне экрана по z
	glRotatef(xrot, 1.0f, 0.0f, 0.0f); // Вращение по оси X на xrot
	glRotatef(yrot, 0.0f, 1.0f, 0.0f); // Вращение по оси Y по yrot
	glRotatef(zrot, 0.0f, 0.0f, 1.0f); // Вращение по оси Y по yrot

	glBindTexture(GL_TEXTURE_2D, texture[filter]);    // Выбор текстуры основываясь на filter

	glBegin(GL_QUADS);       // Начало рисования четырехугольников

	// Передняя грань
	glNormal3f(0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Точка 1 (Перед)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // Точка 2 (Перед)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // Точка 3 (Перед)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Точка 4 (Перед)

	// Задняя грань
	glNormal3f(0.0f, 0.0f, -1.0f);     // Нормаль указывает от наблюдателя
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Точка 1 (Зад)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Точка 2 (Зад)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // Точка 3 (Зад)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // Точка 4 (Зад)

	// Верхняя грань
	glNormal3f(0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Точка 1 (Верх)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Точка 2 (Верх)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // Точка 3 (Верх)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // Точка 4 (Верх)

	// Нижняя грань
	glNormal3f(0.0f, -1.0f, 0.0f);     // Нормаль указывает вниз
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Точка 1 (Низ)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // Точка 2 (Низ)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // Точка 3 (Низ)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Точка 4 (Низ)

	// Правая грань
	glNormal3f(1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // Точка 1 (Право)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // Точка 2 (Право)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // Точка 3 (Право)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // Точка 4 (Право)

	// Левая грань
	glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Точка 1 (Лево)
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Точка 2 (Лево)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Точка 3 (Лево)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Точка 4 (Лево)
	glEnd();        // Кончили рисовать четырехугольник

	xrot += xspeed;        // Добавить в xspeed значение xrot
	yrot += yspeed;        // Добавить в yspeed значение yrot
	zrot += zspeed;        // Добавить в yspeed значение yrot
	
	
	
	return true;                // Прорисовка прошла успешно
}
#if 1
GLvoid KillGLWindow(GLvoid)              // Корректное разрушение окна
{
	
	 
	/*
	    Проверить, находимся ли мы в полноэкранном режиме.
		Если это так, то переключаемся назад на рабочий стол.
		Мы должны уничтожить окно предварительно выйдя из полноэкранного режима
     */
		if (StSysVar.fullscreen)              // Мы в полноэкранном режиме?
		{
			/*
			   Мы используем ChangeDisplaySettings(NULL, 0) для возврата нашего рабочего стола в первоначальное состояние.
			   Передача NULL в первом параметре и 0 во втором принуждает окно использовать параметры, 
			   хранящиеся в регистре окна(устанавливая разрешение, 
			   битовую глубину, частоту обновления экрана и другое по умолчанию), 
			   действительно восстанавливая первоначальное состояние рабочего стола.
			   После переключения обратно к оконному режиму мы должны сделать курсор видимым.
           */
			ChangeDisplaySettings(NULL, 0);    // Если да, то переключаемся обратно в оконный режим
			ShowCursor(true);                  // Показать курсор мышки
		}
		/*
	        Код приведённый ниже проверяет, существует ли Контекст Рендеринга(hRC).
			Если его нет, то программа переходит на секцию кода, 
			расположенную ниже и проверяющие существует ли Контекст Устройства(hDC).
         */
		if (StSysVar.hRC)                // Существует ли Контекст Рендеринга?
		{
			/*
			Если он существует, код ниже проверит, 
			возможно ли освободить его(отсоединить RC от DC).
			С помощью сообщений можно отследить ошибки.Мы просим программу освободить 
			Контекст Рендеринга(с помощью вызова wglMakeCurrent(NULL, NULL)), затем проверяем, 
			благополучно ли завершена эта операция или нет.
            */
				if (!wglMakeCurrent(NULL, NULL))        // Возможно ли освободить RC и DC?
				{
					/*
					Если невозможно уничтожить контексты RC и DC, 
					выскочит сообщение об ошибке, это позволит понять, что контексты не уничтожены.
					NULL в функции MessageBox() означает, что у сообщения не будет родительского окна.
					Текст справа от NULL - текст, который будет содержать сообщение. 
					"SHUTDOWN ERROR" - текст, который будет содержаться в заголовке окна - сообщения.
					Следом мы видим MB_OK, это означает, что окно - сообщение будет с одной кнопкой 
					помеченной "ОК".MB_ICONINFORMATION создаёт иконку в области окна - сообщения(что заставляет обратить на себя внимание).
                    */
						MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				}
				/*
			       Потом мы пытаемся удалить Контекст Рендеринга.
				   Если это не возможно выскочит соответствующее сообщение.
                */
				if (!wglDeleteContext(StSysVar.hRC))        // Возможно ли удалить RC?
				{
					/*
					  Если невозможно удалить Контекст Рендеринга код, приведённый ниже, 
					  выведет окно - сообщение позволяющее понять, что его удаление - невозможно.
					  hRC будет установлено в NULL.
                    */
						MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				}
				StSysVar.hRC = NULL;              // Установить RC в NULL
		}
		/*
	      Теперь мы проверим, имеет ли программа Контекст Устройства, и если это так, 
		  то мы попробуем его уничтожить.Если это невозможно окно - сообщение выведет соответствующее сообщение и hDC будет установлен в NULL.
        */
		if (StSysVar.hDC && !ReleaseDC(StSysVar.hWnd, StSysVar.hDC))          // Возможно ли уничтожить DC?
		{
			MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			StSysVar.hDC = NULL;                // Установить DC в NULL
		}
		    /*
	           Теперь проверим, есть ли дескриптор окна, а если есть, мы попробуем уничтожить окно, 
			   используя DestroyWindow(hWnd).
			   Если это невозможно окно - сообщение выведет соответствующее сообщение и hWnd будет установлен в NULL.
            */
		
		if (StSysVar.hWnd && !DestroyWindow(StSysVar.hWnd))            // Возможно ли уничтожить окно?
		{
			MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			StSysVar.hWnd = NULL;                // Установить hWnd в NULL
		}
		/*
	          Последнее, что нам необходимо сделать так это разрегистрировать(операция, обратная регистрации) класс окна.
			  Это позволяет нам корректным образом уничтожить окно и открыть другое без получения 
			  сообщения об ошибке "Windows Class already registered" (Класс окна уже зарегистрирован).
        */
#ifndef SFML
		if (!UnregisterClass(StSysVar.lpClassName, StSysVar.hInstance))        // Возможно ли разрегистрировать класс
		{
			MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			StSysVar.hInstance = NULL;                // Установить hInstance в NULL
		}
#endif
}
#endif

int LoadGLTextures()                      // Загрузка картинки и конвертирование в текстуру
{
	int Status = FALSE;                        // Индикатор состояния

	AUX_RGBImageRec *TextureImage[1];        // Создать место для текстуры

	memset(TextureImage, 0, sizeof(void *) * 1); // Установить указатель в NULL

	
	
	// Загрузка картинки, проверка на ошибки, если картинка не найдена - выход
	TextureImage[0] = auxDIBImageLoad("Data/metal.bmp"); //CRATE.BMPLoadBMP("Data/CRATE1.BMP");
	if (TextureImage[0] != false)
	{
		Status = TRUE;       // Установим Status в TRUE
		glGenTextures(3, &texture[0]);     // Создание трех текстур

		// Создание текстуры с фильтром по соседним пикселям
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// Создание текстуры с линейной фильтрацией
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// Создание Текстуры с Мип-Наложением
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); // 

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY,
			GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); //
	}


	if (TextureImage[0])           // Если текстура существует
	{
		if (TextureImage[0]->data)    // Если изображение текстуры существует
		{
			free(TextureImage[0]->data); // Освобождение памяти изображения текстуры
		}

		free(TextureImage[0]);        // Освобождение памяти под структуру
	}

	return Status;        // Возвращаем статус
}

AUX_RGBImageRec *LoadBMP(char *Filename)     // Загрузка картинки
{
#if 0
	FILE *File=NULL;          // Индекс файла
	if (!Filename)            // Проверка имени файла
	{
		return NULL;             // Если нет вернем NULL
	}

	File=fopen(Filename,"r"); // Проверим существует ли файл

	if (File)                 // Файл существует?
	{
		fclose(File);            // Закрыть файл
		return auxDIBImageLoad(Filename); // Загрузка картинки и вернем на нее указатель
	}
#endif
	return NULL;              // Если загрузка не удалась вернем NULL
}
#if 0
// Загрузка картинки и конвертирование в текстуру
GLvoid LoadGLTextures()
{
	// Загрузка картинки
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad("Data/CRATE.BMP");
	// Создание текстуры
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

