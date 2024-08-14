//
// Created by lazar on 25.04.2024.
//

#include "ui.h"
#include "validator/validator.h"
void printMenu()
{
    std::cout << "This is the menu :\n";
    std::cout << "0 . Exit\n";
    std::cout << "1 . Add a book\n";
    std::cout << "2 . Remove a book\n";
    std::cout << "3 . Search if a book exists\n";
    std::cout << "4 . Modify a book\n";
    std::cout << "5 . Print all books\n";
    std::cout << "6 . Filter books by author\n";
    std::cout << "7 . Sort books by year of release\n";
    std::cout << "8 . Add a book to the collection\n";
    std::cout << "9 . Remove all books from collection\n";
    std::cout << "10 . Print all books from collection\n";
    std::cout << "11 . Generate a given number of books to the collection\n";
    std::cout << "12 . Export the collection to a file\n";
    std::cout << "13 . Make a raport about the frequench of the release year\n";
    std::cout << "14 . Undo\n";
}

void UI::run()
{
    Validator validator;
    int command = 0;
    printMenu();
    std::cin >> command;
    while(1)
    {
        if(command == 0)
        {
            break;
        }
        else if(command == 1)
        {
            // Add a book
            std::string title;
            std::string author;
            std::string gen;
            int releaseYear = 0;
            std::cout << "Enter the title of the book : ";
            try {
                std::cin >> title;
                Validator::validateTitle(title);
            }
            catch (std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }

            std::cout << "Enter the author of the book : ";
            try {
                std::cin >> author;
                Validator::validateAuthor(author);
            }
            catch (std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }

            std::cout << "Enter the gen of the book : ";
            try {
                std::cin >> gen;
                Validator::validateGen(gen);
            }
            catch (std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }

            std::cout << "Enter the release year of the book : ";
            try {
                std::cin >> releaseYear;
                Validator::validateYear(releaseYear);
            }
            catch (std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }
            service.serviceAddBook(Book(title , author , gen , releaseYear));
        }
        else if(command == 2)
        {
            std::string title;
            std::cout << "Enter the title of the book you want to remove : ";
            try {
                std::cin >> title;
                Validator::validateTitle(title);
            }
            catch (std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }

            vector<Book> books = service.serviceGetBooks();
            std::string author;
            std::string gen;
            int releaseYear;;
            for(const auto & book : books)
            {
                if(book.getTitle() == title)
                {
                    author = book.getAuthor();
                    gen = book.getGen();
                    releaseYear = book.getReleaseYear();
                    break;
                }
            }
            Book bookToDelete(title , author , gen , releaseYear);
            service.serviceRemoveBook(bookToDelete);
        }
        else if(command == 3)
        {
            //Search a book based on title
            std::string title;
            std::cout << "Enter the title of the book you want to search : ";
            try {
                std::cin >> title;
                Validator::validateTitle(title);
            }
            catch(std::runtime_error & e)
            {
                std::cout << e.what() ;
                continue;
            }
            bool ok = service.serviceFindBook(Book(title , "" , "" , 0));
            if(ok == true)
            {
                std::cout << "The book exists in the repo !\n";
            }
            else
            {
                std::cout << "The book doesn't exist in the repo !\n";
            }
        }
        else if(command == 4)
        {
            // Modify a book
            std::string title;
            std::string newTitle;
            std::string newAuthor;
            std::string newGen;
            int newReleaseYear;
            std::cout << "Enter the title of the book you want to modify : ";
            try {
                std::cin >> title;
                Validator::validateTitle(title);
            }
            catch(std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }
            std::cout << "Enter the new title of the book : ";
            try {
                std::cin >> newTitle;
                Validator::validateTitle(newTitle);
            }
            catch(std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }
            std::cout << "Enter the new author of the book : ";
            try {
                std::cin >> newAuthor;
                Validator::validateAuthor(newAuthor);
            }
            catch(std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }
            std::cout << "Enter the new gen of the book : ";
            try {
                std::cin >> newGen;
                Validator::validateGen(newGen);
            }
            catch(std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }
            std::cout << "Enter the new release year of the book : ";
            try {
                std::cin >> newReleaseYear;
                Validator::validateYear(newReleaseYear);
            }
            catch(std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }
            // I wan to get the autor and gen of the book that I want to modify
            vector<Book> books = service.serviceGetBooks();
            std::string oldAuthor;
            std::string oldGen;
            int oldReleaseYear;
            for(const auto & book : books)
            {
                if(book.getTitle() == title)
                {
                    oldAuthor = book.getAuthor();
                    oldGen = book.getGen();
                    oldReleaseYear = book.getReleaseYear();
                    break;
                }
            }
            Book book1(title , oldAuthor , oldGen , oldReleaseYear);
            Book book2(newTitle , newAuthor , newGen , newReleaseYear);
            service.serviceUpdateBook(book1 , book2);
        }
        else if(command == 5)
        {
            // Print all books
            vector<Book> books = service.serviceGetBooks();
            for(const auto & b : books)
            {
                std::cout << b.getTitle() << " " << b.getAuthor() << " " << b.getGen() << " " << b.getReleaseYear() << "\n";
            }
        }
        else if(command == 6)
        {
            // Filter books by author
            std::string author;
            std::cout << "Enter the author : ";
            try {
                std::cin >> author;
                Validator::validateAuthor(author);
            }
            catch(std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }
            vector<Book> books = service.filterBooksByAuthor(author);
            for(const auto & b : books)
            {
                std::cout << b.getTitle() << " " << b.getAuthor() << " " << b.getGen() << " " << b.getReleaseYear() << "\n";
            }
        }
        else if(command == 7)
        {
            // Sort books by year of release
            int year ;
            try {
                std::cin >> year;
                Validator::validateYear(year);
            }
            catch(std::runtime_error & e)
            {
                std::cout << e.what();
                continue;
            }
        }
        else if(command == 8) {
            // Add a book to the collection
            std::string title;
            std::string gen;
            std::string author;
            int releaseYear;
            std::cout << "Enter the title of the book : ";
            try {
                std::cin >> title;
                Validator::validateTitle(title);
            }
            catch (std::runtime_error &e) {
                std::cout << e.what();
                continue;
            }
            // lets get the book from the repo
            vector<Book> books = service.serviceGetBooks();
            for (const auto &b : books) {
                if (b.getTitle() == title) {
                    author = b.getAuthor();
                    gen = b.getGen();
                    releaseYear = b.getReleaseYear();
                    break;
                }
            }
            try {
                service.serviceAddBookToCollection(Book(title, author, gen, releaseYear));
            }
            catch (std::runtime_error &e) {
                std::cout << e.what();
            }
        }
        else if(command == 9)
        {
            // Remove all books from collection
            service.serviceRemoveAllBooksFromCollection();
            std::cout << "All books were removed from the collection !\n";
        }
        else if(command == 10)
        {
            // Print all books from collection
            vector<Book> books = service.serviceGetAllBooksFromCollection();
            for(const auto & b : books)
            {
                std::cout << b.getTitle() << " " << b.getAuthor() << " " << b.getGen() << " " << b.getReleaseYear() << "\n";
            }
        }
        else if(command == 11)
        {
            // Generate a given number of books to the collection
            int number;
            std::cout << "Enter the number of books you want to generate : ";
            std::cin >> number;
            service.serviceAddRandomBooksToCollection(number);
        }
        else if(command == 12)
        {
            // we have 2 options : html / csv
            std::cout << "Do you want to export the collection to a html file or a csv file ?\n";
            int optionExport;
            std::cout << "1 -> HTML\n";
            std::cout << "2 -> CSV\n";
            std::cin >> optionExport;
            if(optionExport == 1)
            {
                std::string filename;
                std::cout << "Enter the name of the file : ";
                std::cin >> filename;
                service.serviceExportCollectionToHTML(filename);
            }
            else if(optionExport == 2)
            {
                std::string filename;
                std::cout << "Enter the name of the file : ";
                std::cin >> filename;
                service.serviceExportCollectionToCSV(filename);
            }
            else
            {
                std::cout << "Invalid command !\n";
            }
        }
        else if(command == 13)
        {
            // Make a raport about the frequency of the release year
            /*std::unordered_map<int , int> raport = service.serviceRaport();
            for(const auto & r : raport)
            {
                std::cout << "Year : " << r.first << " and the number is : " << r.second << "\n";
            }*/
        }
        else if(command == 14)
        {
            // Undo
            try{
                service.serviceUndo();
            }
            catch(std::runtime_error & e) {
                std::cout << e.what();
            }

        }
        else
        {
            std::cout << "Invalid command !\n";
        }
        std::cout << "Enter a new command !\n";
        std::cin >> command;
    }
}

