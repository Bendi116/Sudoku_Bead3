#include "mapgenerator.hpp"
#include <algorithm>
#include <random>
#include "iostream"
using namespace std;

mapGenerator::mapGenerator(std::vector<std::vector<int>> gBB):recurCounter(0),
    gridBoxBorders(gBB),
    checkCol(-1),checkRow(-1),
    beforeCol(-1),beforeRow(-1)
{
    generatedMap={
                {"","","","","","","","",""},
                {"","","","","","","","",""},
                {"","","","","","","","",""},
                {"","","","","","","","",""},
                {"","","","","","","","",""},
                {"","","","","","","","",""},
                {"","","","","","","","",""},
                {"","","","","","","","",""},
                {"","","","","","","","",""}
                };
    tempMap={
        {"","","","","","","","",""},
        {"","","","","","","","",""},
        {"","","","","","","","",""},
        {"","","","","","","","",""},
        {"","","","","","","","",""},
        {"","","","","","","","",""},
        {"","","","","","","","",""},
        {"","","","","","","","",""},
        {"","","","","","","","",""}
    };

}

void printGrid(std::vector<std::vector<std::string>>& generatedMap){
    string s = "";
    for (size_t row = 0; row < generatedMap.size(); ++row) {
        s="";
        for (size_t col = 0; col < generatedMap[row].size(); ++col) {
            if(generatedMap[row][col]==""){
                s+="_";
            }else{
                s+=generatedMap[row][col];
            }
        }
        cout<<s<<endl;
    }
}

void mapGenerator::generateMap(){

    shuffleVector();
    //creatMapWithShift();
    createMap();
    printGrid(generatedMap);
    createPuzzle();
    printGrid(generatedMap);

}
void mapGenerator::shuffleVector(){
    for (int i = 1; i < 10; ++i) {
        firstRow.push_back(to_string(i));
    }

    srand(time(0));
    int randInd = 0;
    string temp = "";
    for (int i = 0; i < firstRow.size(); ++i) {
        randInd = rand() % 9;
        temp = firstRow[i];
        firstRow[i]=firstRow[randInd];
        firstRow[randInd]=temp;
    }
}

void mapGenerator::createMap(){
    generatedMap[0]=firstRow;
    fillMap();
}

bool mapGenerator::fillMap(){
    if(!findBlankSquare(generatedMap)){
        return true;
    }
    for (int num = 1; num < 10; ++num) {
        if(check(generatedMap, to_string(num)))
        {
            generatedMap[checkRow][checkCol] = to_string(num);
            if(fillMap()){
                return true;
            }
            if(checkRow==0){
                checkRow-=1;
                checkCol=8;
            }else{
                checkCol-=1;
            }
            generatedMap[checkRow][checkCol] = "";
        }
    }
    return false;
}

void mapGenerator::createPuzzle(){
    int delNumCount = 50;
    string temp="";
    int max = 0;
    int row = 0;
    int col = 0;

    //generatedMap[rand() % 9][rand() % 9]="";

    while(delNumCount!=0&& max < 1000000){
        row  = rand() % 9;
        col  = rand() % 9;
        if(generatedMap[row][col]==""){
            while(generatedMap[row][col]==""){
                row  = rand() % 9;
                col  = rand() % 9;
            }
        }
        temp=generatedMap[row][col];
        generatedMap[row][col]="";

        copyVector();
        //tempMap(generatedMap.begin(), generatedMap.end(), back_inserter(tempMap));
        //tempMap=generatedMap;



        if(!bactrackingSolver(row,col,temp)){
            generatedMap[row][col]=temp;
            delNumCount++;
        }
        /*else if(tempMap[x][y]!=temp){
            generatedMap[x][y]=temp;
            tempMap[x][y]=temp;
            randNum++;
        }*/
        delNumCount--;
        max++;
        //cout<<randNum<<endl;
        //tempMap=generatedMap;

    }

}
void mapGenerator::copyVector(){
    for (int row = 0; row < generatedMap.size(); ++row) {
        for (int col = 0; col < generatedMap[row].size(); ++col) {
            tempMap[row][col]=generatedMap[row][col];
        }
    }
}

bool mapGenerator::bactrackingSolver(int row, int col, string checkNum){

    recurCounter++;
    if(!findBlankSquare(tempMap)){
        return true;
    }
    for (int num = 1; num < 10; ++num) {
        if(check(tempMap, to_string(num)))
        {
            /*
            if(checkRow == row && checkCol == col && to_string(num) != checkNum){
                return false;
            }
            */
            //cout<<"Deleted:"<<row<<"_"<<col<<"__"<<checkRow<<"__"<<checkCol<<endl;
            if(checkRow == row && checkCol == col && to_string(num) != checkNum){
                //cout<<"cont"<<endl;
                continue;
            }

            tempMap[checkRow][checkCol] = to_string(num);

            if(bactrackingSolver(row,col,checkNum)){
                return true;
            }
            /*
            if(checkCol>0 && checkRow>0){
                if(checkRow==0){
                    checkRow-=1;
                    checkCol=8;
                }else{
                    checkCol-=1;
                }

            }
            */
            //2 esett
            tempMap[checkRow][checkCol] = "";




        }
    }
    return false;
}

bool mapGenerator::findBlankSquare(std::vector<std::vector<std::string>> map){
    checkRow=-1;
    checkCol=-1;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(map[i][j]==""){
                checkRow=i;
                checkCol=j;
                return true;
            }
        }
    }
    return false;
}

bool mapGenerator::check(std::vector<std::vector<std::string>> map,string checkNum){
    for (int i = 0; i < 9; ++i) {
        if(map[i][checkCol]==checkNum && i!=checkRow){
            return false;
        }
    }
    for (int i = 0; i < 9; ++i) {
        if(map[checkRow][i]==checkNum && i!=checkCol){
            return false;
        }
    }
    for (vector<int> border: gridBoxBorders) {
        if(checkRow>=border[0]&&checkRow<=border[2]
            &&checkCol>=border[1]&&checkCol<=border[3]){
            for (int i  = border[0]; i  <=border[2] ; ++i ) {
                for (int j = border[1]; j <= border[3]; ++j) {
                    if(map[i][j]==checkNum && i != checkRow && j != checkCol){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

/*void sudokuApp::checkBox(int row, int col){
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
}*/


