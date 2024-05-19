#include "mapgenerator.hpp"
#include "iostream"

using namespace std;

mapGenerator::mapGenerator(std::vector<std::vector<int>> gBB):
    checkRow(-1), checkCol(-1),
    beforeRow(-1),beforeCol(-1),gridBoxBorders(gBB)
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
    //debughoz kellet
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

std::vector<std::vector<std::string>> mapGenerator::generateMap(){

    initGeneratedMap();
    shuffleVector();
    createMap();
    createPuzzle();
    return generatedMap;

}
void mapGenerator::shuffleVector(){
    firstRow = {};
    for (int i = 1; i < 10; ++i) {
        firstRow.push_back(to_string(i));
    }

    srand(time(0));
    int randInd = 0;
    string temp = "";
    for (size_t i = 0; i < firstRow.size(); ++i) {
        randInd = rand() % 9;
        temp = firstRow[i];
        firstRow[i]=firstRow[randInd];
        firstRow[randInd]=temp;
    }
}

void mapGenerator::initGeneratedMap(){
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
}

void mapGenerator::createMap(){
    generatedMap[0]=firstRow;
    fillMap();
}

bool mapGenerator::fillMap(){
    int row = -1;
    int col = -1;
    if(!findBlankSquare(generatedMap)){
        return true;
    }
    row = checkRow;
    col = checkCol;
    for (int num = 1; num < 10; ++num) {
        if(check(generatedMap, to_string(num),row,col))
        {
            generatedMap[row][col] = to_string(num);
            if(fillMap()){
                return true;
            }

            generatedMap[row][col] = "";

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

    while(delNumCount!=0&& max < 10000000){
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

        if(!bactrackingSolver(row,col,temp)){
            generatedMap[row][col]=temp;
            delNumCount++;
        }

        delNumCount--;
        max++;
    }

}
void mapGenerator::copyVector(){
    for (size_t row = 0; row < generatedMap.size(); ++row) {
        for (size_t col = 0; col < generatedMap[row].size(); ++col) {
            tempMap[row][col]=generatedMap[row][col];
        }
    }
}
bool mapGenerator::bactrackingSolver(int _row, int _col, string checkNum){
    int row = -1;
    int col = -1;
    if(!findBlankSquare(tempMap)){
        return true;
    }
    row = checkRow;
    col = checkCol;
    for (int num = 1; num < 10; ++num) {
        if(check(tempMap, to_string(num),row,col))
        {

            if(row == _row && col == _col && to_string(num) != checkNum){
                return false;
            }


            tempMap[row][col] = to_string(num);

            if(bactrackingSolver(_row,_col,checkNum)){
                return true;
            }
            tempMap[row][col] = "";




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

bool mapGenerator::check(std::vector<std::vector<std::string>> map,string checkNum,int row,int col){
    for (int i = 0; i < 9; ++i) {
        if(map[i][col]==checkNum && i!=row){
            return false;
        }
    }
    for (int i = 0; i < 9; ++i) {
        if(map[row][i]==checkNum && i!=col){
            return false;
        }
    }
    for (vector<int> border: gridBoxBorders) {
        if(row>=border[0]&&row<=border[2]
            &&col>=border[1]&&col<=border[3]){
            for (int i  = border[0]; i  <=border[2] ; ++i ) {
                for (int j = border[1]; j <= border[3]; ++j) {
                    if(map[i][j]==checkNum && i != row && j != col){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
