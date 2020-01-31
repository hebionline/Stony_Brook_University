Dear Professor Chen,

Due to the time limitation, i just can finish one alpha version of homework 5. (For example, currently i only check the row number and colume number are equal or not, not considering the memory access issue) So error handling work which should be implemented in these function has not been finsihed. I will improve it when i find more time. Actually i have NOT USE "rand.hpp" and only use "test1.txt" and "test2.txt" now.

Firstly, put all these files into one folder:
-main.cpp
-Makefile
-Makefile.in
-matrix.cpp
-matrix.hpp
-prog (optional)
-rand.hpp
-rand_usage.cpp
-readme.txt
-test1.txt
-test2.txt

Secondly, cd to this directory and run "make". Makefile will compile and execute the pre-built or newly built executable automatically. You may see some error info in the end but don't be panic because these info is not related with code but with the makefile. I haven't figure out a solution for this now.

The main program will perform following tasks:
step 1: check construction function
step 2: check input and output operator overloading functions
step 3: check size querying function
step 4: check assignment function
step 5: check various operator overloading function
step 6: check free functions



