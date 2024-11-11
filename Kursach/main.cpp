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
	cout << "\n\n>> Э|x| Введите любой символ для продожения...\n\n$->: ";
	cin >> check;
}


// Сортировка файла с помощью asm вставок
void sortedAsm() 
{

}


// Чтение информации с файла
int readFile(string& path)
{
	ifstream file(path);
	if (!file.is_open())
	{
		cerr << "\n|!| Ошибка, файл не может быть открыт!" << endl;
		delay();
		return 1;
	}
	heading();
	cout << "\n                                           Содержимое файла:\n" << endl;
	cout << "->|" << path <<  "|>>>\n\n    >> ";
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

void working_with_file(string& path)
{
	int flagChose;
	do
	{
		heading();
		cout << "\n                                            Работа с файлом" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|x| Действия:" << endl;
		cout << "        |\n        | 1 - Чтение файла;\n        | 2 - Сортировка {Ключевое поле - 'Знаки'};\n        | 0 - Выход в меню;\n        |\n\n$->: ";
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
			readFile(path);
			system("cls");
			break;
		case 2:
			system("cls");

			system("cls");
			break;

		}
	} while (flagChose != 0);
}


int sevedFiles(List <string>& filePath, string& path)
{
	int flagChose;
	do
	{
		heading();
		cout << "\n                                       Список сохраненных файлов" << endl;
		cout << "\n   |Saved files| == " << filePath.getSize() << " ==" << endl;
		cout << "         |\n         |\n         |-|x| Выбор:\n            |" << endl;
		if (filePath.getSize())
		{
			for (int i = 0; i < filePath.getSize(); i++)
			{
				cout << "            | " << i + 1 << " - " << filePath[i] << ";" << endl;
			}
			cout << "\n\n$->:|File|-> ";
		}
		else
		{
			cout << "           |!| Файлы не найдены!\n\n>> |!| Введите 0 для выхода... " << endl;
			cout << "\n$->: ";
		}
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
			continue;
		}
		if (flagChose > filePath.getSize() || flagChose < 0)
		{
			system("cls");
			cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
			continue;
		}
		if (flagChose > 0)
		{
			path = filePath[flagChose - 1];
			return 1;
		}
	} while (flagChose != 0);
	return 0;
}


void delFile(List <string>& filePath)
{
	int flagChose;
	do
	{
		heading();
		cout << "\n                                       Выбор файла для удаления" << endl;
		cout << "\n   |Saved files| == " << filePath.getSize() << " ==" << endl;
		cout << "         |\n         |\n         |-|x| Выбор:\n            |" << endl;
		for (int i = 0; i < filePath.getSize(); i++)
		{
			cout << "            | " << i + 1 << " - " << filePath[i] << ";" << endl;
		}
		cout << "\n\n$->:|File|-> ";
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
			continue;
		}
		if (flagChose > filePath.getSize() || flagChose < 0)
		{
			system("cls");
			cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
			continue;
		}
		if (flagChose > 0)
		{
			filePath.del(flagChose - 1);
			flagChose = 0;
		}
	} while (flagChose != 0);
}


void newFile(List <string>& filePath)
{
	string path;
	ifstream file;
	int flag = 1;

	do
	{
		heading();
		cout << "\n                                            Добавление файла\n" << endl;
		cout << ">> |x| Введите путь для нахождения файла (Для выхода - 0)\n\n$->|Saved Files|->: ";
		cin >> path;
		if (path == "0") break;
		file.open(path);
		if (!file.is_open()) 
		{
			file.close();
			system("cls");
			cout << "\n>> |!| Ошибка: не удалось открыть файл по указанному пути." << endl;
			continue;
		}
		filePath.append(path);
		flag = 0;
	} while (flag != 0);
}


// Выбор сохраненных файлов
void PathSelection(List <string>& filePath, string& path, int& SF)
{
	int flagChose;
	do
	{
		heading();
		cout << "\n                                              Выбор файла" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|Saved files| == " << filePath.getSize() << " ==" << endl;
		cout << "\t     |\n\t     |\n\t     |-|x| Действия:" << endl;
		cout << "\t\t|\n\t\t| 1 - Выбор файла;\n\t\t| 2 - Добавление файла;\n\t\t| 3 - Удаление файла;\n\t\t| 0 - Выход в меню;\n\t\t|\n\n$->: ";
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
			SF = sevedFiles(filePath, path);
			system("cls");
			break;
		case 2:
			system("cls");
			newFile(filePath);
			system("cls");
			break;
		case 3:
			system("cls");
			delFile(filePath);
			system("cls");
			break;
		}
		if (flagChose < 0 || flagChose > 3)
		{
			system("cls");
			cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
		}
	} while (flagChose != 0);
}


// Меню выбора фалов с возможностью получения информации 
void mainMenu() 
{
	int flagChose, statusFlag = 0;
	string path = "Не выбран!";
	List <string> filePath;
	filePath.append("E:\\Example.txt");
	do 
	{
		heading();
		cout << "\n                                                 Меню" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|x| Действия:" << endl;
		cout << "        |\n        | 1 - Работа с файлом;\n        | 2 - Выбор файла;\n        | 0 - Выход;\n        |\n\n$->: ";	
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n>>|!| Вы ввели неправильное значение!\n" << endl;
			continue;
		}
		switch (flagChose)
		{
		case 1:
			system("cls");
			if (statusFlag == 0)
			{
				cout << "\n>> |!| Файл не найден!\n" << endl;
				break;
			}
			working_with_file(path);
			system("cls");
			break;
		case 2:
			system("cls");
			PathSelection(filePath, path, statusFlag);
			system("cls");
			break;
		}
			if (flagChose < 0 || flagChose > 2)
			{
				system("cls");
				cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
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
	system("cls");
	cout << "\n>> |!| Завершение работы!" << endl;
	return 0;
}
