#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <string>

class Menu {

public:
    size_t choose;
    int check();
    virtual void drawMenu() const = 0;
    virtual ~Menu() = default;
};

#endif