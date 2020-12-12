#ifndef RSACLASS_H
#define RSACLASS_H

// Подключение необходимых библиотек и модулей
#include <crypto++/rsa.h>
#include <crypto++/modes.h>
#include <iostream>
#include <fstream>

// Класс содержит основные методы и поля для работы с алгоритмом RSA
class RsaClass
{
public:
    RsaClass();// конструктор
    RsaClass(RsaClass& other_); // конструктор копирования
    RsaClass& operator=(const RsaClass& other_);// перегрузка оператора копирования
    ~RsaClass(); // деструктор

    void rsaGenerateKey(); // генерация ключей
    CryptoPP::RSA::PublicKey getPublicRsaKey() const; // получение публичного ключа
    CryptoPP::RSA::PrivateKey getPrivateRsaKey() const; // получение закрытого ключа

    // получение публичного ключа в виде строки
    std::string getStringPublicRsaKey(CryptoPP::RSA::PublicKey m_PublicRsaKey) const;

    // получение закрытого ключа в виде строки
    std::string getStringRsaPrivateKey(CryptoPP::RSA::PublicKey m_PrivateRsaKey) const;

    // функция, которая устанавливает поле открытого ключа
    void setPublicRsaKey(std::string publicRsaKeyString, CryptoPP::RSA::PublicKey m_PublicRsaKey);

    // функция, которая устанавливает поле закрытого ключа
    void setPrivateRsaKey(std::string privateRsaKeyString,CryptoPP::RSA::PublicKey m_PrivateRsaKey);
    
    void savePublicKey(const std::string& filename, CryptoPP::RSA::PublicKey m_PublicRsaKey);
    void savePrivateKey(const std::string& filename, CryptoPP::RSA::PrivateKey m_PrivateRsaKey);

    void LoadPublicKey(const std::string& filename,CryptoPP::RSA::PublicKey& m_PublicRsaKey);
    void LoadPrivateKey(const std::string& filename,CryptoPP::RSA::PrivateKey& m_PrivateRsaKey);



  protected:
      CryptoPP::RSA::PublicKey m_PublicRsaKey; // открытый ключ шифрования
      CryptoPP::RSA::PrivateKey m_PrivateRsaKey; // закрытый ключ шифрования
    
  private:
    
};

#endif // RSACLASS_H
