//
// Created by Bennet on 29. Jan. 2018.
//
#ifndef LEARNING_CPP_SUDOKU_CPP
#define LEARNING_CPP_SUDOKU_CPP

#include "Sudoku.hpp"
#include <sstream>
#include <algorithm>

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

template<size_t Size>
bool Sudoku<Size>::seeded = false;

template<size_t Size>
std::mt19937 Sudoku<Size>::rng; // NOLINT

template<size_t Size>
void Sudoku<Size>::generateRandom() {
    size_t x, y, value;
    if (!Sudoku<Size>::seeded) {
        rng.seed(std::random_device()());
        Sudoku<Size>::seeded = true;
    }

    std::uniform_int_distribution<size_t> coord_dist{0, Size - 1};
    std::uniform_int_distribution<size_t> value_dist;

    int count = 0;
    while (count <= Size * Size / 3) {
        x = coord_dist(rng);
        y = coord_dist(rng);
        std::vector<size_t> validVector = validValues(x, y);
        if (validVector.empty()) { continue; }
        value_dist = std::uniform_int_distribution<size_t>{0, validVector.size() - 1};
        size_t index = value_dist(rng);
        value = validVector.at(index);
        if (tryInsert(value, x, y,false)) {
            if(isSolveable()){
                count++;
            }else{
                erase(x,y);
            }
        }
    }
};

template<size_t Size>
std::vector<size_t> Sudoku<Size>::validValues(size_t x, size_t y) const {
    std::vector<size_t> validVals;
    for (int i = 1; i < Size; i++) {
        validVals.push_back(i);
    }
    validVals.push_back(Size);

    for (size_t i = 0; i < Size && !validVals.empty(); i++) {
        if (valueAt(x, i) != 0) {
			std::remove(validVals.begin(), validVals.end(), valueAt(x, i));

        }
        if (valueAt(i, y) != 0) {
			std::remove(validVals.begin(), validVals.end(), valueAt(i, y));
        }
        auto inner_x = x % height() * width() + y % width();
        auto inner_y = x / height() * height() + y / width();
        if (valueAt(inner_x,inner_y)!=0) {
            std::remove(validVals.begin(),validVals.end(),valueAt(inner_x,inner_y));
        }
    }
    return validVals;
};

template<size_t Size>
const bool Sudoku<Size>::solve() {
    std::cout<<"Solve\n";
    printSudoku(*this,*this);
    if (isSolved()) { return true; }
    else if (!isCorrect()) { return false; }

    size_t x = 0;
    size_t y = 0;

	std::uniform_int_distribution<size_t> coord_dist{ 0, Size - 1 };

	while (true) {
		x = coord_dist(rng);
		y = coord_dist(rng);
		if (valueAt(x, y) == 0) {//find first empty field
			break;
		}
	}
    
    
    std::vector<size_t> valid = validValues(x, y);
    size_t value;
    while (!valid.empty()) {
        std::uniform_int_distribution<size_t> index_dist{0,valid.size()-1};
        auto index = index_dist(rng);
        value = valid.at(index);
        valid.erase(valid.begin()+index);
        grid[x][y] = value;
        if (isCorrect()) {
            if (solve()) {
                return true;
            }
        }
        erase(x, y);
    }
    return isSolved();
}

template<size_t Size>
const bool Sudoku<Size>::isSolved() const {
    for (size_t i = 0; i < Size; i++) {
        for (size_t j = 0; j < Size; j++) {
            if (grid[i][j] <= 0) {
                return false;
            }
        }
    }
    return isCorrect();
};

template<size_t Size>
const bool Sudoku<Size>::tryInsert(const size_t value, const size_t x, const size_t y, const bool trySolveablility) {
    if (!(value > 0 && value <= Size)) {
        return false; //value out of range
    }

    if (!checkRange(x, y)) {
        return false; //coordinates out of range
    }

    if (valueAt(x, y) > 0) {
        return false; //field already set
    }

    grid[x][y] = value;
    if (!isCorrect() || (trySolveablility&&!isSolveable())) {
        grid[x][y] = 0; //reset since it is not a valid move
        return false;
    }
    return true;
};


template<size_t Size>
const bool Sudoku<Size>::isSolveable() const {
    return isSolved()||Sudoku<Size>{*this}.solve();
}

template<size_t Size>
const bool Sudoku<Size>::isCorrect() const {
    std::array<bool, Size> flagRow, flagColumn, flagGrid;
    size_t inner_x, inner_y;
    for (size_t x = 0; x < Size; x++) {
        flagRow.fill(false);
        flagColumn.fill(false);
        flagGrid.fill(false);
        for (size_t y = 0; y < Size; y++) {
            if (grid[y][x] != 0) {//check collumn y at position x
                if (flagColumn[grid[y][x]-1]) {
                    return false;
                }
                flagColumn[grid[y][x]-1] = true;
            }
            if (grid[x][y] != 0) {//check row x at position y
                if (flagRow[grid[x][y]-1]) {
                    return false;
                }
                flagRow[grid[x][y]-1] = true;
            }
            inner_x = x % height() * width() + y % width();
            inner_y = x / height() * height() + y / width();
            if (grid[inner_x][inner_y] != 0) {//check inner square at pos y
                if (flagGrid[grid[inner_x][inner_y]-1]) {
                    return false;
                }
                flagGrid[grid[inner_x][inner_y]-1] = true;
            }
        }
    }
    return true;
}

template<size_t Size>
Sudoku<Size>::Sudoku(size_t width, size_t height):inside_height(height), inside_width(width) {
    std::cout << "Creating Sudoku" << std::endl;

    if (height * width != Size) {
        std::stringstream error_msg;
        error_msg << "Inner grid of unexpected size " << height * width << " expected " << Size << "!\n";
        throw std::runtime_error(error_msg.str());
    }

    for (size_t x = 0; x < Size; x++) {
        for (size_t y = 0; y < Size; y++) {
            erase(x, y);
        }
    }
};

template<size_t Size>
Sudoku<Size>::Sudoku(Grid_t p_grid, const size_t width, const size_t height) : grid(p_grid), inside_width(width),
                                                                               inside_height(height) {

};

template<size_t Size>
Sudoku<Size>::Sudoku(const Sudoku<Size> &sudoku)
        :grid(), inside_width(sudoku.inside_width), inside_height(sudoku.inside_height) {
    std::cout << "Copy\n";
    for (size_t x = 0; x < Size; x++) {
        for (size_t y = 0; y < Size; y++) {
            grid[x][y] = sudoku.grid[x][y];
        }
    }
};

template<size_t Size>
inline const bool Sudoku<Size>::checkRange(const size_t x) const {
    return ((x >= 0 && x < grid.size()));
};

template<size_t Size>
inline const bool Sudoku<Size>::checkRange(size_t x, size_t y) const {
    return checkRange(x) && checkRange(y);
};

template<size_t Size>
const size_t Sudoku<Size>::valueAt(const size_t x, const size_t y) const {
    if (!checkRange(x, y)) {
        throw std::runtime_error{"IndexOutOfBounds"};
    }
    return grid[x][y];
};

template<size_t Size>
const bool Sudoku<Size>::erase(size_t x, size_t y) {
    if (!checkRange(x, y)) {
        return false;
    }
    grid[x][y] = 0;
    return true;
};

template<size_t Size>
const size_t Sudoku<Size>::size() const {
    return Size;
};

template<size_t Size>
const size_t Sudoku<Size>::height() const {
    return inside_height;
};

template<size_t Size>
const size_t Sudoku<Size>::width() const {
    return inside_width;
};


#endif //LEARNING_CPP_SUDOKU_CPP

