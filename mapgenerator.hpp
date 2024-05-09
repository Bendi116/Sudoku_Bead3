#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP
#include"vector"
#include"string"

class mapGenerator
{
private:
    std::vector<std::string> firstRow;
    std::vector<std::vector<std::string>> generatedMap ;
public:
    mapGenerator();
    void generateMap();
    void shuffleVector();
    void creatMapWithShift();
    std::vector<std::string> shift(int n);
};

#endif // MAPGENERATOR_HPP
