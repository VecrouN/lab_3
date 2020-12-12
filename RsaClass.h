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
    RsaClass& operator=(RsaClass& other_);// перегрузка оператора копирования
    ~RsaClass(); // деструктор

    void rsaGenerateKey(); // генерация ключей
    CryptoPP::RSA::PublicKey getPublicRsaKey() const; // получение значения поля открытого ключа
    CryptoPP::RSA::PrivateKey getPrivateRsaKey() const; // получение значения из поля закрытого ключа

    // получение публичного ключа в виде строки
    std::string getStringPublicRsaKey(CryptoPP::RSA::PublicKey& m_PublicRsaKey) const;
    // получение закрытого ключа в виде строки
    std::string getStringRsaPrivateKey(CryptoPP::RSA::PublicKey& m_PrivateRsaKey) const;

    // функция, которая устанавливает поле открытого ключа из строки
    void setPublicRsaKey(std::string publicRsaKeyString);
    // функция, которая устанавливает поле закрытого ключа из строки
    void setPrivateRsaKey(std::string privateRsaKeyString);

    // функция, сохраняющая открытый ключ в специальный файл
    void savePublicKey(const std::string& filename);
    // функция, сохраняющая закрытый ключ в специальный файл
    void savePrivateKey(const std::string& filename);

    // функция, загружающая открытый ключ из специального файл
    void LoadPublicKey(const std::string& filename);
    // функция, загружающая открытый ключ из специального файл
    void LoadPrivateKey(const std::string& filename);

  protected:

    CryptoPP::RSA::PublicKey m_PublicRsaKey; // открытый ключ шифрования
    CryptoPP::RSA::PrivateKey m_PrivateRsaKey; // закрытый ключ шифрования

  private:

};

#endif // RSACLASS_H


#endif // RSACLASS_H
