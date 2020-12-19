#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    map = hashmap<std::string>();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Add_clicked()
{
    map << ui->lineEdit->text().toStdString();
    Update();
}

void MainWindow::on_Remove_clicked()
{
    map.erase(ui->lineEdit->text().toStdString());
    ui->lineEdit->clear();
    Update();
}


void MainWindow::on_Clear_clicked()
{
    map.clear();
    Update();
}



void MainWindow::on_Min_clicked()
{
    QString msg = QString::fromStdString(map.min());
    QMessageBox::warning(0, "Min", msg);
}

void MainWindow::on_Max_clicked()
{
    QString msg = QString::fromStdString(map.max());
    QMessageBox::warning(0, "Max", msg);
}

void MainWindow::Update() {
    ui->listWidget->clear();
    if (map.empty()) {
        return;
    }
    for (const auto &bucket : map.buckets_) {
        if (!bucket.empty()) {
            for (const auto &[k_, v_] : bucket) {
                QString item = QString::fromStdString(k_) + " == " + QString::fromStdString(std::to_string(v_));
                ui->listWidget->addItem(item);
            }
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save the file");
    map.print(file_name.toStdString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    map.read(file_name.toStdString());
    Update();
}
