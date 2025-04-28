#include "mainMenu.h"
#include <iostream>

void MenuStart::drawMenu() const
{
	std::cout << "\n                                              ==|Меню|==" << std::endl;
	std::cout << "\n   |File| == " << path << " ==" << std::endl;
	std::cout << "     |\n     |\n     |-|x| Действия:" << std::endl;
	std::cout << "        |\n        | 1 - Работа с файлом;\n        | 2 - Выбор файла;\n        | 0 - Завершение работы;\n        |\n\n$->: ";
}


void MenuStart::setPath(const std::string& newPath)
{
	path = newPath;
}