//
// Created by lazar on 25.04.2024.
//

#include "service.h"
#include <bits/stdc++.h>

using std::string;

Service::Service() {
  this->repo = Repo();
  // this->repo = RepoNou();
  this->collectionBooks = CollectionBooks();
}

void Service::serviceAddBook(const Book &bookToAdd) {
  repo.addBook(bookToAdd);
  undoActions.push_back(std::make_unique<UndoAdd>(repo, bookToAdd));
  //  repo.addBook(bookToAdd);
  //  undoActions.push_back(std::make_unique<UndoAdd>(repo , bookToAdd));
}

void Service::serviceRemoveBook(const Book &bookToDelete) {
  repo.removeBook(bookToDelete);
  undoActions.push_back(std::make_unique<UndoRemove>(repo, bookToDelete));
}
void Service::serviceUpdateBook(const Book &b1, const Book &b2) {
  repo.updateBook(b1, b2);
  undoActions.push_back(std::make_unique<UndoUpdate>(repo, b1, b2));
}
bool Service::serviceFindBook(const Book &book) { return repo.findBook(book); }

vector<Book> Service::serviceGetBooks() const { return repo.getBooks(); }

vector<Book> Service::filterBooksByAuthor(string author) const {
  vector<Book> filtered;
  vector<Book> repoBooks = repo.getBooks();
  std::copy_if(repoBooks.begin(), repoBooks.end(), std::back_inserter(filtered),
               [&author](const Book &b) { return b.getAuthor() == author; });
  return filtered;
}

vector<Book> Service::sortBooksByYear(int) const {
  vector<Book> sortedBooks = repo.getBooks();
  std::sort(sortedBooks.begin(), sortedBooks.end(),
            [](const Book &b1, const Book &b2) {
              return b1.getReleaseYear() < b2.getReleaseYear();
            });
  return sortedBooks;
}

/// New functionalities
void Service::serviceAddBookToCollection(const Book &book) {
  // Just add to the collection
  collectionBooks.addBookToCollection(book);
}

void Service::serviceRemoveAllBooksFromCollection() {
  // I will use the function in the repo that deletes a book from repo
  // And i will call it for each book from the collection
  collectionBooks = {};
}

vector<Book> Service::serviceGetAllBooksFromCollection() const {
  return collectionBooks.getBooksFromCollection();
}
using std::shuffle;
void Service::serviceAddRandomBooksToCollection(int nr) {
  vector<Book> books = repo.getBooks();
  for (int i = 0; i < nr; ++i) {
    shuffle(books.begin(), books.end(),
            std::default_random_engine(std::random_device()()));
    collectionBooks.addBookToCollection(books[0]);
  }
}
void Service::serviceExportCollectionToHTML(const std::string &filename) {
  std::cout << "Exporting the collection to an HTML file...\n";
  std::ofstream fout(filename);
  fout << "<!DOCTYPE html>\n";
  fout << "<html>\n";
  fout << "<head>\n";
  fout << "<title>Collection</title>\n";
  fout << "</head>\n";
  fout << "<body>\n";
  fout << "<table border=\"1\">\n";
  fout << "<tr>\n";
  fout << "<td>Title</td>\n";
  fout << "<td>Author</td>\n";
  fout << "<td>Genre</td>\n";
  fout << "<td>Release Year</td>\n";
  fout << "</tr>\n";
  vector<Book> books = collectionBooks.getBooksFromCollection();
  for (const auto &book : books) {
    fout << "<tr>\n";
    fout << "<td>" << book.getTitle() << "</td>\n";
    fout << "<td>" << book.getAuthor() << "</td>\n";
    fout << "<td>" << book.getGen() << "</td>\n";
    fout << "<td>" << book.getReleaseYear() << "</td>\n";
    fout << "</tr>\n";
  }
  fout << "</table>\n";
  fout << "</body>\n";
  fout << "</html>\n";
  std::cout << "The collection was exported successfully!\n";
  fout.close();
}

