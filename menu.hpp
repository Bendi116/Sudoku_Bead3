#ifndef MENU_HPP
#define MENU_HPP
#include "widget.hpp"
#include "vector"

class Menu:public Widget
{
protected:
    bool opened;
    std::vector<std::string> elementList;
    std::string currentElement;
    double offset,barButtonSize,openedSize,dy;
    int charSize;

public:
    Menu(Application* parent, int x, int y, int l, int h, std::vector<std::string>,int oS);
    ~Menu() override;
    void drawWidget()const override;
    void handleEvent(genv::event ev) override;
    bool isSelected(int posX,int posY)override;
    void movePart(genv::event ev) override;
    void swicthElement(int y);
    void increaseOffset();
    void decreaseOffset();
    void drawBasicMenuCanvas(genv::canvas& canvasOut)const;
    void mouseDist(int Mousey);
    std::string getCurrentData()const override;
    void updateMenu(std::vector<std::string>);
};

#endif // MENU_HPP
