#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QDebug>
//#include <QScreen>
#include <QWindowStateChangeEvent>


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

    //Ursprüngliche Fenstergröße speichern zur Berechnung der Schriftgröße
    fenstergroesseOriginal = this->size();
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

    //Lineare Abbildung berechnen
    float steigung = ((spinBoxMax2-spinBoxMin2)/(spinBoxMax1-spinBoxMin1));
    float yAchse = (spinBoxMin2 - (steigung * spinBoxMin1));
    float ergebnis = ((steigung*spinBoxBewertung1)+yAchse);

    //Ergebnis in Zeichenkette umwandeln
    //QString ergebnisText = QString::number(ergebnis);
    QString ergebnisText = QLocale::system().toString(ergebnis, 'f', 2);

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

void MainWindow::resizeEvent(QResizeEvent *event) {
    qDebug() << "resizeEvent aufgerufen\n";
    //Standard-Resize-Event
    //QWidget::resizeEvent(event);

    qreal scaleX = static_cast<qreal>((this->size().width()) / fenstergroesseOriginal.width());
    qreal scaleY = static_cast<qreal>((this->size().height()) / fenstergroesseOriginal.height());


    //Neue Schriftgröße errätseln
    int neueSchriftgroesse = 14;
    int neueSchriftgroesseFusszeile = 8;
    neueSchriftgroesse = static_cast<int>((neueSchriftgroesse * qMin(scaleX, scaleY)));
    neueSchriftgroesseFusszeile = static_cast<int>((neueSchriftgroesseFusszeile * qMin(scaleX, scaleY)));

    //Größenbegrenzung
    int minimaleSchriftgroesse = 8;
    int maximaleSchriftgroesse = 40;

    if (neueSchriftgroesse < minimaleSchriftgroesse) {
        neueSchriftgroesse = minimaleSchriftgroesse;
    } else if (neueSchriftgroesse > maximaleSchriftgroesse) {
        neueSchriftgroesse = maximaleSchriftgroesse;
    }

    // if (neueSchriftgroesseFusszeile < minimaleSchriftgroesse) {
    //     neueSchriftgroesseFusszeile = minimaleSchriftgroesse;
    // } else if (neueSchriftgroesseFusszeile > maximaleSchriftgroesse) {
    //     neueSchriftgroesseFusszeile = maximaleSchriftgroesse;
    // }

    QFont fontStandard = QFont("Times New Roman", neueSchriftgroesse);
    // QFont fontFusszeile = QFont("Times New Roman", neueSchriftgroesse);

    //Schriftgröße setzen
     ui->pushButtonBeenden->setFont(fontStandard);
     ui->pushButtonKopieren->setFont(fontStandard);
     ui->pushButtonTransform->setFont(fontStandard);
     ui->groupBox->setFont(fontStandard);
     ui->groupBox_3->setFont(fontStandard);
     ui->label->setFont(fontStandard);
     ui->labelBewertung->setFont(fontStandard);
     ui->label_2->setFont(fontStandard);
     ui->label_3->setFont(fontStandard);
     ui->label_4->setFont(fontStandard);
     ui->label_5->setFont(fontStandard);
     ui->label_6->setFont(fontStandard);
     ui->spinBoxBewertung1->setFont(fontStandard);
     ui->spinBoxMax1->setFont(fontStandard);
     ui->spinBoxMax2->setFont(fontStandard);
     ui->spinBoxMin1->setFont(fontStandard);
     ui->spinBoxMin2->setFont(fontStandard);
    // ui->labelFusszeile->setFont(fontFusszeile);
}




