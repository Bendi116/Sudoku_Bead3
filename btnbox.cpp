#include "btnbox.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

btnBox::btnBox(Application* p,int x, int y, int l, int h, std::string s, std::function<void()> oF):Widget(p,x,y,l,h), btnText(s), ownFunction(oF) {

}

void btnBox::drawWidget()const{
    gout.load_font("LiberationSans-Regular.ttf",20);
    gout<<color(255,255,255)<<move_to(xCoord,yCoord)<<box(length,height);
    gout<<color(0,0,0)<<move_to(xCoord+5,yCoord+height*0.3)<<text(btnText);
}

void btnBox::handleEvent(genv::event ev){
    if(ev.type==ev_mouse && ev.button ==btn_left){
        action();
    }
}

void btnBox::action(){
    ownFunction();
};

bool btnBox::isSelected(int x,int y){
    return x>xCoord&&x<xCoord+length&&y>yCoord&&y<yCoord+height;
}

void btnBox::movePart(genv::event ev){};

std::string btnBox::getCurrentData()const{
    return btnText;
}

btnBox::~btnBox(){};
