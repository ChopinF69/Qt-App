//
// Created by lazar on 25.04.2024.
//

#ifndef LAB9_SERVICE_H
#define LAB9_SERVICE_H
#include "undo.h"
#include <bits/stdc++.h>
#include <domain.h>
#include <repo.h>
using std::string;

class Service {
private:
  Repo repo;
  // RepoNou repoNou;
  // RepoNou repo;
  CollectionBooks collectionBooks;
  vector<std::unique_ptr<ActionUndo>> undoActions;

public:
  /// CONSTRUCTOR
  Service();
  /// CRUD
  void serviceAddBook(const Book &);
  void serviceRemoveBook(const Book &);
  void serviceUpdateBook(const Book &, const Book &);
  bool serviceFindBook(const Book &);

  vector<Book> serviceGetBooks() const;
  vector<Book> filterBooksByAuthor(string) const;
  vector<Book> filterBooksByGen(string) const;
  vector<Book> filterBooksByYear(int) const;
  vector<Book> sortBooksByYear(int) const;
  vector<Book> sortBooksByGen(int) const;
  vector<Book> sortBooksByAuthor(int) const;
  vector<Book> sortBooksByTitle(int) const;
  /// New functionalities
  void serviceAddBookToCollection(const Book &);
  void serviceRemoveAllBooksFromCollection();
  vector<Book> serviceGetAllBooksFromCollection() const;
  void serviceAddRandomBooksToCollection(int);
  void serviceExportCollectionToHTML(const string &filename);
  void serviceExportCollectionToCSV(const string &filename);

  CollectionBooks &getCollectionBooks() { return collectionBooks; }
  /// Raport
  std::unordered_map<std::string, int> serviceRaport(std::string) const;
  std::unordered_map<std::string, int> serviceMakeRaport();
  /// Undo
  void serviceUndo();
};

/// Tests
void serviceTestConstructor();
void serviceTestAddBook();
void serviceTestRemoveBook();
void serviceTestUpdateBook();
void serviceTestFindBook();
void serviceTestGetBooks();
void serviceTestFilterBooksByAuthor();
void serviceTestSortBooksByYear();
void serviceTestAddBookToCollection();
void serviceTestRemoveAllBooksFromCollection();
void serviceTestGetAllBooksFromCollection();
void serviceTestAddRandomBooksToCollection();
void serviceTestExportCollectionToHTML();
void serviceTestExportCollectionToCSV();
void serviceTestRaport();
void serviceTestUndo();
void testAllService();

#endif // LAB9_SERVICE_H
