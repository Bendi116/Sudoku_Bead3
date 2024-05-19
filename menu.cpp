#include "menu.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

Menu::Menu(Application* p,int x, int y, int l, int h, std::vector<std::string> el, int oS):Widget(p,x,y,l,h),elementList(el),openedSize(oS) {
    if(elementList.size()!=0){
    dy = 0.0;
    buttonSize = length*0.2;
    offset = 0.0;
    currentElement=elementList[0];
    opened=false;
    barButtonSize = (openedSize/elementList.size())*openedSize*height;
    charSize=height * 0.35;
    }else{
    dy = 0.0;
    buttonSize = length*0.2;
    offset = 0.0;
    currentElement="";
    opened=false;
    barButtonSize = 0;
    }

};
void Menu::drawBasicMenuCanvas(canvas& canvasOut)const{
    //draw canvas for menu list elements
    for (size_t i = 0; i < elementList.size(); ++i) {
        if(elementList[i]==currentElement){
            canvasOut<<color(200,200,150)<<move_to(0,i*height)<<box(length,height);
            canvasOut<<color(255,255,255)<<move_to(10,height*0.4+i*height)<<text(elementList[i]);
        }else{
            canvasOut<<color(20,200,150)<<move_to(0,i*height)<<box(length,height);
            canvasOut<<color(255,255,255)<<move_to(10,height*0.4+i*height)<<text(elementList[i]);
        }
    }
}
void Menu::drawWidget()const{
    canvas elementCanvas(length,height*elementList.size());
    elementCanvas.load_font("LiberationSans-Regular.ttf",charSize);
    gout.load_font("LiberationSans-Regular.ttf",charSize);
    drawBasicMenuCanvas(elementCanvas);
    if(!opened){
        gout<<color(60,200,150)<<move_to(xCoord,yCoord)<<box(length-buttonSize,height)<<move_to(xCoord+length-buttonSize,yCoord)<<color(200,200,200)<<box(buttonSize,height);
        gout<<color(0,0,0)<<move_to(xCoord+length-buttonSize,yCoord)<<line_to(xCoord+length-buttonSize/2,yCoord+height/2)<<line_to(xCoord+length,yCoord);
    }else{
        gout<<color(60,200,150)<<move_to(xCoord,yCoord)<<box(length-buttonSize,height)<<move_to(xCoord+length-buttonSize,yCoord)<<color(200,200,200)<<box(buttonSize,height);
        gout<<color(0,0,0)<<move_to(xCoord+length-buttonSize,yCoord+height)<<line_to(xCoord+length-buttonSize/2,yCoord+height/2)<<line_to(xCoord+length,yCoord+height);
        if(elementList.size()!=0){
        if(elementList.size()>=openedSize){
        gout << stamp(elementCanvas, 0, offset, length,openedSize*height, xCoord, yCoord+height);
        //side bar
        gout<<color(100,100,100)<<move_to(xCoord+length-buttonSize/2,yCoord+height)<<box(buttonSize/2,height*openedSize);
        //side bar button
        gout<<color(200,200,200)<<move_to(xCoord+length-buttonSize/2,yCoord+height+offset*openedSize/elementList.size())<<box(buttonSize/2,barButtonSize);
        }else{
            gout << stamp(elementCanvas, 0, offset, length,elementList.size()*height, xCoord, yCoord+height);
            //side bar
            gout<<color(100,100,100)<<move_to(xCoord+length-buttonSize/2,yCoord+height)<<box(buttonSize/2,height*elementList.size());
            //side bar button
            gout<<color(200,200,200)<<move_to(xCoord+length-buttonSize/2,yCoord+height)<<box(buttonSize/2,height*elementList.size());
        }}
    }
    canvas c(length-buttonSize,height);
    c.transparent(true);
    c.load_font("LiberationSans-Regular.ttf",charSize);
    c.set_antialias(false);
    c<<color(255,255,255)<<move_to(10,height*0.4)<<text(currentElement);
    gout<<stamp(c,xCoord,yCoord);
};

