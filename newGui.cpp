//
// Created by lazar on 15.05.2024.
//

#include "newGui.h"
#include <QMessageBox>
#include <QString>
#include <set>
void BookGUI::initGUI() {
  // Main layout
  QHBoxLayout *lyMain = new QHBoxLayout;
  this->setLayout(lyMain);

  // left part of the window , pentru care setam un layout vertical
  QWidget *left = new QWidget;
  QVBoxLayout *lyLeft = new QVBoxLayout;
  left->setLayout(lyLeft);

  QWidget *form = new QWidget;
  QFormLayout *lyForm = new QFormLayout;
  form->setLayout(lyForm);
  editTitle = new QLineEdit;
  editAuthor = new QLineEdit;
  editGen = new QLineEdit;
  editReleaseYear = new QLineEdit;

  // Title
  lyForm->addRow(lblTitle, editTitle);
  // Autor
  lyForm->addRow(lblAuthor, editAuthor);
  // Gen
  lyForm->addRow(lblGen, editGen);
  // An aparitie
  lyForm->addRow(lblReleaseYear, editReleaseYear);

  btnAdd = new QPushButton{"Adauga o carte"};
  lyForm->addWidget(btnAdd);
  btnUpdate = new QPushButton{"Modifica o carte"};
  lyForm->addWidget(btnUpdate);
  btnDelete = new QPushButton{"Sterge o carte"};
  lyForm->addWidget(btnDelete);
  lyLeft->addWidget(form);

  // Cream un GroupBox pentru radiobuttons care corespund sortarii
  QVBoxLayout *lyRadioBox = new QVBoxLayout;
  this->groupBox->setLayout(lyRadioBox);
  lyRadioBox->addWidget(radioBtnReleaseYear);
  lyRadioBox->addWidget(radioBtnAuthor);
  lyRadioBox->addWidget(radioBtnGen);

  btnSortYear = new QPushButton{"Sorteaza dupa an"};
  lyRadioBox->addWidget(btnSortYear);
  btnSortAuthor = new QPushButton{"Sorteaza dupa autor"};
  lyRadioBox->addWidget(btnSortAuthor);
  btnSortGen = new QPushButton{"Sorteaza dupa gen"};
  lyRadioBox->addWidget(btnSortGen);

  // Adaugam acest grup in partea stanga , dupa form
  lyLeft->addWidget(groupBox);
  // Cream un form pentru filtrari
  QWidget *formFilter = new QWidget;
  QFormLayout *lyFormFilter = new QFormLayout;
  formFilter->setLayout(lyFormFilter);

  editFilter = new QLineEdit();
  lyFormFilter->addRow(lblFilter, editFilter);
  btnFilterYear = new QPushButton{"Filtreaza dupa an"};
  lyFormFilter->addWidget(btnFilterYear);
  btnFilterAuthor = new QPushButton{"Filtreaza dupa autor"};
  lyFormFilter->addWidget(btnFilterAuthor);
  btnFilterGen = new QPushButton{"Filtreaza dupa gen"};
  lyFormFilter->addWidget(btnFilterGen);
  lyLeft->addWidget(formFilter);

  // Btuon pentru reload data
  btnReloadData = new QPushButton("Reincarca datele");
  lyLeft->addWidget(btnReloadData);

  btnUndo = new QPushButton("Undo");
  lyLeft->addWidget(btnUndo);

  // Pentru cos de acum
  btnCos = new QPushButton("Wishlist");
  adaugaCos = new QPushButton("Adauga in wishlist");
  titluCos = new QLineEdit;
  adaugaRandomCos = new QPushButton("Adauga random in wishlist");
  numarRandom = new QLineEdit;
  golesteCos = new QPushButton("Goleste wishlist");
  editExport = new QLineEdit;

  this->listaCos = new QListWidget();
  exportaCos = new QPushButton("Exporta wishlist");

  // Pentru laborator 13
  btnCosCRUDGui = new QPushButton("Cos CRUD GUI");
  lyLeft->addWidget(btnCosCRUDGui);

  btnCosReadOnlyGui = new QPushButton("Cos ReadOnly GUI");
  lyLeft->addWidget(btnCosReadOnlyGui);
  // Componenta right - contine doar tabelul cu oferte
  QWidget *right = new QWidget;
  lyRight = new QVBoxLayout;
  right->setLayout(lyRight);
  int nrCol = 4;
  int nrRow = 10;
  this->tableBooks = new QTableWidget{nrRow, nrCol};

  // Setam headerul tabelului
  QStringList tableHeader;
  tableHeader << "Title" << "Author" << "Gen" << "Release Year";
  this->tableBooks->setHorizontalHeaderLabels(tableHeader);

  // Acum vreau sa fac lista ca sa am pe langa tableBooks
  this->listBooks = new QListWidget;
  lyRight->addWidget(listBooks);

  // optiune pentru a se redimensiona automat coloanele
  this->tableBooks->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  this->listBooks->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);
  for (int i = 0; i < 10; ++i) {
    btnDinamice[i] = new QPushButton;
    lyRight->addWidget(btnDinamice[i]);
    btnDinamice[i]->setVisible(false);
  }

  // Trebuie sa generam raportul
  std::unordered_map<std::string, int> raport = service.serviceMakeRaport();
  int row = 0;
  for (const auto &[gen, contor] : raport) {
    ++row;
    btnDinamice[row]->setText(QString::fromStdString(gen));

    if (contor != 0)
      btnDinamice[row]->setVisible(true);
    else
      btnDinamice[row]->setVisible(false);
  }

  lyRight->addWidget(tableBooks);

  lyRight->addWidget(btnCos);
  lyMain->addWidget(left);
  lyMain->addWidget(right);
}
// Connect signals and slots
void BookGUI::connectingSignalsSlots() {
  QObject::connect(btnAdd, &QPushButton::clicked, this, &BookGUI::guiAddBook);
  QObject::connect(btnDelete, &QPushButton::clicked, this,
                   &BookGUI::guiDeleteBook);
  QObject::connect(btnUpdate, &QPushButton::clicked, this,
                   &BookGUI::guiUpdateBook);

  QObject::connect(btnUndo, &QPushButton::clicked, this, [&]() {
    service.serviceUndo();
    reloadBooks(service.serviceGetBooks());
  });
  /// Sortare
  QObject::connect(btnSortYear, &QPushButton::clicked, this, [&]() {
    if (radioBtnReleaseYear->isChecked()) {
      reloadBooks(service.sortBooksByYear(1));
    }
  });
  QObject::connect(btnSortAuthor, &QPushButton::clicked, this, [&]() {
    if (radioBtnAuthor->isChecked()) {
      reloadBooks(service.sortBooksByAuthor(1));
    }
  });
  QObject::connect(btnSortGen, &QPushButton::clicked, this, [&]() {
    if (radioBtnGen->isChecked()) {
      reloadBooks(service.sortBooksByGen(1));
    }
  });
  // filtrare
  QObject::connect(btnFilterAuthor, &QPushButton::clicked, this, [&]() {
    reloadBooks(service.filterBooksByAuthor(editFilter->text().toStdString()));
  });
  QObject::connect(btnFilterGen, &QPushButton::clicked, this, [&]() {
    reloadBooks(service.filterBooksByGen(editFilter->text().toStdString()));
  });
  QObject::connect(btnFilterYear, &QPushButton::clicked, this, [&]() {
    reloadBooks(service.filterBooksByYear(editFilter->text().toInt()));
  });

  QObject::connect(btnReloadData, &QPushButton::clicked, this,
                   [&]() { reloadBooks(service.serviceGetBooks()); });

  for (int i = 0; i < 10; ++i) {
    QObject::connect(btnDinamice[i], &QPushButton::clicked, this, [=, this]() {
      // Capturăm i și this prin valoare
      std::string genText = btnDinamice[i]->text().toStdString();
      int numarCarti = 0;
      for (const auto &b : service.serviceGetBooks()) {
        if (b.getGen() == genText) {
          numarCarti++;
        }
      }

      std::string textCurent = btnDinamice[i]->text().toStdString();
      // Vreau pana la spatiu sa fac rost de gen
      std::string gen = textCurent.substr(0, textCurent.find(' '));
      // Si dupa spatiu sa fie contorul
      std::string contor =
          textCurent.substr(textCurent.find(' ') + 1, textCurent.size());

      QMessageBox::information(
          this, QString::fromStdString(gen),
          "Numarul de carti de genul " + QString::fromStdString(gen) +
              " este : " + QString::fromStdString(std::to_string(numarCarti)));
    });
  }

  QObject::connect(
      this->tableBooks, &QTableWidget::itemSelectionChanged, this, [&]() {
        auto selectedRow = this->tableBooks->selectedItems();
        if (selectedRow.isEmpty()) {
          return;
        }
        int row = selectedRow.at(0)->row();
        editTitle->setText(this->tableBooks->item(row, 0)->text());
        editAuthor->setText(this->tableBooks->item(row, 1)->text());
        editGen->setText(this->tableBooks->item(row, 2)->text());
        editReleaseYear->setText(this->tableBooks->item(row, 3)->text());
      });

  QObject::connect(
      this->listBooks, &QListWidget::itemSelectionChanged, this, [&]() {
        auto selectedItems = this->listBooks->selectedItems();
        if (selectedItems.isEmpty()) {
          return;
        }

        // Obține primul element selectat (presupunem o singură selecție)
        QListWidgetItem *selectedItem = selectedItems.first();
        int row = this->listBooks->row(selectedItem);

        editTitle->setText(this->listBooks->item(row)->text());
        editAuthor->setText(this->listBooks->item(row)->text());
        editGen->setText(this->listBooks->item(row)->text());
        editReleaseYear->setText(this->listBooks->item(row)->text());
      });

  QObject::connect(btnCos, &QPushButton::clicked, this, [&]() {
    // reloadBooksCos(service.serviceGetAllBooksFromCollection());
    QWidget *fereastraCos = new QWidget;
    QFormLayout *lyCos = new QFormLayout;
    fereastraCos->setLayout(lyCos);
    titluCos = new QLineEdit;

    lyCos->addRow("Titlu : ", titluCos);
    lyCos->addWidget(adaugaCos);
    lyCos->addRow(lblRandom, numarRandom);
    lyCos->addWidget(adaugaRandomCos);
    lyCos->addWidget(golesteCos);
    lyCos->addWidget(listaCos);
    editExport = new QLineEdit;
    lyCos->addRow(lblExport, editExport);
    lyCos->addWidget(exportaCos);
    lyCos->addRow(listaCos);
    fereastraCos->show();
  });

  QObject::connect(adaugaCos, &QPushButton::clicked, this, [&]() {
    string titlu = titluCos->text().toStdString();
    Book b;
    for (int i = 0; i < service.serviceGetBooks().size(); ++i) {
      if (service.serviceGetBooks()[i].getTitle() == titlu) {
        b = service.serviceGetBooks()[i];
      }
    }
    // Book b{titlu , "" , "" , 0};
    service.serviceAddBookToCollection(b);
    reloadBooksCos(service.serviceGetAllBooksFromCollection());
  });

  QObject::connect(adaugaRandomCos, &QPushButton::clicked, this, [&]() {
    int nr = numarRandom->text().toInt();
    service.serviceAddRandomBooksToCollection(nr);
    reloadBooksCos(service.serviceGetAllBooksFromCollection());
  });

  QObject::connect(golesteCos, &QPushButton::clicked, this, [&]() {
    service.serviceRemoveAllBooksFromCollection();
    reloadBooksCos(service.serviceGetAllBooksFromCollection());
  });

  QObject::connect(exportaCos, &QPushButton::clicked, this, [&]() {
    string filename = editExport->text().toStdString();
    if (filename.find(".html") != string::npos) {
      service.serviceExportCollectionToHTML(filename);
    } else if (filename.find(".csv") != string::npos) {
      service.serviceExportCollectionToCSV(filename);
    }
  });

  // Pentru lab13
  QObject::connect(btnCosCRUDGui, &QPushButton::clicked, this, [&]() {
    // auto fereastraCos = new
    // CosCRUDGui(service.serviceGetAllBooksFromCollection());
    auto fereastraCos2 = new CosCRUDGui(service.getCollectionBooks());
    fereastraCos2->show();
  });
  QObject::connect(btnCosReadOnlyGui, &QPushButton::clicked, this, [&]() {
    auto fereastraCosReadOnly = new HistogramGUI(service.getCollectionBooks());
    fereastraCosReadOnly->show();
  });
}