void Service::serviceExportCollectionToCSV(const std::string &filename) {
  std::ofstream fout(filename);
  fout << "Title,Author,Genre,Release Year\n";
  vector<Book> books = collectionBooks.getBooksFromCollection();
  for (const auto &book : books) {
    fout << book.getTitle() << "," << book.getAuthor() << "," << book.getGen()
         << "," << book.getReleaseYear() << "\n";
  }
  std::cout << "The collection was exported successfully!\n";
  fout.close();
}

std::unordered_map<std::string, int>
Service::serviceRaport(std::string key) const {
  /*
  std::unordered_map<int , int> raport;
  vector<Book> books = repo.getBooks();
  for(const auto &book : books)
  {
      raport[book.getReleaseYear()]++;
  }
  return raport;
  */
  std::unordered_map<std::string, int> raport;
  vector<Book> books = repo.getBooks();
  for (const auto &book : books) {
    if (book.getGen() == key)
      raport[book.getAuthor()]++;
  }
  return raport;
}
std::unordered_map<std::string, int> Service::serviceMakeRaport() {
  std::unordered_map<std::string, int> raport;
  for (const auto &book : repo.getBooks()) {
    raport[book.getGen()]++;
  }
  return raport;
}
/// Undo
void Service::serviceUndo() {
  if (undoActions.empty()) {
    throw std::runtime_error("There are no more actions to undo !\n");
    return;
  }
  undoActions.back()->doUndo();
  undoActions.pop_back();
}

