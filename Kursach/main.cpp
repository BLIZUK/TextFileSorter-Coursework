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
#include <set>
#include "List.h"



// Удаление макроса
#undef max


using namespace std;


// Заголовок работы
void heading() 
{
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
  //cout << "|\t\t\t\t\t\tКурсовая работа\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\tKursach\t\t\t\t\t\t\t|" << endl;
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
}


// Задержка перед переходом
void delay()
{
	char check;
	cout << "\n\n>> |x| Введите любой символ для продожения...\n\n$->: ";
	cin >> check;
}

void characterOutput()
{

}


// Нахождение символов в предложение и занесение их в лист
void foundSymb(string text, List <char>& symbols)
{
	int count = 0;
	set <char> punctuationMarks =
	{
		'.', ',', '!', '?', ';', ':', '-', '_',
		'(', ')', '[', ']', '{', '}', '<', '>',
		'\'', '\"', '\\', '/', '|', '@', '#',
		'$', '%', '^', '&', '*', '+', '=',
		'~', '`'
	};
	// ' ', '\t'

	for (char s : text)
	{
		if (punctuationMarks.find(s) != punctuationMarks.end())
		{
			count += 1;
			symbols.append(s);
		}
	}
}


// Нахождение символов в предложение и подсчет их
int foundSymb(string text)
{
	int count = 0;
	set <char> punctuationMarks =
	{
		'.', ',', '!', '?', ';', ':', '-', '_',
		'(', ')', '[', ']', '{', '}', '<', '>',
		'\'', '\"', '\\', '/', '|', '@', '#',
		'$', '%', '^', '&', '*', '+', '=',
		'~', '`'
	};
	// ' ', '\t'

	for (char s : text)
	{
		if (punctuationMarks.find(s) != punctuationMarks.end())
		{
			count += 1;
		}
	}
	return count;
}


// Сортировка файла за счет С++ (Пример работы)
void sortedC(List <string>& text)
{
	List <string> SortedText;
	int count, flag = 0;

	for (int i = 0; i < text.getSize(); i++)
	{
		if (SortedText.empty()) SortedText.append(text[0]);
	}


	// Вывод
	SetConsoleOutputCP(CP_UTF8);
	text.print();
	SetConsoleOutputCP(1251);
	delay();

}



// Сортировка файла с помощью asm вставок
void sortedAsm() 
{
}


// Запись новых данных в файл
void writeFile()
{

}





// Чтение информации с файла
int readFile(string& path, List <string>& text)
{
	ifstream file(path);
	if (!file.is_open())
	{
		file.close();
		return 1;
	}
	char symbol;
	string suggestions, multipoint = "";
	while (file.get(symbol))
	{
		if (multipoint != "")
		{
			if (symbol != '.')
			{
				text.append(suggestions);
				suggestions = "";
				multipoint = "";
			}
		}
		

		suggestions += symbol;
		if (symbol == '.')
		{
			multipoint += symbol; 
		}
		if (symbol == '!')
		{
			text.append(suggestions);
			suggestions = "";
		}
		if (symbol == '?')
		{
			text.append(suggestions);
			suggestions = "";
		}
	}
	text.append(suggestions);
	file.close();
	return 0;
}


void output(string& path, List <string>& text)
{
	List <char> symbols; // Список знаков в предложение из файла
	int count;
	heading();
	cout << "\n                                        ==|Содержимое файла|==\n" << endl;
	cout << ">> |" << path << "| \n\n";
	if (readFile(path, text))
	{
		cout << "\n>> |!| Ошибка, файл не может быть открыт!" << endl;
		delay();
		return;
	}
	//readFile(path, text);
	cout << ">> |Text|>:\n" << endl;
	SetConsoleOutputCP(CP_UTF8);
	text.print();
	SetConsoleOutputCP(1251);
	//cout << endl << ">> |Количество предложений|>:\n\n" << text.getSize() << endl;
	cout << endl << ">> |Info|>:\n\n";
	cout << "\n\t---------------------------------------------------------------------------------" << endl;
	cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|" << endl;
	cout << "\t|\tНомер\t|\t\t\tСимволы\t\t\t|\tКол-Во\t|" << endl;
	cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|";
	for (int i = 0; i < text.getSize(); i++)
	{
		count = foundSymb(text[i]);
		cout << "\n\t---------------------------------------------------------------------------------" << endl;
		cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|" << endl;
		cout << "\t|\t" << i + 1<< "\t|\t";
		foundSymb(text[i], symbols);
		if (count < 30) {
			while (count != 0)
			{
				cout << symbols[i] << " ";
				count--;
			}
			cout << "\t\t\t\t|\t" << foundSymb(text[i]) << "\t|" << endl;
			cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|";
		}
	}
	delay();
}


