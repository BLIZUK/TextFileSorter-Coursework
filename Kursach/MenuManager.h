#ifndef MENUMANAGER_H
#define MENUMANAGER_H


class Menu
{
/*
private:
	string path;
	size_t count;
*/

	//string path, size_t count
public:
	// Виртуальная функция, для отрисовки меню
	virtual void DrowMenu() const = 0;
	virtual ~Menu() = default;

};


class MainMenu : public Menu
{
private:
	string path;

public:
	void DrowMenu() const override
	{

	}
};



#endif // !MENUMANAGER_H
