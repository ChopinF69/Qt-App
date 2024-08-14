//
// Created by lazar on 05.06.2024.
//

#include "storeGUImodele.h"

void StoreGUIModele::initGUIcmps()
{
    // Main layout
    QHBoxLayout* lyMain = new QHBoxLayout;
    this->setLayout(lyMain);
    //left part of the window , pentru care setam
    // layout vertical
    QWidget* left = new QWidget;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    left->setLayout(lyLeft);
    QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    form->setLayout(lyForm);

    // Adaugam label-urile si editurile
    editTitle = new QLineEdit;
    editAuthor = new QLineEdit;
    editGenre = new QLineEdit;
    editReleaseYear = new QLineEdit;
    lyForm->addRow(lblTitle, editTitle);
    lyForm->addRow(lblAuthor, editAuthor);
    lyForm->addRow(lblGenre, editGenre);
    lyForm->addRow(lblReleaseYear, editReleaseYear);

    // Buttoanele
    btnAdd = new QPushButton{"Add"};
    lyForm->addRow(btnAdd);
    btnDelete = new QPushButton{"Delete"};
    lyForm->addRow(btnDelete);
    btnUpdate = new QPushButton{"Update"};
    lyForm->addRow(btnUpdate);
    lyLeft->addWidget(form);

    // Cream un groupbox pt criterii de sortare
    QVBoxLayout* lyRadioBox = new QVBoxLayout;
    this->groupBox->setLayout(lyRadioBox);
    lyRadioBox->addWidget(radioSrtTitle);
    lyRadioBox->addWidget(radioSrtAuthor);
    btnSort = new QPushButton{"Sort"};
    lyRadioBox->addWidget(btnSort);

    lyLeft->addWidget(groupBox);

    // Cream un form pentru filtrare
    QWidget* formFilter = new QWidget;
    QFormLayout* lyFormFilter = new QFormLayout;
    formFilter->setLayout(lyFormFilter);
    editFilter = new QLineEdit;
    lyFormFilter->addRow("Filter by genre", editFilter);
    btnFilter = new QPushButton{"Filter"};
    lyFormFilter->addRow(btnFilter);
    // Cealalta filtrare
    btnFilterAuthor = new QPushButton{"Filter by author"};
    editFilterAuthor = new QLineEdit;
    lyFormFilter->addRow("Filter by author", editFilterAuthor);
    lyFormFilter->addRow(btnFilterAuthor);
    lyLeft->addWidget(formFilter);

    // buton pentru a reincarca datele
    btnReloadData = new QPushButton{"Reload data asd"};
    lyLeft->addWidget(btnReloadData);

    btnUndo = new QPushButton{"Undo"};
    lyLeft->addWidget(btnUndo);
    // Componenta right
    QWidget* right = new QWidget;
    QVBoxLayout* lyRight = new QVBoxLayout;
    right->setLayout(lyRight);
    lyRight->addWidget(tblV);
    // Pentru cos
    btnCos = new QPushButton{"Cos"};
    lyRight->addWidget(btnCos);
    addCos = new QPushButton{"Add to cos"};
    lyRight->addWidget(addCos);
    titluCarte = new QLineEdit;
    addRandomCos = new QPushButton{"Add random to cos"};
    lyRight->addWidget(addRandomCos);
    editRandom = new QLineEdit;
    golesteCos = new QPushButton{"Goleste cos"};
    editExport = new QLineEdit;
    editExport = new QLineEdit;
    exportCos = new QPushButton{"Export cos"};



    btnAddCoss = new QPushButton{"Add Book to cos"};
    btnDeleteCos = new QPushButton{"Delete Book from cos"};
    lyRight->addWidget(btnAddCoss);
    lyRight->addWidget(btnDeleteCos);
    btnGenerateCos = new QPushButton{"Add random book to cos"};
    lyRight->addWidget(btnGenerateCos);

    btnCosCRUDGUI = new QPushButton{"Cos CRUD GUI"};
    lyRight->addWidget(btnCosCRUDGUI);
    btnCosReadOnlyGUI = new QPushButton{"Cos ReadOnly GUI"};
    lyRight->addWidget(btnCosReadOnlyGUI);
    lyMain->addWidget(left);
    lyMain->addWidget(right);
}

