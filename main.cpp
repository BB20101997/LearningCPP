#include <iostream>
#include "Sudoku.hpp"



int main() try {

    Sudoku<4> game{2,2};
    game.generateRandom();
    std::cout << "Playing a Game of " << game.size() << "x" << game.size() << "-Sudoku" << std::endl;
    const Sudoku<4> orig{game};

    size_t x,y,v;

    while (!game.isSolved()) {
        printSudoku(orig, game);
        std::cout<<"Where do you want to fill in(1-"<<orig.size()<<"): ";
        std::cin >> x >> y;
        std::cout << "What do you want to fill in: ";
        std::cin >> v;
        if(v==-1){
            break;
        }
        if(!game.tryInsert(v,x-1,y-1)){
          std::cout << "Invalid move\n";
        }
    }

    return 0;

}
catch (std::exception &error) {
    //this code is reacheable if an exception is thrown
	std::cerr << "Unbehandelter Fehler: " << error.what()<<'\n';
}