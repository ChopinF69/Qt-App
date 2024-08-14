//
// Created by lazar on 28.04.2024.
//

#include "validator.h"

bool Validator::validateTitle(const std::string &title)
{
    if(title.empty())
    {
        throw std::runtime_error("Title cannot be empty !\n");
    }
    if(title.size() < 3)
    {
        throw std::runtime_error("Title must have at least 3 characters\n");
    }
    return 1;
}

bool Validator::validateAuthor(const std::string &author)
{
    if(author.empty())
    {
        throw std::runtime_error("Author cannot be empty !\n");
    }
    if(author.size() < 3)
    {
        throw std::runtime_error("Author cannot have less than 3 characters !\n");
    }
    return 1;
}

bool Validator::validateYear(const int &year)
{
    if(year < 0)
    {
        throw std::runtime_error("Year cannot be negative !\n");
    }
    if(year > 2024)
    {
        throw std::runtime_error("Year cannot be greater that 2024 !\n");
    }
    return 1;
}
bool Validator::validateGen(const std::string &gen)
{
    if(gen.empty())
    {
        throw std::runtime_error("Gen cannot be empty !\n");
    }
    if(gen.size() < 3)
    {
        throw std::runtime_error("Gen cannot have less than 3 characters !\n");
    }
    return 1;
}

void testValidateTitle() {
    Validator validator;

    // Test empty title
    try {
        validator.validateTitle("");
        // If the above line doesn't throw an exception, the test fails
     //   assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Title cannot be empty !\n");
    }

    // Test title with less than 3 characters
    try {
        validator.validateTitle("ab");
        // If the above line doesn't throw an exception, the test fails
     //   assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Title must have at least 3 characters\n");
    }

    // Test valid title
    bool result = validator.validateTitle("Valid Title");
    assert(result == true); // Ensure the function returns true for a valid title
}
void testValidateAuthor() {
    Validator validator;

    // Test empty author
    try {
        validator.validateAuthor("");
        // If the above line doesn't throw an exception, the test fails
      //  assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Author cannot be empty !\n");
    }

    // Test author with less than 3 characters
    try {
        validator.validateAuthor("ab");
        // If the above line doesn't throw an exception, the test fails
      //  assert(false);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Author cannot have less than 3 characters !\n");
    }

    // Test valid author
    bool result = validator.validateAuthor("Valid Author");
    assert(result == true); // Ensure the function returns true for a valid author
}
void testValidateGen() {
    Validator validator;

    // Test empty gen
    try {
        validator.validateGen("");
        // If the above line doesn't throw an exception, the test fails
      //  assert(false && "Expected exception not thrown");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Gen cannot be empty !\n");
    }

    // Test gen with less than 3 characters
    try {
        validator.validateGen("ab");
        // If the above line doesn't throw an exception, the test fails
       // assert(false && "Expected exception not thrown");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Gen cannot have less than 3 characters !\n");
    }

    // Test valid gen
    bool result = validator.validateGen("Valid Gen");
    assert(result == true); // Ensure the function returns true for a valid gen
}
void testValidateYear() {
    Validator validator;

    // Test negative year
    try {
        validator.validateYear(-1);
        // If the above line doesn't throw an exception, the test fails
       // assert(false && "Expected exception not thrown");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Year cannot be negative !\n");
    }

    // Test year greater than 2024
    try {
        validator.validateYear(2025);
        // If the above line doesn't throw an exception, the test fails
       // assert(false && "Expected exception not thrown");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Year cannot be greater that 2024 !\n");
    }

    // Test valid year
    bool result = validator.validateYear(2024);
    assert(result == true); // Ensure the function returns true for a valid year
}
void testAllValidator() {
    testValidateTitle();
    // Add more tests for the other validation functions
     testValidateAuthor();
     testValidateGen();
     testValidateYear();
}