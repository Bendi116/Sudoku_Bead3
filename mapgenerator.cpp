#include "mapgenerator.hpp"
#include <algorithm>
#include <random>
#include"iostream"
using namespace std;

mapGenerator::mapGenerator() {
    for (int i = 1; i < 10; ++i) {
        firstRow.push_back(to_string(i));
    }
    generatedMap={};
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
    creatMapWithShift();
    printGrid(generatedMap);

}
void mapGenerator::shuffleVector(){
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

void mapGenerator::creatMapWithShift(){
    bool first = true;

    for (int i = 0; i < 3; ++i) {
        if(first){
            first=false;
            generatedMap.push_back(firstRow);
        }else{
            generatedMap.push_back(shift(1));

        }
        generatedMap.push_back(shift(3));
        generatedMap.push_back(shift(3));
    }
}
vector<string> mapGenerator::shift(int n){
    vector<string> temp;
    for (int i = 0; i < n; ++i) {
        string s = firstRow[firstRow.size()-1];
        firstRow.pop_back();
        temp.push_back(s);
    }
    reverse(temp.begin(),temp.end());
    for (int i = 0; i < firstRow.size(); ++i) {
        temp.push_back(firstRow[i]);
    }
    firstRow=temp;
    return firstRow;
};


