//
// Created by Bennet on 29. Jan. 2018.
//

#ifndef LEARNINGCPP_SUDOKU_HPP
#define LEARNINGCPP_SUDOKU_HPP

#include <array>

template <int Size>
class Sudoku {
    private:
        using Grid_t = std::array<std::array<int,Size>,Size>;
        const bool checkRange(int x) const;
        Grid_t grid;
    public:
        static Sudoku<Size> generateRandom();

        const bool isSolved() const;
        const bool isCorrect() const;
        const bool erase(int x, int y);
        const bool tryInsert(int value, int x, int y);
        const int valueAt(int x, int y) const;
        Sudoku();
        Sudoku(Grid_t p_grid);

    const bool checkRange(int x, int y) const;
};



#include "../Sudoku.cpp"

#endif //LEARNINGCPP_SUDOKU_HPP
