#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QDebug>
#include <QTimer>


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

    //Ursprüngliche Fenstergröße speichern
    fenstergroesseOriginal = this->size();

    ui->labelFusszeile->setStyleSheet("color: rgba(0, 0, 0, 153);"); //60 % durchsichtig

    //Verzögerungszeitgeber für die Aktualisierung der Schriftgrößen nach Programmstart
    schriftenTimer = new QTimer(this);
    schriftenTimer->setSingleShot(true);
    connect(schriftenTimer, &QTimer::timeout, this, &MainWindow::updateFontSize);
    schriftenTimer->start(20); //20ms Kontemplation
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


//Das überrittene Resize-Event ruft die Funktion zur Schriftgrößenanpassung auf
void MainWindow::resizeEvent(QResizeEvent *event) {

    qDebug() << "resizeEvent aufgerufen\n";

    QSize fenstergroesseNeu = this->size();
    qDebug() << "Alte Fenstergröße: " << fenstergroesseOriginal << '\n';
    qDebug() << "Neue Fenstergröße: " << fenstergroesseNeu << '\n';

    if (fenstergroesseOriginal != fenstergroesseNeu){
    schriftgroesseAnpassen(ui->centralwidget);
    fenstergroesseOriginal = fenstergroesseNeu;
    }

}


void MainWindow::schriftgroesseAnpassen(QWidget* parentWidget) {
    qDebug() << "schriftgroesseAnpassen aufgerufen\n";
    qDebug() << "Label Font: " << ui->label->font() << '\n';
    qDebug() << "Beenden Font: " << ui->pushButtonBeenden->font() << '\n';
    qDebug() << "Transformieren Font: " << ui->pushButtonTransform->font() << '\n';

    //Kinder-Widgets durchstöbern
    foreach (QObject* child, parentWidget->children()) {
            QWidget* widget = qobject_cast<QWidget*>(child);
            if (widget) {
                qDebug() << "Parent-Widget: " << parentWidget << '\n';
                qDebug() << "Widget: " << widget << '\n';
                qDebug() << "Widget-Breite: " << widget->width() << '\n';
                qDebug() << "Widget-Schriftgröße: " << widget->font().pointSizeF() << '\n';

                //Schriftgröße definieren
                qreal newFontSize = 1.0;

                //Mt 22,21
                if (widget->objectName() == "labelFusszeile"){
                    newFontSize = static_cast<qreal>(widget->width()) * 0.018;
                } else if (widget->objectName() == "labelScala2" || widget->objectName() == "labelScala1"){
                    newFontSize = static_cast<qreal>(widget->width()) * 0.07;
                } else{
                     newFontSize = static_cast<qreal>(widget->width()) * 0.1;
                }

                QFont font = widget->font();
                font.setPointSizeF(newFontSize);
                widget->setFont(font);
                qDebug() << "Objektname: " << widget->objectName() << '\n';
                qDebug() << "Widget neue Schriftgröße: " << widget->font().pointSizeF() << '\n';
            }
        }
    }


//Timer-Methode, die die Anpassung der Schriftgrößen nach Programmstart freundlichst verzögert
void MainWindow::updateFontSize() {
    schriftgroesseAnpassen(ui->centralwidget);

    if (schriftenTimer->isActive()){
    schriftenTimer->stop();
    }
}

