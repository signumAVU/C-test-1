// pr3.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	

	//ErrCode = 1358; // ���� ������ ����� ��� ��� ������������ ��������� ���� ����� ������������� ������ ���� ����
	//MyMes(0,0);
	
	

	
	/* �������� ���*/
	//CircleShape shape(100.f);
	//shape.setFillColor(Color::Green);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**/

	// ��������� ������� ����
	bool running = true;
	while (running)
	{
		// ������������ �������
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// ���� ��������� ����������
				running = false;
			}
			else if (event.type == Event::Resized)
			{
				// ��������� ������� ���������, ����� �������� ������� ����
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		// ������� ������
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ������

		// ����� �������� ����� (������ ������� �������� � ������ ������)
		window.display();
	}
	return 0;
}









