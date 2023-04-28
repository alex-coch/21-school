#include "gtest/gtest.h"
#include "s21_matrix_plus.h"

namespace Q {
TEST(ComplementsTest, test1) {
  S21Matrix matrixA(3, 3);
  S21Matrix matrixB(3, 3);

  matrixA(0, 0) = 5;
  matrixA(0, 1) = -1;
  matrixA(0, 2) = 1;
  matrixA(1, 0) = 2;
  matrixA(1, 1) = 3;
  matrixA(1, 2) = 4;
  matrixA(2, 0) = 1;
  matrixA(2, 1) = 0;
  matrixA(2, 2) = 3;

  matrixB(0, 0) = 9;
  matrixB(0, 1) = -2;
  matrixB(0, 2) = -3;
  matrixB(1, 0) = 3;
  matrixB(1, 1) = 14;
  matrixB(1, 2) = -1;
  matrixB(2, 0) = -7;
  matrixB(2, 1) = -18;
  matrixB(2, 2) = 17;

  ASSERT_TRUE(matrixA.CalcComplements().EqMatrix(matrixB));
}

TEST(ComplementsTest, test2) {
  S21Matrix matrixA(1, 1);
  S21Matrix matrixB(1, 1);

  matrixA(0, 0) = 5;
  matrixB(0, 0) = 5;

  ASSERT_TRUE(matrixA.CalcComplements().EqMatrix(matrixB));
}

TEST(ComplementsTest, test3) {
  S21Matrix matrixA(0, 0);
  S21Matrix matrixB(0, 0);

  ASSERT_TRUE(matrixA.CalcComplements().EqMatrix(matrixB));
}

TEST(ErrorComplementsTest, test4) {
  S21Matrix matrix(2, 1);
  ASSERT_ANY_THROW((void)matrix.CalcComplements());
}

TEST(ComplementsTest, test5) {
  S21Matrix matrixA(2, 2);
  S21Matrix matrixB(2, 2);

  matrixA(0, 0) = 5;
  matrixA(0, 1) = -1;
  matrixA(1, 0) = 2;
  matrixA(1, 1) = 3;

  matrixB(0, 0) = 9;
  matrixB(0, 1) = -2;
  matrixB(1, 0) = 3;
  matrixB(1, 1) = 14;

  ASSERT_FALSE(matrixA.CalcComplements().EqMatrix(matrixB));
}

TEST(ConstructTest, test1) { ASSERT_ANY_THROW(S21Matrix a(-100, 10)); }
TEST(ConstructTest, test2) { ASSERT_ANY_THROW(S21Matrix a(100, -100)); }
TEST(ConstructTest, test3) { ASSERT_NO_THROW(S21Matrix a(1, 0)); }
TEST(ConstructTest, test4) { ASSERT_NO_THROW(S21Matrix a(0, 100)); }
TEST(ConstructTest, test5) { ASSERT_ANY_THROW(S21Matrix a(-10, -10)); }
TEST(ConstructTest, test6) { ASSERT_NO_THROW(S21Matrix a(0, 0)); }
TEST(ConstructTest, test7) { ASSERT_NO_THROW(S21Matrix a); }
TEST(ConstructTest, test8) { ASSERT_NO_THROW(S21Matrix a(1, 1)); }

TEST(DetTest, test1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5;

  ASSERT_TRUE(fabs(matrix.Determinant() - 5) < EPS);
}

TEST(DetTest, test2) {
  S21Matrix matrix(3, 3);

  matrix(0, 0) = 0.25;
  matrix(0, 1) = 1.25;
  matrix(0, 2) = 2.25;
  matrix(1, 0) = 3.25;
  matrix(1, 1) = 10;
  matrix(1, 2) = 5.25;
  matrix(2, 0) = 6.25;
  matrix(2, 1) = 7.25;
  matrix(2, 2) = 8.25;

  ASSERT_TRUE(fabs(matrix.Determinant() + 69) < EPS);
}

TEST(DetTest, test3) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1;
  matrix(0, 1) = 1;
  matrix(1, 0) = 2;
  matrix(1, 1) = 2;

