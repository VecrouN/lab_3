#ifndef AESDECRYPTOR_H
#define AESDECRYPTOR_H

#include "Decryptor.h"

#include <fstream>
#include <QFileDialog>

#include <crypto++/aes.h>

class AesDecryptor : public Decryptor
{

	  // ************* //
	 //    public     //
	// ************* //
	public: AesDecryptor();
	public: ~AesDecryptor();
	public: void aesDecryptFile(const std::string& filePath);
	public: void setPublicInitializationVector(byte (&changedPublicInitializationVector)[ CryptoPP::AES::BLOCKSIZE ]);
	public: void readFileForDecryption(const std::string& filePath, std::string& textForDecryption);
	public: void writeFileForDecryption(const std::string& filePath, const std::string& encryptedText);

	  // ************* //
	 //   protected   //
	// ************* //
	protected:

	  // ************* //
	 //    private    //
	// ************* //
	private: byte m_PrivateAesKey[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // ключ шифрования
	private: byte m_PublicInitializationVector[ CryptoPP::AES::BLOCKSIZE ]; // вектор инициализации для шифровки 1ого блока, не скрывается

};

#endif // AESDECRYPTOR_H
