#include <iostream> 
#include <cstring>
#include "MenuManager.h"

// �������� �������
#undef max



int Menu::check()
{
	if (!(std::cin >> choose))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		choose = -1;
		system("cls");
		std::cout << "\n>>|!| �� ����� ������������ ��������!\n" << std::endl;
		return 0;
	}
}