#include "..\headers\mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <QPixmap>
#include <QPushButton>
#include <QIntValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QErrorMessage>
#include <QRegularExpressionValidator>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    string encrFileIn = "";
    string decrFileIn = "";
    nKey = 0;
    eKey = 0;

    // validate to only have 19 digits (the limit of unsigned long long)
    ui->led_nKey->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{19}")));
    ui->led_eKey->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{19}")));

    //set labels
    lblValidateKeys = ui->lbl_ValidationMessage;
    lblNKey = ui->lbl_nKey;
    lblEKey = ui->lbl_eKey;
    lblSelectedEncrFile = ui->lbl_SelectedEncrFile;
    lblSelectedDecrFile = ui->lbl_SelectedDecrFile;
    lblEncrFile = ui->lbl_EncrFile;
    lblDecrFile = ui->lbl_DecrFile;

    lblSelectedEncrFile->hide();
    lblSelectedDecrFile->hide();
    lblEncrFile->hide();
    lblDecrFile->hide();
    ui->lbl_CurrentKeys->hide();
    ui->btn_DownloadEncrFile->hide();
    ui->btn_DownloadDecrFile->hide();

    //connect buttons to functions
    connect(ui->btn_ValidateKeys, SIGNAL(released()), this, SLOT(validateKeysClicked()));
    connect(ui->btn_Encrypt, SIGNAL(released()), this, SLOT(encryptClicked()));
    connect(ui->btn_Decrypt, SIGNAL(released()), this, SLOT(decryptClicked()));
    connect(ui->btn_SelectEncrFile, SIGNAL(released()), this, SLOT(selectFileEncClicked()));
    connect(ui->btn_SelectDecrFile, SIGNAL(released()), this, SLOT(selectFileDecClicked()));
    connect(ui->btn_DownloadEncrFile, SIGNAL(released()), this, SLOT(downloadEncrFileClicked()));
    connect(ui->btn_DownloadDecrFile, SIGNAL(released()), this, SLOT(downloadDecrFileClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuitTriggered() {

    remove("encrypted.txt");
    remove("decrypted.txt");
    this->close();

}

void MainWindow::validateKeysClicked(){

    QString nKeyString = ui->led_nKey->text();
    nKey = nKeyString.toULongLong();
    QString eKeyString = ui->led_eKey->text();
    eKey = eKeyString.toULongLong();

    if(nKey < 128){
        lblValidateKeys->setText("n Key must be greater than 127.");
    }
    else {
        bool isValidated = false;
        if(encrypto.isValidN(nKey)){
            unsigned long long int nKeyTemp = nKey;
            encrypto.setN(nKey);
            if(encrypto.isValidE(eKey)){
                encrypto.setE(eKey);
                lblValidateKeys->setText("Keys Successfully Validated !");
                ui->lbl_CurrentKeys->show();
                lblNKey->setText("n: " + nKeyString);
                lblEKey->setText("e: " + eKeyString);
                isValidated = true;
            }
            else {
                encrypto.setN(nKeyTemp);
            }
        }

        if (!isValidated) {
            lblValidateKeys->setText("Unsuccessful Keys Validation.");
        }
    }

}

void MainWindow::selectFileEncClicked(){

    QString encrFileInQ = QFileDialog::getOpenFileName(this, "Open Text File", QDir::homePath(), "text files (*.txt)");
    encrFileIn = encrFileInQ.toStdString();

    QFileInfo fileInfo(encrFileInQ);
    lblSelectedEncrFile->show();
    lblSelectedEncrFile->setText(fileInfo.fileName());

}

void MainWindow::selectFileDecClicked(){

    QString decrFileInQ = QFileDialog::getOpenFileName(this, "Open Text File", QDir::homePath(), "text files (*.txt)");
    decrFileIn = decrFileInQ.toStdString();

    QFileInfo fileInfo(decrFileInQ);
    lblSelectedDecrFile->show();
    lblSelectedDecrFile->setText(fileInfo.fileName());
}

void MainWindow::encryptClicked(){

    if(lblNKey->text().length() > 0 && encrFileIn.length() > 0){
        encrypto.encrypt(encrFileIn);
        lblEncrFile->show();
        ui->btn_DownloadEncrFile->show();
    }
    else if (lblNKey->text().length() == 0){
        QMessageBox::information(this, "Encryption Error", "No keys have been validated.");
    }
    else if (encrFileIn.length() == 0){
        QMessageBox::information(this, "Encryption Error", "No file has been selected.");
    }

}

void MainWindow::decryptClicked(){

    if(lblNKey->text().length() && decrFileIn.length() > 0){
        encrypto.decrypt(decrFileIn);
        lblDecrFile->show();
        ui->btn_DownloadDecrFile->show();
    }
    else if (lblNKey->text().length() == 0){
        QMessageBox::information(this, "Decryption Error", "No keys have been validated.");
    }
    else if (decrFileIn.length() == 0){
        QMessageBox::information(this, "Decryption Error", "No file has been selected.");
    }

}

void MainWindow::downloadEncrFileClicked(){

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir::homePath(), "text files (*.txt)");
    string fileSaved = fileName.toStdString();

    string fileIn = "encrypted.txt";
    ifstream in (fileIn.c_str());
    ofstream out (fileSaved.c_str());
    out << in.rdbuf();
    out.close();
    in.close();

}

void MainWindow::downloadDecrFileClicked(){

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir::homePath(), "text files (*.txt)");
    string fileSaved = fileName.toStdString();

    string fileIn = "decrypted.txt";
    ifstream in (fileIn.c_str());
    ofstream out (fileSaved.c_str());
    out << in.rdbuf();
    out.close();
    in.close();

}
