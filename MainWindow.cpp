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
	this->m_aesEncryptor->setNewInitializationVector(tmpArray); // установка поля iv в аес енкриптор
	std::string tmpConvertString = "";

	for(int i = CryptoPP::AES::BLOCKSIZE; i < CryptoPP::AES::BLOCKSIZE+CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
	{
		tmpArray[i-CryptoPP::AES::BLOCKSIZE] = this->m_TmpByteArray[i];
		tmpConvertString.push_back(static_cast<char>(this->m_TmpByteArray[i]));
	}

	m_aesEncryptor->setNewPrivateAesKey(tmpArray); // установка ключа в аес енкриптор
	// m_aesEncryptor->setIsKeyToEncryptReady(true);
	this->m_aesEncryptor->setEncryptedAesKey(m_rsaEncryptor->rsaEncryptKey(tmpConvertString)); // сохранение в енкрипт шифрованого ключа


	this->m_aesEncryptor->aesEncryptFile(this->m_filePathToEncrypt);
}



void MainWindow::on_createNewRsaKeysPushButton_clicked()
{
	QString QDirectoryPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
													"/home/victor/Documents/miem/oop/build-lab_3-Desktop_Qt_5_15_1_GCC_64bit-Debug",
													QFileDialog::ShowDirsOnly
													| QFileDialog::DontResolveSymlinks);

	if(QDirectoryPath.toStdString() != "")
	{
		// генерация рса ключей

		std::string directoryPath = QDirectoryPath.toStdString();

		this->m_rsaEncryptor->rsaGenerateKey();
		this->m_aesEncryptor->setIsKeyToEncryptReady(true);
		this->m_rsaEncryptor->savePrivateKey(directoryPath);
		this->m_rsaEncryptor->savePublicKey(directoryPath);

		this->ui->publicRsaKeyPathLineEdit->setText("publicRsaKey.dat");
		QMessageBox msgBox;
		msgBox.setText("Ключи созданы");
		msgBox.exec();

		/*
		memset( m_TmpByteArray , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
		readyIndex = 0;
		ptrReadyIndex = &readyIndex;
		m_Dialog = new createNewKeys(m_TmpByteArray, ptrReadyIndex, this);
		connect(m_Dialog, &createNewKeys::accepted, this, &MainWindow::setNewIV_PublicKey);
		m_Dialog->setModal(true);
		m_Dialog->show();
		*/
	}


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

		memset( m_TmpByteArray , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
		readyIndex = 0;
		ptrReadyIndex = &readyIndex;

		m_Dialog = new createNewKeys(m_TmpByteArray, ptrReadyIndex, this);
		connect(m_Dialog, &createNewKeys::accepted, this, &MainWindow::setNewIV_PublicKey);
		m_Dialog->setModal(true);
		m_Dialog->show();

		// this->m_aesEncryptor->aesEncryptFile(this->m_filePathToEncrypt);
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
		this->m_aesDecryptor->setRsaDecryptor(this->m_rsaDecryptor);
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

	QString QFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													"/home/victor/Documents/miem/oop/build-lab_3-Desktop_Qt_5_15_1_GCC_64bit-Debug",
													tr("TextFile (*.dat)"));
	if(QFileName.toStdString() != "")
	{
		std::string pathToPublicKey = QFileName.toStdString();
		this->m_rsaEncryptor->readPublicKey(pathToPublicKey);
		this->m_aesEncryptor->setIsKeyToEncryptReady(true);

		int i;
		for(i = pathToPublicKey.length(); i > 0 && pathToPublicKey[i] != '/'; --i);
		++i;

		this->ui->fileToEncryptLineEdit->setText(QString::fromStdString(pathToPublicKey.substr(i, pathToPublicKey.length()-1)));
	}
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

	QString QFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													"/home/victor/Documents/miem/oop/build-lab_3-Desktop_Qt_5_15_1_GCC_64bit-Debug",
													tr("TextFile (*.dat)"));
	if(QFileName.toStdString() != "")
	{
		std::string pathToPrivateKey = QFileName.toStdString();
		this->m_rsaDecryptor->readPrivateKey(pathToPrivateKey);
		this->m_aesDecryptor->setIsKeyToDecryptReady(true);

		int i;
		for(i = pathToPrivateKey.length(); i > 0 && pathToPrivateKey[i] != '/'; --i);
		++i;

		this->ui->pathFileToDecryptLineEdit->setText(QString::fromStdString(pathToPrivateKey.substr(i, pathToPrivateKey.length()-1)));
	}
}
