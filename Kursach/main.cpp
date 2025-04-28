/* 
Автор: Близученко А.Г.
Учебная дисциплина: Архитектура вычислительных систем
Тема: "Сортировка последовательностей"
Цель: "Сортировка предложений текста в текстовом файле по числу знаков"
Шифры группы: ИВТ2-23
Год выполнения (Version 1.0): 2024 

== РЕЛИЗ ==
*/


// Описание библиотек 
#include <iostream> 
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <limits>
#include <cstring>
#include "List.h"


#include "mainMenu.h"
#include <memory>



// Удаление макроса
#undef max


using namespace std;



//-----------------------------------------------------------------------------------------------> Сервисные


//>>> Функция: Вывод заголовка работы
static void HeadingWork()
{
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
  //cout << "|\t\t\t\t\t\tКурсовая работа\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\tKursach\t\t\t\t\t\t\t|" << endl;
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
}


//>>> Функция: Задержка перед переходом
static void DelayInput()
{
	char check;
	cout << "\n\n>> |x| Введите любой символ для продожения...\n\n$->: ";
	cin >> check;
}

//-----------------------------------------------------------------------------------------------|



//-----------------------------------------------------------------------------------------------> Меню взаимодействия с файлом


//>>> Функция: Сравнивает переменную с массивом символов
static int Comparison(char symbol)
{
	const char punctuationMarks[256] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23, 24, 25,
		26, 27, 28, 29, 30, 31, 32, ' ',
		'!', '"', '#', '$', '%', '&', '\'',
		'(', ')', '*', '+', ',', '-', '.',
		'/', '0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9', ':', ';', '<',
		'=', '>', '?', '@', 'A', 'B', 'C',
		'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q',
		'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', '[', '\\', ']', '^', '_',
		'`','a','b','c','d','e','f','g',
		'h','i','j','k','l','m','n','o',
		'p','q','r','s','t','u','v','w',
		'x','y','z','{','|','}','~',

		'\xC0','\xC1','\xC2','\xC3','\xC4',
		'\xC5','\xC6','\xC7','\xC8','\xC9',
		'\xD0','\xD1','\xD2','\xD3','\xD4',
		'\xD5','\xD6','\xD7','\xD8','\xD9',
		'\xE0','\xE1','\xE2','\xE3','\xE4',
		'\xE5','\xE6','\xE7','\xE8','\xE9',
		'\xF0','\xF1','\xF2','\xF3','\xF4',
		'\xF5','\xF6'
	};
	int flag = 0, lenPM = sizeof(punctuationMarks) / sizeof(punctuationMarks[0]);

//----------------------------------------------------------------------->>>> Ассемблерная вставка для занесения символов в List 
	__asm
	{
		mov al, symbol              // Загружаем текущий символ в регистр AL
		lea ebx, punctuationMarks   // Загружаем адрес массива символов пунктуации в регистр EBX
		mov ecx, lenPM              // Загружаем количество символов в массиве пунктуации в регистр ECX

			//---------------------------------|
			//>>> Метка: Сравнение нашего символа с требуемыми символами 
		check_punctuation :

			cmp ecx, 0				// Проверяем, остались ли символы для проверки
			je end_loop				// Если нет, выходим из проверки
			cmp al, [ebx]			// Сравниваем с текущим символом пунктуации
			je flag_add				// Если совпадает, увеличиваем счетчик
			inc ebx					// Переходим к следующему символу пунктуации
			dec ecx					// Уменьшаем счетчик для массива пунктуации
			jmp check_punctuation	// Повторяем для всех символов пунктуации

			//---------------------------------|
			//>>> Метка: Изменение состояния флага для проверик на сходство
		flag_add:

			inc flag				// Увеличиваем счетчик найденных символов пунктуации
	
			//---------------------------------|
			//>>> Метка: Выход
		end_loop:
	}
//----------------------------------------------------------------------->>>> Конец ссемблерной вставки
	return flag;
}



//>>> Функция: Нахождение символов в предложение и занесение их в лист 
static void foundSymb(string text, List <char>& symbols)
{
	for (char s : text)
	{
		if (Comparison(s))
		{
			symbols.append(s);
		}
	}
}


