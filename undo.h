//
// Created by lazar on 29.04.2024.
//

#ifndef LAB9_UNDO_H
#define LAB9_UNDO_H
#include "domain.h"
#include "repo.h"
class ActionUndo{
public:
    virtual void doUndo() = 0;
    virtual ~ActionUndo() = default;
};

class UndoAdd : public ActionUndo{
private:
    Book bookAdded;
    //RepoNou &repo;
    Repo &repo;
public:
    UndoAdd(Repo &repo, const Book &bookAdded) : repo{repo}, bookAdded{bookAdded}{}
    void doUndo() override{
        repo.removeBook(bookAdded);
        std::cout << bookAdded.getTitle() << " " << bookAdded.getAuthor() << " " << bookAdded.getGen() << " " << bookAdded.getReleaseYear() << " was removed from the repository\n";
    }
};
class UndoRemove : public ActionUndo{
private:
    Book bookRemoved;
    //RepoNou &repo;
    Repo &repo;
public:
    UndoRemove(Repo &repo, const Book &bookRemoved) : repo{repo}, bookRemoved{bookRemoved}{}
    void doUndo() override{
        repo.addBook(bookRemoved);
        std::cout << bookRemoved.getTitle() << " " << bookRemoved.getAuthor() << " " << bookRemoved.getGen() << " " << bookRemoved.getReleaseYear() << " was added back to the repository\n";
    }
};

class UndoUpdate : public ActionUndo{
private:
    Book bookBeforeUpdate;
    Book bookAfterUpdate;
    //RepoNou &repo;
    Repo &repo;
public:
    UndoUpdate(Repo &repo, const Book &bookBeforeUpdate, const Book &bookAfterUpdate) : repo{repo}, bookBeforeUpdate{bookBeforeUpdate}, bookAfterUpdate{bookAfterUpdate}{}
    void doUndo() override{
        repo.updateBook(bookAfterUpdate, bookBeforeUpdate);
        std::cout << bookAfterUpdate.getTitle() << " " << bookAfterUpdate.getAuthor() << " " << bookAfterUpdate.getGen() << " " << bookAfterUpdate.getReleaseYear() << " was updated back to " << bookBeforeUpdate.getTitle() << " " << bookBeforeUpdate.getAuthor() << " " << bookBeforeUpdate.getGen() << " " << bookBeforeUpdate.getReleaseYear() << "\n";

    }
};
#endif //LAB9_UNDO_H
