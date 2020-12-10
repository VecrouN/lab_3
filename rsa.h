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
   
    CryptoPP::RSA::PublicKey getPublicRsaKey(); // получение публичного ключа
    CryptoPP::RSA::PrivateKey getPrivateRsaKey(); // получение закрытого ключа
   
    std::string getStringPublicRsaKey(); // получение публичного ключа в виде строки
    std::string getStringRsaPrivateKey(); // получение закрытого ключа в виде строки
   
    CryptoPP::RSA::PublicKey setPublicRsaKey(); // функция, которая устанавливает поле открытого ключа
    CryptoPP::RSA::PrivateKey setPrivateRsaKey(); // функция, которая устанавливает поле закрытого ключа

  protected:

  private:
      CryptoPP::RSA::PublicKey m_PublicRsaKey; // открытый ключ шифрования
      CryptoPP::RSA::PrivateKey m_PrivateRsaKey; // закрытый ключ шифрования
};

#endif // RSA_H
