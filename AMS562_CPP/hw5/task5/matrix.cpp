
#include "matrix.hpp"

#include <iostream>
#include <cstdlib>

namespace ams562 {
/// copy constructor
/// \param[in] other the other matrix
/// \warning must make deep copy!
  matrix::matrix(const matrix &other)
  {	
    unsigned s = other._mat.size();
    unsigned t = other._mat[0].size();
    _mat.resize(s);
    for(unsigned i = 0; i < s; i++)
      for(unsigned j = 0; j < t; j++)
        _mat[i].push_back(other._mat[i][j]);
  }

  //----------------
  // size querying
  //----------------

  /// get number of rows
  unsigned matrix::rows() const
  {
    unsigned max_row_no;
    max_row_no = _mat.size();
    return max_row_no;
  }

  /// get number of columns
  unsigned matrix::cols() const
  {
    unsigned max_col_no;
    max_col_no = _mat[0].size();
    return max_col_no;
  }

  //--------------
  // assignment
  //--------------

  /// assignment
  /// \brief copy values of \a rhs to \a this
  /// \param[in] rhs input matrix
  /// \note don't forget return *this
  matrix & matrix::operator=(const matrix &rhs)
  {	
    unsigned s = rhs._mat.size();
    unsigned t = rhs._mat[0].size();
    this->_mat.resize(s);
    for(unsigned i = 0; i < s; i++)
    {
      this->_mat[i].resize(t);
      for(unsigned j = 0; j < t; j++)
      {
        this->_mat[i][j] = rhs._mat[i][j];
      }
    }
	
    return *(this);
  }

  /// copy scalar
  /// \param[in] rhs scalar input
  /// \note on return, \a this = \a rhs
  matrix & matrix::operator=(double rhs)
  {
    unsigned s = this->_mat.size();
    unsigned t = this->_mat[0].size();
    for(unsigned i = 0; i < s; i++)
    {
      for(unsigned j = 0; j < t; j++)
      {
        this->_mat[i][j] = rhs;
      }
    }	  
    return (*this);	  
  }
  
  /// plus assign
  /// \param[in] rhs input matrix
  /// \note on return, \a this = \a this + \a rhs
  matrix & matrix::operator+=(const matrix &rhs)
  {
    if(rhs.rows() != this->rows())
    {
      std::cout << "Warning: matrix's row number doesn't equal with each other, so computing result is not reliable!" << "\n";
    }
	
    if(rhs.cols() != this->cols())
    {
      std::cout << "Warning: matrix's row number doesn't equal with each other, so computing result is not reliable!" << "\n";
    }
	
    unsigned s = rhs._mat.size();
    unsigned t = rhs._mat[0].size();
    _mat.resize(s);
    for(unsigned i = 0; i < s; i++)
    {
      _mat[i].resize(t);
      for(unsigned j = 0; j < t; j++)
      {
        _mat[i][j] += rhs._mat[i][j];
      }	  
    }
    return (*this);
  }
  
  /// plus assign a scalar
  /// \param[in] rhs input scalar
  matrix & matrix::operator+=(double rhs)
  {
    unsigned s = this->_mat.size();
    unsigned t = this->_mat[0].size();
    for(unsigned i = 0; i < s; i++)
    {
      for(unsigned j = 0; j < t; j++)
      {
        this->_mat[i][j] += rhs;
      }
    }
    return (*this);	    
  }
  
  /// minus assign
  /// \param[in] rhs input matrix
  /// \note on return \a this = \a this - \a rhs
  matrix & matrix::operator-=(const matrix &rhs)
  {	
    if(rhs.rows() != this->rows())
    {
      std::cout << "Warning: matrix's row number doesn't equal with each other, so computing result is not reliable!" << "\n";
    }
	
    if(rhs.cols() != this->cols())
    {
      std::cout << "Warning: matrix's row number doesn't equal with each other, so computing result is not reliable!" << "\n";
    }
	
    unsigned s = rhs._mat.size();
    unsigned t = rhs._mat[0].size();
    _mat.resize(s);
    for(unsigned i = 0; i < s; i++)
    {
      _mat[i].resize(t);
      for(unsigned j = 0; j < t; j++)
      {
        _mat[i][j] -= rhs._mat[i][j];
      }
    }	  
    return (*this);	  
  }

  /// minus assign scalars
  /// \param[in] rhs input scalars
  matrix & matrix::operator-=(double rhs)
  {
    unsigned s = this->_mat.size();
    unsigned t = this->_mat[0].size();
    for(unsigned i = 0; i < s; i++)
    {
      for(unsigned j = 0; j < t; j++)
      {
        this->_mat[i][j] -= rhs;
      }
    }	  
    return (*this);	  
  }

