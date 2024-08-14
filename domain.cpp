//
// Created by lazar on 25.04.2024.
//

#include "domain.h"
/**
 * Default constructor for a book
 * @return a book with empty fields
 */
Book::Book()
{
    this->title = "";
    this->author = "";
    this->gen = "";
    this->releaseYear = 0;
}



 /**
  * Copy constructor for a book
  * @param book - the book to be copied
  * @return a book with the same fields as the given book
  */
Book::Book(const Book &book)
{
    this->title = book.getTitle();
    this->author = book.getAuthor();
    this->gen = book.getGen();
    this->releaseYear = book.getReleaseYear();
}
/**
 * Constructor for a book
 * @param title - the title of the book
 * @param author - the author of the book
 * @param genre - the genre of the book
 * @param year - the release year of the book
 * @return a book with the given fields
 */
Book::Book(const std::string &title, const std::string &author, const std::string &gen, int releaseYear)
{
    this->title = title;
    this->author = author;
    this->gen = gen;
    this->releaseYear = releaseYear;
}

/**
 * Getter for the title of a book
 * @return the title of the book
 */

std::string Book::getTitle() const
{
    return this->title;
}


/**
 * Getter for the genre of a book
 * @return the genre of the book
 */

std::string Book::getGen() const
{
    return this->gen;
}


/**
 * Getter for the author of a book
 * @return the author of the book
 */


std::string Book::getAuthor() const
{
    return this->author;
}

/**
 * Getter for the release year of a book
 * @return the release year of the book
 */

int Book::getReleaseYear() const
{
    return this->releaseYear;
}
/**
 * Setter for the title of a book
 * @param title - the new title of the book
 */


void Book::setAuthor(const std::string &author)
{
    this->author = author;
}

/**
 * Setter for the genre of a book
 * @param gen - the new genre of the book
 */

void Book::setGen(const std::string &gen)
{
    this->gen = gen;
}

/**
 * Setter for the release year of a book
 * @param releaseYear - the new release year of the book
 */


void Book::setTitle(const std::string &title)
{
    this->title = title;
}

/**
 * Setter for the release year of a book
 * @param releaseYear - the new release year of the book
 */

void Book::setReleaseYear(int releaseYear)
{
    this->releaseYear = releaseYear;
}

/// Tests for the domain class
void testConstructorBook()
{
    Book book;
    assert(book.getTitle() == "");
    assert(book.getAuthor() == "");
    assert(book.getGen() == "");
    assert(book.getReleaseYear() == 0);

    Book book1("title", "author", "gen", 2000);
    assert(book1.getTitle() == "title");
    assert(book1.getAuthor() == "author");
    assert(book1.getGen() == "gen");
    assert(book1.getReleaseYear() == 2000);

    Book book2(book1);
    assert(book2.getTitle() == "title");
    assert(book2.getAuthor() == "author");
    assert(book2.getGen() == "gen");
    assert(book2.getReleaseYear() == 2000);

}

void testGetTitle()
{
    Book book("title", "author", "gen", 2000);
    assert(book.getTitle() == "title");
}

void testGetAuthor()
{
    Book book("title", "author", "gen", 2000);
    assert(book.getAuthor() == "author");
}

void testGetGen()
{
    Book book("title", "author", "gen", 2000);
    assert(book.getGen() == "gen");
}

void testGetReleaseYear()
{
    Book book("title", "author", "gen", 2000);
    assert(book.getReleaseYear() == 2000);
}

void testSetTitle()
{
    Book book;
    book.setTitle("title");
    assert(book.getTitle() == "title");
}

void testSetAuthor()
{
    Book book;
    book.setAuthor("author");
    assert(book.getAuthor() == "author");
}

void testSetGen()
{
    Book book;
    book.setGen("gen");
    assert(book.getGen() == "gen");
}

void testSetReleaseYear()
{
    Book book;
    book.setReleaseYear(2000);
    assert(book.getReleaseYear() == 2000);
}

void testAllDomain()
{
    testConstructorBook();
    testGetTitle();
    testGetAuthor();
    testGetGen();
    testGetReleaseYear();
    testSetTitle();
    testSetAuthor();
    testSetGen();
    testSetReleaseYear();
}
