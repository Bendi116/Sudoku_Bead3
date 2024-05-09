#include "sudokuapp.hpp"
#include "sudokucell.hpp"
#include "iostream"
#include"fstream"
#include "btnbox.hpp"
#include "menu.hpp"



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
    gridStartX = ((windowWidth - 9 *cellSize)/2)+100;
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
    //createGrid(gridMap);
    gamestate=MENU;
    updateWidgetsVector();
    eventLoop();
}

void sudokuApp::createGrid(std::vector<std::vector<std::string>> blueprint){
    for (size_t row = 0; row < blueprint.size(); ++row) {
        sudokuCell*cell;
        vector<sudokuCell*> temp;
        for (size_t col = 0; col < blueprint[row].size(); ++col) {
            if(blueprint[row][col]!=""){
                cell =new sudokuCell(this,gridStartX+col*cellSize,gridStartY+row*cellSize,cellSize,blueprint[row][col]);
            }else{
                cell =new sudokuCell(this,gridStartX+cellSize*col,gridStartY+cellSize*row,cellSize);
            }

            temp.push_back(cell);
        }
        cellVector.push_back(temp);
    }
};


void sudokuApp::action(string cmd){
    if(cmd=="check"&&gamestate==GAME){
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


void sudokuApp::updateWidgetsVector(){
    widgetVector={};
    cellVector={};
    if(gamestate==MENU){
        plaxBtn = new btnBox(this,200,225,300,50,"Play",[this](){gamestate=GAME;loadGameLevel();updateWidgetsVector();});
        playRandBtn = new btnBox(this,200,320,300,50,"Play Random",[this](){});
        exitBtn = new btnBox(this,200,415,300,50,"Exit Game",[this](){appRun=false;});
        levelMenu = new Menu(this,525,225,200,50,{"Easy","Medium","Hard"},3);
    }else if(gamestate==GAME){
        createGrid(gridMap);
        returnToMenu = new btnBox(this,25,400,150,50,"Return to menu",[this](){gamestate=MENU;updateWidgetsVector();});
        exitBtn = new btnBox(this,25,475,150,50,"Exit Game",[this](){appRun=false;});
    }
};

void sudokuApp::loadGameLevel(){
    gridMap={};
    ifstream file("levelData.txt");
    readFile(file);
    file.close();
};


void sudokuApp::readFile(ifstream &file){
    if(!file.good()){
        cout<<"file was wrong";
    }
    string line;
    while(file.good()){
        getline(file,line);
        if(levelMenu->getCurrentData()==line){
            fromFileMakeGridMap(file);
            break;
        }
    }
}
void sudokuApp::fromFileMakeGridMap(ifstream &file){
    string line;
    for (int row = 0; row < 9; ++row) {
        getline(file,line);
        vector<string> temp;
        for (int col = 0; col < line.size(); ++col) {
            if(line[col]=='_'){
                temp.push_back("");
            }else if(line[col]!=','){
                string s="";
                s.push_back(line[col]);
                temp.push_back(s);
            }
        }

        gridMap.push_back(temp);



    }

}

