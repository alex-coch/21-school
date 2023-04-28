#include "s21_matrix_plus.h"

namespace Q {
/// @brief Addition and substraction
/// @param other a second operand
/// @param sign a feature of addition or substraction

void S21Matrix::Merge(const S21Matrix &other, int sign) {
  if (!IsSameSize(other))
    throw std::logic_error("Different dimension of matrices");

  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++) matrix_[y][x] += other(y, x) * sign;
}

/// @brief Multiply a matrix by a number
/// @param num A number
void S21Matrix::MulNumber(const double num) noexcept {
  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++) matrix_[y][x] *= num;
}

/// @brief Multiply matrixes
/// @param other a second matrix
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (GetCols() != other.GetRows())
    throw std::logic_error(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");

  S21Matrix tmpMatrix(GetRows(), other.GetCols());
  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < other.GetCols(); x++)
      for (int x_a = 0, y_b = 0; x_a < GetCols() && y_b < other.GetRows();
           x_a++, y_b++)
        tmpMatrix(y, x) += matrix_[y][x_a] * other(y_b, x);

  *this = std::move(tmpMatrix);
}

/// @brief Comparision of matrixes
/// @param other a comparing matrix
/// @return true if the matrixes are equal
bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  if (!IsSameSize(other)) return false;

  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++)
      if (fabs(matrix_[y][x] - other(y, x)) > EPS) return false;

  return true;
}

/// @brief Contructor
S21Matrix::S21Matrix() noexcept { Remake(0, 0); };  // = default;
S21Matrix::S21Matrix(int rows, int cols) { Remake(rows, cols); }
S21Matrix::S21Matrix(const S21Matrix &other) noexcept {
  Remake(other.GetRows(), other.GetCols(), &other);
}
S21Matrix::S21Matrix(S21Matrix &&other) noexcept { *this = std::move(other); }

/// @brief Destructior
void S21Matrix::Delete() {
  for (rows_--; rows_ >= 0; rows_--) delete[] matrix_[rows_];
  delete[] matrix_;

  // rows is already 0
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::~S21Matrix() noexcept { Delete(); }

/// @brief Creates a matrix with the dimension rows x cols
/// if copy_matrix given, the cell of the new matrix are fill out from the
/// former
/// @param rows a number of rows
/// @param cols a number of colums
/// @param copy_matrix a copying matrix
void S21Matrix::Remake(int rows, int cols, S21Matrix const *copy_matrix) {
  if (rows < 0 || cols < 0) {
    throw std::runtime_error("error");
  } else {
    double **new_matrix_ = nullptr;
    if (rows) {
      new_matrix_ = new double *[rows];

      for (int y = 0; y < rows; y++) {
        if (cols) {
          try {
            new_matrix_[y] = new double[cols];
          } catch (...) {
            delete[] new_matrix_;
            throw;
          }
          for (int x = 0; x < cols; x++) {
            if (copy_matrix && copy_matrix->GetRows() > y &&
                copy_matrix->GetCols() > x)
              new_matrix_[y][x] = (*copy_matrix)(y, x);
            else
              new_matrix_[y][x] = 0;
          }
        } else {
          new_matrix_[y] = nullptr;
        }
      }
    }

    Delete();

    rows_ = rows;
    cols_ = cols;
    matrix_ = new_matrix_;
  }
}

/// @brief Overload plus operator
/// @param a a first summand
/// @param b a second summand
/// @return sum
S21Matrix operator+(const S21Matrix &a, const S21Matrix &b) {
  S21Matrix tmp = a;
  tmp += b;
  return tmp;
}

/// @brief Overload minus operator
/// @param a a subtrahend
/// @param b a deducted
/// @return a remainder
S21Matrix operator-(const S21Matrix &a, const S21Matrix &b) {
  S21Matrix tmp = a;
  tmp -= b;
  return tmp;
}

/// @brief Overload operator of multiplication by number
/// @param a an input matrix
/// @param num a number
/// @return a resulting mitrix
S21Matrix operator*(const S21Matrix &a, const double num) noexcept {
  S21Matrix tmp = a;
  tmp.MulNumber(num);
  return tmp;
}

/// @brief Overload operator of multiplication of number by matrix
/// @param a an input matrix
/// @param num a number
/// @return a resulting mitrix
S21Matrix operator*(const double num, const S21Matrix &a) noexcept {
  return a * num;
}

/// @brief Overload operator of multiplication of matrixes
/// @param a a 1st matrix
/// @param num a 2nd matrix
/// @return a resulting mitrix
S21Matrix operator*(const S21Matrix &a, const S21Matrix &b) {
  S21Matrix tmp = a;
  tmp.MulMatrix(b);
  return tmp;
}

/// @brief Copy assignment operator
/// @param other a copied matrix
/// @return a new matrix
S21Matrix &S21Matrix::operator=(const S21Matrix &other) noexcept {
  if (this != &other) Remake(other.GetRows(), other.GetCols(), &other);
  return *this;
}

/// @brief Move assignment operator
/// @param other a moved matrix
/// @return a new matrix
S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    Delete();

    rows_ = other.GetRows();
    cols_ = other.GetCols();
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

// The row of overloading functions
S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  Merge(other, 1);
  return *this;
}
S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  Merge(other, -1);
  return *this;
}
S21Matrix S21Matrix::operator*=(double const num) noexcept {
  MulNumber(num);
  return *this;
}
S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

