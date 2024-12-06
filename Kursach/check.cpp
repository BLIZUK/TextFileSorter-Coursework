/*
����������� ����

� �������� ��������� ���� �� ���������� � ������� foundSymb ���� ������� ������������� ������
������� ��������� ���������� �������� - 47.
�� ���� ���������� �������� �� �������. �� ���� �� ������ ������� ��������. �� � � ����� �� ����� ����� �������� �� ���� ����������.
� ������ �� ��� ����������� 0. ������� ����� ��� �� �������� � ������� ������������������ �������. 
� �������� �������� ��������� �������������� - ����� ������� � ������ ������� �����������, 
� ������� EAX ���������� �������� ����� ������� � ��������� ASCII. � ����� ����������� � ���� �������� ���� �����.
�� �������� � ASCII ������� 46. ��� ��� ��� ������, �� ���� ��������� ������� � �������� eax. ����� ��������� �������� �� eax � ��� ���������� � �������.
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


// ������� ��� ��������
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
		mov esi, text_C // ��������� �� ������ ������
		mov ecx, lenTxt // ����� ������

// |---------------------------------------------------------------------------------------> ERROR
		// mov eax, count // ������� (count)
// |---------------------------------------------------------------------------------------> ERROR
				
				next_char :

			cmp ecx, 0 // �������� �� ����� ������
			je exit_end // ���� �����, ������� �� �����

			mov al, [esi] // ��������� ������� ������
			inc esi // ��������� � ���������� �������
			dec ecx // ��������� �������

			push ecx // ��������� ����� ���������� ������
			mov ecx, lenPM // ������������� ����� ������� ����������
			lea ebx, punctuationMarks // ��������� �� ������ ����������

				check_punctuation :

			cmp ecx, 0 // ���������, �������� �� ������� ��� ��������
			je pop_ecx // ���� ���, ������� �� ��������

			cmp al, [ebx] // ���������� � ������� �������� ����������
			je count_add // ���� ���������, ����������� �������
			inc ebx // ��������� � ���������� ������� ����������
			dec ecx // ��������� ������� ��� ������� ����������
			jmp check_punctuation // ��������� ��� ���� �������� ����������

				pop_ecx :

			pop ecx // ��������������� �������
			jmp next_char // ������� � ���������� �������

				count_add :
// |---------------------------------------------------------------------------------------> ERROR
			// inc eax 
// |---------------------------------------------------------------------------------------> ERROR

			inc count // ����������� ������� ����������
			pop ecx // ��������������� �������
			jmp next_char // ������� � ���������� �������

				exit_end :
// |---------------------------------------------------------------------------------------> ERROR
			//mov count, eax // ��������� ��������� � ���������� count
// |---------------------------------------------------------------------------------------> ERROR
			
	}

	return count; // ���������� ���������� ��������� �������� ����������
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


// ����� ����� ����� ��� ��������
int t_main()
{
	int returnValue;
	// ����� ������
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
// ��������