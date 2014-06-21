#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

struct position {
    int x;
    int y;
    char alpha;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage* image;
    QColor color;

private slots:
    void bildEinlesen();
    void farbeEinlesen();
};

#endif // MAINWINDOW_H
