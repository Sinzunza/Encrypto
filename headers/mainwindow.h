#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rsacrypto.h"
#include <QMainWindow>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actionQuitTriggered();

    //clicked
    void validateKeysClicked();
    void encryptClicked();
    void decryptClicked();
    void selectFileEncClicked();
    void selectFileDecClicked();
    void downloadEncrFileClicked();
    void downloadDecrFileClicked();

private:
    Ui::MainWindow *ui;

    string encrFileIn;
    string decrFileIn;

    // crypto vars
    rsaCrypto encrypto;
    unsigned long long int nKey;
    unsigned long long int eKey;

    // Q vars
    QLabel *lblValidateKeys;
    QLabel *lblNKey;
    QLabel *lblEKey;
    QLabel *lblSelectedEncrFile;
    QLabel *lblSelectedDecrFile;
    QLabel *lblEncrFile;
    QLabel *lblDecrFile;
};
#endif // MAINWINDOW_H
