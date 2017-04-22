// pr3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "var.h"
#include "Message.h"
#include "GlSet.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//int fl1 = 0, Fullscreen_ = 0;
	IniPr();
    //system("pause");
	//system("cls");
	

	//ErrCode = 1358; // Тест задать любой код для тестирования сообщений если число отрицательное значит коды свои
	//MyMes(0,0);
	
	

	
	/* Тестовый код*/
	//CircleShape shape(100.f);
	//shape.setFillColor(Color::Green);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**/

	// запускаем главный цикл
	bool running = true;
	while (running)
	{
		// обрабатываем события
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// пора закрывать приложение
				running = false;
			}
			else if (event.type == Event::Resized)
			{
				// применяем область просмотра, когда изменены размеры окна
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		// очищаем буферы
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// рисуем

		// конец текущего кадра (меняем местами передний и задний буферы)
		window.display();
	}
	return 0;
}









