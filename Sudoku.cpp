//
// Created by Bennet on 29. Jan. 2018.
//
#ifndef LEARNINGCPP_SUDOKU_CPP
#define LEARNINGCPP_SUDOKU_CPP

#include "Sudoku.hpp"

template<int Size>
inline const bool Sudoku<Size>::checkRange(int x) const {
    return ((x >= 0 && x < grid.size()));
}

template<int Size>
inline const bool Sudoku<Size>::checkRange(int x, int y) const {
    return checkRange(x) && checkRange(y);
}


template<int Size>
Sudoku<Size> Sudoku<Size>::generateRandom() {
    return Sudoku<Size>();
}

template<int Size>
const bool Sudoku<Size>::isSolved() const {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (grid[i][j] <= 0) {
                return false;
            }
        }
    }
    return isCorrect();
}

template<int Size>
const int Sudoku<Size>::valueAt(const int x, const int y) const {
    if (!checkRange(x, y)) {
        return -1;
    }
    return grid[x][y];
}


template<int Size>
const bool Sudoku<Size>::tryInsert(const int value, const int x, const int y) {
    if (!(value > 0 && value <= grid.size()))

        if (!checkRange(x, y)) {
            return false;
        }

    if (valueAt(x, y) <= 0) {
        return false;
    }

    grid[x][y] = value;

}

template<int Size>
Sudoku<Size>::Sudoku() {

}

template<int Size>
Sudoku<Size>::Sudoku(Grid_t p_grid) : grid(p_grid) {

}

template<int Size>
const bool Sudoku<Size>::isCorrect() const {
    //TODO
    return 0;
}

template<int Size>
const bool Sudoku<Size>::erase(int x, int y) {
    if (!checkRange(x, y)) {
        return false;
    }
    grid[x][y] = -1;
    return true;
};

#endif //LEARNINGCPP_SUDOKU_CPP