void StoreGUIModele::connectSignalsSlots()
{
    QObject::connect(btnAdd, &QPushButton::clicked, this, &StoreGUIModele::guiAddBook);
    QObject::connect(btnDelete, &QPushButton::clicked, this, &StoreGUIModele::guiDeleteBook);
    QObject::connect(btnUpdate, &QPushButton::clicked, this, &StoreGUIModele::guiModifyBook);

    QObject::connect(btnUndo , &QPushButton::clicked ,[&](){
        try {
            service.serviceUndo();
            reloadList(service.serviceGetBooks());
        }
        catch (...) {
            QMessageBox::critical(this , "Error" , "Undo failed");
        }
    });
    QObject::connect(btnSort , &QPushButton::clicked ,[&](){
        if(radioSrtTitle->isChecked())
        {
            reloadList(service.sortBooksByTitle(1));
        }
        else if(radioSrtAuthor->isChecked())
        {
            reloadList(service.sortBooksByAuthor(1));
        }
        else if(radioSrtGenre->isChecked())
        {
            reloadList(service.sortBooksByGen(1));
        }
    });

    QObject::connect(btnFilter , &QPushButton::clicked ,[&](){
        reloadList(service.filterBooksByGen(editFilter->text().toStdString()));
    });
    QObject::connect(btnFilterAuthor , &QPushButton::clicked ,[&](){
        reloadList(service.filterBooksByAuthor(editFilterAuthor->text().toStdString()));
    });
    QObject::connect(btnReloadData , &QPushButton::clicked ,[&](){
        reloadList(service.serviceGetBooks());
    });
    QObject::connect(tblV->selectionModel() , &QItemSelectionModel::selectionChanged ,[&](){
        QModelIndexList index = tblV->selectionModel()->selectedIndexes();
        if(index.isEmpty())
        {
            editTitle->setText("");
            editAuthor->setText("");
            editGenre->setText("");
            editReleaseYear->setText("");
        }
        else
        {
            int row = index.at(0).row();
            editTitle->setText(QString::fromStdString(service.serviceGetBooks()[row].getTitle()));
            editAuthor->setText(QString::fromStdString(service.serviceGetBooks()[row].getAuthor()));
            editGenre->setText(QString::fromStdString(service.serviceGetBooks()[row].getGen()));
            editReleaseYear->setText(QString::number(service.serviceGetBooks()[row].getReleaseYear()));
        }
    });

    QObject::connect(btnCos , &QPushButton::clicked ,[&](){
        QWidget* fereastra_cos = new QWidget;
        QFormLayout* lyCos = new QFormLayout;
        fereastra_cos->setLayout(lyCos);
        titluCarte= new QLineEdit;
        lyCos->addRow(lblDenumireCos , titluCarte);
        lyCos->addRow(addCos);
        editRandom = new QLineEdit;
        lyCos->addRow(lblRandom , editRandom);
        lyCos->addRow(addRandomCos);
        lyCos->addRow(golesteCos);
        editExport = new QLineEdit;
        lyCos->addRow(lblExport , editExport);
        lyCos->addRow(exportCos);
        lyCos->addRow(listaCos);
        fereastra_cos->show();
    });

    QObject::connect(addCos , &QPushButton::clicked ,[&](){
        try {
            service.serviceAddBookToCollection(Book{titluCarte->text().toStdString() , "" , "" , 0});
            reloadList(service.serviceGetBooks());
        }
        catch (...) {
            QMessageBox::critical(this , "Error" , "Add to cos failed");
        }
    });
    QObject::connect(addRandomCos , &QPushButton::clicked ,[&](){
        try {
            service.serviceAddRandomBooksToCollection(editRandom->text().toInt());
            reloadList(service.serviceGetBooks());
        }
        catch (...) {
            QMessageBox::critical(this , "Error" , "Add random to cos failed");
        }
    });
    QObject::connect(golesteCos , &QPushButton::clicked ,[&](){
        try {
            service.serviceRemoveAllBooksFromCollection();
            reloadList(service.serviceGetBooks());
        }
        catch (...) {
            QMessageBox::critical(this , "Error" , "Goleste cos failed");
        }
    });
    QObject::connect(exportCos , &QPushButton::clicked ,[&](){
        try {
            service.serviceExportCollectionToHTML(editExport->text().toStdString());
            reloadList(service.serviceGetBooks());
        }
        catch (...) {
            QMessageBox::critical(this , "Error" , "Export cos failed");
        }
    });
    QObject::connect(btnCosCRUDGUI , &QPushButton::clicked ,[&](){
        auto fereastra_cos = new CosCRUDGui{service.getCollectionBooks()};
        fereastra_cos->show();
    });
    QObject::connect(btnCosReadOnlyGUI , &QPushButton::clicked ,[&](){
        auto fereastraFiguri = new HistogramGUI{service.getCollectionBooks()};
        fereastraFiguri->show();
    });
    QObject::connect(btnAddCoss , &QPushButton::clicked ,[&](){
        try {
            std::string title = editTitle->text().toStdString();
            std::string author = editAuthor->text().toStdString();
            std::string genre = editGenre->text().toStdString();
            int releaseYear = editReleaseYear->text().toInt();
            editTitle->clear();
            editAuthor->clear();
            editGenre->clear();
            editReleaseYear->clear();
            service.serviceAddBookToCollection(Book{title , author , genre , releaseYear});
            //service.serviceAddBookToCollection(Book{titluCarte->text().toStdString() , "" , "" , 0});
           // reloadList(service.serviceGetBooks());
        }
        catch (...) {
            QMessageBox::critical(this , "Error" , "Add to cos failed");
        }
    });
    QObject::connect(btnDelete , &QPushButton::clicked ,[&](){
        try {
            std::cout << titluCarte->text().toStdString() << "\n";
            service.serviceRemoveBook(Book{titluCarte->text().toStdString() , "" , "" , 0});
            reloadList(service.serviceGetBooks());
        }
        catch (...) {
            QMessageBox::critical(this , "Error" , "Delete from cos failed");
        }
    });
    QObject::connect(btnGenerateCos , &QPushButton::clicked ,[&](){
        try {
            service.serviceAddRandomBooksToCollection(3);
            reloadList(service.serviceGetBooks());
        }
        catch (...) {
            QMessageBox::critical(this , "Error" , "Generate cos failed");
        }
    });

}

