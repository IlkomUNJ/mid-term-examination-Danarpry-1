#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "drawingcanvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    DrawingCanvas *m_canvas;
    QPushButton *m_clearButton, *m_drawButton, *m_detectButton;
};


#endif // MAINWINDOW_H