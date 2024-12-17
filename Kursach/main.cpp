/* 
Автор: Близученко А.Г.
Учебная дисциплина: Архитектура вычислительных систем
Тема: "Сортировка последовательностей"
Цель: "Сортировка предложений текста в текстовом файле по числу знаков"
Шифры группы: ИВТ2-23
Год выполнения: 2024 
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
int Comparison(char symbol)
{
	const char punctuationMarks[] =
	{
	'.', ',', '!', '?', ';', ':', '-', '_',
	'(', ')', '[', ']', '{', '}', '<', '>',
	'\'', '\"', '\\', '/', '|', '@', '#',
	'$', '%', '^', '&', '*', '+', '=',
	'~', '`'
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
void foundSymb(string text, List <char>& symbols)
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
int foundSymb(const string& text)
{
	int count = 0;
	const char punctuationMarks[] =
	{
	'.', ',', '!', '?', ';', ':', '-', '_',
	'(', ')', '[', ']', '{', '}', '<', '>',
	'\'', '\"', '\\', '/', '|', '@', '#',
	'$', '%', '^', '&', '*', '+', '=',
	'~', '`'
	};
	int lenPM = sizeof(punctuationMarks) / sizeof(punctuationMarks[0]);
	const char* text_C = text.c_str();
	int lenTxt = strlen(text_C);

	//----------------------------------------------------------------------->>>> Ассемблерная вставка для подсчета символов в предложение
	__asm
	{
		mov esi, text_C					// Указатель на начало строки
		mov ecx, lenTxt					// Длина строки
	//---------------------------------|
	//>>> Метка: Переход к следующему символу
				next_char :

			cmp ecx, 0					// Проверка на конец строки
			je end_loop					// Если конец, выходим из цикла
			mov al, [esi]				// Загружаем текущий символ
			inc esi						// Переходим к следующему символу
			dec ecx						// Уменьшаем счетчик
			push ecx					// Сохраняем длину оставшейся строки
			mov ecx, lenPM				// Устанавливаем длину массива пунктуации
			lea ebx, punctuationMarks	// Указатель на массив пунктуаци

	//---------------------------------|
	//>>> Метка: Сравнение нашего символа с требуемыми символами 
				check_punctuation : 

			cmp ecx, 0					// Проверяем, остались ли символы для проверки
			je pop_ecx					// Если нет, выходим из проверки
			cmp al, [ebx]				// Сравниваем с текущим символом пунктуации
			je count_add				// Если совпадает, увеличиваем счетчик
			inc ebx						// Переходим к следующему символу пунктуации
			dec ecx						// Уменьшаем счетчик для массива пунктуации
			jmp check_punctuation		// Повторяем для всех символов пунктуации

    //---------------------------------|
	//>>> Метка: Восстановление счетчика в массиве символов
				pop_ecx :

			pop ecx						// Восстанавливаем счетчик
			jmp next_char				// Переход к следующему символу

	//---------------------------------|
	//>>> Метка: Увеличение счетчика символов
				count_add :		

			inc count					// Увеличиваем счетчик совпадений
			pop ecx						// Восстанавливаем счетчик
			jmp next_char				// Переход к следующему символу

	//---------------------------------|
	//>>> Метка: выхода
				end_loop :				// Выход из вставки
	}
	//----------------------------------------------------------------------->>>> Конец ссемблерной вставки

/*
В процессе написания кода на ассемблере в функции foundSymb была найдена повторяющаяся ошибка
Функция постоянно возвращала значение - 47.
На глаз определить проблему не удалось. ИИ тоже не смогли выявить проблему. Да и в целом ИИ очень плохо отвечает по теме ассемблера.
И пользы от нее практичекси 0. Поэтому выбор пал на дебагинг с помощью дизассемблирования функции. 
В процессе проверки выявилась закономерность - после прохода к новому символу предложения, 
В регистр EAX заносилось значение этого символа в кодировки ASCII. В конце предложения в моих примерах была точка.
Ее значение в ASCII формате 46. Так как это символ, то цикл добавляет единицу к регистру eax. Затем переносит значение из eax в мою переменную и выходит.
Решение оказалось простым - избавление от взаимодействия с регистром eax и работа со счетчиком (count) напрямую.
*/

	return count; // Возвращаем количество найденных символов пунктуации
}


