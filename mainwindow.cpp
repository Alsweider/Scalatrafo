#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QDebug>
#include <cmath>


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

    //Jede Eingabe löst sofort die Neuberechnung aus
    const QList<QDoubleSpinBox *> eingaben = {
        ui->spinBoxMin1, ui->spinBoxMax1, ui->spinBoxMin2,
        ui->spinBoxMax2, ui->spinBoxBewertung1
    };
    for (QDoubleSpinBox *box : eingaben) {
        connect(box, qOverload<double>(&QDoubleSpinBox::valueChanged),
                this, &MainWindow::on_pushButtonTransform_clicked);
    }

    //Auch die Zahl der Nachkommastellen löst die Neuberechnung aus
    connect(ui->spinBoxStellen, qOverload<int>(&QSpinBox::valueChanged),
            this, &MainWindow::on_pushButtonTransform_clicked);

    ui->spinBoxMin1->setFocus();   //Eingabe beginnt bei Minimum 1
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonTransform_clicked()
{
    //Bei Fehlern Meldung zeigen und Kopieren sperren
    auto fehler = [this](const QString &text) {
        ui->labelBewertung->setText(text);
        ui->pushButtonKopieren->setEnabled(false);
    };

    //Zahlen einlesen
    double spinBoxMin1 = ui->spinBoxMin1->value();
    double spinBoxMax1 = ui->spinBoxMax1->value();
    double spinBoxMin2 = ui->spinBoxMin2->value();
    double spinBoxMax2 = ui->spinBoxMax2->value();
    double spinBoxBewertung1 = ui->spinBoxBewertung1->value();

    if (spinBoxMin1 >= spinBoxMax1 || spinBoxMin2 >= spinBoxMax2) {
        fehler("Ungültig: min >= max");
        return;
    }

    if (spinBoxBewertung1 < spinBoxMin1 || spinBoxBewertung1 > spinBoxMax1) {
        fehler("min/max überschritten");
        return;
    }

    //Lineare Abbildung berechnen
    double steigung = ((spinBoxMax2-spinBoxMin2)/(spinBoxMax1-spinBoxMin1));
    double yAchse = (spinBoxMin2 - (steigung * spinBoxMin1));
    ergebnis = ((steigung*spinBoxBewertung1)+yAchse);

    //Gleitkommarauschen wegrunden (nach 9 Nachkommastellen), damit genaue
    //Halbstufen wie 4,5 nicht als 4,4999999999999 in die Rundung gelangen
    if (std::abs(ergebnis) < 1e6)
        ergebnis = std::round(ergebnis * 1e9) / 1e9;

    //Ergebnis nach gewählter Rundung in eine Zeichenkette umwandeln
    QLocale ort = QLocale::system();
    ort.setNumberOptions(QLocale::OmitGroupSeparator);   //keine Tausenderpunkte

    switch (ui->comboBoxRunden->currentIndex()) {
    case 1:   //Ganzzahlen
        ergebnis = std::round(ergebnis);
        ergebnisText = ort.toString(ergebnis, 'f', 0);
        break;
    case 2:   //Halbzahlen
        ergebnis = std::round(ergebnis * 2.0) / 2.0;
        ergebnisText = ort.toString(ergebnis, 'f', 1);
        break;
    case 3:   //Viertelzahlen
        ergebnis = std::round(ergebnis * 4.0) / 4.0;
        ergebnisText = ort.toString(ergebnis, 'f', 2);
        break;
    default:  //Dezimalzahlen
        ergebnisText = ort.toString(ergebnis, 'f', ui->spinBoxStellen->value());
        break;
    }

    //Aus "-0" oder "-0,00" wird "0" bzw. "0,00"
    const QString minus = ort.negativeSign();
    if (ergebnisText.startsWith(minus) && ort.toDouble(ergebnisText) == 0.0)
        ergebnisText.remove(0, minus.size());

    ui->labelBewertung->setText(ergebnisText);

    //Kopieren-Schaltfläche aktivieren
    ui->pushButtonKopieren->setEnabled(true);
}


void MainWindow::on_pushButtonBeenden_clicked()
{
    close();
}


void MainWindow::on_pushButtonKopieren_clicked()
{
    QApplication::clipboard()->setText(ui->labelBewertung->text());
}


void MainWindow::on_comboBoxRunden_currentIndexChanged(int index)
{
    ui->spinBoxStellen->setEnabled(index == 0);
    on_pushButtonTransform_clicked();
}

