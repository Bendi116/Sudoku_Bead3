#include"sudokuapp.hpp"
#include"mapgenerator.hpp"

int main()
{
    sudokuApp app(800,600);
    mapGenerator mG;
    //app.run();
    mG.generateMap();

    return 0;
}