  ASSERT_TRUE(fabs(matrix.Determinant()) < EPS);
}

TEST(ErrorDetTest, test1) {
  S21Matrix matrix(0, 0);

  ASSERT_ANY_THROW((void)matrix.Determinant());
}

TEST(ErrorDetTest, test2) {
  S21Matrix matrix(3, 2);

  ASSERT_ANY_THROW((void)matrix.Determinant());
}

class EqSimple : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);

  virtual void SetUp() {
    matrixA(0, 0) = 0.25;
    matrixA(0, 1) = 1.25;
    matrixA(0, 2) = 2.25;
    matrixA(1, 0) = 3.25;
    matrixA(1, 1) = 4.25;
    matrixA(1, 2) = 5.25;
    matrixA(2, 0) = 6.25;
    matrixA(2, 1) = 7.25;
    matrixA(2, 2) = 8.25;

    matrixB(0, 0) = 0.25;
    matrixB(0, 1) = 1.25;
    matrixB(0, 2) = 2.25;
    matrixB(1, 0) = 3.25;
    matrixB(1, 1) = 4.25;
    matrixB(1, 2) = 5.25;
    matrixB(2, 0) = 6.25;
    matrixB(2, 1) = 7.25;
    matrixB(2, 2) = 8.25;
  }
};

TEST_F(EqSimple, operator_eq) { ASSERT_TRUE(matrixA == matrixB); }

TEST_F(EqSimple, A_eq_B) { ASSERT_TRUE(matrixA.EqMatrix(matrixB)); }

TEST_F(EqSimple, B_eq_A) { ASSERT_TRUE(matrixB.EqMatrix(matrixA)); }

class EqSimple2 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(1, 3);
  S21Matrix matrixB = S21Matrix(3, 1);
};

TEST_F(EqSimple2, operator_eq2) { ASSERT_FALSE(matrixA == matrixB); }

TEST_F(EqSimple2, A_eq_B2) { ASSERT_FALSE(matrixA.EqMatrix(matrixB)); }

TEST_F(EqSimple2, B_eq_A2) { ASSERT_FALSE(matrixB.EqMatrix(matrixA)); }

class EqSimple3 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);

  virtual void SetUp() {
    matrixA(0, 0) = 0.26;  // < !!!
    matrixA(0, 1) = 1.25;
    matrixA(0, 2) = 2.25;
    matrixA(1, 0) = 3.25;
    matrixA(1, 1) = 4.25;
    matrixA(1, 2) = 5.25;
    matrixA(2, 0) = 6.25;
    matrixA(2, 1) = 7.25;
    matrixA(2, 2) = 8.25;

    matrixB(0, 0) = 0.25;  // < !!!
    matrixB(0, 1) = 1.25;
    matrixB(0, 2) = 2.25;
    matrixB(1, 0) = 3.25;
    matrixB(1, 1) = 4.25;
    matrixB(1, 2) = 5.25;
    matrixB(2, 0) = 6.25;
    matrixB(2, 1) = 7.25;
    matrixB(2, 2) = 8.25;
  }
};

TEST_F(EqSimple3, operator_eq2) { ASSERT_FALSE(matrixA == matrixB); }

TEST_F(EqSimple3, A_eq_B2) { ASSERT_FALSE(matrixA.EqMatrix(matrixB)); }

TEST_F(EqSimple3, B_eq_A2) { ASSERT_FALSE(matrixB.EqMatrix(matrixA)); }

class EqSimple4 : public ::testing::Test {
 protected:
  S21Matrix matrixA;
  S21Matrix matrixB = S21Matrix(0, 0);
};

TEST_F(EqSimple4, operator_eq) { ASSERT_TRUE(matrixA == matrixB); }

TEST_F(EqSimple4, A_eq_B) { ASSERT_TRUE(matrixA.EqMatrix(matrixB)); }

TEST_F(EqSimple4, B_eq_A) { ASSERT_TRUE(matrixB.EqMatrix(matrixA)); }

