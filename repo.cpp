//
// Created by lazar on 25.04.2024.
//

#include "repo.h"
#include <bits/stdc++.h>

using std::string;
Repo::Repo() { this->books = {}; }

void Repo::addBook(const Book &book) {
  /// Lets check if the book already exists
  for (int i = 0; i < books.size(); ++i) {
    if (book.getTitle() == books[i].getTitle()) {
      throw std::runtime_error("The book already exists !");
    }
  }
  books.push_back(book);
}

void Repo::removeBook(const Book &book) {
  // Here i will remove the book from the repo
  bool exists = false;
  for (int i = 0; i < books.size(); ++i) {
    Book b = books[i];
    if (b.getTitle() == book.getTitle()) {
      books.erase(books.begin() + i);
      exists = true;
    }
  }
}
void Repo::updateBook(const Book &book1, const Book &book2) {
  bool exists = false;
  for (int i = 0; i < books.size(); ++i) {
    Book book = books[i];
    if (book.getTitle() == book1.getTitle()) {
      books[i] = book2;
      exists = true;
    }
  }
}

bool Repo::findBook(const Book &book) {
  for (const auto &b : books) {
    if (b.getTitle() == book.getTitle()) {
      return true;
    }
  }
  return false;
}

vector<Book> Repo::getBooks() const { return books; }

/// --------------------------------------------------------------------------------
/// Now for collection
CollectionBooks::CollectionBooks() { this->booksCollection = {}; }
void CollectionBooks::addBookToCollection(const Book &book) {
  booksCollection.push_back(book);
  notify();
}

void CollectionBooks::removeBookFromCollection(const Book &book) {
  bool exists = false;
  for (int i = 0; i < booksCollection.size(); ++i) {
    Book b = booksCollection[i];
    if (b.getTitle() == book.getTitle()) {
      booksCollection.erase(booksCollection.begin() + i);
      exists = true;
    }
  }
  notify();
}

vector<Book> CollectionBooks::getBooksFromCollection() const {
  return booksCollection;
}

/// -----------------------------------------------------------------------------------
/// Now for the abstract repo
RepoAbstract::RepoAbstract() {
  // Empty constructor
}
RepoNou::RepoNou() {
  this->probability = 0;
  this->booksMap = {};
}

void RepoNou::addBook(const Book &book) {
  std::srand(std::time(nullptr));
  int random = std::rand() % 100;
  if (random <= probability) {
    throw std::runtime_error("The book cannot be added to the repository !");
  }
  booksMap[book.getTitle()] = book;
}

void RepoNou::removeBook(const Book &book) {
  std::srand(std::time(nullptr));
  int random = std::rand() % 100;
  if (random <= probability) {
    throw std::runtime_error(
        "The book cannot be removed from the repository !");
  }
  booksMap.erase(book.getTitle());
}

bool RepoNou::findBook(const Book &book) {
  std::srand(std::time(nullptr));
  int random = std::rand() % 100;
  if (random <= probability) {
    throw std::runtime_error("The book cannot be found in the repository !");
  }
  return booksMap.find(book.getTitle()) != booksMap.end();
}

void RepoNou::updateBook(const Book &b1, const Book &b2) {
  std::srand(std::time(nullptr));
  int random = std::rand() % 100;
  if (random <= probability) {
    throw std::runtime_error("The book cannot be updated in the repository !");
  }
  booksMap[b1.getTitle()] = b2;
}

std::vector<Book> RepoNou::getBooks() const {
  std::srand(std::time(nullptr));
  int random = std::rand() % 100;
  if (random <= probability) {
    throw std::runtime_error(
        "The books cannot be retrieved from the repository !");
  }
  std::vector<Book> books;
  for (const auto &b : booksMap) {
    books.push_back(b.second);
  }
  return books;
}
int RepoNou::getProbability() const { return probability; }
void RepoNou::setProbability(int probability) {
  this->probability = probability;
}