// Compare matrixes
bool operator==(const S21Matrix &a, const S21Matrix &b) noexcept {
  return a.EqMatrix(b);
}

// Assign to a cell[i][j] a new value
double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= GetRows() || j < 0 || j >= GetCols())
    throw std::out_of_range("Index outside the matrix");
  return matrix_[i][j];
}

// Retrieve a value from a cell[i][j]
double S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= GetRows() || j < 0 || j >= GetCols())
    throw std::out_of_range("Index outside the matrix");
  return matrix_[i][j];
}

/// @brief Calulate of a mitrix complement
/// @return a complement of a matrix
S21Matrix S21Matrix::CalcComplements() const {
  if (!IsMatrixSquare()) throw std::logic_error("The matrix is not square");

  S21Matrix newMatrix(GetRows(), GetCols());
  if (GetRows() == 1) {
    newMatrix(0, 0) = matrix_[0][0];
  } else {
    for (int y = 0; y < GetRows(); y++)
      for (int x = 0; x < GetCols(); x++)
        newMatrix(y, x) = Curve(y, x).Determinant() * ((y + x) % 2 ? -1 : 1);
  }

  return newMatrix;
}

/// @brief Cut i row and j column out in a matrix
/// @param i a new number of rows
/// @param j a new number of columns
/// @return a new matrix
S21Matrix S21Matrix::Curve(int i, int j) const {
  S21Matrix newMatrix(GetRows() - 1, GetCols() - 1);

  for (int y = 0, new_y = 0; (y < GetRows()); y++) {  // && (y < i)
    if (y == i) continue;
    for (int x = 0, new_x = 0; x < GetCols(); x++) {
      if (x == j) continue;
      newMatrix(new_y, new_x) = matrix_[y][x];
      new_x++;
    }
    new_y++;
  }

  return newMatrix;
}

/// @brief Evalute determinant of a matrix
/// @return a determinant
double S21Matrix::Determinant() const {
  if (!IsMatrixSquare()) throw std::logic_error("The matrix is not square");

  double result = 0;
  if (!GetRows())
    throw std::logic_error("The matrix is empty");
  else if (GetRows() == 1)
    result = matrix_[0][0];
  else if (GetRows() == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else
    for (int y = 0; y < GetRows(); y++)
      result += Curve(y, 0).Determinant() * matrix_[y][0] * ((y % 2) ? -1 : 1);

  return result;
}

/// @brief Invert a matrix
/// @return a interted matrix
S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();

  if (fabs(det) < EPS)
    throw std::logic_error("The determinant of the matrix is 0");

  if (GetRows() == 1) {
    S21Matrix newMatrix(GetRows(), GetCols());
    newMatrix(0, 0) = 1.0 / det;
    return newMatrix;
  } else {
    S21Matrix newMatrix = CalcComplements().Transpose();
    newMatrix.MulNumber(1.0 / det);
    return newMatrix;
  }
}

/// @brief Transponse a matrix
/// @return a transponded matrix
S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix newMatrix(GetCols(), GetRows());

  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++) newMatrix(x, y) = matrix_[y][x];

  return newMatrix;
}

}  // namespace Q