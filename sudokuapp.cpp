#include "sudokuapp.hpp"
#include "sudokucell.hpp"
#include "iostream"
#include "widget.hpp"


using namespace std;
using namespace genv;

sudokuApp::sudokuApp(int a,int b):Application(a,b) {
    gridMap={
               {"","","","7","","6","","5",""},
               {"","","4","","","","","",""},
               {"","","","","","","","",""},
               {"9","","","","5","","2","",""},
               {"7","","6","4","2","","1","",""},
               {"8","","1","","","","","",""},
               {"","","7","1","","8","6","","2"},
               {"","","","6","","","","","8"},
               {"","","","","","4","","9","7"}};
    cellSize=50;
    windowWidth=800;
    windowHeight=600;
    gridStartX = (windowWidth - 9 *cellSize)/2;
    gridStartY= (windowHeight - 9 *cellSize)/2;
    gridBoxBorders={{0,0,2,2},{0,3,2,5},{0,6,2,8},{3,0,5,2},{3,3,5,5},{3,6,5,8},{6,0,8,2},{6,3,8,5},{6,6,8,8}};
}


void sudokuApp::printGrid(){
    string s = "";
    for (size_t row = 0; row < cellVector.size(); ++row) {
        s="";
        for (size_t col = 0; col < cellVector[row].size(); ++col) {
            if(cellVector[row][col]->getCurrentData()==""){
                s+="_";
            }else{
                s+=cellVector[row][col]->getCurrentData();
            }
        }
        cout<<s<<endl;
    }

}

void sudokuApp::run(){
    gout.open(800,600);
    createGrid(gridMap);
    eventLoop();
}

void sudokuApp::createGrid(std::vector<std::vector<std::string>> blueprint){
    for (size_t row = 0; row < blueprint.size(); ++row) {
        sudokuCell*cell2;
        vector<sudokuCell*> temp;
        for (size_t col = 0; col < blueprint[row].size(); ++col) {
            Widget* cell;
            if(blueprint[row][col]!=""){
                cell = cell2 =new sudokuCell(this,gridStartX+col*cellSize,gridStartY+row*cellSize,cellSize,blueprint[row][col]);
            }else{
                cell = cell2 =new sudokuCell(this,gridStartX+cellSize*col,gridStartY+cellSize*row,cellSize);
            }
            widgetVector.push_back(cell);
            temp.push_back(cell2);
        }
        cellVector.push_back(temp);
    }
};


void sudokuApp::action(string cmd){
    if(cmd=="check"){
        checkGrid();
    }


};

void sudokuApp::checkGrid(){
    for (size_t row = 0; row < cellVector.size(); ++row) {
        for (size_t col = 0; col < cellVector[row].size(); ++col) {
            cellVector[row][col]->setWrongFalse();
            if(gridMap[row][col]!=cellVector[row][col]->getCurrentData()){
                checkRow(row,col);
                checkCol(row,col);
                checkBox(row,col);
            }

        }
    }
}

void sudokuApp::checkRow(int row, int col){
    for (size_t i = 0; i < gridMap.size(); ++i) {
        if(cellVector[row][col]->getCurrentData()==cellVector[row][i]->getCurrentData() && col != i){
            cellVector[row][col]->setWrongTrue();
        }
    }
}

void sudokuApp::checkCol(int row, int col){
    for (size_t i = 0; i < gridMap.size(); ++i) {
        if(cellVector[row][col]->getCurrentData()==cellVector[i][col]->getCurrentData() && row != i){
            cellVector[row][col]->setWrongTrue();
        }
    }
}
void sudokuApp::checkBox(int row, int col){
    for (vector<int> border : gridBoxBorders) {
        if(row>=border[0]&&row<=border[2]&&col>=border[1]&&col<=border[3]){
            for (int i = border[0]; i <= border[2]; ++i) {
                for (int j = border[1]; j <= border[3]; ++j) {
                    if(cellVector[row][col]->getCurrentData() == cellVector[i][j]->getCurrentData() && (row != i || col != j)){
                        cellVector[row][col]->setWrongTrue();
                    }
                }
            }
        }
    }
}


