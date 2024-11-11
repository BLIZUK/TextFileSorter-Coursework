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
#include "List.h"


// Удаление макроса
#undef max


using namespace std;


// Заголовок работы
void heading() 
{
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	//cout << "|\t\t\t\t\t\tКурсовая работа\t\t\t\t\t\t| " << endl;
	cout << "|\t\t\t\t\t\tKursach\t\t\t\t\t\t\t| " << endl;
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
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
	//heading("");
	cout << "\n\t\t\t\t\t\t  Содержимое: \n" << endl;
	cout << "->  ";
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




// Меню выбора фалов с возможностью получения информации 
void mainMenu() 
{
	int flagChose;
	string path = "Не выбран!";
	List <string> filePath;
	do 
	{
		heading();
		cout << "\n                                                 Меню                              " << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|x| Действия:" << endl;
		cout << "        |\n        | 1 - Работа с файлом;\n        | 2 - Выбор файла;\n        | 0 - Выход;\n        |\n\n$->: ";	
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
				manualMode(filePath);
				break;
			case 3:
				system("cls");
				//sysInfo();
				break;
			}
			system("cls");
			if (flagChose < 0 || flagChose > 2)
			{
				cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
			}
	} while (flagChose != 0);
	filePath.~List();
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
