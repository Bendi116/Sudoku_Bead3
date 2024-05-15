#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP
#include"vector"
#include"string"

class mapGenerator
{
private:
    std::vector<std::string> firstRow;
    std::vector<std::vector<std::string>> generatedMap ;
    std::vector<std::vector<std::string>> tempMap ;
    int checkRow,checkCol,recurCounter,beforeRow,beforeCol;
    std::vector<std::vector<int>> gridBoxBorders;
    void shuffleVector();
    void createMap();
    bool fillMap();
    void createPuzzle();
    bool bactrackingSolver(int, int,std::string);
    void copyVector();
    bool findBlankSquare(std::vector<std::vector<std::string>> map);
    bool check(std::vector<std::vector<std::string>>,std::string);
public:
    mapGenerator(std::vector<std::vector<int>>);
    void generateMap();
};

#endif // MAPGENERATOR_HPP