void BookGUI::reloadBooks(vector<Book> books) {
  this->tableBooks->clearContents();
  this->tableBooks->setRowCount(books.size());
  this->listBooks->clear();
  int lineNumber = 0;
  for (const auto &book : books) {
    this->tableBooks->setItem(
        lineNumber, 0,
        new QTableWidgetItem(QString::fromStdString(book.getTitle())));
    this->tableBooks->setItem(
        lineNumber, 1,
        new QTableWidgetItem(QString::fromStdString(book.getAuthor())));
    this->tableBooks->setItem(
        lineNumber, 2,
        new QTableWidgetItem(QString::fromStdString(book.getGen())));
    this->tableBooks->setItem(
        lineNumber, 3,
        new QTableWidgetItem(QString::number(book.getReleaseYear())));
    lineNumber++;
  }
  // Updtam lista de books
  for (const auto &book : books) {
    auto item = new QListWidgetItem(QString::fromStdString(
        book.getTitle() + " " + book.getAuthor() + " " + book.getGen() + " " +
        std::to_string(book.getReleaseYear())));
    this->listBooks->addItem(item);
  }

  std::unordered_map<std::string, int> raport;
  // Il scriem manual
  for (const auto &book : books) {
    raport[book.getGen()]++;
  }

  int row = -1;
  for (int i = 0; i < 10; ++i) {
    btnDinamice[i]->setVisible(false);
    // delete button
  }
  for (const auto &[gen, contor] : raport) {
    ++row;
    if (contor != 0) {
      btnDinamice[row]->setVisible(true);
      btnDinamice[row]->setText(QString::fromStdString(gen));
    } else {
      btnDinamice[row]->setVisible(false);
    }
  }
}

