#include <iostream>
#include <cmath>
#include <vector>
#include "matrix.hpp"
//#include "rand.hpp"

int main(void) 
{
    std::cout << "step 1: check construction function" << '\n';
    ams562::matrix matrix1(22);
    ams562::matrix matrix3(3, 5);
    ams562::matrix matrix2(matrix3);

    std::cout<<matrix1<<"\n";
    std::cout<<matrix2<<"\n";
    std::cout<<matrix3<<"\n";
    
    std::cout << "step 2: check input and output operator overloading functions" << '\n';
    std::string matrix_file1;
    matrix_file1 = "test1.txt";
    matrix1 = ams562::readFromFile(matrix_file1);

    std::string matrix_file2;
    matrix_file2 = "test1.txt";
    matrix2 = ams562::readFromFile(matrix_file2);

    std::cout<<matrix2<<"\n";

    std::cout << "step 3: check size querying function" << '\n';
    unsigned num_row = matrix2.rows();
    unsigned num_col = matrix2.cols();

    std::cout << num_row << "\n";
    std::cout << num_col << "\n";

    std::cout << "step 4: check assignment function" << '\n';
    //read out a specific element in matrix by referring its index
    const double mat_rand_elem = matrix1(1, 3);
    std::cout << "matrix1[1][3] = " << mat_rand_elem << "\n";

    //read out a specific row from matrix by referring row number
    std::vector<double> mat_row = matrix1[1];
    std::cout << "matrix1[1] = ";
    for(unsigned i = 0; i < mat_row.size(); i++)
      std::cout << mat_row[i] << " ";
    std::cout<<"\n"<<"\n";

    std::vector<double> mat_row_2 = matrix1.row(2);
    std::cout << "matrix1[2] = ";
    for(unsigned i = 0; i < mat_row_2.size(); i++)
      std::cout << mat_row_2[i] << " ";
    std::cout<<"\n"<<"\n";

    std::vector<double> mat_col_2 = matrix1.col(2);
    std::cout << "matrix1[2] = ";
    for(unsigned i = 0; i < mat_col_2.size(); i++)
      std::cout << mat_col_2[i] << " ";
    std::cout<<"\n"<<"\n";

    matrix2.resize(3,5);
    std::cout<<matrix2<<"\n";
    
    std::cout << "step 5: check various operator overloading function" << '\n';
    //check operator "=" overloading function
    matrix3 = matrix1;
    std::cout<<matrix3<<"\n";
    //check operator "+=" overloading function
    matrix1 += matrix3;
    std::cout<<matrix1<<"\n";
    //check operator "-=" overloading function
    matrix1 -= matrix3;
    std::cout<<matrix1<<"\n";
    //check operator "*=" with a scalar 
    matrix1 *= -2.0;
    std::cout<<matrix1<<"\n";

    std::cout << "step 6: check free functions" << '\n';
    //check free function: operator "*=" with a scalar 
    matrix3 = matrix1*(-2.0);
    std::cout<<matrix3<<"\n";
   
    matrix3 = (-2.0)*matrix3;
    std::cout<<matrix3<<"\n";
    
    //check free function: operator "*=" with a vector
    std::cout<<matrix2<<"\n";
    mat_row_2 = matrix2.row(2);
    for(unsigned i = 0; i < mat_row_2.size(); i++)
      std::cout << mat_row_2[i] << " ";
    std::cout<<"\n"<<"\n";

    std::vector<double> mat_row_3 = matrix2 * mat_row_2;
    for(unsigned i = 0; i < mat_row_3.size(); i++)
      std::cout << mat_row_3[i] << " ";
    std::cout<<"\n"<<"\n";
  
    std::cout<<matrix2<<"\n";
    mat_col_2 = matrix2.col(1);
    for(unsigned i = 0; i < mat_col_2.size(); i++)
      std::cout << mat_col_2[i] << " ";
    std::cout<<"\n"<<"\n";

    std::vector<double> mat_col_1 = mat_col_2 * matrix2;
    for(unsigned i = 0; i < mat_col_1.size(); i++)
      std::cout << mat_col_1[i] << " ";
    std::cout<<"\n"<<"\n";
 
    matrix2.resize(3,3);
    std::cout<<matrix2<<"\n";

    ams562::matrix matrix4(3, 3);
    matrix4 = matrix2 * matrix2;
    std::cout<<matrix4<<"\n";

    //ams562::RandGen gen;
    //std::cout << gen.generate() << '\n';

    return 1;  
}
