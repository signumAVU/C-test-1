// pr3.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include "var.h"
#include "menu.h"
#include "Message.h"
#include "GlSet.h"
#include "OpGL.h"


int _tmain(int argc, _TCHAR* argv[])
{
	
	IniPr();
	//RenderWindow window(sf::VideoMode(1376, 768), "Kychka-pc.ru 31");
	//ErrCode = 1358; // “ест задать любой код дл€ тестировани€ сообщений если число отрицательное значит коды свои
	//MyMes(0,0);	
	/* “естовый код*/
	//CircleShape shape(100.f);
	//shape.setFillColor(Color::Green);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**/
	InitGL(StSysVar.SysWidth, StSysVar.SysHeight);


	// „ерез системные часы получаем объект типа time_point.
	auto lastTimePoint = chrono::system_clock::now();
	
	// запускаем главный цикл
	Clock clock;
	bool running = true;
	while (running)
	{
		/* Ёлементы временной синхронизации */
		// ѕолучаем второй момент времени (после итерации).
		auto newTimePoint = chrono::system_clock::now();
		auto dtMsec = chrono::duration_cast < chrono::milliseconds > (newTimePoint - lastTimePoint);
		lastTimePoint = newTimePoint;
		float dtSeconds = 0.001f * float(dtMsec.count());
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		//time = time / 800;
		//cout << "time: "<<time * 0.000001f << "<< " << endl;
		//cout <<"system_clock: " <<dtSeconds << "<< " << endl;
		// обрабатываем событи€
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
			{
				// пора закрывать приложение
				running = false;
			}
			else if (event.type == Event::Resized)
			{
				// примен€ем область просмотра, когда изменены размеры окна
				glViewport(0, 0, event.size.width, event.size.height);
				resiz();  
			} // окно потер€ло/приобрело фокус
			else if (event.type == Event::LostFocus)
			{
				cout << " ќкно потер€ло фокус." << endl <<endl;
				BitClrStat(STAT_FOCUSWIN);
				//cout << time << "<< " << endl;
			}
			else if (event.type == Event::GainedFocus)
			{
				cout << " ќкно приобрело фокус." << endl << endl;
				BitSetStat(STAT_FOCUSWIN);
			}
			
			
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::N)
				{
					// закрыть консоль
					//CloseCons();
					//
					if (window.isOpen())
					{
						KillGLWindow();
						window.close();
					} else{}
					//
				}else
				if (event.key.code == Keyboard::M)
				{
					
					glDisable(GL_LIGHTING);  // «апрет освещени€
					// открыть консоль
					//OpenCons();
					//FindWindow("TForm1", "Form1");//≈сли имеетс€ окно класса 'TForm1' с заголовком 'Form1'
				}
				else
					if (event.key.code == Keyboard::L)
					{

						glEnable(GL_LIGHTING);   // –азрешить освещение
						// открыть консоль
						//OpenCons();
						//FindWindow("TForm1", "Form1");//≈сли имеетс€ окно класса 'TForm1' с заголовком 'Form1'
					}
					else
						if (event.key.code == Keyboard::S)
						{

							yspeed = 0.0f;
							xspeed = 0.0f;
							xrot = 0.0f;
							yrot = 0.0f;
						}
						else
							if (event.key.code == Keyboard::F)
							{
								
								filter += 1;           // значение filter увеличиваетс€ на один
								if (filter>2)        // «начение больше чем 2?
								{
									filter = 0;           // ≈сли так, то установим filter в 0
								}cout << " filter : " << filter << endl;
							}
							else
								if (event.key.code == Keyboard::Z)
								{

									z -= 0.02f; cout << " Z : " << z << endl;
								}
								else
									if (event.key.code == Keyboard::X)
									{

										z += 0.02f; cout << " Z : " << z << endl;
									}
			}
		}
		yspeed = 0.1f;
		xspeed = 0.2f;
		zspeed = 0.3f;
		DrawGLScene();
		//SwapBuffers(StSysVar.hDC);			// ѕереключить буфер экрана
		// очищаем буферы
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// рисуем
		
		// конец текущего кадра (мен€ем местами передний и задний буферы)
		window.display();
	}
	return 0;
}











