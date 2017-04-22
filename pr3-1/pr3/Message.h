//#define DELCLASSVIS // 


class MyMes
{
public:
#define LENMES 255U
	

	CHAR ErrNumMes[10];
	CHAR Message[LENMES];
	//TCHAR Buf[LENMES];
	HANDLE HandleM = NULL;
	//DWORD ErrCode;
	
	//int Fl;
	//void SetFl(int fl){ Fl = fl; }
	MyMes(int, int);
	~MyMes();

	int MyErr(int err)
	{
		return 0;
	}
	int SysErr(void)
	{
		string Ru = "Ошибка № : ";
		string En = "Error № : ";
		string Temp1;
		string  TmpStr;
		if (LANGID != MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA))
		{
			Temp1 = En;
			TmpStr = EN;
		}
		else
		{
			Temp1 = Ru;
			TmpStr = RU;
		}
		string Temp(Temp1 + (string)ErrNumMes);
		string Temp2(Temp + " - ");
		string Buf(Temp2 + (string)Message);
		
		MessageBox(NULL, &Buf[0], &TmpStr[0], MB_OK);
		
		return 0;
	}

private:
	int Tmp = 0;
	string const RU = "ОШИБКА";
	string const EN = "ERROR";
};

MyMes::MyMes(int mes, int err)
{
	extern unsigned int GetOptPr(void);    // Прочитать настройки программы
	extern unsigned int GetStat(void);     // Прочитать статус программы
	if (mes == 2){ ErrCode = err; mes = 0; } // Выводим коды ошибок используя локальный err
	if (mes == 0) // Выводим коды ошибок используя глобальный ErrCode
	{
		if (ErrCode < -1)// Мои коды
		{

		}
		else
			if (ErrCode == -1){ SetLastError(0); } // Если -1 сбросить ошибки
			else if (ErrCode > 0)                  // Если 0 ничего, если больше ноля системные ошибки
			{
				//if (Fl == 0){ _itoa_s(ErrCode, ErrNumMes, 10); }
				//else        { _itoa_s(ErrCode, ErrNumMes, 16); }
				_itoa_s(ErrCode, ErrNumMes, 10);
				FormatMessage(
					/*FORMAT_MESSAGE_ALLOCATE_BUFFER |*/
					FORMAT_MESSAGE_FROM_SYSTEM | /*  */
					/* FORMAT_MESSAGE_FROM_HMODULE |*/
					FORMAT_MESSAGE_IGNORE_INSERTS
					, HandleM,
					ErrCode,
					langId,
					(LPSTR)&Message,
					LENMES,
					NULL
					);
				SysErr(); // Вывести системную ошибку в диалоговом окне			
			}// Конец Error 
	}else
		if (mes == 1)
		{ 
		  // добавить доп сообщения
			_itoa_s((int)GetStat(), ErrNumMes, 16);
			string Buf("Статус код : 0x00" + (string)ErrNumMes);
			MessageBox(NULL, &Buf[0], "Статус программы", MB_OK);
		}else
	if (mes == 3)
	{
		// добавить доп сообщения
		_itoa_s((int)GetOptPr(), ErrNumMes, 16);
		string Buf("Настройки код : 0x00" + (string)ErrNumMes);
		MessageBox(NULL, &Buf[0], "Настройки программы", MB_OK);
	}
}

MyMes::~MyMes()
{
#ifndef DELCLASSVIS

#else
	cout << "Delete MyMes" << endl << endl; // Проверка деструктора
#endif
}














