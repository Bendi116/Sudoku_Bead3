#include"sudokuapp.hpp"

int main()
{
    sudokuApp app(800,600);
    app.run();
    //mapGenerator mapGen({{0,0,2,2},{0,3,2,5},{0,6,2,8},{3,0,5,2},{3,3,5,5},{3,6,5,8},{6,0,8,2},{6,3,8,5},{6,6,8,8}});
    //mapGen.generateMap();

    return 0;
}
