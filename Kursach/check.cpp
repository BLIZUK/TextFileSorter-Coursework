/*
Проверочный файл

В процессе написания кода на ассемблере в функции foundSymb была найдена повторяющаяся ошибка
Функция постоянно возвращала значение - 47.
На глаз определить проблему не удалось. ИИ тоже не смогли выявить проблему. Да и в целом ИИ очень плохо отвечает по теме ассемблера.
И пользы от нее практичекси 0. Поэтому выбор пал на дебагинг с помощью дизассемблирования функции. 
В процессе проверки выявилась закономерность - после прохода к новому символу предложения, 
В регистр EAX заносилось значение этого символа в кодировки ASCII. В конце предложения в моих примерах была точка.
Ее значение в ASCII формате 46. Так как это символ, то цикл добавляет единицу к регистру eax. Затем переносит значение из eax в мою переменную и выходит.
*/



#include <iostream> 
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <limits>
#include <set>
#include <cstring>
#include "List.h"


using namespace std;


// Функция для проверки
int foundSymb_disassembling(const string& text)
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

	//int lenTxt = text.length();
	int lenPM = sizeof(punctuationMarks) / sizeof(punctuationMarks[0]);
	const char* text_C = text.c_str();
	int lenTxt = strlen(text_C);

	__asm
	{
		mov esi, text_C // Указатель на начало строки
		mov ecx, lenTxt // Длина строки

// |---------------------------------------------------------------------------------------> ERROR
		// mov eax, count // Счетчик (count)
// |---------------------------------------------------------------------------------------> ERROR
				
				next_char :

			cmp ecx, 0 // Проверка на конец строки
			je exit_end // Если конец, выходим из цикла

			mov al, [esi] // Загружаем текущий символ
			inc esi // Переходим к следующему символу
			dec ecx // Уменьшаем счетчик

			push ecx // Сохраняем длину оставшейся строки
			mov ecx, lenPM // Устанавливаем длину массива пунктуации
			lea ebx, punctuationMarks // Указатель на массив пунктуации

				check_punctuation :

			cmp ecx, 0 // Проверяем, остались ли символы для проверки
			je pop_ecx // Если нет, выходим из проверки

			cmp al, [ebx] // Сравниваем с текущим символом пунктуации
			je count_add // Если совпадает, увеличиваем счетчик
			inc ebx // Переходим к следующему символу пунктуации
			dec ecx // Уменьшаем счетчик для массива пунктуации
			jmp check_punctuation // Повторяем для всех символов пунктуации

				pop_ecx :

			pop ecx // Восстанавливаем счетчик
			jmp next_char // Переход к следующему символу

				count_add :
// |---------------------------------------------------------------------------------------> ERROR
			// inc eax 
// |---------------------------------------------------------------------------------------> ERROR

			inc count // Увеличиваем счетчик совпадений
			pop ecx // Восстанавливаем счетчик
			jmp next_char // Переход к следующему символу

				exit_end :
// |---------------------------------------------------------------------------------------> ERROR
			//mov count, eax // Переносим результат в переменную count
// |---------------------------------------------------------------------------------------> ERROR
			
	}

	return count; // Возвращаем количество найденных символов пунктуации
}


void classCheckString()
{
	List <string> Temp;
	Temp.append("GAV");
	Temp.append("VAG");
	Temp.append("AU");
	Temp.append("EAX");
	Temp.append("RCX");
	cout << "\n\n|--> |!| OUTPUT before: " << endl;
	Temp.print();
	Temp[1] = "mya";
	Temp[3] = "wau";
	cout << "\n\n|--> |!| OUTPUT after: " << endl;
	Temp.print();
}


void classCheckInt()
{
	List <int> Temp;
	int i = 0;
	while (i < 5)
	{
		Temp.append(i);
		i++;
	}
	cout << "\n\n|--> |!| OUTPUT before: " << endl;
	Temp.print();
	Temp[1] = 10;
	Temp[3] = 29;
	cout << "\n\n|--> |!| OUTPUT after: " << endl;
	Temp.print();
	Temp.~List();
}


// Точка входа файла для проверки
int t_main()
{
	int returnValue;
	// Текст пример
	string text = "G 1 _ .";
	returnValue = foundSymb_disassembling(text);
	cout << "\t\t~~ DEBUG MOD ~~" << endl;
	cout << "\n\n|--> |!| OUTPUT: " << returnValue << endl << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	classCheckInt();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;;
	classCheckString();
	return 0;
}
// Проверка