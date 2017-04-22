
void menu(RenderWindow &window) {
	Texture menuTexture1,menuTexture2,menuTexture3,	aboutTexture,menuBackground;
	Clock clock;
	menuTexture1.loadFromFile("im/higloss_graphite_4.png");
	menuTexture2.loadFromFile("im/higloss_graphite_4.png");
	menuTexture3.loadFromFile("im/higloss_graphite_4.png");
	aboutTexture.loadFromFile("im/dT6edGdnc.png");
	menuBackground.loadFromFile("im/metal-background.jpg");

	Sprite menu1, menu2, menu3, menu1o, menu2o, menu3o, about, menuBg;

	menu1.setTexture(menuTexture1);
	menu2.setTexture(menuTexture2);
	menu3.setTexture(menuTexture3);
	menu1o.setTexture(menuTexture1);
	menu2o.setTexture(menuTexture2);
	menu3o.setTexture(menuTexture3);
	about.setTexture(aboutTexture);
	menuBg.setTexture(menuBackground);

	bool isMenu = 1;
	int menuNum = 0;
	Vector2i size_but;
	Vector2i pos_but;
	Vector2i pos_Bg;
	int OffsetH, dOffsetH = 10;
	size_but.x = 200; // Длина
	size_but.y = 20;  // Ширина

	pos_but.x = 100; // Первоначальная кордината установки кнопки
	pos_but.y = 60;  //

	pos_Bg.x = 0; // Позиция фоновой картинки
	pos_Bg.y = 0;   // 
    
	OffsetH = size_but.y + pos_but.y + dOffsetH;
	int offsetW = 600;
	menu1.setPosition(pos_but.x, pos_but.y);
	menu2.setPosition(pos_but.x, pos_but.y + OffsetH);
	menu3.setPosition(pos_but.x, pos_but.y + OffsetH * 2);

	menu1o.setPosition(pos_but.x + offsetW, pos_but.y);
	menu2o.setPosition(pos_but.x + offsetW, pos_but.y + OffsetH);
	menu3o.setPosition(pos_but.x + offsetW, pos_but.y + OffsetH * 2);
	
	menuBg.setPosition(pos_Bg.x, pos_Bg.y);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;
		
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu1o.setColor(Color::White);
		menu2o.setColor(Color::White);
		menu3o.setColor(Color::White);
		menuBg.setScale(0.8, 0.5);
		menu1o.setRotation(0);
		menu1o.setScale(1.0, 1.0);
		menu2o.setScale(1.0, 1.0);
		menu3o.setScale(1.0, 1.0);
		menuNum = 0;

		window.clear(Color(129, 181, 221));
		
		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

		
		if ((pos.x >= pos_but.x) && (pos.x <= (pos_but.x + size_but.x)))
		{
			
			if ((pos.y >= pos_but.y)               && (pos.y <= (OffsetH * 1))) { menu1.setColor(Color::Blue); menuNum = 1; }
			if ((pos.y >= pos_but.y + OffsetH)     && (pos.y <= (OffsetH * 2))) { menu2.setColor(Color::Blue); menuNum = 2; }
			if ((pos.y >= pos_but.y + OffsetH * 2) && (pos.y <= (OffsetH * 3))) { menu3.setColor(Color::Blue); menuNum = 3; }
		}else
		if ((pos.x >= pos_but.x + offsetW) && (pos.x <= (pos_but.x + offsetW + size_but.x)))
		{

			if ((pos.y >= pos_but.y) && (pos.y <= (OffsetH * 1))) { menu1o.setColor(Color::Red); menu1o.setScale(0.9, 0.99); menuNum = 1; }
			if ((pos.y >= pos_but.y + OffsetH) && (pos.y <= (OffsetH * 2))) { menu2o.setColor(Color::Red); menu2o.setScale(0.9, 0.99); menuNum = 2; }
			if ((pos.y >= pos_but.y + OffsetH * 2) && (pos.y <= (OffsetH * 3))) { menu3o.setColor(Color::Red); menu3o.setScale(0.9, 0.99); menuNum = 3; }
		}
		//if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		//if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		//if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) {
				window.draw(about); 
				window.display(); 
				Event out;
				int i = 1;
				while (i){
					while (window.pollEvent(out))
					{
						if (out.key.code == Keyboard::Escape){ i = 0; }
					}
				}
			}
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu1o);
		window.draw(menu2o);
		window.draw(menu3o);
		window.display();
	}
	////////////////////////////////////////////////////
}