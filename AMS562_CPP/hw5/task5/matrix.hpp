#ifndef _AMX562_MATRIX_HPP
#define _AMX562_MATRIX_HPP

#include <fstream>
#include <iostream>
#include <vector>

namespace ams562 {

/// \brief a \a matrix class for numerical computation
///
/// With the popularity of ML and DL, let's implement a matrix class that
/// enables most commonly used arithmetic operations.
///
/// Notice that since a matrix is a 2D structure, the trivalest idea to
/// represent it is by using a 2D member structure as well.
///
/// \note
///     This is a homework assignment that aims for educational purpose, the
///     actual \a matrix implementation is far away from this class. But
///     it's still extremely valuable as a starting point for understanding
///     essential usages of operator overloading and matrix operations.
///
/// \warning
///     You should use \a std::vector member functions instead of dealing with
///     POD, i.e. (plain old data types, e.g. double pointers).
class matrix {
 public:
  /// default constructor
  matrix()
  {
  };

  /// constructor for squared matrix
  /// \param[in] n row and column size
  explicit matrix(unsigned n)
  {
    _mat.resize(n);
    for (unsigned i = 0 ; i < n ; i++)
      _mat[i].resize(n);     
  };

  /// constructor for general matrix
  /// \param[in] m number of rows
  /// \param[in] n number of columns
  matrix(unsigned m, unsigned n)
  {
    _mat.resize(m);
    for (unsigned i = 0 ; i < m; i++ )
      _mat[i].resize(n);
  };

  /// copy constructor
  /// \param[in] other the other matrix
  /// \warning must make deep copy!
  matrix(const matrix &other);

  //----------------
  // size querying
  //----------------

  /// get number of rows
  unsigned rows() const;

  /// get number of columns
  unsigned cols() const;

  //----------------
  // data accessing
  //----------------

  /// get reference
  /// \param[in] row row index, 0-based
  /// \param[in] col column index, 0-based
  /// \return reference to the underlying data _mat
  inline double &operator()(unsigned row, unsigned col)
  {
    return (this->_mat[row].at(col));
  };

  /// get constant reference
  /// \param[in] row row index, 0-based
  /// \param[in] col column index, 0-based
  /// \return constant reference to the underlying data _mat
  inline const double &operator()(unsigned row, unsigned col) const
  {
    return (this->_mat[row].at(col));
  };

  /// get reference of a row
  /// \param[in] row row index, 0-based
  inline std::vector<double> &operator[](unsigned row)
  {
    return (this->_mat.at(row));
  };

  /// get constant reference of a row
  /// \param[in] row row index, 0-based
  inline const std::vector<double> &operator[](unsigned row) const
  {
    return (this->_mat.at(row)); 
  };

  //--------------
  // assignment
  //--------------

  /// assignment
  /// \brief copy values of \a rhs to \a this
  /// \param[in] rhs input matrix
  /// \note don't forget return *this
  matrix &operator=(const matrix &rhs);

  /// copy scalar
  /// \param[in] rhs scalar input
  /// \note on return, \a this = \a rhs
  matrix &operator=(double rhs);

  /// plus assign
  /// \param[in] rhs input matrix
  /// \note on return, \a this = \a this + \a rhs
  matrix &operator+=(const matrix &rhs);

  /// plus assign a scalar
  /// \param[in] rhs input scalar
  matrix &operator+=(double rhs);

  /// minus assign
  /// \param[in] rhs input matrix
  /// \note on return \a this = \a this - \a rhs
  matrix &operator-=(const matrix &rhs);

  /// minus assign scalars
  /// \param[in] rhs input scalars
  matrix &operator-=(double rhs);

  /// scaling this my a factor
  /// \param[in] rhs scaling factor
  /// \warning not matrix matrix multiplication!
  /// \note on return, \a this = \a this * \a rhs
  matrix &operator*=(double rhs);

  // create row and column vectors

  /// create row vector given a row index
  /// \param[in] i number of row
  /// \note on return, the vector is the i-th row of \a this
  std::vector<double> row(unsigned i) const;

  /// create column vector, given a column index
  /// \param[in] j number of col
  /// \note on return, the vector is the j-th column of \a this
  std::vector<double> col(unsigned j) const;

  /// resize
  /// \param[in] new_row new row size
  /// \param[in] new_col new column size
  void resize(unsigned new_row, unsigned new_col);

 private:
  std::vector<std::vector<double> > _mat;
};

/// \brief impl matrix scalar multiplation
/// \param[in] A matrix lhs
/// \param[in] x scalar rhs
/// \note
///     with \ref matrix::operator*=, this function should be no more than 3
///     lines.

matrix operator*(const matrix &A, double x);

/// \brief impl scalar matrix multiplation
/// \param[in] x scalar lhs
/// \param[in] A matrix rhs
/// \note single line impl with the function above
matrix operator*(double x, const matrix &A);

/// \brief impl matrix vector multiplation
/// \param[in] A matrix lhs
/// \param[in] x vector rhs
/// \note compute dot product, i.e. y=A*x
std::vector<double> operator*(const matrix &A, const std::vector<double> &x);

/// \brief impl vector matrix multiplication
/// \param[in] x vector lhs
/// \param[in] A matrix rhs
/// \note compute dot product, i.e. y = x*A
/// \warning it is **NOT** the same as A*x
std::vector<double> operator*(const std::vector<double> &x, const matrix &A);

/// \brief impl matrix matrix multiplication
/// \param[in] A lhs matrix
/// \param[in] B rhs matrix
/// \note compute C = A*B
/// \note be careful about the shape of C
matrix operator*(const matrix &A, const matrix &B);

/// C++ output
/// \param[in,out] o_str standard output streamer
/// \param[in] mat matrix for output
///
/// The output must be 2D matrix structure, for instance, given a matrix
///     | 1 2 3 |
///     | 4 5 6 |
/// which has size 2-by-3, then the C++ output streamer result is:
///
///           1 2 3\n4 5 6\n
std::ostream &operator<<(std::ostream &o_str, const matrix &mat);

/// C++ input
/// \param[in,out] i_str standard input streamer
/// \param[out] mat matrix for reading values from \a i_str
std::istream &operator>>(std::istream &i_str, matrix &mat);

// with the >> and << properly implemented, you can call the following
// functions for IO wit matrix.

inline matrix readFromFile(const std::string &filename) {
  // first, get the size
  unsigned m, n;
  std::ifstream file(filename.c_str());
  matrix mat;
  // if file is open, the read call C++ input
  if (file.is_open()) {
    // read size first
    file >> m >> n;
    std::cout << "creating matrix with size (" << m << ',' << n << ")\n";
    mat.resize(m, n); // resize triggered here.
    file >> mat; // input operator
    file.close();
  }
  return mat;
}

inline void writeToFile(const std::string &filename, const matrix &mat) {
  std::ofstream file(filename.c_str());
  if (file.is_open()) {
    std::cout << "writing matrix with size (" << mat.rows() << ',' << mat.cols()
              << ")\n";
    // first write the row and column sizes with wight space separator
    // and newline at the end
    file << mat.rows() << ' ' << mat.cols() << '\n';
    // directly call output operator on matrix
    file << mat; // output operator
    file.close();
  }
}

}  // namespace ams562

#endif
