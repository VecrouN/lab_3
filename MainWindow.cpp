#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <iostream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
	QString QFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													"/home/victor/Documents/miem/oop/build-lab_3-Desktop_Qt_5_15_1_GCC_64bit-Debug",
													tr("TextFile (*.txt)"));
	std::string fileName = QFileName.toStdString();
	// std::cout<<fileName.toStdString()<<std::endl;
	int i;
	for(i = fileName.length(); i > 0 && fileName[i] != '/'; --i);
	++i;
	std::cout<<fileName<<std::endl;
	std::cout<<fileName.substr(i, fileName.length()-1)<<std::endl;
	ui->lineEdit->setText(QString::fromStdString(fileName.substr(i, fileName.length()-1)));
	/*
	for(int i = fileName[fileName.length()]; i >= 0 && fileName[i] == '/'; --i)
	{
		std::cout<<fileName[i]<<std::endl;

	}
	for(int i = fileName.length()-1; i > 0 || fileName[i] == '/'; --i)
	{

	}
	*/
}