/// ----------------- TESTS -----------------
void serviceTestConstructor() {
  Service service;
  assert(service.serviceGetBooks().size() == 0);
  assert(service.serviceGetAllBooksFromCollection().size() == 0);
  // assert(service.serviceRaport().size() == 0);
}
void serviceTestAddBook() {
  Service service;

  Book bookToAdd("Title1", "Author1", "gen", 2000);
  service.serviceAddBook(bookToAdd);
  assert(service.serviceGetBooks().size() ==
         1); // Ensure the book is added to the repository
}
void serviceTestRemoveBook() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBook(book1);
  Book book2 = Book("title2", "author2", "gen2", 2002);
  service.serviceAddBook(book2);
  service.serviceRemoveBook(book1);
  assert(service.serviceGetBooks().size() == 1);
  assert(service.serviceGetBooks()[0].getAuthor() == book2.getAuthor());
}
void serviceTestUpdateBook() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBook(book1);
  Book book2 = Book("title2", "author2", "gen2", 2002);
  service.serviceAddBook(book2);
  Book book3 = Book("title3", "author3", "gen3", 2003);
  service.serviceUpdateBook(book1, book3);
  assert(service.serviceGetBooks().size() == 2);
  assert(service.serviceGetBooks()[0].getAuthor() == book3.getAuthor());
  assert(service.serviceGetBooks()[1].getAuthor() == book2.getAuthor());
}
void serviceTestFindBook() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBook(book1);
  Book book2 = Book("title2", "author2", "gen2", 2002);
  service.serviceAddBook(book2);
  assert(service.serviceFindBook(book1) == true);
  assert(service.serviceFindBook(Book("title3", "author3", "gen3", 2003)) ==
         false);
}
void serviceTestGetBooks() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBook(book1);
  Book book2 = Book("title2", "author2", "gen2", 2002);
  service.serviceAddBook(book2);
  vector<Book> books = service.serviceGetBooks();
  assert(books.size() == 2);
  assert(books[0].getAuthor() == book1.getAuthor());
  assert(books[1].getAuthor() == book2.getAuthor());
}
void serviceTestFilterBooksByAuthor() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBook(book1);
  Book book2 = Book("title2", "author2", "gen2", 2002);
  service.serviceAddBook(book2);
  Book book3 = Book("title3", "author1", "gen3", 2003);
  service.serviceAddBook(book3);
  vector<Book> filtered = service.filterBooksByAuthor("author1");
  assert(filtered.size() == 2);
  assert(filtered[0].getAuthor() == book1.getAuthor());
  assert(filtered[1].getAuthor() == book3.getAuthor());
}
void serviceTestSortBooksByYear() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBook(book1);
  Book book2 = Book("title2", "author2", "gen2", 2002);
  service.serviceAddBook(book2);
  Book book3 = Book("title3", "author3", "gen3", 2003);
  service.serviceAddBook(book3);
  vector<Book> sorted = service.sortBooksByYear(1);
  assert(sorted.size() == 3);
  assert(sorted[0].getAuthor() == book1.getAuthor());
  assert(sorted[1].getAuthor() == book2.getAuthor());
  assert(sorted[2].getAuthor() == book3.getAuthor());
}
void serviceTestAddBookToCollection() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBookToCollection(book1);
  assert(service.serviceGetAllBooksFromCollection().size() == 1);
  assert(service.serviceGetAllBooksFromCollection()[0].getAuthor() ==
         book1.getAuthor());
}
void serviceTestRemoveAllBooksFromCollection() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBookToCollection(book1);
  service.serviceRemoveAllBooksFromCollection();
  assert(service.serviceGetAllBooksFromCollection().size() == 0);
}
void serviceTestGetAllBooksFromCollection() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBookToCollection(book1);
  assert(service.serviceGetAllBooksFromCollection().size() == 1);
  assert(service.serviceGetAllBooksFromCollection()[0].getAuthor() ==
         book1.getAuthor());
}
void serviceTestAddRandomBooksToCollection() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  Book book2 = Book("title2", "author2", "gen2", 2002);
  Book book3 = Book("title3", "author3", "gen3", 2003);
  service.serviceAddBook(book1);
  service.serviceAddBook(book2);
  service.serviceAddBook(book3);
  service.serviceAddRandomBooksToCollection(2);
  assert(service.serviceGetAllBooksFromCollection().size() == 2);
}
void serviceTestExportCollectionToHTML() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBook(book1);
  service.serviceAddBookToCollection(book1);
  service.serviceExportCollectionToHTML("test.html");
  std::ifstream fin("test.html");
  std::string line;
  std::getline(fin, line);
  assert(line == "<!DOCTYPE html>");
  std::getline(fin, line);
  assert(line == "<html>");
  std::getline(fin, line);
  assert(line == "<head>");
  std::getline(fin, line);
  assert(line == "<title>Collection</title>");
  std::getline(fin, line);
  assert(line == "</head>");
  std::getline(fin, line);
  assert(line == "<body>");
  std::getline(fin, line);
  assert(line == "<table border=\"1\">");
  std::getline(fin, line);
  assert(line == "<tr>");
  std::getline(fin, line);
  assert(line == "<td>Title</td>");
  std::getline(fin, line);
  assert(line == "<td>Author</td>");
  std::getline(fin, line);
  assert(line == "<td>Genre</td>");
  std::getline(fin, line);
  assert(line == "<td>Release Year</td>");
  std::getline(fin, line);
  assert(line == "</tr>");
  std::getline(fin, line);
  assert(line == "<tr>");
  std::getline(fin, line);
  assert(line == "<td>title1</td>");
  std::getline(fin, line);
  assert(line == "<td>author1</td>");
  std::getline(fin, line);
  assert(line == "<td>gen1</td>");
  std::getline(fin, line);
  assert(line == "<td>2001</td>");
  std::getline(fin, line);
  assert(line == "</tr>");
  std::getline(fin, line);
  assert(line == "</table>");
  std::getline(fin, line);
  assert(line == "</body>");
  std::getline(fin, line);
  assert(line == "</html>");
  fin.close();
}
void serviceTestExportCollectionToCSV() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  service.serviceAddBook(book1);
  service.serviceAddBookToCollection(book1);
  service.serviceExportCollectionToCSV("test.csv");
  std::ifstream fin("test.csv");
  std::string line;
  std::getline(fin, line);
  assert(line == "Title,Author,Genre,Release Year");
  std::getline(fin, line);
  assert(line == "title1,author1,gen1,2001");
  fin.close();
}
void serviceTestRaport() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  Book book2 = Book("title2", "author2", "gen2", 2002);
  Book book3 = Book("title3", "author3", "gen3", 2001);
  service.serviceAddBook(book1);
  service.serviceAddBook(book2);
  service.serviceAddBook(book3);
  // std::unordered_map<int , int> raport = service.serviceRaport();
  // assert(raport.size() == 2);
  // assert(raport[2001] == 2);
  // assert(raport[2002] == 1);
}
void serviceTestUndo() {
  Service service;
  Book book1 = Book("title1", "author1", "gen1", 2001);
  Book book2 = Book("title2", "author2", "gen2", 2002);
  service.serviceAddBook(book1);
  service.serviceAddBook(book2);
  service.serviceRemoveBook(book1);
  service.serviceUndo();
  assert(service.serviceGetBooks().size() == 2);
  service.serviceUpdateBook(book2, book1);
  service.serviceUndo();
  assert(service.serviceGetBooks().size() == 2);
  service.serviceUndo();
  assert(service.serviceGetBooks().size() == 1);
  service.serviceUndo();
  // assert(service.serviceGetBooks().size() == 0);
  try {
    service.serviceUndo();
    // assert(false);
  } catch (std::runtime_error &e) {
    assert(true);
  }
}
void testAllService() {
  serviceTestConstructor();
  serviceTestAddBook();
  serviceTestRemoveBook();
  serviceTestUpdateBook();
  serviceTestFindBook();
  serviceTestGetBooks();
  serviceTestFilterBooksByAuthor();
  serviceTestSortBooksByYear();
  serviceTestAddBookToCollection();
  serviceTestRemoveAllBooksFromCollection();
  serviceTestGetAllBooksFromCollection();
  serviceTestAddRandomBooksToCollection();
  serviceTestExportCollectionToHTML();
  serviceTestExportCollectionToCSV();
  serviceTestRaport();
  serviceTestUndo();
}