// Обработка файла - чтение сортировка.
void working_with_file(string& path)
{
	List <string> text; // Список предложений текста из файла
	int flagChose, flagActive = 0, exit;
	do
	{
		heading();
		cout << "\n                                         ==|Работа с файлом|==" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|x| Действия:" << endl;
		cout << "        |\n        | 1 - Чтение файла;\n        | 2 - Сортировка {Ключевое поле - 'Знаки'};\n        | 0 - Выход в меню;\n        |\n\n$->: ";
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
			continue;
		}
		switch (flagChose)
		{
		case 1:
			system("cls");
			output(path, text);
			text.~List();
			system("cls");
			break;
		case 2:
			system("cls");
			//sortedC(text);
			flagActive = 1;
			system("cls");
			break;
		// Проверка на наличие несохраенных данных для выхода из функции и записи в файл отсортированного текста
		case 0:
			do
			{
				if (flagActive == 1)
				{
					cout << "\n    >> |!| Есть несохраненные данные. Сохранить?\n\n$->: ";
					if (!(cin >> exit))
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						flagChose = -1;
						//system("cls");
						cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
						continue;
					}
					if (exit == 1)
					{
						// Запись данных в файл
						writeFile();
						flagActive = 0;
					}
					if (exit == 0) flagActive = 0;
					if (exit != 0)
					{
						cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
						continue;
					}

				}
				text.~List();
			} while (flagActive != 0);
			break;

		}
		if (flagChose < 0 || flagChose > 2)
		{
			system("cls");
			cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
		}
	} while (flagChose != 0);
}


// Список сохраненных файлов 
int sevedFiles(List <string>& filePath, string& path)
{
	int flagChose;
	do
	{
		heading();
		cout << "\n                                    ==|Список сохраненных файлов|==" << endl;
		cout << "\n   |Saved files| == " << filePath.getSize() << " ==" << endl;
		cout << "         |\n         |\n         |-|x| Выбор:\n            |" << endl;
		if (filePath.getSize())
		{
			for (int i = 0; i < filePath.getSize(); i++)
			{
				cout << "            | " << i + 1 << " - " << filePath[i] << " ;" << endl;
			}
			cout << "            | " << endl;
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


// Удаление файла
void delFile(List <string>& filePath)
{
	int flagChose;
	do
	{
		heading();
		cout << "\n                                    ==|Выбор файла для удаления|==" << endl;
		cout << "\n   |Saved files| == " << filePath.getSize() << " ==" << endl;
		cout << "         |\n         |\n         |-|x| Выбор:\n            |" << endl;
		for (int i = 0; i < filePath.getSize(); i++)
		{
			cout << "            | " << i + 1 << " - " << filePath[i] << " ;" << endl;
		}
		cout << "            | " << endl;
		cout << "\n\n$->:|Saved files|-> ";
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


// создание нового файла
void newFile(List <string>& filePath)
{
	string path;
	ifstream file;
	int flag = 1;

	do
	{
		heading();
		cout << "\n                                         ==|Добавление файла|==\n" << endl;
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
		cout << "\n                                           ==|Выбор файла|==" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|Saved files| == " << filePath.getSize() << " ==" << endl;
		cout << "\t     |\n\t     |\n\t     |-|x| Действия:" << endl;
		cout << "\t\t|\n\t\t| 1 - Список файлов;\n\t\t| 2 - Добавление файла;\n\t\t| 3 - Удаление файла;\n\t\t| 0 - Выход в меню;\n\t\t|\n\n$->: ";
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
	filePath.append("D:\\example.txt");
	do 
	{
		heading();
		cout << "\n                                              ==|Меню|==" << endl;
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
	system("cls");
	cout << "\n>> |!| Завершение работы!" << endl;
}


// Точка входа
int main()
{
	// Изменение кодировки терминала для работы с кириллицей
	system("chcp 1251 > nul");
	mainMenu();
	return 0;
}
