/* Practice task 4 */
#include <iostream>
#include <cstdlib>
#include "array.hpp"


Array::~Array()
{
  if (_data)
     delete[] _data;
  _size = 0;
}
	
	// get the length of array
unsigned Array::size() const
{
  return _size;
}

	// get the data pointer of array
double * Array::data()
{
  return (_data);
}
	
	// get read-only pointer of array
const double * Array::data() const
{
  return (_data);
}
	
// given a rhs Array, copy its value
// make sure the sizes are same
void Array::copy(const Array &rhs)
{
  if (rhs._size == _size)
  {
    double *p = rhs._data;
    double *q = _data;
    for(int i = 0; i < _size; i++)
    {
      *q = *p; 
      p++;
      q++;
    }
  }
  else
  {
    std::cout << "copy function requires the size of input array should be same" << '\n';
  }
}
// reference entry "index" of the data
double & Array::at(unsigned index)
{
  return *(this->_data + index);  
}

// read-only reference entry "index" of the data
const double & Array::at(unsigned index) const
{
  return *(_data + index);
}
	
void Array::resize(unsigned new_size, bool prsv)
{
  double *new_data;
  unsigned min_size = (new_size > _size?_size: new_size);
  new_data = new double[new_size]();
  if(prsv == true)
  {  
    double *p = new_data;
    double *q = _data;
    for(int i = 0; i < min_size; i++)
    {
        *p = *q; 
        p++;
        q++;
    }
    delete this->_data;
    this->_data = new_data;
  }
  else
  {
    delete this->_data;
    this->_data = new_data;
  }
  _size = new_size;
}
	
// L-2 norm, sum, maximum/minimum, and dot (inner) products
double Array::norm() const
{
  double sum;
  const double *p = this->_data;
	  
  sum = 0.0;
  for(int i = 0; i < this->_size; i++)
  {
    sum += (*p) * (*p);
    p++;	  
  }
  return sum;
}
	
double Array::sum() const
{
  double sum;
  const double *p = this->_data;
	  
  sum = 0.0;
  for(int i=0; i < this->_size; i++)
  {
    sum += (*p);
    p++;	  
  }
  return sum;
}
	
double Array::max() const
{
  double max;
  const double *p = this->_data;
	  
  max = 0.0;
  for(int i=0; i < this->_size; i++)
  {
    max = (max > (*p)) ? max: (*p);
    p++;	  
  }
  return max;
}

double Array::min() const
{
  double min;
  const double *p = this->_data;
	  
  min = 0.0;
  for(int i=0; i < this->_size; i++)
  {
    min = (min < (*p)) ? min: (*p);
    p++;	  
  }
  return min;
}
	
double Array::dot(const Array &rhs) const
{
  Array tmp(*this);
  if(tmp._size != rhs._size) 
    std::cout << "array dot function requires the size of input array should be same" << '\n';

  double dot = 0.0;
  if(tmp._size == rhs._size)
  {  
    double *p = rhs._data;
    double *q = tmp._data;
    
    for(int i = 0; i < this->_size; i++)
    {
      dot += (*q) * (*p); 
      p++;
      q++;
    }
  }
  return dot;
}

// addition: this+rhs, return a new array
Array Array::add(const Array &rhs) const
{
  Array tmp(*this);
  if(tmp._size != rhs._size) 
    std::cout << "array add function requires the size of input array should be same" << '\n';

  if(tmp._size == rhs._size)
  {
    double *p = rhs._data;
    double *q = tmp._data;
    for(int i = 0; i < this->_size; i++)
    {
      *q += (*p); 
      p++;
      q++;
      //std::cout << "*q = " << *q << '\n';
    }
  }
  //tmp.print();
  return tmp;
  
}
	
// subtraction: this-rhs, return a new array
Array Array::sub(const Array &rhs) const
{
  Array tmp(*this);
  if(tmp._size != rhs._size) 
    std::cout << "array add function requires the size of input array should be same" << '\n';

  if(tmp._size == rhs._size)
  {
    double *p = rhs._data;
    double *q = tmp._data;
    for(int i = 0; i < this->_size; i++)
    {
      *q -= (*p); 
      p++;
      q++;
    }
  }
  //tmp.print();
  return tmp;
}
	
// do some terminal printing
void Array::print() const
{
  std::cout << "size of this array is " << _size << '\n';
  const double *q = this->_data;
  std::cout << "content of this array is listed as follows:" << '\n';
  for(int i = 0; i < this->_size; i++)
  {
    std::cout << *q << "   ";
    q++;
  }
  std::cout << '\n';
}