void Menu::handleEvent(genv::event ev){
    bool insideButton = ev.pos_x>xCoord+length-buttonSize&&ev.pos_x<xCoord+length&&ev.pos_y>yCoord&&ev.pos_y<yCoord+height;
    bool insideSlection = ev.pos_x>xCoord&&ev.pos_x<xCoord+length-buttonSize/2&&ev.pos_y>yCoord+height&&ev.pos_y<yCoord+(openedSize+1)*height;
    if(ev.type == ev_mouse && ev.button==btn_left){
        if(insideButton&&elementList.size()!=0){
            opened=!opened;
        }else if(ev.pos_x>=xCoord+length-buttonSize/2
                   && ev.pos_x<=xCoord+length
                   &&ev.pos_y>=yCoord+height+offset*openedSize/elementList.size()
                   &&ev.pos_y<=yCoord+height+offset*openedSize/elementList.size()+barButtonSize
                    ){
            movePart(ev);
        }
        else if(insideSlection){
            swicthElement(ev.pos_y);
            opened=false;
            offset=0;
        }
    }else if(ev.type == ev_mouse && ev.button==btn_wheelup&&insideSlection && elementList.size()>=openedSize){
        decreaseOffset();
    }else if(ev.type == ev_mouse && ev.button==btn_wheeldown&&insideSlection && elementList.size()>=openedSize){
        increaseOffset();
    }

};

bool Menu::isSelected(int posX,int posY){
    //if button pressed
    if(posX>xCoord+length-buttonSize&&posX<xCoord+length&&posY>yCoord&&posY<yCoord+height){
        return true;
    }
    //if bar pressed
    else if(posX>=xCoord+length-buttonSize/2
             && posX<=xCoord+length
             &&posY>=yCoord+height+offset*openedSize/elementList.size()
             &&posY<=yCoord+height+offset*openedSize/elementList.size()+barButtonSize){
        mouseDist(posY);
        return true;
    }
    else{
        opened=false;
        return false;
    }
};


void Menu::mouseDist(int Mousey){
    dy = Mousey-yCoord-height-(offset*openedSize/elementList.size());
}

void Menu::movePart(genv::event ev){
    if(ev.pos_x>=xCoord+length-buttonSize/2
        && ev.pos_x<=xCoord+length
        &&ev.pos_y>=yCoord+height+offset*openedSize/elementList.size()
        &&ev.pos_y<=yCoord+height+offset*openedSize/elementList.size()+barButtonSize
        && elementList.size()>=openedSize)
    {
        offset = (-dy+ev.pos_y-yCoord-height)*(elementList.size()/openedSize);
        if(offset<0) offset=0;
        else if(offset>(elementList.size()-openedSize)*height)offset=(elementList.size()-openedSize)*height;
    }

}

void Menu::swicthElement(int y){
    int dy = y +offset - yCoord;

    dy /= height;

    currentElement=elementList[dy-1];
}

void Menu::decreaseOffset(){
    offset-=3;
    if(offset<0)offset=0;
}

void Menu::increaseOffset(){
    offset+=3;
    if(offset>(elementList.size()-openedSize)*height){
        offset=(elementList.size()-openedSize)*height;
    }
}
std::string Menu::getCurrentData()const{
    return currentElement;
};

Menu::~Menu(){};

void Menu::updateMenu(vector<string> list){

    if(list.size()==0){
        currentElement="";
        barButtonSize = 0;
        elementList={};
    }else{
        //ha nincs benne első elem
        bool currentElemenetInVector = false;
        for (string s : list) {
            if(currentElement == s){
                currentElemenetInVector=true;
                break;
            }else{
                currentElemenetInVector=false;
            }
        }
        if(!currentElemenetInVector){
            currentElement=list[0];
        }


        elementList = list;
        barButtonSize = (openedSize/elementList.size())*openedSize*height;
    }
}