//>>> Функция: Нахождение символов в предложение и подсчет их
static int foundSymb(const string& text)
{
	int punctuationCount = 0; // Изменено название переменной
	const char punctuationMarks[256] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23, 24, 25,
		26, 27, 28, 29, 30, 31, 32, ' ',
		'!', '"', '#', '$', '%', '&', '\'',
		'(', ')', '*', '+', ',', '-', '.',
		'/', '0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9', ':', ';', '<',
		'=', '>', '?', '@', 'A', 'B', 'C',
		'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q',
		'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', '[', '\\', ']', '^', '_',
		'`','a','b','c','d','e','f','g',
		'h','i','j','k','l','m','n','o',
		'p','q','r','s','t','u','v','w',
		'x','y','z','{','|','}','~',

		'\xC0','\xC1','\xC2','\xC3','\xC4',
		'\xC5','\xC6','\xC7','\xC8','\xC9',
		'\xD0','\xD1','\xD2','\xD3','\xD4',
		'\xD5','\xD6','\xD7','\xD8','\xD9',
		'\xE0','\xE1','\xE2','\xE3','\xE4',
		'\xE5','\xE6','\xE7','\xE8','\xE9',
		'\xF0','\xF1','\xF2','\xF3','\xF4',
		'\xF5','\xF6'
	};

	int lenPM = sizeof(punctuationMarks) / sizeof(punctuationMarks[0]);
	const char* text_C = text.c_str();
	int lenTxt = strlen(text_C);

	//----------------------------------------------------------------------->>>> Ассемблерная вставка для подсчета символов в предложение
	__asm
	{
		mov esi, text_C                    // Указатель на начало строки
		mov ecx, lenTxt                    // Длина строки
			//---------------------------------|
			//>>> Метка: Переход к следующему символу
		next_char :

		cmp ecx, 0						   // Проверка на конец строки
			je end_loop                    // Если конец, выходим из цикла
			mov al, [esi]                  // Загружаем текущий символ
			inc esi                        // Переходим к следующему символу
			dec ecx                        // Уменьшаем счетчик
			push ecx                       // Сохраняем длину оставшейся строки
			mov ecx, lenPM                 // Устанавливаем длину массива пунктуации
			lea ebx, punctuationMarks      // Указатель на массив пунктуации

			//---------------------------------|
			//>>> Метка: Сравнение нашего символа с требуемыми символами 
		check_punctuation:

		cmp ecx, 0						   // Проверяем, остались ли символы для проверки
			je pop_ecx                     // Если нет, выходим из проверки
			cmp al, [ebx]                  // Сравниваем с текущим символом пунктуации
			je count_add                   // Если совпадает, увеличиваем счетчик
			inc ebx                        // Переходим к следующему символу пунктуации
			dec ecx                        // Уменьшаем счетчик для массива пунктуации
			jmp check_punctuation          // Повторяем для всех символов пунктуации

			//---------------------------------|
			//>>> Метка: Восстановление счетчика в массиве символов
		pop_ecx:

		pop ecx							   // Восстанавливаем счетчик
			jmp next_char                  // Переход к следующему символу

			//---------------------------------|
			//>>> Метка: Увеличение счетчика символов
		count_add:

		inc punctuationCount			   // Увеличиваем счетчик совпадений
			pop ecx                        // Восстанавливаем счетчик
			jmp next_char                  // Переход к следующему символу

			//---------------------------------|
			//>>> Метка: выхода
		end_loop:						  // Выход из вставки
	}
	//----------------------------------------------------------------------->>>> Конец ассемблерной вставки

	return punctuationCount; // Возвращаем количество найденных символов пунктуации
}



//>>> Функция: Сортировка файла методом insertion sort (Сортировка вставками)
static void Sorted(List<string>& Text, string& path)
{


	int status;
	for (int i = 1; i < Text.getSize(); i++)
	{
		status = (i * 100) / Text.getSize();


		string current = Text[i]; 
		int j = i - 1;

		// Сравниваем с предыдущими элементами
		while (j >= 0 && foundSymb(Text[j]) > foundSymb(current))
		{
			Text[j + 1] = Text[j]; 
			--j; 
		}

		Text[j + 1] = current; 

		system("cls");
		HeadingWork();
		cout << "\n                                         ==|Работа с файлом|==" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|x| Действия:" << endl;
		cout << "        |\n        | 1 - Чтение файла;\n        | 2 - Сортировка {Ключевое поле - 'Знаки'};\n        | 0 - Выход в меню;\n        |\n";

		cout << "\n>>> |Processing| == |";
		for (int j = 1; j <= (status / 10); j++)
		{
			cout << "[]";
		}
		for (int j = 1; j <= (10 - status / 10); j++)
		{
			cout << "--";
		}
		cout << "|" << status <<"% ==\n" << endl;


	}

	system("cls");
	HeadingWork();
	cout << "\n                                         ==|Работа с файлом|==" << endl;
	cout << "\n   |File| == " << path << " ==" << endl;
	cout << "     |\n     |\n     |-|x| Действия:" << endl;
	cout << "        |\n        | 1 - Чтение файла;\n        | 2 - Сортировка {Ключевое поле - 'Знаки'};\n        | 0 - Выход в меню;\n        |\n";
	cout << "\n>>> |Processing| == |[][][][][][][][][][]|100% == ";
	cout << "\n         |";
}


