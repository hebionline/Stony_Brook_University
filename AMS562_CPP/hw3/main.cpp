//#include "stdafx.h"
#include <iostream>
#include <string> 
#include <cmath>
#include <cstdlib>

#define ERR_NO_ERROR 0
const double tolerent_value = 1e-6;
// the interface of the function is:
//  inputs:
//    a       left limit
//    b       right limit
//    maxit   maximal iteration allowed
//    eval    function pointer to a mathmatic calculation
//  outputs:
//    root    the root of the function
//    iters   iterations
//  return:
//    true if a root is found, false if failed

bool bisecFlex(const double a, const double b, const int maxit, double (*eval)(double),
	           double *root, int *iters);

double Squar_Less_Two(double a);
double abs_two(double x_abs, double y_abs);

int main(int argc, char *argv[]) 
{
    bool ret_val;
	int max_count, num_iters, func_choice;
    int err = ERR_NO_ERROR;
	double input_1, input_2, output_result;	

	bool (*pfunc)(const double a, const double b, const int maxit, double *output_result, int *num_iters);

    std::cout << "This program implements finding non-linear root for mathmatic functions and " << '\n';
	std::cout << "currently only two f(x) functions are supported: one is sin(x), the other is (x^2 - 2)" << '\n';
	std::cout << '\n';
    std::cout << "The command line is in form of " << '\n';
    std::cout << "./CPP_hw1.exe <func-choice> <a> <b> <maxit>" << '\n';
	std::cout << "func-choice = 1, sin(x) and func-choice = 2, (x^2 - 2)" <<'\n';
    std::cout << "a and b define the interval of f(x) you want choose " << '\n';
	std::cout << "maxit is the maximal iteration counts allowed" << '\n';

	output_result = 0.0;
	num_iters = 0;

    if (argc < 5)
    {
      //remind end user to provide a valid input.
      std::cerr << "Please enter necessary inputs, you can refer to printed reminder above" << '\n';
      return ERR_NO_ERROR;
    }
    else
    {
      //initialize with user's input parameters.
      func_choice = (int)std::atof(argv[1]);
      input_1 = (double)std::atof(argv[2]); //a
	  input_2 = (double)std::atof(argv[3]); //b
	  max_count = (int)std::atof(argv[4]);  //maxit
	  num_iters = 0;
	}
    if(func_choice == 1)
	{
		ret_val = bisecFlex(input_1, input_2, max_count, std::sin, &output_result, &num_iters);
		//pfunc = bisecSin;
		//ret_val = pfunc(input_1, input_2, max_count, &output_result, &num_iters);
	}
	else if (func_choice == 2)
	{
		ret_val = bisecFlex(input_1, input_2, max_count, Squar_Less_Two, &output_result, &num_iters);
		//pfunc = bisecQuadratic;
		//ret_val = pfunc(input_1, input_2, max_count, &output_result, &num_iters);
	}
	else
	{
		std::cerr << "Please enter either 1 -> sin(x) and 2 -> x^2 - 2" << '\n';
        return ERR_NO_ERROR;
	}

	if (ret_val == true)
	{
		std::cout << "the root = " << output_result << '\n';
		std::cout << "the number of iter-cycle = " << num_iters << '\n';
	}
	else 
	{
		std::cerr << "failed to calculate" << '\n';
	}

	return ERR_NO_ERROR;
}

double abs_two(double x_abs, double y_abs)
{
	double temp;
	if (x_abs > y_abs)
		temp = x_abs - y_abs;
	else 
		temp = y_abs - x_abs;
	return temp;
}

double Squar_Less_Two(double a)
{
	double temp;
	temp = a * a - 2;
	return temp;
}

bool bisecFlex(const double a, const double b, const int maxit, double (*eval)(double),
	           double *root, int *iters)
{
	double input_a, input_b,temp;
	int max_num_cycles;

    if ((root == NULL) || (iters == NULL)) 
	{
		std::cerr << "input points are NULL in func bisecFlex()" << '\n';
		return false;
	}
	max_num_cycles = maxit;
	input_a = a;
	input_b = b;
	temp = eval(input_a) * eval(input_b);
	if(temp < 0)
	{
		int i;
		for (i = 0; i < max_num_cycles; i++)
		{
			double temp_2;
			temp_2 = abs_two(input_a, input_b);
			if (temp_2 > tolerent_value)
			{
				double t, u;
				u = (input_a + input_b)/2;
				*root = u;
				*iters = i;
				t = eval(input_a) * eval(u);
				if (t == 0)
                    break;
				else if (t > 0)
					input_a = u;
				else
					input_b = u;
			}
			else
			{
				*root = input_a;
				*iters = i;
				break;
			}
		}
		return true;
	}
	else if (temp == 0)
	{
		if(input_a == 0)
			*root = a;
		else
			*root = b;
		*iters = 0;
		return true;
	}
	else
	{
		std::cout << "we only accept reasonable a and b value, which makes f(a) * f(b) < 0" << '\n';
		return false;
	}

	return true;
}