TEST(InverseTest, test1) {
  S21Matrix matrixA(1, 1);
  S21Matrix matrixB(1, 1);

  matrixA(0, 0) = 1.25;
  matrixB(0, 0) = 0.8;

  ASSERT_TRUE(matrixA.InverseMatrix().EqMatrix(matrixB));
}

TEST(InverseTest, test2) {
  S21Matrix matrixA(3, 3);
  S21Matrix matrixB(3, 3);

  matrixA(0, 0) = 2;
  matrixA(0, 1) = 5;
  matrixA(0, 2) = 7;
  matrixA(1, 0) = 6;
  matrixA(1, 1) = 3;
  matrixA(1, 2) = 4;
  matrixA(2, 0) = 5;
  matrixA(2, 1) = -2;
  matrixA(2, 2) = -3;

  matrixB(0, 0) = 1;
  matrixB(0, 1) = -1;
  matrixB(0, 2) = 1;
  matrixB(1, 0) = -38;
  matrixB(1, 1) = 41;
  matrixB(1, 2) = -34;
  matrixB(2, 0) = 27;
  matrixB(2, 1) = -29;
  matrixB(2, 2) = 24;

  ASSERT_TRUE(matrixA.InverseMatrix().EqMatrix(matrixB));
}
TEST(InverseTest, test3) {
  S21Matrix matrixA(1, 1);
  S21Matrix matrixB(1, 1);

  matrixA(0, 0) = 1.2;
  matrixB(0, 0) = 0.7;

  ASSERT_FALSE(matrixA.InverseMatrix().EqMatrix(matrixB));
}

TEST(ErrorInverseTest, test1) {
  S21Matrix matrixA(1, 3);

  ASSERT_ANY_THROW((void)matrixA.InverseMatrix());
}

TEST(ErrorInverseTest, test2) {
  S21Matrix matrixA(0, 0);
  S21Matrix matrixB(0, 0);

  ASSERT_ANY_THROW((void)matrixA.InverseMatrix());
}

TEST(ErrorInverseTest, test3) {
  S21Matrix matrixA(2, 2);
  ASSERT_ANY_THROW((void)matrixA.InverseMatrix());
}

class MulMatrix1x1 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(1, 1);
  S21Matrix matrixB = S21Matrix(1, 1);
  S21Matrix matrixC = S21Matrix(1, 1);

  void SetUp() override {
    matrixA(0, 0) = 1;
    matrixB(0, 0) = 10;
    matrixC(0, 0) = 10;
  }
};

TEST_F(MulMatrix1x1, test1) {
  ASSERT_TRUE((matrixA * matrixB).EqMatrix(matrixC));
}

TEST_F(MulMatrix1x1, test2) {
  ASSERT_TRUE((matrixA *= matrixB).EqMatrix(matrixC));
}

class ErrorMulMatrix : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(1, 2);
  S21Matrix matrixB = S21Matrix(1, 1);
};

TEST_F(ErrorMulMatrix, test1) { ASSERT_ANY_THROW(matrixA * matrixB); }

TEST_F(ErrorMulMatrix, test2) { ASSERT_ANY_THROW(matrixA *= matrixB); }

class MulMatrix2x3 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 2);
  S21Matrix matrixB = S21Matrix(2, 3);
  S21Matrix matrixC = S21Matrix(3, 3);

  void SetUp() override {
    matrixA(0, 0) = 0;
    matrixA(0, 1) = 1;
    matrixA(1, 0) = 3;
    matrixA(1, 1) = 4;
    matrixA(2, 0) = 6;
    matrixA(2, 1) = 7;

    matrixB(0, 0) = 9;
    matrixB(0, 1) = 8;
    matrixB(0, 2) = 7;
    matrixB(1, 0) = 6;
    matrixB(1, 1) = 5;
    matrixB(1, 2) = 4;

    matrixC(0, 0) = 6;
    matrixC(0, 1) = 5;
    matrixC(0, 2) = 4;
    matrixC(1, 0) = 51;
    matrixC(1, 1) = 44;
    matrixC(1, 2) = 37;
    matrixC(2, 0) = 96;
    matrixC(2, 1) = 83;
    matrixC(2, 2) = 70;
  }
};