//>>> Функция: Запись новых данных в файл
static string writeFile(List <string>& filePath, string path, List<string>& text)
{
	// Создание имени файла с добавленным словом "_sorted"
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
	int flag = 1;
	for (int i = 0; i < filePath.getSize(); i++)
	{
		if (sortedPath == filePath[i]) flag--;
	}
	if (flag)
	{
		filePath.append(sortedPath);
	}
	return "         |->|!| Данные успешно отсортированы и записаны в файл == " + sortedPath + " ==";
}


//>>> Функция: Чтение информации с файла в структуру данных
static int readFile(string& path, List<string>& text)
{
	ifstream file(path);
	if (!file.is_open())
		return 1; // Не удалось открыть файл

	char symbol;
	string suggestions;

	// Чтение файла посимвольно
	while (file.get(symbol))
	{
		// Проверка на окончание предложения
		if (symbol == '.' || symbol == '!' || symbol == '?')
		{
			suggestions += symbol; // Добавляем последний символ (знак окончания)
			text.append(suggestions); // Добавляем предложение в список
			suggestions.clear(); // Очищаем строку для следующего предложения
		}
		else if (symbol != '\n') // Игнорируем символы новой строки
			suggestions += symbol; // Добавляем символ к текущему предложению
	}


	// Добавление последнего предложения, если оно не пустое
	if (!suggestions.empty()) {
		text.append(suggestions);
	}

	file.close();
	return 0; // Успешное завершение функции
}



//>>> Функция: Вывод информации о файле
static void outputFileInfo(string& path, List <string>& text)
{
	List <char> symbols; // Список знаков в предложение из файла
	int count;
	// Вызов заголовка
	HeadingWork();
	cout << "\n                                        ==|Содержимое файла|==\n" << endl;
	cout << ">> |" << path << "| \n\n";
	// Проверка на существование файла
	if (readFile(path, text))
	{
		cout << "\n>> |!| Ошибка, файл не может быть открыт!" << endl;
		DelayInput();
		return;
	}
	
	cout << ">> |Text|>:\n" << endl;

/*
У меня существует проблема в кодировках, поэтому информация из файла выводится иероглифами.
Но после изменения кодировки вывода в консоль на UTF8, дальнейшие русские символы из программы тоже перестают нормально выводиться.
Поэтому после вывода информации из текстового файла в консоль нужно снова поменять кодировку на CP1251 для нормального вывода русского текста
из программы.
*/
	if (text.getSize() > 1)
	{
		// Изменение кодировки для вывода содержимого файла в консоль
		SetConsoleOutputCP(CP_UTF8);
		// Вывод информации из структуры данных
		text.print();
		// Изменение кодировки для вывода текста программы в консоль
		SetConsoleOutputCP(1251);
		// Вывод таблицы
		cout << endl << ">> |Info|>:\n\n";
		cout << "\n\t---------------------------------------------------------------------------------" << endl;
		cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|" << endl;
		SetConsoleOutputCP(CP_UTF8);
		cout << "\t|    № Номер\t|\t\t    Символы\t\t\t|     Кол-Во\t|" << endl;
		SetConsoleOutputCP(1251);
		cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|";
		for (int i = 0; i < text.getSize(); i++)
		{
			count = foundSymb(text[i]);
			cout << "\n\t|---------------|-----------------------------------------------|---------------|" << endl;
			cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|" << endl;
			cout << "\t|\t" << i + 1 << "\t|    ";
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
			else if (count < 1001)
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
				SetConsoleOutputCP(CP_UTF8);
				cout << "\t\tПЕРЕПОЛНЕНИЕ\t\t\t|\t>100\t|" << endl;
				SetConsoleOutputCP(1251);
				cout << "\t|\t\t|\t\t\t\t\t\t|\t\t|";
			}
			symbols.~List();
		}
		cout << "\n\t---------------------------------------------------------------------------------" << endl;
	}
	else
	{
		SetConsoleOutputCP(CP_UTF8);
		cout << "\n\t\t~~ В файле не найдены предложения! ~~ " << endl; 
	}
	SetConsoleOutputCP(CP_UTF8);
	DelayInput();
}


