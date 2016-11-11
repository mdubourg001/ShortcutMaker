#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <sys/stat.h>
#include "fstream"
#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_load()
{
    if(geteuid() == 0)
        ui->runRootLabel->setVisible(false);
    chdir("/");
}

void MainWindow::on_pathExplorerButton_clicked()
{
    ui->pathField->setText(QFileDialog::getOpenFileName());
}

void MainWindow::on_iconPathExplorerButton_clicked()
{
    ui->iconField->setText(QFileDialog::getOpenFileName());

}

void MainWindow::on_pushButton_clicked()
{
    ui->commentsField->clear();
    ui->iconField->clear();
    ui->commandlineField->clear();
    ui->nameField->clear();
    ui->pathField->clear();
}

void MainWindow::on_validButton_clicked()
{
    QMessageBox *alertBox = new QMessageBox(this);
    if(ui->nameField->text().isEmpty() || (ui->pathField->text().isEmpty() && ui->commandlineField->text().isEmpty()))
    {
        alertBox->setText("You have to fill 'name' and 'path' fields at least.");
        alertBox->exec();
    }

    else
    {
        createShortcut();
        alertBox->setText("Shortcut succesfully created!");
        alertBox->exec();
    }

    delete alertBox;
}

void MainWindow::createShortcut()
{
    chdir("/usr/share/applications/");

    cout << ui->nameField->text().toStdString() << endl;
    const char *filename = ui->nameField->text().toStdString().c_str();
    const char *extension = ".desktop";
    char *final = new char[strlen(filename) + 1 + 4];
    strcpy(final, filename);
    strcat(final, extension);

    ofstream shortcut_file (final);
    if(!shortcut_file)
        cerr << "Cannot create / open file" << endl;
    else
    {
        shortcut_file << "[Desktop Entry]" << endl << "Encoding=" + ui->encodingField->currentText().toStdString() << endl;
        shortcut_file << "Name=" + ui->nameField->text().toStdString() << endl;
        shortcut_file << "Exec=" + (ui->pathField->text().isEmpty() ? ui->commandlineField->text().toStdString() : ui->pathField->text().toStdString()) << endl;
        shortcut_file << "Terminal=" << (ui->terminalCheckbox->isChecked() ? "true" : "false") << endl;
        shortcut_file << "Icon=" + ui->iconField->text().toStdString() << endl;
        shortcut_file << "Type=" + ui->typeField->currentText().toStdString() << endl;
        shortcut_file << "Comment=" + ui->commentsField->toPlainText().toStdString() << ";" << endl;
        shortcut_file.flush();
        shortcut_file.close();
    }

    delete final;
}
