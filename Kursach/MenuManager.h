#ifndef MENUMANAGER_H
#define MENUMANAGER_H


class Menu
{

private:
	string path;
	size_t count;

public:
	virtual int DrowMenu(string path, size_t count) const = 0;

};


class MainMenu : Menu
{
public:
	// Завернуть по требованию интерфейсов.
	//int DrowMenu;
};



#endif // !MENUMANAGER_H
