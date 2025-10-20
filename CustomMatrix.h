#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H
#include <QDebug>

class CustomMatrix{
public:
    bool mat[3][3]={0};

    CustomMatrix(){}

    void fillMatrix(bool m[3][3]){
        for (int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++){
                mat[i][j] = m[i][j];
            }
        }
    }

    void printMatrix() const {
        for (int i = 0; i < 3; ++i) {
            QString row;
            for (int j = 0; j < 3; ++j) {
                row += (mat[i][j] ? "1" : "0");
            }
            qDebug() << row;
        }
    }
};

#endif // CUSTOMMATRIX_H