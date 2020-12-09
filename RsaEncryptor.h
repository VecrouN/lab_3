#ifndef RSAENCRYPTOR_H
#define RSAENCRYPTOR_H

#include "Encryptor.h"

class RsaEncryptor : public Encryptor
{
public:
        RsaEncryptor(); // конструктор
        RsaEncryptor(RsaEncryptor& other_); // конструктор копирования
        RsaEncryptor& operator=(const RsaEncryptor& other_);// перегрузка оператора копирования
        ~RsaEncryptor(); // деструктор

        void rsaGenerateKey(); // генерация ключей
        void writeKeyInFileForEncryptor(CryptoPP::RSA::PublicKey m_PublicRsaKey, std::string& aesKeyString); // сохранение публичного ключа вместе с шифрованным ключом для AES
        std::string rsaEncryptKey(std::string& aesKeyString); // шифрование ключа AES, получение зашифрованного ключа в виде строки
        void savePrivateKey(CryptoPP::RSA::PrivateKey m_PrivateRsaKey); // сохранение приватного ключа в файл

    protected:

    private:
        CryptoPP::RSA::PublicKey m_PublicRsaKey; // открытый ключ шифрования
        CryptoPP::RSA::PrivateKey m_PrivateRsaKey; // ключ шифрования
};

#endif // RSAENCRYPTOR_H
