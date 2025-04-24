#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <string>

class Menu {
public:
    virtual void drawMenu() const = 0;
    virtual ~Menu() = default;
};

#endif