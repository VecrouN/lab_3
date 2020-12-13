#ifndef RSACLASS_H
#define RSACLASS_H

// Подключение необходимых библиотек и модулей
#include <crypto++/rsa.h>
#include <crypto++/modes.h>
#include <crypto++/osrng.h>
#include <crypto++/files.h>
#include <QMessageBox>

// Класс содержит основные методы и поля для работы с алгоритмом RSA
class RsaClass
{
public:
    RsaClass();// конструктор
    RsaClass(RsaClass& other_); // конструктор копирования
    RsaClass& operator=(RsaClass& other_);// перегрузка оператора копирования
    ~RsaClass(); // деструктор

	void rsaGenerateKey(const std::string& dirPath); // генерация ключей
    CryptoPP::RSA::PublicKey getPublicRsaKey() const; // получение значения поля открытого ключа
    CryptoPP::RSA::PrivateKey getPrivateRsaKey() const; // получение значения из поля закрытого ключа

    // получение публичного ключа в виде строки
	std::string getStringPublicRsaKey() const;
    // получение закрытого ключа в виде строки
	std::string getStringRsaPrivateKey(	) const;

    // функция, которая устанавливает поле открытого ключа из строки
    void setPublicRsaKey(std::string publicRsaKeyString);
    // функция, которая устанавливает поле закрытого ключа из строки
    void setPrivateRsaKey(std::string privateRsaKeyString);

    // функция, сохраняющая открытый ключ в специальный файл
	void savePublicKey(const std::string& filename, CryptoPP::RSA::PublicKey pubKey);
    // функция, сохраняющая закрытый ключ в специальный файл
	void savePrivateKey(const std::string& filename, CryptoPP::RSA::PrivateKey privKey	);

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