//NEW
static void SortProc(string& path, List <string>& Text, List <string>& filePath)
{
	Text.~List();
	// Вызов функции чтения файла для заполнения структуры 
	readFile(path, Text);
	// Вызов функции сортировки предложений
	Sorted(Text, path);
	cout << "\n" << writeFile(filePath, path, Text) << "\n\n$->: ";
	Text.~List();
}


//>>> Функция: Функция: Обработка файла - чтение и сортировка.
static void processingFile(List <string>& filePath, string& path)
{
	List <string> Text; // Список предложений текста из файла
	int flagChose, flagActive = 0;
	// Вызов заголовка
	HeadingWork();
	cout << "\n                                         ==|Работа с файлом|==" << endl;
	cout << "\n   |File| == " << path << " ==" << endl;
	cout << "     |\n     |\n     |-|x| Действия:" << endl;
	cout << "        |\n        | 1 - Чтение файла;\n        | 2 - Сортировка {Ключевое поле - 'Знаки'};\n        | 0 - Выход в меню;\n        |\n\n$->: ";
	do
	{

		// Проверка на ввод нечислового значения
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			// Вызов заголовка
			HeadingWork();
			cout << "\n                                         ==|Работа с файлом|==" << endl;
			cout << "\n   |File| == " << path << " ==" << endl;
			cout << "     |\n     |\n     |-|x| Действия:" << endl;
			cout << "        |\n        | 1 - Чтение файла;\n        | 2 - Сортировка {Ключевое поле - 'Знаки'};\n        | 0 - Выход в меню;\n        |\n";
			cout << "\n>> |!| Вы ввели неправильное значение!\n\n$->: ";
			continue;
		}
		switch (flagChose)
		{
		// Вывод информации о файле
		case 1:
			system("cls");
			outputFileInfo(path, Text);
			Text.~List();
			system("cls");
			HeadingWork();
			cout << "\n                                         ==|Работа с файлом|==" << endl;
			cout << "\n   |File| == " << path << " ==" << endl;
			cout << "     |\n     |\n     |-|x| Действия:" << endl;
			cout << "        |\n        | 1 - Чтение файла;\n        | 2 - Сортировка {Ключевое поле - 'Знаки'};\n        | 0 - Выход в меню;\n        |\n";
			cout << "\n\n$->: ";
			break;
		// Сортировка файла
		case 2:
			//--------------------------------------------\/ Тут нужно дополнить
			system("cls");
			if (readFile(path, Text))
			{
				cout << "\n>> |!| Ошибка, файл не может быть открыт!\n" << endl;
				break;
			}
			SortProc(path, Text, filePath);
			break;
			//--------------------------------------------/\ Тут нужно дополнить
		}
		if (flagChose < 0 || flagChose > 2)
		{
			system("cls");
			// Вызов заголовка
			HeadingWork();
			cout << "\n                                         ==|Работа с файлом|==" << endl;
			cout << "\n   |File| == " << path << " ==" << endl;
			cout << "     |\n     |\n     |-|x| Действия:" << endl;
			cout << "        |\n        | 1 - Чтение файла;\n        | 2 - Сортировка {Ключевое поле - 'Знаки'};\n        | 0 - Выход в меню;\n        |\n";
			cout << "\n>> |!| Вы ввели неправильное значение!\n\n$->: " << endl;
		}
	} while (flagChose != 0);
}

//-----------------------------------------------------------------------------------------------|




//-----------------------------------------------------------------------------------------------> Меню выбора файлов


//>>> Функция: Функция: Вывод списка сохраненных файлов 
static int sevedFiles(List <string>& filePath, string& path)
{
	int flagChose;
	do
	{
		// Вызов заголовка 
		HeadingWork();
		cout << "\n                                    ==|Список сохраненных файлов|==" << endl;
		cout << "\n   |Saved files| == " << filePath.getSize() << " ==" << endl;
		cout << "         |\n         |\n         |-|x| Выбор:\n            |" << endl;
		// Вывод всех сохраненных файлов в структуре
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
		// Проверка на ввод нечислового значения
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
			// Выбор файал сохраняется в оригинальную переменную path 
			path = filePath[flagChose - 1];
			return 1;
		}
	} while (flagChose != 0);
	return 0;
}


