#ifndef AESENCRYPTOR_H
#define AESENCRYPTOR_H

#include "AesClass.h"

#include <QMainWindow>


class AesEncryptor : public AesClass
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
	public: void setNewInitializationVector(const byte _newPublicInitializationVector[]);
	public: void setIsKeyToEncryptReady(bool _isKeyToEncryptReady);
	public: bool getIsKeyToEncryptReady();
	public: std::string getEncryptedAesKey();
	public: void setEncryptedAesKey(const std::string &_encryptedAesKey);

	  // ************* //
	 //    private    //
	// ************* //
	private: byte m_PrivateTmpArray[ CryptoPP::AES::BLOCKSIZE+CryptoPP::AES::DEFAULT_KEYLENGTH ]; // вектор инициализации для шифровки 1ого блока, не скрывается
	private: std::string m_encryptedAesKey = "";

	bool m_isKeyToEncryptReady;
};

#endif // AESENCRYPTOR_H