void BookGUI::reloadBooksCos(vector<Book> books) {
  this->listaCos->clear();
  for (const auto &book : books) {
    // this->listaCos->addItem(QString::fromStdString(book.getTitle()));
    auto item = new QListWidgetItem(QString::fromStdString(
        book.getTitle() + " " + book.getAuthor() + " " + book.getGen() + " " +
        std::to_string(book.getReleaseYear())));
    this->listaCos->addItem(item);
  }
}

void BookGUI::guiAddBook() {
  string title = editTitle->text().toStdString();
  string author = editAuthor->text().toStdString();
  string gen = editGen->text().toStdString();
  int releaseYear = editReleaseYear->text().toInt();
  Book b{title, author, gen, releaseYear};
  service.serviceAddBook(b);
  reloadBooks(service.serviceGetBooks());
}

void BookGUI::guiDeleteBook() {
  string title = editTitle->text().toStdString();
  string author = editAuthor->text().toStdString();
  string gen = editGen->text().toStdString();
  int releaseYear = editReleaseYear->text().toInt();
  Book b{title, author, gen, releaseYear};
  service.serviceRemoveBook(b);
  reloadBooks(service.serviceGetBooks());
}

void BookGUI::guiUpdateBook() {
  string title = editTitle->text().toStdString();
  string author = editAuthor->text().toStdString();
  string gen = editGen->text().toStdString();
  int releaseYear = editReleaseYear->text().toInt();
  Book b{title, author, gen, releaseYear};
  service.serviceUpdateBook(b, b);
  reloadBooks(service.serviceGetBooks());
}
// For run
void BookGUI::show() {
  // Implementation of the show function
  QWidget::show(); // If you want to call the base class implementation
}
