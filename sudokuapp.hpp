#ifndef SUDOKUAPP_HPP
#define SUDOKUAPP_HPP

#include"application.hpp"
#include "vector"
#include "sudokucell.hpp"

class sudokuApp:public Application
{
protected:
    std::vector<std::vector<std::string>> gridMap;
    int cellSize,gridStartX,gridStartY,windowWidth,windowHeight;
    std::vector<std::vector<sudokuCell*>> cellVector;
    std::vector<std::vector<int>> gridBoxBorders;
public:
    sudokuApp(int a, int b);
    void action(std::string) override;
    void run();
    void createGrid(std::vector<std::vector<std::string>> blueprint);
    void checkGrid();
    void checkRow(int row, int col);
    void checkCol(int row, int col);
    void checkBox(int row, int col);
    void printGrid();
};

#endif // SUDOKUAPP_HPP