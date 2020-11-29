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


	std::string filePath = QFileName.toStdString();
	std::cout<<"old path = "<<filePath<<std::endl;
	std::ofstream outFile;

	int i;
	for(i = filePath.length(); i > 0 && filePath[i] != '/'; --i);
	++i;
	std::string path = filePath.substr(0, i);
	std::string name = filePath.substr(i, filePath.length()-1);
	name = "decrypted_" + name;
	std::string outFilePath = path+name;

	/*
	outFile.open(outFilePath);
	if(outFile.is_open())
	{
		outFile<<this->m_PublicInitializationVector<<"\n";
		outFile<<encryptedText;
	}
	outFile.close();
	*/


	// std::cout<<fileName.toStdString()<<std::endl;

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







