#ifndef AESENCRYPTOR_H
#define AESENCRYPTOR_H

#include "Encryptor.h"

#include "RsaEncryptor.h"
#include "RsaDecryptor.h"


#include <QMainWindow>
#include <QMessageBox>
#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <iostream>
#include <fstream>

class AesEncryptor : public Encryptor
{
	  // ************* //
	 //    public     //
	// ************* //
	public: AesEncryptor();
	public: AesEncryptor(QWidget *parent);
	public: AesEncryptor(AesEncryptor& _other);
	public: AesEncryptor& operator=(const AesEncryptor& _other);
	public: ~AesEncryptor();
	public: void aesEncryptFile(const std::string& filePath);
	public: void createNewPublicInitializationVector(byte (&changedPublicInitializationVector)[ CryptoPP::AES::BLOCKSIZE ]);
	public: void readFileForEncryption(const std::string& filePath, std::string& textForEncryption);
	public: void writeFileForEncryption(const std::string& filePath, const std::string& encryptedText);
	public: void addEncryptToPath(std::string& filePath);
	public: void setIsNewKey(bool _newValue);
	public: void setNewInitializationVector(const byte _newPublicInitializationVector[]);
	public: void setNewPrivateAesKey(const byte _newPrivateAesKey[]);
	public: void setIsKeyToEncryptReady(bool _isKeyToEncryptReady);
	public: bool getIsKeyToEncryptReady();

	  // ************* //
	 //   protected   //
	// ************* //
	protected:

	  // ************* //
	 //    private    //
	// ************* //
	private: byte m_PrivateAesKey[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // ключ шифрования
	private: byte m_PublicInitializationVector[ CryptoPP::AES::BLOCKSIZE ]; // вектор инициализации для шифровки 1ого блока, не скрывается
	private: byte m_PrivateTmpArray[ CryptoPP::AES::BLOCKSIZE+CryptoPP::AES::DEFAULT_KEYLENGTH ]; // вектор инициализации для шифровки 1ого блока, не скрывается

	private: QWidget *m_parent;

	private: bool m_isNewKey;
	bool m_isKeyToEncryptReady;
};

#endif // AESENCRYPTOR_H