TEST_F(MulMatrix2x3, test1) {
  ASSERT_TRUE((matrixA * matrixB).EqMatrix(matrixC));
}

TEST_F(MulMatrix2x3, test2) {
  ASSERT_TRUE((matrixA *= matrixB).EqMatrix(matrixC));
}

class MulMatrix3x3 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);
  S21Matrix matrixC = S21Matrix(3, 3);

  void SetUp() override {
    matrixA(0, 0) = 1;
    matrixA(0, 1) = 2;
    matrixA(0, 2) = 3;
    matrixA(1, 0) = 4;
    matrixA(1, 1) = 5;
    matrixA(1, 2) = 6;
    matrixA(2, 0) = 7;
    matrixA(2, 1) = 8;
    matrixA(2, 2) = 9;

    matrixB(0, 0) = 9;
    matrixB(0, 1) = 8;
    matrixB(0, 2) = 7;
    matrixB(1, 0) = 6;
    matrixB(1, 1) = 5;
    matrixB(1, 2) = 4;
    matrixB(2, 0) = 3;
    matrixB(2, 1) = 2;
    matrixB(2, 2) = 1;

    matrixC(0, 0) = 30;
    matrixC(0, 1) = 24;
    matrixC(0, 2) = 18;
    matrixC(1, 0) = 84;
    matrixC(1, 1) = 69;
    matrixC(1, 2) = 54;
    matrixC(2, 0) = 138;
    matrixC(2, 1) = 114;
    matrixC(2, 2) = 90;
  }
};

TEST_F(MulMatrix3x3, test1) {
  ASSERT_TRUE((matrixA * matrixB).EqMatrix(matrixC));
}

TEST_F(MulMatrix3x3, test2) {
  ASSERT_TRUE((matrixA *= matrixB).EqMatrix(matrixC));
}

class MulMatrix2x2 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(2, 2);
  S21Matrix matrixB = S21Matrix(2, 2);
  S21Matrix matrixC = S21Matrix(2, 2);

  void SetUp() override {
    matrixA(0, 0) = 1;
    matrixA(0, 1) = 2;
    matrixA(1, 0) = 4;
    matrixA(1, 1) = 5;

    matrixB(0, 0) = 9;
    matrixB(0, 1) = 8;
    matrixB(1, 0) = 6;
    matrixB(1, 1) = 5;

    matrixC(0, 0) = 30;
    matrixC(0, 1) = 24;
    matrixC(1, 0) = 84;
    matrixC(1, 1) = 69;
  }
};

TEST_F(MulMatrix2x2, test1) {
  ASSERT_FALSE((matrixA * matrixB).EqMatrix(matrixC));
}

TEST_F(MulMatrix2x2, test2) {
  ASSERT_FALSE((matrixA *= matrixB).EqMatrix(matrixC));
}

class MulNumber : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);

  virtual void SetUp() {
    matrixA(0, 0) = 0.25;
    matrixA(0, 1) = 0.25;
    matrixA(0, 2) = 0.25;
    matrixA(1, 0) = 0.25;
    matrixA(1, 1) = 0.25;
    matrixA(1, 2) = 0.25;
    matrixA(2, 0) = 0.25;
    matrixA(2, 1) = 0.25;
    matrixA(2, 2) = 0.25;

    matrixB(0, 0) = 1.0;
    matrixB(0, 1) = 1.0;
    matrixB(0, 2) = 1.0;
    matrixB(1, 0) = 1.0;
    matrixB(1, 1) = 1.0;
    matrixB(1, 2) = 1.0;
    matrixB(2, 0) = 1.0;
    matrixB(2, 1) = 1.0;
    matrixB(2, 2) = 1.0;
  }
};

TEST_F(MulNumber, test1) {
  matrixA.MulNumber(4);
  ASSERT_TRUE(matrixA.EqMatrix(matrixB));
}

