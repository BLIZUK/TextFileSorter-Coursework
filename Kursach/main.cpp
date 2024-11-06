#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <limits>


// �������� �������
#undef max


using namespace std;


// ��������� ������
void heading() 
{
	cout << "-----------------------------------------------------------------" << endl;
	cout << "|\t\t\t�������� ������\t\t\t\t| " << endl;
	cout << "-----------------------------------------------------------------" << endl;
}


// �������� ����� ���������
void delay()
{
	char check;
	cout << "\n\n|x| ������� ����� ������ ��� ����������...\n\n$->: ";
	cin >> check;
}


// ������ ���������� � �����
int readFile(string path) 
{
	ifstream file(path);
	if (!file.is_open())
	{
		cerr << "\n|!| ������, ���� �� ����� ���� ������!" << endl;
		delay();
		return 1;
	}
	SetConsoleOutputCP(CP_UTF8);
	string line;
	while (getline(file, line))
	{
		cout << line << endl;
	}
	SetConsoleOutputCP(1251);
	file.close();
	delay();
	return 0;
}


// ��������� ����� � ������� ������������ ����
void autoMode()
{
	string path = "D:\\example.txt";
	int flagChose;
	do {
		heading();
		cout << "\n\t\t       ���� ��������� �����\n" << endl;
		cout << "|!| ���� � ����� - 'D:\\example.txt';" << endl;
		cout << "|!| �������� ���� - '�����';\n" << endl;
		cout << "|x| �������� ����� �������� �����:" << endl;
		cout << "\n   | 0 - �����;\n   | 1 - �������� ����������� �����;\n   | 2 - ���������� �����;\n\n$->: ";
		// �������� �� ���� �����
		if (!(cin >> flagChose))
		{
			// �������� ����� ������
			cin.clear();
			// ������� ������� ������
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| �� ����� ������������ ��������!\n" << endl;
			continue;
		}
		
		switch (flagChose)
		{
		case 1:
			system("cls");
			readFile(path);
			
			system("cls");
			break;
		case 2:
			break;
		}
	} while (flagChose != 0);
}


// ��������� ����� � ������� ������� ����� ���� 
void manualMode()
{
	string path = "D:\\example.txt";
	int flagChose;
	do {
		heading();
		cout << "\n\t\t       ���� ��������� �����\n" << endl;
		cout << "|!| ���� � ����� - 'D:\\example.txt';" << endl;
		cout << "|!| �������� ���� - '�����';\n" << endl;
		cout << "|x| �������� ����� �������� �����:" << endl;
		cout << "\n   | 0 - �����;\n   | 1 - �������� ����������� �����;\n   | 2 - ���������� �����;\n\n$->: ";
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| �� ����� ������������ ��������!\n" << endl;
			continue;
		}

		switch (flagChose)
		{
		case 1:
			system("cls");
			readFile(path);

			system("cls");
			break;
		case 2:
			break;
		}
	} while (flagChose != 0);
}


// ��������� ������� ���������� � �������������� � ����������
void sysInfo()
{
	cout << "\n\n|!| � ��������! \n" << endl;
	delay();
}



// ���� ������ ����� � ������������ ��������� ���������� 
void mainMenu() 
{
	int flagChose;

	do 
	{
		heading();
		cout << "\n\t\t       ���� ������ �����\n" << endl;
		cout << "|x| �������� ����� �������� �����:" << endl;
		cout << "\n   | 0 - �����;\n   | 1 - ����������� ���� � �����;\n   | 2 - ������ �������� �����;\n   | 3 - � ���������;\n\n$->: ";	
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| �� ����� ������������ ��������!\n" << endl;
			continue;
		}
			switch (flagChose)
			{
			case 1:
				system("cls");
				autoMode();
				break;
			case 2:
				system("cls");
				manualMode();
				break;
			case 3:
				system("cls");
				sysInfo();
				break;
			}
			system("cls");
			if (flagChose < 0 || flagChose > 3)
			{
				cout << "\n|!| �� ����� ������������ ��������!\n" << endl;
			}
	} while (flagChose != 0);
}


// ����� �����
int main()
{
	// ��������� ��������� ��������� ��� ������ � ����������
	system("chcp 1251 > nul");
	mainMenu();
	cout << "\n|!| ���������� ������!" << endl;
	return 0;
}