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
void sortedC(List<string>& Text, List<string>& SortedText)
{
	for (int i = 0; i < Text.getSize(); i++)
	{
		bool inserted = false;

		if (SortedText.empty())
		{
			SortedText.append(Text[i]);
			continue;
		}

		for (int j = 0; j < SortedText.getSize(); j++)
		{
			if (foundSymb(Text[i]) <= foundSymb(SortedText[j]))
			{
				SortedText.push(j, Text[i]);
				inserted = true;
				break;
			}
		}

		if (!inserted)
		{
			SortedText.append(Text[i]);
		}
	}

	/*
	SetConsoleOutputCP(CP_UTF8);
	cout << SortedText.getSize() << endl;
	for (int i = 0; i < SortedText.getSize(); i++)
	{
		cout << SortedText[i] << endl << foundSymb(SortedText[i]) << endl;
	}
	SetConsoleOutputCP(1251);
	delay();
	*/
}


// Сортировка файла с помощью asm вставок
void sortedAsm() 
{
}


// Запись новых данных в файл
string writeFile(List <string>& filePath, string path, List<string>& text)
{
	// Создание имени файла с добавленным словом "sorted"
	size_t dotPosition = path.find_last_of('.');
	string filename = path.substr(0, dotPosition);
	string extension = path.substr(dotPosition);
	string sortedPath = filename + "_sorted" + extension;

	// Открытие файла в режиме записи
	ofstream file(sortedPath, ios::trunc);

	if (!file.is_open())
	{
		return ">>> |!| Не удалось открыть файл для записи.";
	}

	// Запись строк из списка в файл
	for (int i = 0; i < text.getSize(); i++)
	{
		file << "\n" << text[i];
	}

	// Закрытие файла
	file.close();

	filePath.append(sortedPath);
	return ">>> |!| Данные успешно записаны в файл == " + sortedPath + " ==";
}





// Чтение информации с файла и заполнение структуры данных
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


// Вывод информации о файле
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
	
	cout << ">> |Text|>:\n" << endl;
	SetConsoleOutputCP(CP_UTF8);
	text.print();
	SetConsoleOutputCP(1251);
	// Вывод таблицы
	cout << endl << ">> |Info|>:\n\n";
	cout << "\n\t---------------------------------------------------------------------------------" << endl;
	cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|" << endl;
	cout << "\t|    № Номер\t|\t\t    Символы\t\t\t|     Кол-Во\t|" << endl;
	cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|";
	for (int i = 0; i < text.getSize(); i++)
	{
		count = foundSymb(text[i]);
		cout << "\n\t|---------------|-----------------------------------------------|---------------|" << endl;
		cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|" << endl;
		cout << "\t|\t" << i + 1<< "\t|    ";
		foundSymb(text[i], symbols);
		// Если знаков меньше 20
		if (count < 21) {
			int j = 0;
			while (j < count)
			{
				cout << symbols[j] << " ";
				j++;
			}
			for (j *= 2; j < 43; j++)
			{
				cout << " ";
			}
			cout << "|\t" << foundSymb(text[i]) << "\t|" << endl;
			cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|";
		}
		// если знаков меньше 100
		else if (count < 101)
		{
			int k = 0, counter = 0, step = 0;
			while (count > k)
			{
				if (counter == 20 && step == 0)
				{
					cout << "   |\t" << foundSymb(text[i]) << "\t|\n";
					cout << "\t|\t\t|    ";
					counter = 0;
					step++;
				}
				if (counter == 20)
				{
					cout << "   |\t\t|\n";
					cout << "\t|\t\t|    ";
					counter = 0;
				}
				cout << symbols[k] << " ";
				counter += 1;
				k++;
			}
			for (counter *= 2; counter < 43; counter++)
			{
				cout << " ";
			}
			cout << "|\t\t|" << endl;
			cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|";
		}
		// В случае переполнения таблицы
		else
		{
			cout << "\t\tПЕРЕПОЛНЕНИЕ\t\t\t|\t>100\t|" << endl;
			cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|";
		}
		symbols.~List();
	}
	cout << "\n\t---------------------------------------------------------------------------------" << endl;
	delay();
}


// Обработка файла - чтение сортировка.
void working_with_file(List <string>& filePath, string& path)
{
	List <string> text; // Список предложений текста из файла
	List <string> SortedText; // Список отсортированных предложений текста из файла
	int flagChose, flagActive = 0;
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
			readFile(path, text);
			sortedC(text, SortedText);
			cout << "\n\n" << writeFile(filePath, path, SortedText) << "\n\n";
			//flagActive = 1;
			text.~List();
			SortedText.~List();
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
void PathSelection(List <string>& filePath, string& path)
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
			sevedFiles(filePath, path);
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
	int flagChose;
	string path = "Не выбран!";
	List <string> filePath;
	filePath.append("E:\\Example.txt");
	filePath.append("D:\\example.txt");
	filePath.append("D:\\ex.txt");
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
			if (path == "Не выбран!")
			{
				cout << "\n>> |!| Файл не найден!\n" << endl;
				break;
			}
			working_with_file(filePath, path);
			system("cls");
			break;
		case 2:
			system("cls");
			PathSelection(filePath, path);
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
