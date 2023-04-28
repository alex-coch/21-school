#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_H
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_H

#include <cmath>
#include <stdexcept>

#define EPS (1e-6)
namespace Q {
class S21Matrix {
 public:
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other) noexcept;
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix() noexcept;

  bool EqMatrix(const S21Matrix &other) const noexcept;  // [[nodiscard]]
  void SumMatrix(const S21Matrix &other) { Merge(other, 1); }
  void SubMatrix(const S21Matrix &other) { Merge(other, -1); }
  void MulNumber(double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  [[nodiscard]] S21Matrix Transpose() const noexcept;
  [[nodiscard]] S21Matrix CalcComplements() const;
  [[nodiscard]] double Determinant() const;
  [[nodiscard]] S21Matrix InverseMatrix() const;
  S21Matrix &operator=(const S21Matrix &other) noexcept;
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const double num) noexcept;
  S21Matrix operator*=(const S21Matrix &other);

  double &operator()(int i, int j);
  double operator()(int i, int j) const;

 private:
  int rows_ = 0, cols_ = 0;
  double **matrix_ = nullptr;
  void Delete();

  void Merge(const S21Matrix &other, int sign);
  [[nodiscard]] int GetRows() const noexcept { return rows_; }
  [[nodiscard]] int GetCols() const noexcept { return cols_; }
  void Remake(int rows, int cols, S21Matrix const *copy_matrix = nullptr);
  void SetRows(int rows) { Remake(rows, GetCols(), this); }
  void SetCols(int cols) { Remake(GetRows(), cols, this); };

  [[nodiscard]] S21Matrix Curve(int i, int j) const;
  [[nodiscard]] bool IsMatrixSquare() const noexcept {
    return GetRows() == GetCols();
  }
  [[nodiscard]] bool IsSameSize(const S21Matrix &other) const noexcept {
    return GetRows() == other.GetRows() && GetCols() == other.GetCols();
  }
};

S21Matrix operator+(const S21Matrix &a, const S21Matrix &b);
S21Matrix operator-(const S21Matrix &a, const S21Matrix &b);
S21Matrix operator*(const S21Matrix &a, double num) noexcept;
S21Matrix operator*(const double num, const S21Matrix &a) noexcept;
S21Matrix operator*(const S21Matrix &a, const S21Matrix &b);
bool operator==(const S21Matrix &a, const S21Matrix &b) noexcept;
}  // namespace Q
#endif  // CPP1_S21_MATRIXPLUS_S21_MATRIX_H
