#ifndef RSA_H
#define RSA_H

// Подключение необходимых библиотек и модулей
#include <crypto++/rsa.h>
#include <crypto++/modes.h>
#include <iostream>
#include <fstream>

// Класс содержит основные методы и поля для работы с алгоритмом RSA
class RSA
{
public:
    RSA();// конструктор
    RSA(RSA& other_); // конструктор копирования
    RSA& operator=(const RSA& other_);// перегрузка оператора копирования
    ~RSA(); // деструктор

    void rsaGenerateKey(); // генерация ключей
    
    CryptoPP::RSA::PublicKey getPublicRsaKey() const; // получение публичного ключа
    CryptoPP::RSA::PrivateKey getPrivateRsaKey() const; // получение закрытого ключа

    // получение публичного ключа в виде строки
    std::string getStringPublicRsaKey(CryptoPP::RSA::PublicKey m_PublicRsaKey) const;

    // получение закрытого ключа в виде строки
    std::string getStringRsaPrivateKey(CryptoPP::RSA::PublicKey m_PrivateRsaKey) const;

    // функция, которая устанавливает поле открытого ключа
    void setPublicRsaKey(std::string& PublicRsaKeyString, CryptoPP::RSA::PublicKey m_PublicRsaKey);

    // функция, которая устанавливает поле закрытого ключа
    void setPrivateRsaKey(std::string& PrivateRsaKeyString,CryptoPP::RSA::PublicKey m_PrivateRsaKey);

  protected:

  private:
      CryptoPP::RSA::PublicKey m_PublicRsaKey; // открытый ключ шифрования
      CryptoPP::RSA::PrivateKey m_PrivateRsaKey; // закрытый ключ шифрования
};

#endif // RSA_H
