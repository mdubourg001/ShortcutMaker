#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void on_load();

private slots:

    void on_pathExplorerButton_clicked();

    void on_iconPathExplorerButton_clicked();

    void on_pushButton_clicked();

    void on_validButton_clicked();

    void createShortcut();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
