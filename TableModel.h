#pragma once
#include "service.h"
#include <QAbstractTableModel>
#include <qbrush.h>
#include <qdebug.h>
class TableModel : public QAbstractTableModel, public Observer {
private:
  std::vector<Book> books;

public:
  TableModel(const std::vector<Book> &books) : books{books} {}

  int rowCount(const QModelIndex &parent = QModelIndex{}) const override {
    return books.size();
  }

  int columnCount(const QModelIndex &parent = QModelIndex{}) const override {
    return 4;
  }

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override {
    int row = index.row();
    int column = index.column();
    const Book &book = books[row];
    if (role == Qt::DisplayRole) {
      switch (column) {
      case 0:
        return QString::fromStdString(book.getTitle());
      case 1:
        return QString::fromStdString(book.getAuthor());
      case 2:
        return QString::fromStdString(book.getGen());
      case 3:
        return QString::number(book.getReleaseYear());
      default:
        break;
      }
    }
    return QVariant{};
  }

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
      switch (section) {
      case 0:
        return "Title";
      case 1:
        return "Author";
      case 2:
        return "Genre";
      case 3:
        return "Release Year";
      default:
        break;
      }
    }
    return QVariant{};
  }

  void update() override {
    beginResetModel();
    endResetModel();
  }

  void setBooks(const std::vector<Book> &books) {
    this->books = books;
    auto topLeft = createIndex(0, 0);
    auto bottomRight = createIndex(rowCount(), columnCount());
    emit dataChanged(topLeft, bottomRight);
  }
};
