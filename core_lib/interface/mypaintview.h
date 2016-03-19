/*

Pencil - Traditional Animation Software
Copyright (C) 2005-2007 Patrick Corrieri & Pascal Naidon
Copyright (C) 2013-2014 Matt Chiawen Chang

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation;

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

*/
#ifndef MYPAINTVIEW_H
#define MYPAINTVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPushButton>
#include <QColorDialog>

#include "mphandler.h"
#include "mpbrush.h"
#include "mpsurface.h"
#include "mptile.h"

class MyPaintView : public QGraphicsView
{
    Q_OBJECT

public:
    MyPaintView();
    ~MyPaintView();

private:

    QGraphicsScene m_scene;
    QColor m_color;
    bool using_tablet;

protected:
    virtual void tabletEvent(QTabletEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

public slots:
    //  void BrushSelected(const QByteArray& content);
    void btnChgColorPressed();

    void onNewTile(MPSurface *surface, MPTile *tile);
    void onUpdateTile(MPSurface *surface, MPTile *tile);
};

#endif // MYPAINTVIEW_H
