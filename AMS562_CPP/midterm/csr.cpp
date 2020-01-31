// This is the source file that contains the implementation of
// CSRMatrix and its corresponding functions

#include "csr.hpp"
#include "vec.hpp"

#include <iostream>

namespace csr {

// create a csr matrix
CSRMatrix *create(const int n, const int nnz) {
  CSRMatrix *ptr = nullptr;
  if ((n <= 0)||(nnz <=0)) {
    // invalid input size, return nullptr
    return ptr;
  }
    // first allocate a pointer that points to DenseVec
  ptr = new CSRMatrix;
  
  // allocation failed
  if (!ptr) {
    return nullptr;
  }

  ptr->value = nullptr;
  ptr->indices = nullptr;
  ptr->indptr = nullptr;
  ptr->n = n;

  ptr->value = new double[nnz]();
  if (!ptr->value) {
    delete ptr;
    return nullptr;
  }
  
  ptr->indices = new int[nnz]();
  if (!ptr->indices) {
    delete ptr->value;
    delete ptr;
    return nullptr;
  }
  
  ptr->indptr = new int[nnz]();
  if (!ptr->indptr) {
    delete ptr->value;
	delete ptr->indices;
    delete ptr;
    return nullptr;
  }

  return ptr;
}

// destroy a csr matrix
void destroy(CSRMatrix *mat) {
  if (!mat) return;
  if (mat->value)
    delete[] mat->value;
  if (mat->indices)
    delete[] mat->indices;
  if (mat->indptr)
    delete[] mat->indptr;
  
  delete mat;
}

// assign a row
bool assign_row(CSRMatrix &mat, const int row, const int *cols,
                const double *vals, const int nnz) {


  if (row < 0 || row > mat.n || nnz < 0) return true;
  
  bool fail = false;

  const int *p = cols;
  const double *q = vals;

  const int start = mat.indptr[row];  // bonus, this is how to get the starting entry of this row

  for (int i = 0; i < nnz; i++)
  {
    mat.value[start + i] = *q;
    mat.indices[start + i] = *p;
    p++; q++;
  }

  mat.indptr[row+1] += mat.indptr[row] + nnz;
  
  return fail;
}


// extract the diagonal values - Normal Search to search
bool extract_diag(const CSRMatrix &A, vec::DenseVec &diag) {
  if (A.n != diag.n) return true;
  bool fail = false;
  
  for (int i = 0; i < A.n; i++) {
    diag.value[i] = 0.0;
  }

  //each raw is calculate one time;
  for (int i = 0; i < A.n; i++) {
    int start = A.indptr[i];      //start index of row;
    int end = A.indptr[i+1];      //start index of next row;
    int diff = end - start;	  //row length;

    for (int j = 0; j < diff; j++)
    {
	int VetIndex = A.indices[start + j];
        if (VetIndex == i)
        {
	    diag.value[i] = A.value[start + j];
        }
    }
  }

  return fail;
}


// matrix vector multiplication
bool mv(const CSRMatrix &A, const vec::DenseVec &x, vec::DenseVec &y) {
  bool fail = false;

  for (int i = 0; i < A.n; i++) {
    y.value[i] = 0.0;
  }
  //each raw is calculate one time;
  for (int i = 0; i < A.n; i++) {
    int start = A.indptr[i];      //start index of row;
    int end = A.indptr[i+1];      //end index of row; potenial bug here A.indptr[A.n]
    int diff = end - start;	  //row length;

    for (int j = 0; j < diff; j++)
    {
	int VetIndex = A.indices[start + j];
	y.value[i] += (A.value[start + j]) * (x.value[VetIndex]);
    }
  }
  return fail;
}

}  // namespace csr