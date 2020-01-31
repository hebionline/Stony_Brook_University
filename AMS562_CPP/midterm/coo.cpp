// source code of COO format
#include "coo.hpp"
#include "vec.hpp"

#include <iostream>

namespace coo {

// create a csr matrix
COOMatrix *create(const int n, const int nnz) {
  COOMatrix *ptr = nullptr;
  if ((n <= 0)||(nnz <=0)) {
    // invalid input size, return nullptr
    return ptr;
  }
    // first allocate a pointer that points to DenseVec
  ptr = new COOMatrix;
  
  // allocation failed
  if (!ptr) {
    return nullptr;
  }

  ptr->v = nullptr;
  ptr->i = nullptr;
  ptr->j = nullptr;
  ptr->n = n;
  ptr->nnz = nnz;

  ptr->v = new double[nnz]();
  if (!ptr->v) {
    delete ptr;
    return nullptr;
  }
  
  ptr->i = new int[nnz]();
  if (!ptr->i) {
    delete ptr->v;
    delete ptr;
    return nullptr;
  }
  
  ptr->j = new int[nnz]();
  if (!ptr->j) {
    delete ptr->v;
	delete ptr->i;
    delete ptr;
    return nullptr;
  }

  return ptr;
}

// destroy a csr matrix
void destroy(COOMatrix *mat) {
  if (!mat) return;
  if (mat->v)
    delete[] mat->v;
  if (mat->i)
    delete[] mat->i;
  if (mat->j)
    delete[] mat->j;
  
  delete mat;
  return;
}

// assign a triplet (i,j,v)
bool assign_ijv(COOMatrix &mat, const int i, const int j, const double v,
                const int nnz_index) {
  bool fail = false;
  // invalid input size, return nullptr
  if ((i < 0)||(j < 0)||(nnz_index < 0)) {
    return true;
  }
  *(mat.i + nnz_index) = i;
  *(mat.j + nnz_index) = j;
  *(mat.v + nnz_index) = v;
  mat.nnz = nnz_index + 1;

  return fail;
}

// extract the diagonal values
bool extract_diag(const COOMatrix &A, vec::DenseVec &diag) {
  if (A.n != diag.n) return true;
  bool fail = false;
  
  for (int i = 0; i < A.n; i++) {
    diag.value[i] = 0.0;
  }

  std::cerr << "in func extract_diag, A.nnz = " << A.nnz << "\n";
  
  for (int k = 0; k < A.nnz; k++) {
    int m = *(A.i + k);
    int n = *(A.j + k);
    if (m == n)
    {
        diag.value[m] = *(A.v + k);
    }
  }

  return fail;
}

// matrix vector multiplication
bool mv(const COOMatrix &A, const vec::DenseVec &x, vec::DenseVec &y) {
  if(A.n != x.n) return true;
  if(A.n != y.n) return true;

  bool fail = false;

  for (int i = 0; i < A.n; i++) {
    y.value[i] = 0.0;
  }
  for (int i = 0; i < A.n; i++) {
    for (int j = 0; j < A.n; j++)
    {
	y.value[i] += (A.v[j + (A.n * i)]) * (x.value[j]);
    }
  }

  return fail;
}

}  // namespace coo