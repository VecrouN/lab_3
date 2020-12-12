#ifndef AESCLASS_H
#define AESCLASS_H

#include <crypto++/rsa.h>
#include <crypto++/aes.h>
#include <crypto++/modes.h>

#include "RsaEncryptor.h"
#include "RsaDecryptor.h"

#include <fstream>
#include <QFileDialog>
#include <QMessageBox>

class AesClass
{
	public:	AesClass();
	public:	~AesClass();
	public: void setNewPrivateAesKey(const byte _newPrivateAesKey[]);


	protected: byte m_PrivateAesKey[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // ключ шифрования
	protected: byte m_PublicInitializationVector[ CryptoPP::AES::BLOCKSIZE ]; // вектор инициализации для шифровки 1ого блока, не скрывается
	protected: QWidget *m_parent = nullptr;

};

#endif // AESCLASS_H
