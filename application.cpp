#include "application.hpp"
#include "graphics.hpp"
#include"widget.hpp"

using namespace genv;

Application::Application(int a, int b):windowWidth(a),windowHeight(b){
   selected=0;
   caught=0;
}

void Application::eventLoop(){
    gout.open(windowWidth,windowHeight);
    event ev;
    while(gin >> ev ) {
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
        else if(ev.type==ev_key&&ev.keycode==key_enter){
            action("enter");
        }
        if(selected){
            selected->handleEvent(ev);
        }
        if(ev.type==ev_key && ev.keycode==key_escape){
            return;
        }

        clearGout();
        for(Widget* w:widgetVector){
            w->drawWidget();
        }
        gout<<refresh;
    }


}


void Application::clearGout(){
    gout<<color(0,0,0)<<move_to(0,0)<<box(windowWidth,windowHeight);
}


void Application::registerWidget(Widget* w){
    widgetVector.push_back(w);
}
