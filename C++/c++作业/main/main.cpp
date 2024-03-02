#include <iostream>
#include "matrix.h"
Matrix::Matrix(int rows, int cols)
{
    Matrix::rows = rows;
    Matrix::cols = cols;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = 0;
}
Matrix::~Matrix() {}

Matrix operator*(Matrix &a, Matrix &b)
{
    if (a.cols != b.rows)
    {
        std::cout << "这两个矩阵无法相乘" << std::endl;
        Matrix temp(0, 0);
        return temp;
    }
    else
    {
        Matrix temp(a.rows, b.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < b.cols; j++)
            {
                for (int k = 0; k < b.rows; k++)
                    temp.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
        return temp;
    }
}
Matrix operator+(Matrix &a, Matrix &b)
{
    if (a.rows != b.rows || a.rows != b.rows)
    {
        std::cout << "这两个矩阵无法相加" << std::endl;
        Matrix temp(0, 0);
        return temp;
    }
    else
    {
        Matrix temp(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                temp.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
            }
        }
        return temp;
    }
}
Matrix operator-(Matrix &a, Matrix &b)
{
    if (a.rows != b.rows || a.rows != b.rows)
    {
        std::cout << "这两个矩阵无法相减" << std::endl;
        Matrix temp(0, 0);
        return temp;
    }
    else
    {
        Matrix temp(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                temp.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
            }
        }
        return temp;
    }
}
Matrix operator/(Matrix &a, int &b){
    
}
std::istream &operator>>(std::istream &in, Matrix &right)
{
    for (int i = 0; i < right.rows; i++)
    {
        for (int j = 0; j < right.cols; j++)
        {
            std::cin >> right.matrix[i][j];
        }
    }
    return in;
}
std::ostream &operator<<(std::ostream &os, const Matrix &right)
{
    for (int i = 0; i < right.rows; i++)
    {
        for (int j = 0; j < right.cols; j++)
            std::cout << right.matrix[i][j] << " ";
        std::cout << std::endl;
    }
    return os;
}
int main()
{
    int rows, cols;

    std::cin >> rows >> cols;
    Matrix A(rows, cols);
    std::cin >> A;
    std::cin >> rows >> cols;
    Matrix B(rows, cols);
    std::cin >> B;

    std::cout << "乘法"<<A * B;
    std::cout << "加法"<<A + B;
    return 0;
}