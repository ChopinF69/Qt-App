//
// Created by lazar on 15.05.2024.
//

#ifndef LAB10_NEWGUI_H
#define LAB10_NEWGUI_H

#pragma once
#include "CosCRUDGui.h"
#include "CosReadOnlyGUI.h"
#include "service.h"
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QStringList>
#include <QTableWidget>
#include <QtWidgets/QApplication>
#include <qlistwidget.h>
#include <string>
#include <vector>
using std::string;
using std::vector;
class BookGUI : public QWidget {
private:
  Service &service;
  QVBoxLayout *lyRight;
  QLabel *lblAuthor = new QLabel{"Author"};
  QLabel *lblTitle = new QLabel{"Title"};
  QLabel *lblGen = new QLabel{"Gen"};
  QLabel *lblReleaseYear = new QLabel{"Release Year"};

  QLineEdit *editAuthor;
  QLineEdit *editTitle;
  QLineEdit *editGen;
  QLineEdit *editReleaseYear;

  QPushButton *btnAdd;
  QPushButton *btnDelete;
  QPushButton *btnUpdate;

  QGroupBox *groupBox = new QGroupBox(tr("Tip sortare"));

  QRadioButton *radioBtnTitle = new QRadioButton(tr("Title"));
  QRadioButton *radioBtnAuthor = new QRadioButton(tr("Author"));
  QRadioButton *radioBtnGen = new QRadioButton(tr("Gen"));
  QRadioButton *radioBtnReleaseYear = new QRadioButton(tr("Release year"));
  // QRadioButton* radioBtnGen = new QRadioButton(tr("Gen"));
  //  3 butoane pentru fiecare tip de sortare
  //  author gen an
  QPushButton *btnSortYear;
  QPushButton *btnSortAuthor;
  QPushButton *btnSortGen;
  // doar o filtrare
  QLabel *lblFilter = new QLabel{"Filter"};
  QLineEdit *editFilter;
  QPushButton *btnFilterYear;
  QPushButton *btnFilterAuthor;
  QPushButton *btnFilterGen;

  QPushButton *btnReloadData;
  // Astea sunt genurile
  QPushButton *btnDinamice[10];

  QPushButton *btnUndo;

  // pentru tabel
  QTableWidget *tableBooks;
  // pentru lista
  QListWidget *listBooks;

  QPushButton *btnCos;
  QPushButton *adaugaCos;
  QLineEdit *titluCos;

  QPushButton *adaugaRandomCos;
  QLineEdit *numarRandom;
  QPushButton *golesteCos;
  QListWidget *listaCos;
  QLineEdit *editExport;
  QPushButton *exportaCos;

  QLabel *lblRandom = new QLabel{"Numar oferte random : "};
  QLabel *lblExport = new QLabel{"Nume fisier : "};

  // Pentru lab 13
  QPushButton *btnCosCRUDGui;
  QPushButton *btnCosReadOnlyGui;

  CosCRUDGui *fereastraCos;
  HistogramGUI *fereastraFiguri;

  QPushButton *btnAddCos;
  QPushButton *btnDeleteCos;
  QPushButton *btnUpdateCos;

  void initGUI();
  void connectingSignalsSlots();

  void reloadBooks(vector<Book> books);
  void reloadBooksCos(vector<Book> books);

  // Variabila pentru butoane dinaimce
  int nrButoaneDinamice = 0;

public:
  BookGUI(Service &service) : service{service} {
    initGUI();
    connectingSignalsSlots();
    reloadBooks(service.serviceGetBooks());
  }
  void guiAddBook();
  void guiDeleteBook();
  void guiUpdateBook();
  // For run
  void show();
};

#endif // LAB10_NEWGUI_H
