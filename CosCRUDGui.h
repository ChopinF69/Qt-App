//
// Created by lazar on 27.05.2024.
//
#pragma once
#ifndef LAB10_COSCRUDGUI_H
#define LAB10_COSCRUDGUI_H
#include <qwidget.h>
#include <qtimer.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>
#include "service.h"
#include "observer.h"
#include <qlistwidget.h>
#include <qboxlayout.h>
class CosCRUDGui : public QWidget, public Observer {
    CollectionBooks& cos;
    QListWidget* lst = new QListWidget;
    QPushButton* btn;
    QPushButton* btnRandom;

    void loadList(const std::vector<Book>& books)
    {
        lst->clear();
        for (const auto& book : books){
            auto item = new QListWidgetItem(QString::fromStdString(book.getTitle() + " - " + book.getAuthor() + " - " + book.getGen() + " " + std::to_string(book.getReleaseYear())));
            lst->addItem(item);
        }
    }

    void initGUI(){
        QVBoxLayout* lyMain = new QVBoxLayout;
        lst = new QListWidget;
        lyMain->addWidget(lst);
        btn = new QPushButton{"Goleste cos"};
        btnRandom = new QPushButton{"Adauga random"};
        lyMain->addWidget(btn);
        lyMain->addWidget(btnRandom);
        setLayout(lyMain);
    }

    void connectSignals(){
        cos.addObserver(this);
        QObject::connect(btn , &QPushButton::clicked , [&](){
            // Aici le stergem
            cos.removeAllBooksFromCollection();
            loadList(cos.getBooksFromCollection());
        });

        QObject::connect(btnRandom , &QPushButton::clicked , [&](){
            cos.generateRandomBooks(2);
            loadList(cos.getBooksFromCollection());
        });
    }
public:
    CosCRUDGui(CollectionBooks& cos) : cos{cos} {
        initGUI();
        connectSignals();
        loadList(cos.getBooksFromCollection());
    }

    void update() override {
        loadList(cos.getBooksFromCollection());
    }
    ~CosCRUDGui() override {
        cos.removeObserver(this);
    }
};
#endif //LAB10_COSCRUDGUI_H
