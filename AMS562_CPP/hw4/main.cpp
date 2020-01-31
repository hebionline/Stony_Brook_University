//  The main test program
#include <iostream>
#include <cmath>
#include "array.hpp"

int main(int argc, char *argv[]) 
{
    int array_size1 = 5;
    double array_test1[array_size1] = {1.0, 2.0, 3.0, 4.0, 5.0};

    int array_size2 = 5;
    double array_test2[array_size2] = {-1.0, 1.0, 1.0, 1.0, 100.0};

    //constructure function is test below
    std::cout << "step 1: check construction function" << '\n';
    Array array1(array_size1, 0.0); 
    Array array2(array_size2, 0.0); 
    
    array1.print();
    array2.print();

    std::cout << '\n' << '\n';

    std::cout << "step 2: initialze array1 and array2" << '\n';
    //check get "data_pointer" and "size" function
    double *ptr_array_data_wb; //write_enabled
    ptr_array_data_wb = array1.data();
    unsigned size_array_data;
    size_array_data = array1.size();

    //also double check the copy function
    double *q = array_test1;
    for(int i = 0; i < size_array_data; i++)
    {
      *ptr_array_data_wb = *q; 
      ptr_array_data_wb++;
      q++;
    }
    Array array3(array2);
    array3.copy(array1);

    ptr_array_data_wb = array2.data();
    size_array_data = array2.size();
    
    q = array_test2;
    for(int i = 0; i < size_array_data; i++)
    {
      *ptr_array_data_wb = *q; 
      ptr_array_data_wb++;
      q++;
    }

    array1.print();
    array2.print();
    array3.print();
    std::cout << '\n' << '\n';

    std::cout << "step 3: check entry index function" << '\n';    
    double ptr_array_data_index;
    ptr_array_data_index = array1.at(4);
    if (ptr_array_data_index != 5.0)
      std::cout << "wow! stupid!" << '\n'; 
    else
      std::cout << "PASS!!" << '\n'; 

    std::cout << '\n' << '\n';
    
    std::cout << "step 4: check the resize function with diffent input" << '\n';    
    array3.resize(5, true);
    array3.print();
    array3.resize(10, false);
    array3.print();
    array3.resize(5, true);
    array3.copy(array1);    
    array3.print();

    std::cout << '\n' << '\n';

    std::cout << "step 5: check norm and sum function" << '\n';   
    double norm1 = array1.norm();
    double norm2 = array2.norm();
    
    double sum1 = array1.sum();
    double sum2 = array2.sum();

    std::cout << "norm1 is " << norm1 << '\n';
    std::cout << "norm2 is " << norm2 << '\n';
    std::cout << "sum1 is " << sum1 << '\n';
    std::cout << "sum2 is " << sum2 << '\n';

    std::cout << '\n' << '\n';

    std::cout << "step 6: check max and min function" << '\n';   
    double max1 = array1.max();
    double max2 = array2.max();
    
    double min1 = array1.min();
    double min2 = array2.min();

    std::cout << "max1 is " << max1 << '\n';
    std::cout << "max2 is " << max2 << '\n';
    std::cout << "min1 is " << min1 << '\n';
    std::cout << "min2 is " << min2 << '\n';

    std::cout << '\n' << '\n';

    std::cout << "step 7: check dot, add and sub function" << '\n';   
    double dot1 = array1.dot(array1);
    double dot2 = array2.dot(array1);

    std::cout << "dot1 is " << dot1 << '\n';
    std::cout << "dot2 is " << dot2 << '\n';

    array1.add(array3).print();
    array1.sub(array2).print(); 

    std::cout << '\n' << '\n';

}