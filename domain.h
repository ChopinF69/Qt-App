//
// Created by lazar on 25.04.2024.
//

#ifndef LAB9_DOMAIN_H
#define LAB9_DOMAIN_H
#include <bits/stdc.h>
#include <iostream>
class Book {
private:
  std::string title;
  std::string author;
  std::string gen;
  int releaseYear;

public:
  /// Constructors
  Book();
  Book(const Book &book);
  Book(const std::string &title, const std::string &author,
       const std::string &gen, int releaseYear);

  /// Getters
  std::string getTitle() const;
  std::string getAuthor() const;
  std::string getGen() const;
  int getReleaseYear() const;

  /// Setters
  void setTitle(const std::string &title);
  void setAuthor(const std::string &author);
  void setGen(const std::string &gen);
  void setReleaseYear(int releaseYear);
};

void testConstructorBook();
void testGetTitle();
void testGetAuthor();
void testGetGen();
void testGetReleaseYear();
void testSetTitle();
void testSetAuthor();
void testSetGen();
void testSetReleaseYear();
void testAllDomain();

#endif // LAB9_DOMAIN_H
