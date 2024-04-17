#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pushButtonTransform_clicked();

    void on_pushButtonBeenden_clicked();

    void on_spinBoxMax2_editingFinished();

    void on_pushButtonKopieren_clicked();

    void on_spinBoxBewertung1_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    QSize fenstergroesseOriginal;
    void schriftgroesseAnpassen(QWidget*);
    QTimer *schriftenTimer;
    void updateFontSize();


protected:
    void resizeEvent(QResizeEvent *event) override;


};
#endif // MAINWINDOW_H