void testAllRepo() {
  repoTestAllRepo();
  collectionTestAllCollection();
  testAllRepoNou();
}
///-----------------------------------------------------------------------------------
/// Now for the tests
void repoTestConstructor() {
  Repo repo;
  assert(repo.getBooks().size() == 0);
}
void repoTestAddBook() {
  Repo repo;
  Book book{"title", "author", "gen", 2000};
  repo.addBook(book);
  assert(repo.getBooks().size() == 1);
  assert(repo.getBooks()[0].getTitle() == "title");
  assert(repo.getBooks()[0].getAuthor() == "author");
  assert(repo.getBooks()[0].getGen() == "gen");
  assert(repo.getBooks()[0].getReleaseYear() == 2000);
  Book book2("title", "author", "gen", 2000);
  try {
    repo.addBook(book2);
  } catch (std::runtime_error &error) {
    assert(true);
  }
}
void repoTestRemoveBook() {
  Repo repo;
  Book book{"title", "author", "gen", 2000};
  repo.addBook(book);
  repo.removeBook(book);
  assert(repo.getBooks().size() == 0);
}
void repoTestUpdateBook() {
  Repo repo;
  Book book1{"title", "author", "gen", 2000};
  Book book2{"title2", "author2", "gen2", 2002};
  repo.addBook(book1);
  repo.updateBook(book1, book2);
  assert(repo.getBooks().size() == 1);
  assert(repo.getBooks()[0].getTitle() == "title2");
  assert(repo.getBooks()[0].getAuthor() == "author2");
  assert(repo.getBooks()[0].getGen() == "gen2");
  assert(repo.getBooks()[0].getReleaseYear() == 2002);
}
void repoTestFindBook() {
  Repo repo;
  Book book{"title", "author", "gen", 2000};
  repo.addBook(book);
  assert(repo.findBook(book) == true);
  assert(repo.findBook(Book("bbb", "bbb", "bbb", 1)) == false);
}
void repoTestGetBooks() {
  Repo repo;
  Book book{"title", "author", "gen", 2000};
  repo.addBook(book);
  assert(repo.getBooks().size() == 1);
  assert(repo.getBooks()[0].getTitle() == "title");
  assert(repo.getBooks()[0].getAuthor() == "author");
  assert(repo.getBooks()[0].getGen() == "gen");
  assert(repo.getBooks()[0].getReleaseYear() == 2000);
}
void repoTestAllRepo() {
  repoTestConstructor();
  repoTestAddBook();
  repoTestRemoveBook();
  repoTestUpdateBook();
  repoTestFindBook();
  repoTestGetBooks();
}
/// Tests for collection
void collectionTestConstructor() {
  CollectionBooks collection;
  assert(collection.getBooksFromCollection().size() == 0);
}
void collectionTestAddBookToCollection() {
  CollectionBooks collection;
  Book book{"title", "author", "gen", 2000};
  collection.addBookToCollection(book);
  assert(collection.getBooksFromCollection().size() == 1);
  assert(collection.getBooksFromCollection()[0].getTitle() == "title");
  assert(collection.getBooksFromCollection()[0].getAuthor() == "author");
  assert(collection.getBooksFromCollection()[0].getGen() == "gen");
  assert(collection.getBooksFromCollection()[0].getReleaseYear() == 2000);
}
void collectionTestDeleteAllBooksFromCollection() {
  CollectionBooks collection;
  Book book{"title", "author", "gen", 2000};
  collection.addBookToCollection(book);
  collection.removeBookFromCollection(book);
  assert(collection.getBooksFromCollection().size() == 0);
}
void coolectionTestUpdateBookFromCollection() {
  CollectionBooks collection;
  Book book1{"title", "author", "gen", 2000};
  Book book2{"title2", "author2", "gen2", 2002};
  collection.addBookToCollection(book1);
  collection.addBookToCollection(book2);
  collection.removeBookFromCollection(book1);
  assert(collection.getBooksFromCollection().size() == 1);
  assert(collection.getBooksFromCollection()[0].getTitle() == "title2");
  assert(collection.getBooksFromCollection()[0].getAuthor() == "author2");
  assert(collection.getBooksFromCollection()[0].getGen() == "gen2");
  assert(collection.getBooksFromCollection()[0].getReleaseYear() == 2002);
}
void collectionTestGetBooksFromCollection() {
  CollectionBooks collection;
  Book book{"title", "author", "gen", 2000};
  collection.addBookToCollection(book);
  assert(collection.getBooksFromCollection().size() == 1);
  assert(collection.getBooksFromCollection()[0].getTitle() == "title");
  assert(collection.getBooksFromCollection()[0].getAuthor() == "author");
  assert(collection.getBooksFromCollection()[0].getGen() == "gen");
  assert(collection.getBooksFromCollection()[0].getReleaseYear() == 2000);
}
void collectionTestAllCollection() {
  collectionTestConstructor();
  collectionTestAddBookToCollection();
  collectionTestDeleteAllBooksFromCollection();
  coolectionTestUpdateBookFromCollection();
  collectionTestGetBooksFromCollection();
}

