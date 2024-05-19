#ifndef SUDOKUCELL_HPP
#define SUDOKUCELL_HPP
#include "widget.hpp"

class sudokuCell:public Widget
{

protected:
    bool hasSelected,unchangeable,wrong;
    std::string currentNum;
    int margin,gridPosCol,gridPosRow;


public:
    sudokuCell(Application *_parent,int x, int y, int l);
    sudokuCell(Application *_parent,int x, int y, int l,std::string cN);
    void drawWidget() const override;
    void handleEvent(genv::event ev) override;
    bool isSelected(int posX,int posY) override;
    void movePart(genv::event ev) override;
    std::string getCurrentData()const override;
    bool isChangable();
    void setWrongTrue();
    void setWrongFalse();


};

#endif // SUDOKUCELL_HPP
