#include <iostream>
#include "Sudoku.hpp"

template<size_t Size>
void printSudoku(const Sudoku<Size> &orig, const Sudoku<Size> &current) {

    for (size_t x = 0; x < orig.size(); x++) {
        if(x%orig.height()==0){
            for (size_t i = 0; i < orig.size()  + orig.size() / orig.width() +1; i++) {
                std::cout << '_';
            }
            std::cout << std::endl;
        }
        std::cout << '|';
        for (size_t y = 0; y < orig.size(); y++) {
            if (orig.valueAt(x, y) == current.valueAt(x, y)) {
                if (orig.valueAt(x, y) <= 0) {
                    std::cout << '-' ;
                } else {
                    std::cout << orig.valueAt(x, y);
                }
            } else {
                std::cout << current.valueAt(x, y);
            }
            if ((y + 1) % orig.width() == 0) {
                std::cout << '|';
            }
        }
        std::cout << std::endl;
    }
    for (size_t i = 0; i < orig.size()  + orig.size() / orig.width() +1; i++) {
        std::cout << '_';
    }
    std::cout << std::endl;
};

int main() try {

    Sudoku<9> game{3,3};
    game.generateRandom();
    std::cout << "Playing a Game of " << game.size() << "x" << game.size() << "-Sudoku" << std::endl;
    const Sudoku<9> orig{game};

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