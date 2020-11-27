#ifndef AESENCRYPTOR_H
#define AESENCRYPTOR_H

#include "Encryptor.h"

#include <crypto++/aes.h>


#include <crypto++/rsa.h>
#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <iostream>
#include <fstream>

class AesEncryptor : public Encryptor
{
	public:
		AesEncryptor();
		void AesEncryptFile();
	private: byte m_PrivateAesKey[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // ключ шифрования
	private: byte m_PublicInitializationVector[ CryptoPP::AES::BLOCKSIZE ]; // вектор инициализации для шифровки 1ого блока, не скрывается
};

#endif // AESENCRYPTOR_H