void StoreGUIModele::reloadList(const vector<Book> &books) {
    modelTabel->setBooks(books);
    modelTabel->update();
}

void StoreGUIModele::guiAddBook() {
    try {
        std::string title = editTitle->text().toStdString();
        std::string author = editAuthor->text().toStdString();
        std::string genre = editGenre->text().toStdString();
        int releaseYear = editReleaseYear->text().toInt();
        editTitle->clear();
        editAuthor->clear();
        editGenre->clear();
        editReleaseYear->clear();
        service.serviceAddBook(Book{title , author , genre , releaseYear});
        //service.serviceAddBook(Book{editTitle->text().toStdString() , editAuthor->text().toStdString() , editGenre->text().toStdString() , editReleaseYear->text().toInt()});
        reloadList(service.serviceGetBooks());
    }
    catch (...) {
        QMessageBox::critical(this , "Error" , "Add failed");
    }
}

void StoreGUIModele::guiModifyBook()
{
    try {
        std::string title = editTitle->text().toStdString();
        std::string author = editAuthor->text().toStdString();
        std::string genre = editGenre->text().toStdString();
        int releaseYear = editReleaseYear->text().toInt();
        editTitle->clear();
        editAuthor->clear();
        editGenre->clear();
        editReleaseYear->clear();
        service.serviceUpdateBook(Book{title , author , genre , releaseYear} , Book{title , author , genre , releaseYear});
        reloadList(service.serviceGetBooks());
    }
    catch (...) {
        QMessageBox::critical(this , "Error" , "Update failed");
    }
}
void StoreGUIModele::guiDeleteBook()
{
    try {
        std::string title = editTitle->text().toStdString();
        std::string author = editAuthor->text().toStdString();
        std::string genre = editGenre->text().toStdString();
        int releaseYear = editReleaseYear->text().toInt();
        editTitle->clear();
        editAuthor->clear();
        editGenre->clear();
        editReleaseYear->clear();
        std::cout << title << " " << author << " " << genre << " " << releaseYear << "\n";
        service.serviceRemoveBook(Book{title , author , genre , releaseYear});
        reloadList(service.serviceGetBooks());
    }
    catch (...) {
        QMessageBox::critical(this , "Error" , "Delete failed");
    }
}