TEST_F(MulNumber, test2) {
  matrixA *= 4;
  ASSERT_TRUE(matrixA.EqMatrix(matrixB));
}

TEST_F(MulNumber, test3) {
  matrixA = matrixA * 4;
  ASSERT_TRUE(matrixA.EqMatrix(matrixB));
}

TEST_F(MulNumber, test4) {
  matrixA = 4 * matrixA;
  ASSERT_TRUE(matrixA.EqMatrix(matrixB));
}

TEST_F(MulNumber, test5) {
  matrixA = 3 * matrixA;
  ASSERT_FALSE(matrixA.EqMatrix(matrixB));
}

TEST(ErrorAny, test1) {
  S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(0, 1));
}

TEST(ErrorAny, test2) {
  S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(-1, -1));
}

TEST(ErrorAny, test3) {
  S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(1, 1));
}

TEST(ErrorAny, test4) {
  const S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(0, 1));
}

TEST(ErrorAny, test5) {
  const S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(-1, -1));
}

TEST(ErrorAny, test6) {
  const S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(1, 1));
}

TEST(Any, test1) {
  S21Matrix matrixA(2, 2);
  matrixA(0, 0) = 1;
  matrixA(0, 1) = 2;
  matrixA(1, 0) = 3;
  matrixA(1, 1) = 4;
  S21Matrix matrixB(0, 0);

  S21Matrix matrixC = matrixA;

  matrixB = matrixA;

  ASSERT_TRUE(matrixC.EqMatrix(matrixB));
  matrixB(0, 0) = 11;
  ASSERT_TRUE(matrixA.EqMatrix(matrixC));
  ASSERT_FALSE(matrixB.EqMatrix(matrixC));
}

class SubMatrix1 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);
  S21Matrix matrixC = S21Matrix(3, 3);

  void SetUp() override {
    matrixA(0, 0) = 0;
    matrixA(0, 1) = 0;
    matrixA(0, 2) = 0;
    matrixA(1, 0) = 0;
    matrixA(1, 1) = 0;
    matrixA(1, 2) = 0;
    matrixA(2, 0) = 0;
    matrixA(2, 1) = 0;
    matrixA(2, 2) = 0;

    matrixB(0, 0) = 1;
    matrixB(0, 1) = 1;
    matrixB(0, 2) = 1;
    matrixB(1, 0) = 1;
    matrixB(1, 1) = 1;
    matrixB(1, 2) = 1;
    matrixB(2, 0) = 1;
    matrixB(2, 1) = 1;
    matrixB(2, 2) = 1;

    matrixC(0, 0) = -1;
    matrixC(0, 1) = -1;
    matrixC(0, 2) = -1;
    matrixC(1, 0) = -1;
    matrixC(1, 1) = -1;
    matrixC(1, 2) = -1;
    matrixC(2, 0) = -1;
    matrixC(2, 1) = -1;
    matrixC(2, 2) = -1;
  }
};

TEST_F(SubMatrix1, test1) {
  matrixA -= matrixB;
  ASSERT_TRUE(matrixA.EqMatrix(matrixC));
}

TEST_F(SubMatrix1, test2) {
  ASSERT_TRUE((matrixA - matrixB).EqMatrix(matrixC));
}

TEST_F(SubMatrix1, test3) {
  ASSERT_FALSE((matrixA - matrixB).EqMatrix(2 * matrixC));
}

TEST(SubErrorTest, test1) {
  S21Matrix matrixA = S21Matrix(2, 3);
  S21Matrix matrixB = S21Matrix(3, 3);
  ASSERT_ANY_THROW(matrixA - matrixB);
}

