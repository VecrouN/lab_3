#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include "AesDecryptor.h"
#include "AesEncryptor.h"
#include "CreateNewKeys.h"

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
	AesDecryptor *getAesDecryptor();
	//void setNewIV_PublicKey();

	protected: int readyIndex;

	private slots:

	void on_createNewRsaKeysPushButton_clicked();

	void on_openFileToEncryptPushButton_clicked();

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_openPublicRsaKeyFilePushButton_clicked();

	void setNewIV_PublicKey();


	void on_openFileToDecryptPushButoon_clicked();

	void on_openPrivateRsaKeyFilePushButoon_clicked();

	private: Ui::MainWindow *ui = nullptr;
	private:RsaDecryptor *m_rsaDecryptor = nullptr;
	private:RsaEncryptor *m_rsaEncryptor = nullptr;
	private:AesEncryptor *m_aesEncryptor = nullptr;
	private:AesDecryptor *m_aesDecryptor = nullptr;
	private:CreateNewKeys *m_Dialog = nullptr;
	byte *ptrPrivateAesKey = nullptr;
	protected: int *ptrReadyIndex = nullptr;


	std::string m_filePathToEncrypt;
	std::string m_filePathToDecrypt;
	byte m_TmpByteArray[ CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE];
	std::string m_filePath = "";

	bool m_isTextToEncryptReady;
	bool m_isTextToDecryptReady;

};
#endif // MAINWINDOW_H
