#include "RsaClass.h"

#include <iostream>
#include <fstream>
#include <crypto++/modes.h>
#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>

RsaClass::RsaClass()
{ // конструктор
    CryptoPP::Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9");
	//m_PublicRsaKey.Initialize(e,d);
	//m_PrivateRsaKey.Initialize(n,e,d);
}

// конструктор копирования
RsaClass::RsaClass(RsaClass &other_) {
	
    this->m_PrivateRsaKey.SetPrime1(other_.m_PrivateRsaKey.GetPrime1());
    this->m_PrivateRsaKey.SetPrime2(other_.m_PrivateRsaKey.GetPrime2());
    this->m_PrivateRsaKey.SetPrivateExponent(other_.m_PrivateRsaKey.GetPrivateExponent());
    this->m_PublicRsaKey.SetPublicExponent(other_.m_PublicRsaKey.GetPublicExponent());
    this->m_PublicRsaKey.SetModulus(other_.m_PublicRsaKey.GetModulus());
}

RsaClass &RsaClass::operator=(const RsaClass &other_)
{// перегрузка оператора сравнения
	
    if (this==&other_)
        return *this;
    else {
    	this->m_PrivateRsaKey.SetPrime1(other_.m_PrivateRsaKey.GetPrime1());
    	this->m_PrivateRsaKey.SetPrime2(other_.m_PrivateRsaKey.GetPrime2());
    	this->m_PrivateRsaKey.SetPrivateExponent(other_.m_PrivateRsaKey.GetPrivateExponent());
    	this->m_PublicRsaKey.SetPublicExponent(other_.m_PublicRsaKey.GetPublicExponent());
    	this->m_PublicRsaKey.SetModulus(other_.m_PublicRsaKey.GetModulus());
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

	// parameters.GenerateRandomWithKeySize (rnd, CryptoPP::AES::DEFAULT_KEYLENGTH);
	parameters.GenerateRandomWithKeySize(rnd, 4096);

	CryptoPP::RSA::PublicKey PublicRsaKey(parameters);
	CryptoPP::RSA::PrivateKey PrivateRsaKey(parameters);


	this->m_PublicRsaKey = new CryptoPP::RSA::PublicKey(parameters);
	this->m_PrivateRsaKey = new CryptoPP::RSA::PrivateKey(parameters);
	std::cout<<std::endl;

}

CryptoPP::RSA::PublicKey RsaClass::getPublicRsaKey() const {
	return *m_PublicRsaKey;
}

CryptoPP::RSA::PrivateKey RsaClass::getPrivateRsaKey() const {
	return *m_PrivateRsaKey;
}

std::string RsaClass::getStringPublicRsaKey(CryptoPP::RSA::PublicKey m_PublicRsaKey) const {
// метод принимает открытый ключ в стандартном формате, возвращает его в виде строки
      
    std::string publicRsaKeyString;
      
    CryptoPP::StringSink sourse(publicRsaKeyString);
    m_PublicRsaKey.Save(sourse);
      
    return publicRsaKeyString;
}

std::string RsaClass::getStringRsaPrivateKey(CryptoPP::RSA::PublicKey m_PrivateRsaKey) const {
// метод принимает закрытый ключ в стандартном формате, возвращает его в виде строки
      
    std::string privateRsaKeyString;
      
    CryptoPP::StringSink sourse(privateRsaKeyString);
    m_PrivateRsaKey.Save(sourse);
      
    return privateRsaKeyString;
}

void RsaClass::setPublicRsaKey(std::string publicRsaKeyString, CryptoPP::RSA::PublicKey m_PublicRsaKey) {
// метод принимает открытый ключ как строку, и записывает его в поле класса
      
    CryptoPP::StringSource sourse(publicRsaKeyString,true);
    m_PublicRsaKey.Load(sourse);
}

void RsaClass::setPrivateRsaKey(const std::string &privateRsaKeyString, CryptoPP::RSA::PublicKey m_PrivateRsaKey) {
// метод принимает открытый ключ как строку, и записывает его в поле класса

	CryptoPP::StringSource sourse(privateRsaKeyString, true);
	m_PrivateRsaKey.Load(sourse);
}
