#include "rsaclass.h"

#include <iostream>
#include <fstream>
#include <crypto++/modes.h>
#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>
#include <crypto++/base64.h>
#include <crypto++/files.h>

RsaClass::RsaClass()
{ // конструктор
    //CryptoPP::Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9");
    //m_PublicRsaKey.Initialize(e,d);
    //m_PrivateRsaKey.Initialize(n,e,d);
}

// конструктор копирования
RsaClass::RsaClass(RsaClass &other_){

    this->m_PrivateRsaKey.SetPrime1(other_.m_PrivateRsaKey.GetPrime1());
    this->m_PrivateRsaKey.SetPrime2(other_.m_PrivateRsaKey.GetPrime2());
    this->m_PrivateRsaKey.SetPrivateExponent(other_.m_PrivateRsaKey.GetPrivateExponent());
    this->m_PublicRsaKey.SetPublicExponent(other_.m_PublicRsaKey.GetPublicExponent());
    this->m_PublicRsaKey.SetModulus(other_.m_PublicRsaKey.GetModulus());
}

RsaClass &RsaClass::operator=(RsaClass &other_)
{// перегрузка оператора сравнения

    if (this==&other_)
        return *this;
    else {
        other_.m_PrivateRsaKey.SetPrime1(this->m_PrivateRsaKey.GetPrime1());
        other_.m_PrivateRsaKey.SetPrime2(this->m_PrivateRsaKey.GetPrime2());
        other_.m_PrivateRsaKey.SetPrivateExponent(this->m_PrivateRsaKey.GetPrivateExponent());
        other_.m_PublicRsaKey.SetPublicExponent(this->m_PublicRsaKey.GetPublicExponent());
        other_.m_PublicRsaKey.SetModulus(this->m_PublicRsaKey.GetModulus());
        return *this;
    }
}

RsaClass::~RsaClass()
{ // деструктор

    this->m_PublicRsaKey.~RSAFunction();
    this->m_PrivateRsaKey.~InvertibleRSAFunction();

}

void RsaClass::rsaGenerateKey()
{ //генерация ключей
    CryptoPP::AutoSeededRandomPool rnd;
    CryptoPP::InvertibleRSAFunction parameters;

    parameters.GenerateRandomWithKeySize (rnd, 2048);

    CryptoPP::RSA::PublicKey m_PublicRsaKey(parameters);
    CryptoPP::RSA::PrivateKey m_PrivateRsaKey(parameters);

    savePrivateKey("rsaPrivateKey.key");
    savePublicKey("rsaPublicKey.key");
}

CryptoPP::RSA::PublicKey RsaClass::getPublicRsaKey() const {
    return m_PublicRsaKey;
}

CryptoPP::RSA::PrivateKey RsaClass::getPrivateRsaKey() const {
    return m_PrivateRsaKey;
}

std::string RsaClass::getStringPublicRsaKey(CryptoPP::RSA::PublicKey& m_PublicRsaKey) const {
// метод принимает открытый ключ в стандартном формате, возвращает его в виде строки
    std::string publicRsaKeyString;
    CryptoPP::StringSink sourse(publicRsaKeyString);
    this->m_PublicRsaKey.Save(sourse);
    return publicRsaKeyString;
}

std::string RsaClass::getStringRsaPrivateKey(CryptoPP::RSA::PublicKey& m_PrivateRsaKey) const {
// метод принимает закрытый ключ в стандартном формате, возвращает его в виде строки
    std::string privateRsaKeyString;
    CryptoPP::StringSink sourse(privateRsaKeyString);
    this->m_PrivateRsaKey.Save(sourse);
    return privateRsaKeyString;
}

void RsaClass::setPublicRsaKey(std::string publicRsaKeyString) {
// метод принимает открытый ключ как строку, и записывает его в поле класса
    CryptoPP::StringSource sourse(publicRsaKeyString,true);
    this->m_PublicRsaKey.Load(sourse);
}

void RsaClass::setPrivateRsaKey(std::string privateRsaKeyString) {
// метод принимает открытый ключ как строку, и записывает его в поле класса

    CryptoPP::StringSource sourse(privateRsaKeyString,true);
    this->m_PrivateRsaKey.Load(sourse);
}

void RsaClass::savePrivateKey(const std::string &filename)
{ // сохранение приватного ключа в файл
    CryptoPP::ByteQueue queue;
    this->m_PrivateRsaKey.Save(queue);

    CryptoPP::FileSink file(filename.c_str());

    queue.CopyTo(file);
}

void RsaClass::savePublicKey(const std::string &filename)
{// сохранение открытого ключа в файл
    CryptoPP::ByteQueue queue;
    this->m_PublicRsaKey.Save(queue);

    CryptoPP::FileSink file(filename.c_str());

    queue.CopyTo(file);
}

void RsaClass::LoadPublicKey(const std::string &filename)
{ // извлечение открытого ключа из файла
    CryptoPP::ByteQueue queue;
    CryptoPP::FileSource file(filename.c_str(), true);
    file.TransferTo(queue);

    this->m_PublicRsaKey.Load(queue);
}

void RsaClass::LoadPrivateKey(const std::string &filename)
{ // извлечение закрытого ключа из файла
    CryptoPP::ByteQueue queue;
    CryptoPP::FileSource file(filename.c_str(), true);
    file.TransferTo(queue);

    this->m_PrivateRsaKey.Load(queue);
}
