#include <iostream>
#include "Grid.hpp"

int main()
{
    Grid<int> myIntGrid;
    Grid<double> myDoubleGrid(11, 11);

    std::cout << "ELO" << std::endl;
    myIntGrid.at(0, 0) = 10;

    int x = myIntGrid.at(0, 0).value_or(0);

    std::cout << x << std::endl;
    
    Grid<int> grid2(myIntGrid);
    Grid<int> anotherIntGrid;
    anotherIntGrid = grid2; 
    return 0;
}