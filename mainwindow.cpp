#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *subLayout = new QHBoxLayout();

    DrawingCanvas *m_canvas = new DrawingCanvas(this);
    mainLayout->addWidget(m_canvas);

    m_clearButton = new QPushButton("Clear Canvas", this);
    m_detectButton = new QPushButton("Detect Segment", this);
    m_drawButton = new QPushButton("Draw Lines", this);

    mainLayout->addLayout(subLayout, 1);
    subLayout->addWidget(m_drawButton, 0);
    subLayout->addWidget(m_detectButton, 0);
    subLayout->addWidget(m_clearButton, 0);

    connect(m_clearButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::clearPoints);
    connect(m_drawButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::paintLines);
    connect(m_detectButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::segmentDetection);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Drawing Canvas");
    setFixedSize(450, 450);
}

MainWindow::~MainWindow()
{
}