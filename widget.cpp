#include "widget.hpp"
#include"application.hpp"

Widget::Widget(Application* _parent,int x, int y, int l , int h):xCoord(x), yCoord(y), length(l), height(h),parent(_parent) {
    parent->registerWidget(this);
      };
