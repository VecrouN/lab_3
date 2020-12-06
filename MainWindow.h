#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "AesDecryptor.h"
#include "AesEncryptor.h"


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
	void on_pushButton_2_clicked();

	private:
    Ui::MainWindow *ui;
	// AesDecryptor m_AesDecryptor;
	// AesEncryptor m_AesEncryptor;
	//byte aesKey[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // ключ для (де)шифрования
};
#endif // MAINWINDOW_H
