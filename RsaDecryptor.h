#ifndef RSADECRYPTOR_H
#define RSADECRYPTOR_H

#include "Decryptor.h"

#include <crypto++/modes.h>
#include <crypto++/rsa.h>

class RsaDecryptor : public Decryptor
{
public:
    RsaDecryptor(); // конструктор
    RsaDecryptor(RsaDecryptor& other_); // конструктор копирования
    RsaDecryptor& operator=(const RsaDecryptor& other_);// перегрузка оператора копирования
    ~RsaDecryptor(); // деструктор

    void rsaGenerateKey(); // генерация ключей
    void readPrivateKey(const std::string& filename); // чтение файла с закрытым ключом RSA
    void readKeyInFileForDecryptor(const std::string& filename); // чтение публичного ключа вместе с шифрованным ключом для AES
    std::string rsaDecryptKey(std::string& aesKeyString); // расшифровка ключа AES, получение зашифрованного ключа в виде строки

protected:

private:
    CryptoPP::RSA::PublicKey m_PublicRsaKey; // открытый ключ шифрования
    CryptoPP::RSA::PrivateKey m_PrivateRsaKey; // закрытый ключ шифрования
};

#endif // RSADECRYPTOR_H
