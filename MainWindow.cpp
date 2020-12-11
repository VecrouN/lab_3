#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	this->m_aesEncryptor = new AesEncryptor(this);
	this->m_aesDecryptor = new AesDecryptor(this);
	this->m_rsaEncryptor = new RsaEncryptor();
	this->m_rsaDecryptor = new RsaDecryptor();

	m_isTextToDecryptReady = false;
	m_isTextToEncryptReady = false;
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


AesDecryptor* MainWindow::getAesDecryptor()
{
	return this->m_aesDecryptor;
}


void MainWindow::setNewIV_PublicKey()
{
	byte tmpArray[CryptoPP::AES::BLOCKSIZE];
	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
	{
		tmpArray[i] = this->m_TmpByteArray[i];
	}
	m_aesEncryptor->setNewInitializationVector(tmpArray);
	std::string tmpConvertString = "";

	for(int i = CryptoPP::AES::BLOCKSIZE; i < CryptoPP::AES::BLOCKSIZE+CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
	{
		tmpArray[i-CryptoPP::AES::BLOCKSIZE] = this->m_TmpByteArray[i];
		tmpConvertString.push_back(static_cast<char>(this->m_TmpByteArray[i]));
	}

	m_aesEncryptor->setNewPrivateAesKey(tmpArray);
	m_aesEncryptor->setIsNewKey(true);
	m_aesEncryptor->setIsKeyToEncryptReady(true);
	std::string encryptedKey = m_rsaEncryptor->rsaEncryptKey(tmpConvertString);


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

void MainWindow::on_openFileToEncryptPushButton_clicked() // клик по кнопке открыть файл для шифровки
{
	QString QFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													"/home/victor/Documents/miem/oop/build-lab_3-Desktop_Qt_5_15_1_GCC_64bit-Debug",
													tr("TextFile (*.txt)"));
	if(QFileName.toStdString() != "")
	{
		m_filePathToEncrypt = QFileName.toStdString();
		this->m_isTextToEncryptReady = true;
		int i;
		for(i = m_filePathToEncrypt.length(); i > 0 && m_filePathToEncrypt[i] != '/'; --i);
		++i;
		this->ui->fileToEncryptLineEdit->setText(QString::fromStdString(m_filePathToEncrypt.substr(i, m_filePathToEncrypt.length()-1)));

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


void MainWindow::on_pushButton_2_clicked() // кнопка дешифровки
{
	if(this->m_aesDecryptor->getIsKeyToDecryptReady() && this->m_isTextToDecryptReady)
	{
		this->m_aesDecryptor->aesDecryptFile(this->m_filePathToDecrypt);
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("Вы не выбрали ключ или файл");
		msgBox.exec();
	}

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





void MainWindow::on_openFileToDecryptPushButoon_clicked() // клик по кнопке открыть файл для дешифровки
{
	QString QFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													"/home/victor/Documents/miem/oop/build-lab_3-Desktop_Qt_5_15_1_GCC_64bit-Debug",
													tr("TextFile (*.dat)"));
	if(QFileName.toStdString() != "")
	{
		this->m_filePathToDecrypt = QFileName.toStdString();
		this->m_isTextToDecryptReady = true;
		int i;
		for(i = m_filePathToDecrypt.length(); i > 0 && m_filePathToDecrypt[i] != '/'; --i);
		++i;
		this->ui->pathFileToDecryptLineEdit->setText(QString::fromStdString(m_filePathToDecrypt.substr(i, m_filePathToDecrypt.length()-1)));

	}
}

void MainWindow::on_openPrivateRsaKeyFilePushButoon_clicked() // открыть ключ для дешифровки
{
	byte tmpArray [CryptoPP::AES::DEFAULT_KEYLENGTH];
	memset(tmpArray, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	this->m_aesDecryptor->setIsKeyToDecryptReady(true);
	this->m_aesDecryptor->setNewPrivateAesKey(tmpArray);

}
