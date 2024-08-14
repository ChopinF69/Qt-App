//
// Created by lazar on 27.05.2024.
//

#ifndef LAB10_COSREADONLYGUI_H
#define LAB10_COSREADONLYGUI_H
#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include "repo.h"
#include "qdebug.h"

class HistogramGUI : public QWidget  , public Observer{
private:
    CollectionBooks& cos;
public:
    HistogramGUI(CollectionBooks& cos) : cos{cos} {
        cos.addObserver(this);
    }

    void update()override{
        repaint();
    }

    void paintEvent(QPaintEvent* ev)override{
        QPainter p{this};
        srand(time(NULL));
        for(const auto& book : cos.getBooksFromCollection())
        {
            int x= rand() % 300;
            int y = rand() % 300;
            qDebug() << x << " " << y << "\n";
            p.drawRect(x ,y , 20 , book.getReleaseYear() / 10);
            p.drawImage(x , y , QImage("/home/lazar/Desktop/atestatAlbert/imagini/pozaFractal_2.jpeg"));

        }
    }
};
#endif //LAB10_COSREADONLYGUI_H