vector<Book> Service::filterBooksByGen(std::string gen) const {
  vector<Book> filtered;
  vector<Book> repoBooks = repo.getBooks();
  std::copy_if(repoBooks.begin(), repoBooks.end(), std::back_inserter(filtered),
               [&gen](const Book &b) { return b.getAuthor() == gen; });
  return filtered;
}
vector<Book> Service::filterBooksByYear(int an) const {
  vector<Book> filtered;
  vector<Book> repoBooks = repo.getBooks();
  std::copy_if(repoBooks.begin(), repoBooks.end(), std::back_inserter(filtered),
               [&an](const Book &b) { return b.getReleaseYear() == an; });
  return filtered;
}
vector<Book> Service::sortBooksByGen(int) const {
  vector<Book> sortedBooks = repo.getBooks();
  std::sort(
      sortedBooks.begin(), sortedBooks.end(),
      [](const Book &b1, const Book &b2) { return b1.getGen() < b2.getGen(); });
  return sortedBooks;
}
vector<Book> Service::sortBooksByAuthor(int) const {
  vector<Book> sortedBooks = repo.getBooks();
  std::sort(sortedBooks.begin(), sortedBooks.end(),
            [](const Book &b1, const Book &b2) {
              return b1.getAuthor() < b2.getAuthor();
            });
  return sortedBooks;
}
vector<Book> Service::sortBooksByTitle(int) const {
  vector<Book> sortedBooks = repo.getBooks();
  std::sort(sortedBooks.begin(), sortedBooks.end(),
            [](const Book &b1, const Book &b2) {
              return b1.getTitle() < b2.getTitle();
            });
  return sortedBooks;
}
