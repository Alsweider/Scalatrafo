#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Grenzwerte für die Drehkästchen voll aufdrehen
    ui->spinBoxMin1->setMaximum(std::numeric_limits<double>::max());
    ui->spinBoxMin2->setMaximum(std::numeric_limits<double>::max());
    ui->spinBoxMax1->setMaximum(std::numeric_limits<double>::max());
    ui->spinBoxMax2->setMaximum(std::numeric_limits<double>::max());
    ui->spinBoxBewertung1->setMaximum(std::numeric_limits<double>::max());
    ui->spinBoxMin1->setMinimum(-std::numeric_limits<double>::max());
    ui->spinBoxMin2->setMinimum(-std::numeric_limits<double>::max());
    ui->spinBoxMax1->setMinimum(-std::numeric_limits<double>::max());
    ui->spinBoxMax2->setMinimum(-std::numeric_limits<double>::max());
    ui->spinBoxBewertung1->setMinimum(-std::numeric_limits<double>::max());


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonTransform_clicked()
{
    //Zahlen einlesen
    float spinBoxMin1 = ui->spinBoxMin1->value();
    float spinBoxMax1 = ui->spinBoxMax1->value();
    float spinBoxMin2 = ui->spinBoxMin2->value();
    float spinBoxMax2 = ui->spinBoxMax2->value();
    float spinBoxBewertung1 = ui->spinBoxBewertung1->value();


    //Steigung berechnen
    float steigung = ((spinBoxMax2-spinBoxMin2)/(spinBoxMax1-spinBoxMin1));
    float yAchse = (spinBoxMin2 - (steigung * spinBoxMin1));
    float ergebnis = ((steigung*spinBoxBewertung1)+yAchse);

    QString ergebnisText = QString::number(ergebnis);

    ui->labelBewertung->setText(ergebnisText);

}


void MainWindow::on_pushButtonBeenden_clicked()
{
    close();
}



