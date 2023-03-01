#pragma once

#include <limits>
#include <iomanip>
#include "Complex.h"

/*!
 \brief Пространство имён с шаблонным классом матрицы

 \details Пространство имён с шаблонным классом матрицы и методами вывода матриц в файлы
*/
namespace linalg {
    /*!
        \brief Шаблонный класс матрицы

        \details В этом классе есть методы для работы с матрицами
    */

    template<class T = double>
    class Matrix {
        T *m_ptr;
        unsigned m_rows;
        unsigned m_cols;
    public:
        /*!
            \brief Конструктор по умолчанию
            @param r, c
        */
        Matrix(int r = 0, int c = 1) {
            m_rows = r;
            m_cols = c;

            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] = 0;
                }
            }
        }

        /*!
            \brief Конструктор копирования
            @param other
        */
        Matrix(const Matrix<T> &other) : m_rows(other.m_rows), m_cols(other.m_cols) {
            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] = other.m_ptr[i * m_cols + j];
                }
            }
        }

        /*!
         \brief Конструктор перемещения (std::move(m),  r-value ссылка)
         @param other
         */
        Matrix(Matrix<T> &&other) noexcept: m_rows(other.m_rows), m_cols(other.m_cols),
                                            m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
            other.m_rows = other.m_cols = 0;
        }

        /*!
         \brief Конструктор конструктор для ситуаций m = {1, 2, 3, 4, 5, 6}
         @param lst
         */
        Matrix(const std::initializer_list<T> &lst) {  //
            m_rows = lst.size();
            m_cols = 1;

            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                m_ptr[i * m_cols + 0] = *(lst.begin() + i);
            }
        }

        /*!
            \brief Конструктор для ситуаций m = {{1}, {2}, {3}, {4}, {5}, {6}}; m = {{1, 2, 3}, {4, 5, 6}}
            @param lst
         */
        Matrix(const std::initializer_list<std::initializer_list<T>> &lst) {  //
            m_rows = lst.size();                                               //
            m_cols = lst.begin()->size();                                      //

            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] = *((lst.begin() + i)->begin() + j);
                }
            }
        }

        ~Matrix() {
            delete[] m_ptr;
        }


        unsigned rows() { return m_rows; }

        unsigned rows() const { return m_rows; }

        unsigned cols() { return m_cols; }

        unsigned cols() const { return m_cols; }


        /*!
            \brief Перегрузка оператора копирующего присваивания
            @param rhs
         */
        Matrix<T> &operator=(const Matrix<T> &rhs) {
            if (this == &rhs) {
                return *this;
            }

            delete[] m_ptr;
            m_rows = rhs.m_rows;
            m_cols = rhs.m_cols;

            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] = rhs.m_ptr[i * rhs.m_cols + j];
                }
            }
            return *this;
        }

        /*!
            \brief Перегрузка оператора перемещающего присваивания
            @param rhs
         */
        Matrix<T> &operator=(Matrix<T> &&rhs) noexcept {
            if (this == &rhs) {
                return *this;
            }

            delete[] m_ptr;

            m_rows = rhs.m_rows;
            m_cols = rhs.m_cols;

            m_ptr = rhs.m_ptr;

            rhs.m_ptr = nullptr;
            rhs.m_rows = rhs.m_cols = 0;

            return *this;
        }


        /*!
            \brief Доступ к элементам через круглые скобки (вызов функции)
            @param i, j
         */
        T &operator()(int i, int j) {  //
            if (i >= m_rows || j >= m_cols) {
                throw std::logic_error("index out of range\n");
            }
            return m_ptr[i * m_cols + j];
        } // int a =  m(1, 1);
        // m(1, 1) = 4;

        const T &operator()(int i,
                            int j) const { // доступ к элементам для константной матрицы через круглые скобки (вызов функции)
            if (i >= m_rows || j >= m_cols) {
                throw std::logic_error("index out of range\n");
            }
            return m_ptr[i * m_cols + j];
        } // m(1, 1) = 4;

        // арифметические операции
        Matrix<T> operator+=(const Matrix<T> &rhs) {
            if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
                throw std::logic_error("matrix dimensions are not matching\n");
            }

            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_rows + j] += rhs.m_ptr[i * rhs.m_rows + j];
                }
            }

            return *this;
        }

        friend Matrix<T> operator+(Matrix<T> lhs, const Matrix<T> &rhs) {
            lhs += rhs;
            return lhs;
        }

        Matrix<T> operator-=(const Matrix<T> &rhs) {
            if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
                throw std::logic_error("matrix dimensions are not matching\n");
            }

            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_rows + j] -= rhs.m_ptr[i * rhs.m_rows + j];
                }
            }

            return *this;
        }

        friend Matrix<T> operator-(Matrix<T> lhs, const Matrix<T> &rhs) {
            lhs -= rhs;
            return lhs;
        }

        friend Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs) {
            if (lhs.m_cols != rhs.m_rows) {
                throw std::logic_error("matrix dimensions are not matching\n");
            }

            Matrix<T> tmp(lhs.m_rows, rhs.m_cols);
            for (int i = 0; i < lhs.m_rows; ++i) {
                for (int j = 0; j < rhs.m_cols; ++j) {
                    for (int k = 0; k < lhs.m_cols; ++k) {
                        tmp(i, j) += lhs(i, k) * rhs(k, j);
                    }
                }
            }

            return tmp;
        }

        Matrix<T> &operator*=(T k) {
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] *= k;
                }
            }

            return *this;
        }

        friend Matrix<T> operator*(T k, Matrix<T> rhs) {
            rhs *= k;
            return rhs;
        }

        friend Matrix<T> operator*(Matrix<T> lhs, T k) {
            lhs *= k;
            return lhs;
        }

        // взаимодействие с потоком вывода и оператором <<
        friend std::ostream &operator<<(std::ostream &out, const Matrix<T> &m) {
            for (int i = 0; i < m.m_rows; ++i) {
                out << '|';
                for (int j = 0; j < m.m_cols; ++j) {
                    out << std::scientific << std::setprecision(4) << " " << std::right << std::setw(7) << m(i, j);
                    if (j != m.m_cols - 1) {
                        out << " ";
                    }
                }
                out << "|\n";
            }
            return out;
        }

        // функционал матрицы
        friend void
        getDecreasedMatrix(const Matrix<T> &mat, Matrix<T> &tmp, int p, int q) { // вырезаем строчку и столбец
            unsigned n = mat.m_rows;
            int i = 0, j = 0;

            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    if (row != p && col != q) {
                        tmp(i, j++) = mat(row, col);
                        if (j == n - 1) {
                            j = 0;
                            i++;
                        }
                    }
                }
            }
        }

        T det() const {  // определитель (раскладываем по первой строчке, рекурентно)
            if (m_rows != m_cols) {
                throw std::logic_error("not a square matrix\n");
            }

            if (m_rows == 1) {
                return (*this)(0, 0);
            }

            T d = 0;
            int sgn = 1;
            Matrix<T> tmp(m_rows - 1, m_rows - 1);
            for (int i = 0; i < m_rows; ++i) {
                getDecreasedMatrix(*this, tmp, 0, i);
                d += sgn * (*this)(0, i) * tmp.det();
                sgn *= -1;
            }

            return d;
        }

        friend void row_swap(Matrix<T> &to_swap, int r1, int r2, int c) {  // меняем строчки
            for (int i = 0; i < c; ++i) {
                std::swap(to_swap(r1, i), to_swap(r2, i));
            }
        }

        // поиск ранга
        void change(Matrix<> &tmp, int col, int row, int r) {
            double m = (double) tmp(col, row) / tmp(row, row);
            for (int i = 0; i < tmp.cols(); ++i) {
                tmp(col, i) -= m * tmp(row, i);
            }
        }

        void row_reducing(Matrix<T> res, int r, int rows, int m_cols) {
            Matrix<> tmp(res.rows(), res.cols());
            for (int i = 0; i < tmp.rows(); ++i) {
                for (int j = 0; j < tmp.cols(); ++j) {
                    tmp(i, j) = (double) res(i, j);
                }
            }
            for (int row = 0; row < r; ++row) {
                if (tmp(row, row) != 0) {
                    for (int col = 0; col < rows; ++col) {
                        if (col != row) {
                            change(tmp, col, row, r);
                        }
                    }
                } else {
                    bool to_reduce = true;
                    for (int i = row + 1; i < rows; ++i) {
                        if (tmp(i, row) <= std::numeric_limits<T>::epsilon()) {
                            row_swap(tmp, row, i, r);
                            to_reduce = false;
                            break;
                        }
                    }

                    if (to_reduce) {
                        r--;
                        for (int i = 0; i < rows; ++i) {
                            tmp(i, row) = tmp(i, r);
                        }
                    }
                    row--;
                }
            }
        }


        // сама функция ранга
        int rank() {
            Matrix<T> tmp = (*this);
            int r = std::min(m_rows, m_cols);

            row_reducing(tmp, r, m_rows, m_cols);

            return r;
        }

        // структуры для спецификации вычисления нормы у матрицы с комплексными числами
        double sqr_abs(T el) {
            return el * el;
        }


        // норма матрицы
        double norm() {
            double n = 0;

            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    n += sqr_abs((*this)[i][j]);
                }
            }

            return sqrt(n);
        }

        // след матрицы
        T trace() {
            T tr = 0;
            for (int i = 0; i < std::min(m_rows, m_cols); ++i) {
                tr += m_ptr[i * m_cols + i];
            }

            return tr;
        }

        // транспонирование матрицы
        friend Matrix<T> transpose(const Matrix<T> &m) {
            Matrix<T> tmp(m.m_cols, m.m_rows);

            for (int i = 0; i < m.m_cols; ++i) {
                for (int j = 0; j < m.m_rows; ++j) {
                    tmp(i, j) = m(j, i);
                }
            }

            return tmp;
        }

        // поиск обратной матрицы
        void get_adj(const Matrix<T> &mat, Matrix<> &res) {
            if (mat.rows() != res.rows() || mat.cols() != res.cols()) {
                throw std::logic_error("matrix dimensions are not matching\n");
            }
            if (mat.rows() != res.cols()) {
                throw std::logic_error("not a square matrix\n");
            }
            T mat_det = mat.det();
            for (int i = 0; i < res.rows(); ++i) {
                for (int j = 0; j < res.cols(); ++j) {
                    Matrix<T> tmp(mat.rows() - 1, mat.rows() - 1);
                    getDecreasedMatrix(mat, tmp, i, j);
                    int sgn = (i + j) % 2 == 0 ? 1 : -1;
                    res(j, i) = (double) sgn * tmp.det() / mat_det;
                }
            }
        }

        Matrix<> inv(const Matrix<T> &m) {
            if (sqr_abs(m.det()) <= std::numeric_limits<double>::epsilon()) {
                throw std::logic_error("matrix is singular\n");
            }

            Matrix<> res(m.m_rows, m.m_cols);

            Matrix<T> get_adj(m, res);

            return res;
        }


        // возведение в степень
        friend Matrix<T> pow(const Matrix<T> &m, int n) {
            Matrix<T> tmp(m);
            for (int i = 0; i < n - 1; ++i) {
                tmp = tmp * m;
            }

            return tmp;
        }

        // бинарное возведение в степень
        friend Matrix<T> bin_pow(const Matrix<T> &m, int n) {
            if (n == 1) {
                return m;
            }

            Matrix<T> tmp(m);
            if (n % 2 != 0) {
                return tmp * bin_pow(tmp, n - 1);
            }
            tmp = bin_pow(tmp, n / 2);
            return tmp * tmp;
        }
    };
}