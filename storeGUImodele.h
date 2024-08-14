//
// Created by lazar on 05.06.2024.
//

#ifndef LAB10_STOREGUIMODELE_H
#define LAB10_STOREGUIMODELE_H

#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <QLabel>
#include <qlabel.h>
#include <qline.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <service.h>
#include "TableModel.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "CosCRUDGui.h"
#include "CosReadOnlyGUI.h"
#include "CosReadOnlyGUI.h"
#include "CosCRUDGui.h"
class StoreGUIModele : public QWidget {
private:
    Service& service;
    TableModel* modelTabel;

    QListView* lstV = new QListView;
    QTableView* tblV = new QTableView;

    QLabel* lblTitle = new QLabel{"Title"};
    QLabel* lblAuthor = new QLabel{"Author"};
    QLabel* lblGenre = new QLabel{"Genre"};
    QLabel* lblReleaseYear = new QLabel{"Release Year"};

    QLineEdit* editTitle;
    QLineEdit* editAuthor;
    QLineEdit* editGenre;
    QLineEdit* editReleaseYear;

    QPushButton* btnAdd;
    QPushButton* btnDelete;
    QPushButton* btnUpdate;

    QGroupBox* groupBox = new QGroupBox{tr("Tip sortare")};

    QRadioButton* radioSrtTitle = new QRadioButton{tr("Title")};
    QRadioButton* radioSrtAuthor = new QRadioButton{tr("Author")};
    QRadioButton* radioSrtGenre = new QRadioButton{tr("Genre")};
    QPushButton* btnSort;

    QLabel* lblFilterGen = new QLabel{"Filter dupa gen"};
    QLineEdit* editFilter;
    QPushButton* btnFilter;

    QLabel* lblFilterAuthor = new QLabel{"Filter dupa autor"};
    QLineEdit* editFilterAuthor;
    QPushButton* btnFilterAuthor;

    QPushButton* btnUndo;
    QPushButton* btnReloadData;

    QPushButton* btnCos;
    QPushButton* addCos;
    QLineEdit* titluCarte;
    QPushButton* addRandomCos;
    QLineEdit* editRandom;
    QPushButton* golesteCos;
    QListWidget* listaCos;
    QLineEdit* editExport;
    QPushButton* exportCos;
    QLabel* lblRandom = new QLabel{"Nr. random"};
    QLabel* lblDenumireCos = new QLabel{"Denumire carte"};
    QLabel* lblExport = new QLabel{"Nume fisier"};
    QLabel* lblTitlu = new QLabel{"Titlu carte"};

    QPushButton* btnCosCRUDGUI;
    QPushButton* btnCosReadOnlyGUI;

    QPushButton* btnAddCoss;
    QPushButton* btnDeleteCos;
    QPushButton* btnGenerateCos;

    void initGUIcmps();
    void connectSignalsSlots();
    void reloadList(const vector<Book>& books);
    void guiAddBook();
    void guiModifyBook();
    void guiDeleteBook();
public:
    StoreGUIModele(Service& service) : service{service} {
        initGUIcmps();
        modelTabel = new TableModel{service.serviceGetBooks()};
        connectSignalsSlots();
        reloadList(service.serviceGetBooks());
        tblV->setModel(modelTabel);
    }
    ~StoreGUIModele() {
        delete modelTabel;
    }
};


#endif //LAB10_STOREGUIMODELE_H
