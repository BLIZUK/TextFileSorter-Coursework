/* 
Автор: Близученко А.Г.
Тема: "Сортировка последовательностей"
Учебная дисциплина: Архитектура вычислительных систем
Шифры группы: ИВТ2-23
Год выполнения: 2024 
*/


#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <limits>
#include "D:/apps/Tools/VisualStudio/Projects/List/List/List.h"


// Удаление макроса
#undef max


using namespace std;


// Заголовок работы
void heading() 
{
	cout << "-----------------------------------------------------------------" << endl;
	cout << "|\t\t\tКурсовая работа\t\t\t\t| " << endl;
	cout << "-----------------------------------------------------------------" << endl;
}


// Задержка перед переходом
void delay()
{
	char check;
	cout << "\n\n|x| Введите любой символ для продожения...\n\n$->: ";
	cin >> check;
}


// Сортировка файла с помощью asm вставок
void sortedAsm() 
{

}


// Чтение информации с файла
int readFile(string path) 
{
	ifstream file(path);
	if (!file.is_open())
	{
		cerr << "\n|!| Ошибка, файл не может быть открыт!" << endl;
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


// Вводе пути к файлу
string pathChange()
{
	string path;
	cout << "Введите путь:\n\n$->: ";
	cin >> path;
	return path;
}


// Обработка файла с помощью стнадратного пути
void autoMode()
{
	string path = "D:\\example.txt";
	int flagChose;
	do {
		heading();
		cout << "\n\t\t       Меню обработки файла\n" << endl;
		cout << "|!| Путь к файлу - 'D:\\example.txt';" << endl;
		cout << "|!| Ключевое поле - 'Знаки';\n" << endl;
		cout << "|x| Выберите режим открытия файла:" << endl;
		cout << "\n   | 0 - Выход;\n   | 1 - Просмотр содержимого файла;\n   | 2 - Сортировка файла;\n\n$->: ";
		// Проверка на ввод числа
		if (!(cin >> flagChose))
		{
			// Отчистка флага ошибки
			cin.clear();
			// Пропуск остатка строки
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
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


// Обработка файла с помощью ручного ввода пути 
void manualMode()
{
	string path = "Выберите путь";
	int flagChose, flagActive = 0;
	do {
		heading();
		cout << "\n\t\t       Меню обработки файла\n" << endl;
		cout << "|!| Путь к файлу - '"<< path << "';" << endl;
		cout << "|!| Ключевое поле - 'Знаки';\n" << endl;
		cout << "|x| Выберите режим открытия файла:" << endl;
		cout << "\n   | 0 - Выход;\n   | 1 - Изменить путь\n   | 2 - Просмотр содержимого файла;\n   | 3 - Сортировка файла;\n\n$->: ";
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
			continue;
		}

		switch (flagChose)
		{
		case 1:
			system("cls");
			path = pathChange();
			system("cls");
			break;
		case 2:
			system("cls");
			readFile(path);
			system("cls");
			break;
		case 3:
			break;
		}
	} while (flagChose != 0);
}


// Получение краткой информации о взаимодействие с программой
void sysInfo()
{
	cout << "\n\n|!| В процессе! \n" << endl;
	delay();
}



// Меню выбора фалов с возможностью получения информации 
void mainMenu() 
{
	int flagChose;

	do 
	{
		heading();
		cout << "\n\t\t       Меню выбора файла\n" << endl;
		cout << "|x| Выберите режим открытия файла:" << endl;
		cout << "\n   | 0 - Выход;\n   | 1 - Стандартный путь к файлу;\n   | 2 - Ручное открытие файла;\n   | 3 - О программе;\n\n$->: ";	
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
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
				cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
			}
	} while (flagChose != 0);
}


// Точка входа
int main()
{
	// Изменение кодировки терминала для работы с кириллицей
	system("chcp 1251 > nul");
	mainMenu();
	cout << "\n|!| Завершение работы!" << endl;
	return 0;
}