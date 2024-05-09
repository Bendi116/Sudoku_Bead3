#ifndef BTNBOX_HPP
#define BTNBOX_HPP
#include "widget.hpp"
#include"functional"

class btnBox:public Widget
{
public:
    btnBox(Application* parent, int x, int y, int l , int h, std::string s, std::function<void()> oF );
    ~ btnBox() ;
    void drawWidget()const override;

    void handleEvent(genv::event ev) override;
    bool isSelected(int posX,int posY) override;
    void movePart(genv::event ev) override;
    std::string getCurrentData()const override;
    void action();
protected:
    std::string btnText;
    std::function<void()> ownFunction;
};

#endif // BTNBOX_HPP
