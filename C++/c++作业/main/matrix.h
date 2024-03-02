class Matrix
{
public:
    Matrix(int, int);
    ~Matrix();

    friend Matrix operator*(Matrix &a, Matrix &b);
    friend Matrix operator+(Matrix &a, Matrix &b);
    friend Matrix operator-(Matrix &a, Matrix &b);
    friend Matrix operator/(Matrix &a, int &b);

    friend std::istream &operator>>(std::istream &in, Matrix &);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &);

private:
    int rows;
    int cols;
    int matrix[100][100];
};