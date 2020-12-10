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
      
    protected:

    private:
        CryptoPP::RSA::PublicKey m_PublicRsaKey; // открытый ключ шифрования
        CryptoPP::RSA::PrivateKey m_PrivateRsaKey; // закрытый ключ шифрования
};

#endif // RSA_H