/// Test for RepoNou
void testRepoNouConstructor() {
  RepoNou repoNou;
  assert(repoNou.getBooks().size() == 0);
  assert(repoNou.getProbability() == 0);
}
void testRepoNouAddBook() {
  RepoNou repo;
  Book book("Title", "Author", "gen", 2024);

  // Test adding a book under normal conditions
  repo.addBook(book);
  assert(repo.findBook(book) == true);

  // Test adding a book when the probability condition is met
  repo.setProbability(100); // Ensure the probability is 100%
  try {
    repo.addBook(book);
    // If the above line doesn't throw an exception, the test fails
    // assert(false && "Expected exception not thrown");
  } catch (const std::runtime_error &e) {
    // The test passes if an exception is thrown
    assert(true);
  }
}
void testRepoNouRemoveBook() {
  RepoNou repoNou;
  Book book{"title", "author", "gen", 2000};
  Book book2{"title2", "author2", "gen2", 2002};
  repoNou.addBook(book);
  repoNou.setProbability(100);
  try {
    repoNou.removeBook(book);
  } catch (std::runtime_error &error) {
    assert(true);
  }
  repoNou.setProbability(0);
  repoNou.addBook(book);
  repoNou.removeBook(book);
  assert(repoNou.findBook(book) == false);
}
void testRepoNouFindBook() {
  RepoNou repoNou;
  Book book{"title", "author", "gen", 2000};
  repoNou.addBook(book);
  repoNou.setProbability(100);
  try {
    repoNou.findBook(book);
  } catch (std::runtime_error &error) {
    assert(true);
  }
}
void testRepoNouUpdateBook() {
  RepoNou repoNou;
  Book book1{"title", "author", "gen", 2000};
  Book book2{"title2", "author2", "gen2", 2002};
  repoNou.addBook(book1);
  repoNou.setProbability(100);
  try {
    repoNou.updateBook(book1, book2);
  } catch (std::runtime_error &error) {
    assert(true);
  }
  repoNou.setProbability(0);
  repoNou.updateBook(book1, book2);
  assert(repoNou.findBook(book1) == true);
}
void testRepoNouSetProbability() {
  RepoNou repoNou;
  repoNou.setProbability(50);
  assert(repoNou.getProbability() == 50);
}
void testRepoNouGetBooks() {
  RepoNou repoNou;
  Book book{"title", "author", "gen", 2000};
  repoNou.addBook(book);
  repoNou.setProbability(0);
  assert(repoNou.getBooks().size() == 1);
  assert(repoNou.getBooks()[0].getTitle() == "title");
  assert(repoNou.getBooks()[0].getAuthor() == "author");
  assert(repoNou.getBooks()[0].getGen() == "gen");
  assert(repoNou.getBooks()[0].getReleaseYear() == 2000);
  repoNou.setProbability(100);
  try {
    repoNou.getBooks();
  } catch (std::runtime_error &error) {
    assert(true);
  }
}
void testAllRepoNou() {
  testRepoNouConstructor();
  testRepoNouAddBook();
  testRepoNouRemoveBook();
  testRepoNouFindBook();
  testRepoNouUpdateBook();
  testRepoNouSetProbability();
  testRepoNouGetBooks();
}

void CollectionBooks::generateRandomBooks(int n) {
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    int index = rand() % booksCollection.size();
    Book book = booksCollection[index];
    addBookToCollection(book);
  }
  notify();
}

void CollectionBooks::removeAllBooksFromCollection() {
  booksCollection.clear();
  notify();
}
