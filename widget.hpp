#ifndef WIDGET_HPP
#define WIDGET_HPP
#include"graphics.hpp"
#include "application.hpp"



class Widget
{
protected:
    int xCoord,yCoord,length,height;
    double buttonSize;
    Application * parent;
public:
    Widget(Application* parent,int x, int y, int l , int h);
    virtual ~Widget(){};
    virtual void  drawWidget()const=0;
    virtual void handleEvent(genv::event ev)=0;
    virtual bool isSelected(int posX,int posY) = 0;
    virtual void movePart(genv::event ev)=0;
    virtual std::string getCurrentData()const=0;
};

#endif // WIDGET_HPP