//>>> Функция: Сортировка файла методом insertion sort (Сортировка вставками)
void Sorted(List<string>& Text)
{
	for (int i = 1; i < Text.getSize(); i++)
	{
		string current = Text[i]; 
		int j = i - 1;

		// Сравниваем с предыдущими элементами
		while (j >= 0 && foundSymb(Text[j]) > foundSymb(current))
		{
			Text[j + 1] = Text[j]; 
			--j; 
		}

		Text[j + 1] = current; 
	}
}


//>>> Функция: Запись новых данных в файл
string writeFile(List <string>& filePath, string path, List<string>& text)
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
	filePath.append(sortedPath);
	return ">>> |!| Данные успешно отсортированны и записаны в файл == " + sortedPath + " ==";
}


//>>> Функция: Чтение информации с файла в структуру данных
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
	// Чтение файла посимвольно
	while (file.get(symbol))
	{
		// Проверка на окончание предложения с помощью многоточия
		if (multipoint != "")
		{
			if (symbol != '.')
			{
				if (symbol == ' ' || symbol == '\n')
				{
					// Добавление символа в предложение
					text.append(suggestions);
					suggestions = "";
					multipoint = "";
					continue;
				}
				else multipoint = "";
			}
		}
		// Проверка на окончание предложения с помощью точки
		suggestions += symbol;
		if (symbol == '.')
		{
			multipoint += symbol; 
		}
		// Проверка на окончание предложения с помощью восклицательного знака
		if (symbol == '!')
		{
			text.append(suggestions);
			suggestions = "";
			multipoint = "";
		}
		// Проверка на окончание предложения с помощью вопросительного знака
		if (symbol == '?')
		{
			text.append(suggestions);
			suggestions = "";
			multipoint = "";
		}
	}
	// Добавление последнего предложения, если оно не пустое
	if (!suggestions.empty()) {
		text.append(suggestions);
	}
	file.close();
	return 0;
}


//>>> Функция: Вывод информации о файле
void outputFileInfo(string& path, List <string>& text)
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
		text.print();
		// Изменение кодировки для вывода текста программы в консоль
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
	}
	else
	{
		cout << "\n\t\t~~ В файле не найдены предложения! ~~ " << endl; 
	}
	DelayInput();
}


//>>> Функция: Функция: Обработка файла - чтение и сортировка.
void processingFile(List <string>& filePath, string& path)
{
	List <string> Text; // Список предложений текста из файла
	int flagChose, flagActive = 0;
	do
	{
		// Вызов заголовка
		HeadingWork();
		cout << "\n                                         ==|Работа с файлом|==" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|x| Действия:" << endl;
		cout << "        |\n        | 1 - Чтение файла;\n        | 2 - Сортировка {Ключевое поле - 'Знаки'};\n        | 0 - Выход в меню;\n        |\n\n$->: ";
		// Проверка на ввод нечислового значения
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
			outputFileInfo(path, Text);
			Text.~List();
			system("cls");
			break;
		case 2:
			system("cls");
			// Вызов функции чтения файла для заполнения структуры 
			readFile(path, Text);
			// Вызов функции сортировки предложений
			Sorted(Text);
			cout << "\n\n" << writeFile(filePath, path, Text) << "\n\n";
			//flagActive = 1;
			Text.~List();
			break;
		}
		if (flagChose < 0 || flagChose > 2)
		{
			system("cls");
			cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
		}
	} while (flagChose != 0);
}

//-----------------------------------------------------------------------------------------------|




//-----------------------------------------------------------------------------------------------> Меню выбора файлов


//>>> Функция: Функция: Вывод списка сохраненных файлов 
int sevedFiles(List <string>& filePath, string& path)
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
void delFile(List <string>& filePath)
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
void newFile(List <string>& filePath)
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
void selectionFile(List <string>& filePath, string& path)
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
void MainMenu() 
{
	int flagChose;
	string path = "Не выбран!";
	List <string> filePath;
	// Заполнение структуры списка основными файлами для проверки
	filePath.append("E:\\Example.txt");
	filePath.append("E:\\Example2.txt");
	filePath.append("D:\\example.txt");
	filePath.append("D:\\ex.txt");
	// начала работы меню
	do 
	{
		// Вызов заголовка
		HeadingWork();
		cout << "\n                                              ==|Меню|==" << endl;
		cout << "\n   |File| == " << path << " ==" << endl;
		cout << "     |\n     |\n     |-|x| Действия:" << endl;
		cout << "        |\n        | 1 - Работа с файлом;\n        | 2 - Выбор файла;\n        | 0 - Выход;\n        |\n\n$->: ";
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
	system("chcp 1251 > nul");
	// Запуск главного меню
	MainMenu();
	return 0;
}