  /// scaling this my a factor
  /// \param[in] rhs scaling factor
  /// \warning not matrix matrix multiplication!
  /// \note on return, \a this = \a this * \a rhs
  matrix & matrix::operator*=(double rhs)
  {	
    unsigned s = this->_mat.size();
    unsigned t = this->_mat[0].size();
    for(unsigned i = 0; i < s; i++)
    {
      for(unsigned j = 0; j < t; j++)
      {
        this->_mat[i][j] *= rhs;
      }
    }	  
    return (*this);	  
  }

  // create row and column vectors

  /// create row vector given a row index
  /// \param[in] i number of row
  /// \note on return, the vector is the i-th row of \a this
  std::vector<double> matrix::row(unsigned i) const
  {
    return (this->_mat.at(i));
  }

  /// create column vector, given a column index
  /// \param[in] j number of col
  /// \note on return, the vector is the j-th column of \a this
  std::vector<double> matrix::col(unsigned j) const
  {
    unsigned t = this->rows();
    std::vector<double> myvector;
    for(unsigned i = 0; i < t; i++)
    {
      myvector.push_back(this->_mat[i][j]);
    }	  
    return myvector;
  }
  /// resize
  /// \param[in] new_row new row size
  /// \param[in] new_col new column size
  void matrix::resize(unsigned new_row, unsigned new_col)
  {
    _mat.resize(new_row);
    for (int i = 0 ; i < new_row; i++ )
      _mat[i].resize(new_col);  
  }

/// \brief impl matrix scalar multiplation
/// \param[in] A matrix lhs
/// \param[in] x scalar rhs
/// \note
///     with \ref matrix::operator*=, this function should be no more than 3
///     lines.

matrix operator*(const matrix &A, double x)
{
    matrix C(A);
    C *= x;
    return C;
}

/// \brief impl scalar matrix multiplation
/// \param[in] x scalar lhs
/// \param[in] A matrix rhs
/// \note single line impl with the function above

matrix operator*(double x, const matrix &A)
{
    return (A*x);
}

/// \brief impl matrix vector multiplation
/// \param[in] A matrix lhs
/// \param[in] x vector rhs
/// \note compute dot product, i.e. y=A*x

std::vector<double> operator*(const matrix &A, const std::vector<double> &x)
{
    unsigned s = A.rows();
    unsigned t = A.cols();
    std::vector<double> myvector(s);

    for(unsigned i = 0; i < s; i++)
    {
      std::vector<double> vec_temp = A[i];
      for(unsigned j = 0; j < vec_temp.size(); j++)
        myvector[i] += vec_temp[j] * x[j];
    }	  
    return myvector;
}

/// \brief impl vector matrix multiplication
/// \param[in] x vector lhs
/// \param[in] A matrix rhs
/// \note compute dot product, i.e. y = x*A
/// \warning it is **NOT** the same as A*x

std::vector<double> operator*(const std::vector<double> &x, const matrix &A)
{
    unsigned s = A.rows();
    unsigned t = A.cols();
    std::vector<double> myvector(t);

    for(unsigned i = 0; i < t; i++)
    {
      std::vector<double> vec_temp = A.col(i);
      for(unsigned j = 0; j < vec_temp.size(); j++)
        myvector[i] += vec_temp[j] * x[j];
    }	  
    return myvector;
}

/// \brief impl matrix matrix multiplication
/// \param[in] A lhs matrix
/// \param[in] B rhs matrix
/// \note compute C = A*B
/// \note be careful about the shape of C

matrix operator*(const matrix &A, const matrix &B)
{
    //matrix C(A);
    unsigned s = A.rows();
    unsigned t = A.cols();
    matrix C(s, t);
    for(unsigned i = 0; i < s; i++)
    {
      std::vector<double> row_temp = A[i];
      for(unsigned j = 0; j < t; j++)
      {
        std::vector<double> col_temp = B.col(j);
        for(unsigned k = 0; k < row_temp.size(); k++)
          C(i,j) += row_temp[k] * col_temp[k];
      }
    }
    return C;
}

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
std::ostream &operator<<(std::ostream &o_str, const matrix &mat)
{
    for(unsigned i = 0; i < mat.rows(); i++)
    {
      for(unsigned j = 0; j < mat.cols(); j++)
      {
        o_str << mat(i,j) << " ";
      }
      o_str << "\n";
    }
    return o_str;
}

/// C++ input
/// \param[in,out] i_str standard input streamer
/// \param[out] mat matrix for reading values from \a i_str

std::istream &operator>>(std::istream &i_str, matrix &mat)
{
    for(unsigned i = 0; i < mat.rows(); i++)
      for(unsigned j = 0; j < mat.cols(); j++)
        i_str >> mat(i,j);
    
    return i_str;
}

  
  
}
