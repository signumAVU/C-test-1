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
		string Ru = "������ � : ";
		string En = "Error � : ";
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
	string const RU = "������";
	string const EN = "ERROR";
};

MyMes::MyMes(int mes, int err)
{
	extern unsigned int GetOptPr(void);    // ��������� ��������� ���������
	extern unsigned int GetStat(void);     // ��������� ������ ���������
	if (mes == 2){ ErrCode = err; mes = 0; } // ������� ���� ������ ��������� ��������� err
	if (mes == 0) // ������� ���� ������ ��������� ���������� ErrCode
	{
		if (ErrCode < -1)// ��� ����
		{

		}
		else
			if (ErrCode == -1){ SetLastError(0); } // ���� -1 �������� ������
			else if (ErrCode > 0)                  // ���� 0 ������, ���� ������ ���� ��������� ������
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
				SysErr(); // ������� ��������� ������ � ���������� ����			
			}// ����� Error 
	}else
		if (mes == 1)
		{ 
		  // �������� ��� ���������
			_itoa_s((int)GetStat(), ErrNumMes, 16);
			string Buf("������ ��� : 0x00" + (string)ErrNumMes);
			MessageBox(NULL, &Buf[0], "������ ���������", MB_OK);
		}else
	if (mes == 3)
	{
		// �������� ��� ���������
		_itoa_s((int)GetOptPr(), ErrNumMes, 16);
		string Buf("��������� ��� : 0x00" + (string)ErrNumMes);
		MessageBox(NULL, &Buf[0], "��������� ���������", MB_OK);
	}
}

MyMes::~MyMes()
{
#ifndef DELCLASSVIS

#else
	cout << "Delete MyMes" << endl << endl; // �������� �����������
#endif
}














