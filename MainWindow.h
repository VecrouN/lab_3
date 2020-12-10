#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "AesDecryptor.h"
#include "AesEncryptor.h"
#include "createNewKeys.h"
#include "RsaDecryptor.h"
#include "RsaEncryptor.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	AesEncryptor *getAesEncryptor();
	//void setNewIV_PublicKey();

	protected: int readyIndex;
	protected: int *ptrReadyIndex;

	private slots:

	void on_createNewRsaKeysPushButton_clicked();

	void on_openFileToEncryptPushButton_clicked();

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_openPublicRsaKeyFilePushButton_clicked();

	void setNewIV_PublicKey();


	private: Ui::MainWindow *ui;
	private:RsaDecryptor m_rsaDecryptor;
	private:RsaEncryptor m_rsaEncryptor;
	private:AesDecryptor m_aesDecryptor;
	private:AesEncryptor *m_aesEncryptor;
	private:createNewKeys *m_Dialog;
	std::string m_filePathToEncrypt;
	byte m_TmpByteArray[ CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE];
	byte * ptrPrivateAesKey;

	bool m_isTextToEncryptReady;
	bool m_isTextToDecryptReady;
	bool m_isKeyToDecryptReady;
};
#endif // MAINWINDOW_H