class SumMatrix1 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);
  S21Matrix matrixC = S21Matrix(3, 3);

  void SetUp() override {
    matrixA(0, 0) = 0;
    matrixA(0, 1) = 0;
    matrixA(0, 2) = 0;
    matrixA(1, 0) = 0;
    matrixA(1, 1) = 0;
    matrixA(1, 2) = 0;
    matrixA(2, 0) = 0;
    matrixA(2, 1) = 0;
    matrixA(2, 2) = 0;

    matrixB(0, 0) = 1;
    matrixB(0, 1) = 1;
    matrixB(0, 2) = 1;
    matrixB(1, 0) = 1;
    matrixB(1, 1) = 1;
    matrixB(1, 2) = 1;
    matrixB(2, 0) = 1;
    matrixB(2, 1) = 1;
    matrixB(2, 2) = 1;

    matrixC(0, 0) = 1;
    matrixC(0, 1) = 1;
    matrixC(0, 2) = 1;
    matrixC(1, 0) = 1;
    matrixC(1, 1) = 1;
    matrixC(1, 2) = 1;
    matrixC(2, 0) = 1;
    matrixC(2, 1) = 1;
    matrixC(2, 2) = 1;
  }
};

TEST_F(SumMatrix1, test1) {
  matrixA += matrixB;
  ASSERT_TRUE(matrixA.EqMatrix(matrixC));
}

TEST_F(SumMatrix1, test2) {
  ASSERT_TRUE((matrixA + matrixB).EqMatrix(matrixC));
}

TEST_F(SumMatrix1, test3) {
  ASSERT_FALSE((matrixA + matrixB).EqMatrix(2 * matrixC));
}

TEST(SumErrorTest, test1) {
  S21Matrix matrixA = S21Matrix(2, 3);
  S21Matrix matrixB = S21Matrix(3, 3);
  ASSERT_ANY_THROW(matrixA + matrixB);
}

TEST(TransposeTest, test1) {
  S21Matrix matrixA(0, 0);
  S21Matrix matrixB(0, 0);

  ASSERT_TRUE(matrixA.Transpose().EqMatrix(matrixB));
}

TEST(TransposeTest, test2) {
  S21Matrix matrixA(1, 1);
  S21Matrix matrixB(1, 1);

  matrixA(0, 0) = 10;
  matrixB(0, 0) = 10;

  ASSERT_TRUE(matrixA.Transpose().EqMatrix(matrixB));
}

TEST(TransposeTest, test3) {
  S21Matrix matrixA(1, 3);
  S21Matrix matrixB(3, 1);

  matrixA(0, 0) = 1;
  matrixA(0, 1) = 2;
  matrixA(0, 2) = 3;

  matrixB(0, 0) = 1;
  matrixB(1, 0) = 2;
  matrixB(2, 0) = 3;

  ASSERT_TRUE(matrixA.Transpose().EqMatrix(matrixB));
}

TEST(TransposeTest, test4) {
  S21Matrix matrixA(3, 3);
  S21Matrix matrixB(3, 3);

  matrixA(0, 0) = 0.25;
  matrixA(0, 1) = 1.25;
  matrixA(0, 2) = 2.25;
  matrixA(1, 0) = 3.25;
  matrixA(1, 1) = 4.25;
  matrixA(1, 2) = 5.25;
  matrixA(2, 0) = 6.25;
  matrixA(2, 1) = 7.25;
  matrixA(2, 2) = 8.25;

  matrixB(0, 0) = 0.25;
  matrixB(1, 0) = 1.25;
  matrixB(2, 0) = 2.25;
  matrixB(0, 1) = 3.25;
  matrixB(1, 1) = 4.25;
  matrixB(2, 1) = 5.25;
  matrixB(0, 2) = 6.25;
  matrixB(1, 2) = 7.25;
  matrixB(2, 2) = 8.25;

  ASSERT_TRUE(matrixA.Transpose().EqMatrix(matrixB));
}

TEST(TransposeTest, test5) {
  S21Matrix matrixA(2, 2);
  S21Matrix matrixB(2, 2);

  matrixA(0, 0) = -0.25;
  matrixA(0, 1) = 1.25;
  matrixA(1, 0) = 3.25;
  matrixA(1, 1) = 4.25;

  matrixB(0, 0) = 0.25;
  matrixB(1, 0) = 1.25;
  matrixB(0, 1) = 3.25;
  matrixB(1, 1) = 4.25;

  ASSERT_FALSE(matrixA.Transpose().EqMatrix(matrixB));
}

}  // namespace Q