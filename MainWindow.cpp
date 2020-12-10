#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <iostream>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	this->m_aesEncryptor = new AesEncryptor();
	m_isTextToDecryptReady = false;
	m_isKeyToDecryptReady = false;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

AesEncryptor* MainWindow::getAesEncryptor()
{
	return this->m_aesEncryptor;
}

void MainWindow::setNewIV_PublicKey()
{
	byte tmpArray[CryptoPP::AES::BLOCKSIZE];
	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE-1; ++i)
	{
		tmpArray[i] = this->m_TmpByteArray[i];
	}
	m_aesEncryptor->setNewInitializationVector(tmpArray);
	for(int i = CryptoPP::AES::BLOCKSIZE; i < CryptoPP::AES::BLOCKSIZE+CryptoPP::AES::DEFAULT_KEYLENGTH-1; ++i)
	{
		tmpArray[i-CryptoPP::AES::BLOCKSIZE] = this->m_TmpByteArray[i];
	}
	m_aesEncryptor->setNewPrivateAesKey(m_TmpByteArray);
	m_aesEncryptor->setIsNewKey(true);
	m_aesEncryptor->setIsKeyToEncryptReady(true);
}



void MainWindow::on_createNewRsaKeysPushButton_clicked()
{
	memset( m_TmpByteArray , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	readyIndex = 0;
	ptrReadyIndex = &readyIndex;
	m_Dialog = new createNewKeys(m_TmpByteArray, ptrReadyIndex, this);
	connect(m_Dialog, &createNewKeys::accepted, this, &MainWindow::setNewIV_PublicKey);
	m_Dialog->setModal(true);
	m_Dialog->show();
}

void MainWindow::on_openFileToEncryptPushButton_clicked()
{
	QString QFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													"/home/victor/Documents/miem/oop/build-lab_3-Desktop_Qt_5_15_1_GCC_64bit-Debug",
													tr("TextFile (*.txt)"));
	if(QFileName.toStdString() != "")
	{
		m_filePathToEncrypt = QFileName.toStdString();
		this->m_isTextToDecryptReady = true;
	}
}

void MainWindow::on_pushButton_clicked() // кнопка шифровки
{
	if(this->m_aesEncryptor->getIsKeyToEncryptReady() && this->m_isTextToEncryptReady)
	{

		this->m_aesEncryptor->aesEncryptFile(this->m_filePathToEncrypt);
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("Вы не выбрали ключ или файл");
		msgBox.exec();
	}
}


void MainWindow::on_pushButton_2_clicked() // кнопка шифровки
{
	/*
	 * создаем объект аес энкрипт
	 * читаем текст
	 */

}

void MainWindow::on_openPublicRsaKeyFilePushButton_clicked() //кнопка открыть публичный ключ
{
	m_aesEncryptor->setIsNewKey(false);
	// считываем публичный ключ, в котором хранится зашифрованный аес ключ
	// m_aesEncryptor->setNewPrivateAesKey(newKey)

	/*
	 * считываем файл публичного ключа и записываем в объект rsa энкрипт
	 */
}




