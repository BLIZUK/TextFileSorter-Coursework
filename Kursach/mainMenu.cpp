#include "mainMenu.h"
#include <iostream>

void MenuStart::drawMenu() const
{
	std::cout << "\n                                              ==|����|==" << std::endl;
	std::cout << "\n   |File| == " << path << " ==" << std::endl;
	std::cout << "     |\n     |\n     |-|x| ��������:" << std::endl;
	std::cout << "        |\n        | 1 - ������ � ������;\n        | 2 - ����� �����;\n        | 0 - ���������� ������;\n        |\n\n$->: ";
}


void MenuStart::setPath(const std::string& newPath)
{
	path = newPath;
}