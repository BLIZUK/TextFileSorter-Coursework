#ifndef MAINMENU_H
#define MAINMENU_H


#include "MenuManager.h"


class MenuStart : public Menu
{
private:
    std::string path;

public:
    // mainMenu() = default;  
    void drawMenu() const override;
    void setPath(const std::string& newPath);
    int check();
    // ~mainMenu() = default;

};

#endif