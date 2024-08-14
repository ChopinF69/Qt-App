//
// Created by lazar on 25.04.2024.
//

#ifndef LAB9_REPO_H
#define LAB9_REPO_H
#include "domain.h"
#include <bits/stdc++.h>
void testAllRepo();
using std::vector;
class Repo;
class CollectionBooks;
class RepoAbstract;
class RepoNou;

class Repo {
private:
  vector<Book> books;

public:
  /// Constructors
  Repo();

  /// CRUD
  void addBook(const Book &book);
  void removeBook(const Book &book);
  void updateBook(const Book &book1, const Book &book2);
  bool findBook(const Book &book);

  vector<Book> getBooks() const;

  friend class CollectionBooks;
};

/// Tests
void repoTestConstructor();
void repoTestAddBook();
void repoTestRemoveBook();
void repoTestUpdateBook();
void repoTestFindBook();
void repoTestGetBooks();
void repoTestAllRepo();

#include "observer.h"
/// New class for the repository
class CollectionBooks : public Observable {
private:
  vector<Book> booksCollection;

public:
  /// Constructors
  CollectionBooks();

  /// CRUD
  void addBookToCollection(const Book &book);
  void removeBookFromCollection(const Book &book);
  vector<Book> getBooksFromCollection() const;
  void generateRandomBooks(int n);
  void removeAllBooksFromCollection();
};

/// Tests for Collection

void collectionTestConstructor();
void collectionTestAddBookToCollection();
void collectionTestDeleteAllBooksFromCollection();
void coolectionTestUpdateBookFromCollection();
void collectionTestGetBooksFromCollection();
void collectionTestAllCollection();

// Test for lab
void testFrequencyReleaseYear();

/// Repo abstract
class RepoAbstract {
public:
  RepoAbstract();
  // RepoAbstract(const RepoAbstract& repo) = delete;

  // Add a book to the repository
  virtual void addBook(const Book &book) = 0;

  // Remove a book from the repository
  virtual void removeBook(const Book &book) = 0;

  // Update a book from the repository
  virtual void updateBook(const Book &b1, const Book &b2) = 0;

  // Find a book in the repository
  virtual bool findBook(const Book &book) = 0;

  // Get all the books from the repository
  virtual vector<Book> getBooks() const = 0;
};

class RepoNou : public RepoAbstract {
private:
  std::map<std::string, Book> booksMap;
  int probability;

public:
  /// Constructor
  RepoNou();

  /// CRUD
  vector<Book> getBooks() const override;
  void addBook(const Book &book) override;
  void removeBook(const Book &book) override;
  bool findBook(const Book &book) override;
  void updateBook(const Book &b1, const Book &b2) override;
  void setProbability(int probability);
  int getProbability() const;
};

void testRepoNouConstructor();
void testRepoNouAddBook();
void testRepoNouRemoveBook();
void testRepoNouFindBook();
void testRepoNouUpdateBook();
void testRepoNouGetBooks();
void testRepoNouSetProbability();
void testRepoNouGetProbability();
void testAllRepoNou();

#endif // LAB9_REPO_H
