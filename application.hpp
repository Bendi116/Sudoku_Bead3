#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "graphics.hpp"

#include"vector"
class Widget;


class Application
{
public:
    Application(int a, int b);
    void eventLoop();
    void clearGout() ;
    void registerWidget(Widget* w);
    virtual void action(std::string)=0;

protected:
    std::vector<Widget*> widgetVector;
    Widget * selected;
    Widget * caught;
    int windowWidth,windowHeight;
};


#endif // APP_HPP