//>>> Функция: Вывод меню удаление файла из структуры
static void delFile(List <string>& filePath)
{
	int flagChose;
	do
	{
		HeadingWork();
		cout << "\n                                    ==|Выбор файла для удаления|==" << endl;
		cout << "\n   |Saved files| == " << filePath.getSize() << " ==" << endl;
		cout << "         |\n         |\n         |-|x| Выбор:\n            |" << endl;
		// Вывод всех сохраненных файлов в структуре 
		for (int i = 0; i < filePath.getSize(); i++)
		{
			cout << "            | " << i + 1 << " - " << filePath[i] << " ;" << endl;
		}
		cout << "            | " << endl;
		cout << "\n\n$->:|Saved files|-> ";
		// Проверка на ввод нечислового значения
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


//>>>  Функция: Вывод меню добавления нового файла в структуру
static void newFile(List <string>& filePath)
{
	string path;
	ifstream file;
	int flag = 1;

	do
	{
		// Вызов заголовка
		HeadingWork();
		cout << "\n                                         ==|Добавление файла|==\n" << endl;
		cout << ">> |x| Введите путь для нахождения файла (Для выхода - 0)\n\n$->|Saved Files|->: ";
		cin >> path;
		// Проверка на выход из меню
		if (path == "0") break;
		file.open(path);
		// Проверка на существования файла
		if (!file.is_open()) 
		{
			file.close();
			system("cls");
			cout << "\n>> |!| Ошибка: не удалось открыть файл по указанному пути." << endl;
			continue;
		}
		// Добавление файла в структуру
		filePath.append(path);
		flag = 0;
	} while (flag != 0);
}


//>>>  Функция: Вывод меню выбора файла
static void selectionFile(List <string>& filePath, string& path)
{
	int flagChose;


	// Началао работы меню выбора файлов 
	do
	{
		// Вызов заголовка
		HeadingWork();
		cout << "\n                                           ==|Выбор файла|==" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|Saved files| == " << filePath.getSize() << " ==" << endl;
		cout << "\t     |\n\t     |\n\t     |-|x| Действия:" << endl;
		cout << "\t\t|\n\t\t| 1 - Список файлов;\n\t\t| 2 - Добавление файла;\n\t\t| 3 - Удаление файла;\n\t\t| 0 - Выход в меню;\n\t\t|\n\n$->: ";
		// Проверка на ввод нечислового значения
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
			// Запуск меню с выбором файла из списка
			sevedFiles(filePath, path);
			system("cls");
			break;
		case 2:
			system("cls");
			// Запуск меню добавления файла в структуру
			newFile(filePath);
			system("cls");
			break;
		case 3:
			system("cls");
			// запуск меню удаления файла из СТРУКТУРЫ 
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

//-----------------------------------------------------------------------------------------------|



//-----------------------------------------------------------------------------------------------> Главное меню


//>>> Функция: Вывод главного меню 
static void MainMenu()
{
	int flagChose;
	string path = "Не выбран!";
	List <string> filePath;
	// Заполнение структуры списка основными файлами для проверки
	filePath.append("Example1.txt");
	filePath.append("Example2.txt");

	// начала работы меню
	do 
	{
		// Вызов заголовка
		HeadingWork();
		cout << "\n                                              ==|Меню|==" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|x| Действия:" << endl;
		cout << "        |\n        | 1 - Работа с файлом;\n        | 2 - Выбор файла;\n        | 0 - Завершение работы;\n        |\n\n$->: ";
		// Проверка на ввод нечислового значения
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
				cout << "\n>> |!| Файл не выбран!\n" << endl;
				break;
			}
			// запуск меню работы с файлом
			processingFile(filePath, path);
			system("cls");
			break;
		case 2:
			system("cls");
			// Запуск меню выбора файла 
			selectionFile(filePath, path);
			system("cls");
			break;
		}
			if (flagChose < 0 || flagChose > 2)
			{
				system("cls");
				cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
			}
	} while (flagChose != 0);


	// Отчистка структуры данных
	filePath.~List();
	system("cls");
	cout << "\n>> |!| Завершение работы!" << endl;
}

//-----------------------------------------------------------------------------------------------|



// Точка входа
int main()
{
	// Изменение кодировки терминала для работы с кириллицей
	system("chcp 1251 > nul"); // Почему то слетела....
	//SetConsoleOutputCP(CP_UTF8);
	// Запуск главного меню
	//MainMenu();


	//std::unique_ptr<Menu> menu = std::make_unique<mainMenu>();
	//menu->drawMenu();


	MenuStart menu;
	menu.setPath("C:/Gav.txt");
	menu.drawMenu();


	return 0;
}
