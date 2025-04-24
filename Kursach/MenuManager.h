#ifndef MENUMANAGER_H
#define MENUMANAGER_H


class Menu
{

private:
	string path;
	size_t count;

public:
	// ����������� �������, ��� ��������� ����
	virtual void DrowMenu(string path, size_t count) const = 0;
	virtual void ~Menu() = default;

};


class MainMenu : public Menu
{
public:
	void DrowMenu() const override
	{

	}
};



#endif // !MENUMANAGER_H
