#include <vector>
#include <iostream>

template <typename T>
using matrix = std::vector< std::vector<T> >;

// Returns the element of input at (row, col), or padding if those indexes are
// out of range.
template <typename T>
T getVal(matrix<T>& input, T padding, int row, int col) {
    if (row >= 0 && row < input.size() && col >= 0 && col < input[row].size()) {
        return input[row][col];
    } else {
        return padding;
    }
}

// Applies the kernel to element at (row, col) in input, using padding as needed.
template<typename T>
T applyKernel(matrix<T>& input, matrix<T>& kernel, T padding, int row, int col) {
    T res{0};
    if (kernel.empty()) return res;

    int centerRow = kernel.size() / 2;
    int centerCol = kernel[0].size() / 2;

    for (int krow = 0; krow < kernel.size(); ++krow) {
        for (int kcol = 0; kcol < kernel[krow].size(); ++kcol) {
            int irow = row + (krow - centerRow);
            int icol = col + (kcol - centerCol);
            res += getVal(input, padding, irow, icol) * kernel[krow][kcol];
        }
    }
    return res;
}

// Computes and returns the convolution of the input matrix with the kernel
// matrix.
template <typename T>
matrix<T> convolution2D(matrix<T>& input, matrix<T>& kernel, T padding, std::pair<int, int> stride) {

    matrix<T> out;
    for (int row = 0; row < input.size(); row += stride.first) {
        int columns = input[row].size();
        out.push_back(std::vector<T>(columns));
        for (int col = 0; col < columns; col += stride.second) {
            out[row][col] = applyKernel(input, kernel, padding, row, col);
        }
    }
    return out;
}

template <typename T>
void printMatrix(matrix<T> mat) {
    for (int row = 0; row < mat.size(); ++row) {
        for (int col = 0; col < mat[row].size(); ++col) {
            std::cout << mat[row][col] << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    matrix<int> input {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    matrix<int> kernel {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1}};
    matrix<int> out = convolution2D(input, kernel, 0, {1, 1});
    printMatrix(out);
}