#ifndef _ARRAY_HPP
#define _ARRAY_HPP

class Array {
 public:
  // default constructor
  // overwrite this one to set data and size to
  // empty status
  //Array();
  Array() {
    _data = NULL;
    _size = 0;
        };

  // copy constructor
  // we want to perform a deep copy so that
  // each Array will own its own
  // data and copies the values of the "other"
  // hint: you need a for/while loop here
  //Array(const Array &other);
  Array(const Array &other){
    _size = other._size;
    if(_size > 0)
      _data = new double[_size]();
    double *p = other._data;
    double *q = _data;
    for(int i = 0; i < _size; i++)
    {
      *q = *p; 
      p++;
      q++;
    }
   };

  // constructor with array size and
  // the default initialization value
  //explicit Array(unsigned n, double v = 0.0);
  explicit Array(unsigned n, double v = 0.0){
    _size = n;
    if(_size > 0)
      _data = new double[_size]();
    double *q = _data;
    for(int i = 0; i <_size; i++)
    {
      *q = v; 
      q++;
    }
  };

  // we want to overwrite the implicit destructor
  // so that the memory is freed!
  ~Array();

  // get the length of array
  unsigned size() const;

  // get the data pointer of array
  double *data();

  // get read-only pointer of array
  const double *data() const;

  // given a rhs Array, copy its value
  // make sure the sizes are same
  void copy(const Array &rhs);

  // reference entry "index" of the data
  double &at(unsigned index);

  // read-only reference entry "index" of the data
  const double &at(unsigned index) const;

  // resize the array
  // require memory allocation and deallocation
  // prsv is a flag that indicates if the user
  // wants to preserve the old values
  //
  // pseudo code:
  //   create new_data (dynamically) with size new_size
  //   if presv:
  //      copy _data to new_data with size = min(new_size, _size)
  //   free the old memory (_data)
  //   copy new_data pointer to _data
  void resize(unsigned new_size, bool prsv = true);

  // some math functions
  // L-2 norm, sum, maximum/minimum, and dot (inner) products
  double norm() const;
  double sum() const;
  double max() const;
  double min() const;
  double dot(const Array &rhs) const;

  // addition: this+rhs, return a new array
  Array add(const Array &rhs) const;

  // subtraction: this-rhs, return a new array
  Array sub(const Array &rhs) const;

  // do some terminal printing
  void print() const;

 private:
  double *_data;   ///< data pointer
  unsigned _size;  ///< length of the array
};

#endif