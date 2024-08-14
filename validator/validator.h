//
// Created by lazar on 28.04.2024.
//

#ifndef LAB9_VALIDATOR_H
#define LAB9_VALIDATOR_H
#include <bits/stdc++.h>
class Validator
{
public:
  //  static void validateBook(const std::string & title , const std::string & author , const std::string & gen , const int & year);
    static bool validateTitle(const std::string & title);
    static bool validateAuthor(const std::string & author);
    static bool validateGen(const std::string & gen);
    static bool validateYear(const int &);
};
void testAllValidator();
#endif //LAB9_VALIDATOR_H
