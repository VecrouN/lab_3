#include "RsaClass.h"


RsaClass::RsaClass()
{ // конструктор

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


}

void RsaClass::rsaGenerateKey(const std::string& dirPath)
{ //генерация ключей
    CryptoPP::AutoSeededRandomPool rnd;
    CryptoPP::InvertibleRSAFunction parameters;

    parameters.GenerateRandomWithKeySize (rnd, 2048);

	CryptoPP::RSA::PublicKey m_PublicRsaKey(parameters);
	CryptoPP::RSA::PrivateKey m_PrivateRsaKey(parameters);


	savePrivateKey(dirPath, m_PrivateRsaKey);
	savePublicKey(dirPath, m_PublicRsaKey);
}

CryptoPP::RSA::PublicKey RsaClass::getPublicRsaKey() const {
    return m_PublicRsaKey;
}

CryptoPP::RSA::PrivateKey RsaClass::getPrivateRsaKey() const {
    return m_PrivateRsaKey;
}

std::string RsaClass::getStringPublicRsaKey() const {
// метод принимает открытый ключ в стандартном формате, возвращает его в виде строки
    std::string publicRsaKeyString;
    CryptoPP::StringSink sourse(publicRsaKeyString);
    this->m_PublicRsaKey.Save(sourse);
    return publicRsaKeyString;
}

std::string RsaClass::getStringRsaPrivateKey() const {
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

void RsaClass::savePrivateKey(const std::string &filename, CryptoPP::RSA::PrivateKey privKey)
{ // сохранение приватного ключа в файл
    CryptoPP::ByteQueue queue;
	privKey.Save(queue);

	CryptoPP::FileSink file((filename + "/privateKey.key").c_str());



    queue.CopyTo(file);

}

void RsaClass::savePublicKey(const std::string &filename, CryptoPP::RSA::PublicKey pubKey)
{// сохранение открытого ключа в файл
    CryptoPP::ByteQueue queue;
	pubKey.Save(queue);

	CryptoPP::FileSink file((filename + "/publicKey.key").c_str());

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
