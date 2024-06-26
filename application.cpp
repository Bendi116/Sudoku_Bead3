#include "application.hpp"
#include "graphics.hpp"
#include"widget.hpp"

using namespace genv;

Application::Application(int a, int b):windowWidth(a),windowHeight(b){
   selected=0;
   caught=0;
   gamestate = NONE;
   appRun=true;

}

void Application::eventLoop(){
    gout.open(windowWidth,windowHeight);
    event ev;
    while(gin >> ev && appRun ) {
        if(ev.type ==ev_mouse){
            if ( ev.button==btn_left){
                for (size_t i = 0; i < widgetVector.size(); ++i) {
                    if(widgetVector[i]->isSelected(ev.pos_x,ev.pos_y)){
                        selected = widgetVector[i];
                        caught = widgetVector[i];
                    }
                }
            }
            else if (ev.button==-btn_left){
                caught=0;
            }

            else if(ev.button==0){
                if(caught){
                    caught->movePart(ev);
                }
            }
        }

        if(selected){
            selected->handleEvent(ev);
        }
        if(ev.type==ev_key && ev.keycode==key_escape){
            return;
        }
        action("check");
        clearGout();
        for(Widget* w:widgetVector){
            w->drawWidget();
        }
        gout<<refresh;
    }



}


void Application::clearGout(){
    gout<<color(100,100,100)<<move_to(0,0)<<box(windowWidth,windowHeight);
}


void Application::registerWidget(Widget* w){
    widgetVector.push_back(w);
}
