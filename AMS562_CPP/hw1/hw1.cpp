//CopyRight: Bin Lu @SBU AMS Sep 20th, 2018
//A simple information collection program as a pratice for study


//#include "stdafx.h"
#include <iostream>
#include <string> 

int main() 
{
    std::string str_first_name,str_last_name;
    std::string str_year, str_month, str_date;
    std::string str_self_intro;

    //ask for first name and second name, then save end users' input
    std::cout << "Please enter your first name and last name: ";
    std::cin >> str_first_name >> str_last_name;

    //ask for birthday, year/month/date, then save end users' input
    std::cout << "Please enter your birthday in number - year: ";
    std::cin >> str_year;
    std::cout << "Please enter your birthday in number - month: ";
    std::cin >> str_month;
    std::cout << "Please enter your birthday in number - date: ";
    std::cin >> str_date;

    //ask for self-introduction, then save end users' input
    std::cin.ignore();
    std::cout << "Please enter your self-introduction: ";
    std::getline(std::cin, str_self_intro);

    //print all of input information 
    std::cout << "Title: " << str_first_name << ' ' << str_last_name << '\n';
    std::cout << '\t' << "DOB: " << str_year << '\\' << str_month << '\\' << str_date << '\n';
    std::cout << '\t' << "Bio: " << str_self_intro << '\n';

    return 0;
}