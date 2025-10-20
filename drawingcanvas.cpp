#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    update();
}

void DrawingCanvas::paintLines(){
    isPaintLinesClicked = true;
    update();
}

bool isSegmentPattern(bool x[3][3]) {
    // 1. Horizontal (Baris)
    if (x[0][0] && x[0][1] && x[0][2]) return true; // Atas
    if (x[1][0] && x[1][1] && x[1][2]) return true; // Tengah
    if (x[2][0] && x[2][1] && x[2][2]) return true; // Bawah

    // 2. Vertikal (Kolom)
    if (x[0][0] && x[1][0] && x[2][0]) return true; // Kiri
    if (x[0][1] && x[1][1] && x[2][1]) return true; // Tengah
    if (x[0][2] && x[1][2] && x[2][2]) return true; // Kanan

    // 3. Diagonal
    if (x[0][0] && x[1][1] && x[2][2]) return true; // Diagonal Kanan Bawah
    if (x[0][2] && x[1][1] && x[2][0]) return true; // Diagonal Kiri Bawah

    if (x[1][0] && x[1][1] && !x[1][2]) return true; // Ujung Kanan
    if (x[0][0] && x[1][0] && !x[2][0]) return true; // Ujung Bawah

    if (x[0][0] && x[0][1] && x[1][0]) return true; // Sudut Kiri Atas

    return false;
}

void DrawingCanvas::segmentDetection() {
    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    qDebug() << "--- Mulai Segment Detection ---";
    qDebug() << "Image Width:" << image.width();
    qDebug() << "Image Height:" << image.height();

    std::vector<CustomMatrix> windows;
    m_detectedWindows.clear();

    for (int i = 1; i < image.width() - 1; i++) {
        for (int j = 1; j < image.height() - 1; j++) {
            bool x[3][3] = {false};

            QRgb centerRgb = image.pixel(i, j);
            bool isCenterDrawn = (centerRgb != 0xffffffff);
            qDebug() << "Pusat (" << i << "," << j << "): RGB=" << QColor(centerRgb).name()
                     << ", Is Drawn=" << isCenterDrawn;

            for (int m = -1; m <= 1; m++) {
                for (int n = -1; n <= 1; n++) {
                    QRgb rgbValue = image.pixel(i + m, j + n);
                    bool isDrawn = (rgbValue != 0xffffffff);
                    x[m + 1][n + 1] = isDrawn;
                }
            }

            CustomMatrix mat;
            mat.fillMatrix(x);
            windows.push_back(mat);

            if (isSegmentPattern(x)) {
                m_detectedWindows.push_back(QRect(i - 1, j - 1, 3, 3));
            }

            int activePixels = 0;
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    if (x[r][c]) {
                        activePixels++;
                    }
                }
            }

            if (activePixels >= 1) {
                m_detectedWindows.push_back(QRect(i - 1, j - 1, 3, 3));
            }
        }
    }

    std::set<std::vector<bool>> uniquePatterns;
    std::vector<CustomMatrix> uniqueMatrices;

    for (const auto& mat : windows) {
        std::vector<bool> pattern;
        bool is_empty = true;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                pattern.push_back(mat.mat[i][j]);
                if (mat.mat[i][j]) is_empty = false;
            }
        }

        if (!is_empty && uniquePatterns.find(pattern) == uniquePatterns.end()) {
            uniquePatterns.insert(pattern);
            uniqueMatrices.push_back(mat);
        }
    }

    qDebug() << "Total Windows Terdeteksi (3x3):" << windows.size();
    qDebug() << "--- Pola Window Unik Ditemukan (" << uniqueMatrices.size() << ") ---";
    for (const auto& mat : uniqueMatrices) {
        mat.printMatrix();
    }

    qDebug() << "--- Segment Detection Selesai ---";
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pointPen(Qt::blue, 5);
    painter.setPen(pointPen);
    painter.setBrush(QBrush(Qt::blue));

    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    painter.setBrush(Qt::NoBrush);

    if(isPaintLinesClicked){
        cout << "paint lines block is called" << endl;

        QPen linePen(QColor(128, 0, 128));
        linePen.setWidth(4);
        linePen.setStyle(Qt::SolidLine);
        painter.setPen(linePen);

        for(int i=0;i<m_points.size()-1;i+=2){
            painter.drawLine(m_points[i], m_points[i+1]);
        }
        isPaintLinesClicked = false;
    }

    if (!m_detectedWindows.isEmpty()) {
        QPen detPen(QColor(128, 0, 128));
        detPen.setWidth(1);
        painter.setPen(detPen);

        for (const QRect& rect : std::as_const(m_detectedWindows)) {
            painter.drawRect(rect);
        }
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    m_points.append(event->pos());
    const QPoint& newPoint = m_points.last();
    qDebug() << "Titik Baru Ditambahkan:" << newPoint;
    update();
}