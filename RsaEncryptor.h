#ifndef RSAENCRYPTOR_H
#define RSAENCRYPTOR_H

#include "RsaClass.h"


class RsaEncryptor : public RsaClass
{
	public:
        RsaEncryptor(); // конструктор
        ~RsaEncryptor(); // деструктор

        void readKeyInFileForEncryptor(const std::string& filename); // чтение файла открытого ключа
		void writeKeyInFileForEncryptor(CryptoPP::RSA::PublicKey m_PublicRsaKey, const std::string& aesKeyString); // сохранение публичного ключа вместе с шифрованным ключом для AES
		std::string rsaEncryptKey(const std::string& aesKeyString); // шифрование ключа AES, получение зашифрованного ключа в виде строки
        void savePrivateKey(CryptoPP::RSA::PrivateKey m_PrivateRsaKey); // сохранение приватного ключа в файл

    protected:

    private:
};

#endif // RSAENCRYPTOR_H
