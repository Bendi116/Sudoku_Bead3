#include "sudokucell.hpp"
#include "graphics.hpp"
#include"iostream"

using namespace genv;
using namespace  std ;


sudokuCell::sudokuCell (Application* _parent,int x, int y, int l):Widget(_parent,x,y,l,l){
    hasSelected=false;
    unchangeable=false;
    currentNum="";
    margin = 2;
    wrong = false;

}

sudokuCell::sudokuCell (Application* _parent,int x, int y, int l,string cN):Widget(_parent,x,y,l,l),currentNum(cN){
    hasSelected=false;
    unchangeable=true;
    margin = 2;
    wrong = false;
}


void sudokuCell::drawWidget()const{
    gout.load_font("LiberationSans-Regular.ttf",20);
    gout  <<color(0,0,250)<< move_to(xCoord, yCoord)  << box(length, length);
    if(unchangeable){
        gout  <<color(110,110,110)<< move_to(xCoord+margin, yCoord+margin)  << box(length-margin*2, length-margin*2);
        gout << color(0,0,0)<<move_to(xCoord+0.4*length, yCoord+length*0.6)<<text(currentNum);
    }
    else if(wrong && hasSelected){
        gout  <<color(255,110,110)<< move_to(xCoord+margin, yCoord+margin)  << box(length-margin*2, length-margin*2);
        gout << color(255,255,255)<<move_to(xCoord+0.4*length, yCoord+length*0.6)<<text(currentNum);
    }
    else if(wrong){
        gout  <<color(230,140,140)<< move_to(xCoord+margin, yCoord+margin)  << box(length-margin*2, length-margin*2);
        gout << color(255,255,255)<<move_to(xCoord+0.4*length, yCoord+length*0.6)<<text(currentNum);
    }
    else if(hasSelected){
        gout  <<color(140,140,210)<< move_to(xCoord+margin, yCoord+margin)  << box(length-margin*2, length-margin*2);
        gout << color(255,255,255)<<move_to(xCoord+0.4*length, yCoord+length*0.6)<<text(currentNum);
    }else{
        gout  <<color(200,200,200)<< move_to(xCoord+margin, yCoord+margin)  << box(length-margin*2, length-margin*2);
        gout << color(0,0,0)<<move_to(xCoord+0.4*length, yCoord+length*0.6)<<text(currentNum);
    }

};
void sudokuCell::handleEvent(genv::event ev){
    if (ev.type == ev_key&&!unchangeable) {
        if (ev.keycode == key_backspace) {
            currentNum="";
            }
        else if (ev.keyutf8 != "" && (
                     ev.keyutf8=="0"||
                     ev.keyutf8=="1"||
                     ev.keyutf8=="2"||
                     ev.keyutf8=="3"||
                     ev.keyutf8=="4"||
                     ev.keyutf8=="5"||
                     ev.keyutf8=="6"||
                     ev.keyutf8=="7"||
                     ev.keyutf8=="8"||
                     ev.keyutf8=="9"))
        {
            currentNum=ev.keyutf8;
        }
        }

}



bool sudokuCell::isChangable(){
    return !unchangeable;
}

bool sudokuCell::isSelected(int posX,int posY){
    if(posX>xCoord&&posY>yCoord&&posX<xCoord+length&&posY<yCoord+height){
        hasSelected=true;
        return true;
    }
    hasSelected=false;
    return false;
};

void sudokuCell::movePart(genv::event ev){};


std::string sudokuCell::getCurrentData()const{
    return currentNum;
};

void sudokuCell::setWrongTrue(){
    wrong=true;
}

void sudokuCell::setWrongFalse(){
    wrong=false;
}




