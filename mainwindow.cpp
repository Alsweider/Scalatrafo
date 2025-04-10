#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ergebnis = 0.0;

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

    ui->labelFusszeile->setStyleSheet("color: rgba(0, 0, 0, 153);"); //60 % durchsichtig

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonTransform_clicked()
{
    //Zahlen einlesen
    double spinBoxMin1 = ui->spinBoxMin1->value();
    double spinBoxMax1 = ui->spinBoxMax1->value();
    double spinBoxMin2 = ui->spinBoxMin2->value();
    double spinBoxMax2 = ui->spinBoxMax2->value();
    double spinBoxBewertung1 = ui->spinBoxBewertung1->value();

    if (spinBoxMin1 >= spinBoxMax1) {
        ui->labelBewertung->setText("Ungültig: min >= max");
        return;
    }
    if (spinBoxMin2 >= spinBoxMax2) {
        ui->labelBewertung->setText("Ungültig: min >= max");
        return;
    }

    if (spinBoxBewertung1 < spinBoxMin1 || spinBoxBewertung1 > spinBoxMax1) {
        ui->labelBewertung->setText("min/max überschritten");
        return;
    }

    //Lineare Abbildung berechnen
    double steigung = ((spinBoxMax2-spinBoxMin2)/(spinBoxMax1-spinBoxMin1));
    double yAchse = (spinBoxMin2 - (steigung * spinBoxMin1));
    ergebnis = ((steigung*spinBoxBewertung1)+yAchse);


    //Ergebnis in Zeichenkette umwandeln
    if (ui->comboBoxRunden->currentIndex() == 0){
        ergebnisText = QLocale::system().toString(ergebnis, 'f', 2);
    } else if (ui->comboBoxRunden->currentIndex() == 1){
            ergebnis = qRound(ergebnis);
            ergebnisText = QLocale::system().toString(ergebnis);
    } else if (ui->comboBoxRunden->currentIndex() == 2){
            double gerundet = qRound(ergebnis * 2.0) / 2.0;
            ergebnisText = QLocale::system().toString(gerundet, 'f', 2);
    }


    ui->labelBewertung->setText(ergebnisText);

    //Kopieren-Schaltfläche aktivieren
    ui->pushButtonKopieren->setEnabled(true);
}


void MainWindow::on_pushButtonBeenden_clicked()
{
    close();
}


void MainWindow::on_spinBoxMax2_editingFinished()
{
    on_pushButtonTransform_clicked();
}


void MainWindow::on_pushButtonKopieren_clicked()
{
    QApplication::clipboard()->setText(ui->labelBewertung->text());
}


void MainWindow::on_spinBoxBewertung1_valueChanged(double arg1)
{
    on_pushButtonTransform_clicked();
}


void MainWindow::on_comboBoxRunden_currentIndexChanged(int index)
{
        on_pushButtonTransform_clicked();
}

