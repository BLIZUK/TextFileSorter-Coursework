#include <iostream>


//Первый образ меню
/*
heading;
cout << "\n\t\t\t\t\t       Меню выбора файла\n" << endl;
cout << "|!| Путь к файлу - '" << path << "';" << endl;
cout << "|!| Ключевое поле - 'Знаки';\n" << endl;
cout << "|x| Выберите режим открытия файла:" << endl;
cout << "\n   | 0 - Выход;\n   | 1 - Изменить путь\n   | 2 - Просмотр содержимого файла;\n   | 3 - Сортировка файла;\n\n$->: ";
*/


// Получение краткой информации о взаимодействие с программой
/*
void sysInfo()
{
	heading();
	cout << "\n\t\t\t\t\t   Ифнормация о программе:\n" << endl;
	cout << " - Тема: «Сортировка последовательностей»" << endl;
	cout << " - Цель проектирования - разработка программы по ТЗ «Сортировка предложений текста в текстовом файле по числу знаков»" << endl;
	cout << "\n\t\t\t\t\t   Технические требования:\n" << endl;
	cout << " 1. Для реализации программы использовать вычислительные средства архитектуры IA-32." << endl;
	cout << " 2. Входные данные, предназначенные для вычисления, задаются в отдельном текстовом файле." << endl;
	cout << " 3. Выходные данные, получаемые в результате работы программы, заносятся в отдельный текстовый файл." << endl;
	cout << " 4. Для ввода и вывода информации в программу использовать операторы языка высокого уровня." << endl;
	cout << " 5. Основные операции алгоритма программы должны быть реализованы на ассемблере" << endl;
	cout << "\n\t\t\t\t\t Разработал - Близученко А.Г." << endl;

	delay();
}
*/


// Вычеркнутые функции
/*
// Выбор сохраненных файлов
int PathSelection(List <string>& filePath)
{
	int flagChose;
	do
	{
		//heading("Не выбрано");
		cout << "\n\t\t\t\t\t   Список сохраненных файлов:\n" << endl;
		cout << "|x| Выберете нужный файл:\n" << endl;
		for (int i = 0; i < filePath.getSize(); i++)
		{
			cout << "\n | " << i + 1 << " - " << filePath[i] << ";" << endl;
		}
		cout << "\n\n$->: ";

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
		if (flagChose > filePath.getSize())
		{
			system("cls");
			cout << "\n|!| Вы ввели неправильное значение!\n" << endl;
			continue;
		}
		return flagChose;
	} while (flagChose != 0);
	return flagChose;
}


// Выбор пути к файлу
string pathChange(List <string>& filePath)
{
	string path = "Выберите путь";
	int flagChose, pathChose;
	do
	{
		//heading("Работа с файлом");
		cout << "\n\t\t\t\t\t       Меню выбора файла\n" << endl;
		//cout << "|x| Выберите режим открытия файла:" << endl;
		cout << "\n   | 0 - Выход;\n   | 1 - Просмотр сохраненых файлов;\n   | 2 - Добавление нового файла;\n\n$->: ";
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
			// Просмотр сохраненых файлов
		case 1:
			// Проверка на наличие сохраненных файлов
			if (filePath.getSize() == 0)
			{
				system("cls");
				cout << "\n|!| Сохраненных файлов не обнаружено!\n" << endl;
				break;
			}
			system("cls");
			pathChose = PathSelection(filePath) - 1;
			if (pathChose != 0)
			{
				path = filePath[pathChose];
			}
			system("cls");
			break;
			// Добавление нового файла
		case 2:
			system("cls");
			//heading("");
			cout << "\n\t\t\t\t\t   Добавление файла файла\n" << endl;
			cout << "|x| Введите путь:\n\n$->: ";
			cin >> path;
			filePath.append(path);
			system("cls");
			break;
		}
	} while (flagChose != 0);
	return path;
}


// Обработка файла с помощью стнадратного пути
void autoMode()
{
	string path = "D:\\example.txt";
	int flagChose;
	do {
		//heading("Работ");
		cout << "\n\t\t\t\t\t       Меню обработки файла\n" << endl;
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
void manualMode(List <string>& filePath)
{
	string path = "Выберите путь";
	int flagChose, flagActive = 0;
	do
	{
		//heading(path);
		cout << "\n\t\t\t\t\t       Меню выбора файла\n" << endl;
		cout << "|!| Путь к файлу - '" << path << "';" << endl;
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
			path = pathChange(filePath);
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
*/

