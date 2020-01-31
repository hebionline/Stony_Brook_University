//#include "stdafx.h"
#include <iostream>
#include <string> 
#include <cmath>
#include <cstdlib>

#define ERR_NO_ERROR 0
static void genPointsOnUnitSphere(const int N, float *x, float *y, float *z);

int main(int argc, char *argv[]) 
{
    int count = 1;
    int number = 0;
    int err = ERR_NO_ERROR;
    float *p_input1, *p_input2, *p_input3, *result;

    std::cout << "This program helps you determine the extreme arc lengths of a random " << '\n';
    std::cout << "sample point cloud on the unit sphere. i.e. x*x + y*y + z*z = 1." << '\n';
    std::cout << "In theory, you can input any number of points. In practise, please " << '\n';
    std::cout << "limit the number to an integer. Your input will look like : a.out 100" << '\n';
    std::cout << '\n' << '\n';

    p_input1 = NULL;
    p_input2 = NULL;
    p_input3 = NULL;
    result = NULL;

    if (argc < 2)
    {
      //remind end user to provide a valid input.
      std::cerr << "Please enter a valid number, indicated by previous notification" << '\n';
      return ERR_NO_ERROR;
    }
    else
    {
      number = (int)std::atof(argv[1]);
      p_input1 = (float *)std::malloc(number * sizeof(float));
      p_input2 = (float *)std::malloc(number * sizeof(float));
      p_input3 = (float *)std::malloc(number * sizeof(float));
      result = (float *)std::malloc(number * sizeof(float));
    }
    {
      int i, max_index, min_index;
      float max_val, min_val;

      //project number of random points (x, y, z) to according position(x', y', z') on sphere
      genPointsOnUnitSphere(number, p_input1, p_input2, p_input3);

      result[0] = 0;
      //calculate and save the measured length
      for (i = 1; i < number; i++)
      {
        float m, n,t, sum;
        m = p_input1[i] * p_input1[0];
        n = p_input2[i] * p_input2[0];
        t = p_input3[i] * p_input3[0];
        sum = m + n + t;
        result[i] = std::acos(sum);
      }
      //sort out the maxium measured length and according index (x', y', z');
      max_index = min_index = 0;
      max_val = min_val = result[0];
      for (i = 0; i < (number - 1); i++)
      {
        if (result[i] > max_val)
        {
          max_val = result[i];
          max_index = i;
        }
        if (result[i] < min_val)
        {
          min_val = result[i];
          min_index = i;
        }
      }
      //print out the maxium measured length and according index (x, y, z)
      std::cout << "The Maximu Arc Length is: " << max_val << '\n';
      std::cout << "The Maxium index position is: " << p_input1[max_index];
      std::cout << ": " << p_input2[max_index];
      std::cout << ": " << p_input3[max_index] << '\n';

      std::cout << "The Minum Arc Length is:" << min_val << '\n';
      std::cout << "The Minum index position is: " << p_input1[min_index];
      std::cout << ": " << p_input2[min_index];
      std::cout << ": " << p_input3[min_index] << '\n';     
    }

    if (p_input1 != NULL)
      std::free(p_input1);
    if (p_input2 != NULL)
      std::free(p_input2);
    if (p_input3 != NULL)
      std::free(p_input3);
    if (result != NULL)
      std::free(result);

    return ERR_NO_ERROR;
}

void genPointsOnUnitSphere(const int N, float *x, float *y, float *z) {
  if (x == NULL || y == NULL || z == NULL) {
    std::cerr << "invalid pointers, aborting...\n";
    std::exit(1);
  }
  //std::srand(std::time(0));  // trigger the seed
  const int BD = 10000000, BD2 = 2 * BD;
  const float inv_bd = 1.0f / BD;  // not integer division
  for (int i = 0; i < N; ++i) {
    x[i] = (std::rand() % BD2 - BD) * inv_bd;
    y[i] = (std::rand() % BD2 - BD) * inv_bd;
    z[i] = (std::rand() % BD2 - BD) * inv_bd;
    const float len = std::sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
    if (len > 1e-5f) {
      // project on to unit sphere
      x[i] /= len;
      y[i] /= len;
      z[i] /= len;
    } else {
      // too close to zero
      // directly set the point to be (1,0,0)
      x[i] = 1.0f;
      y[i] = z[i] = 0.0f;
    }
  }
}
