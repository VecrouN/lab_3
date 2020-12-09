#include <crypto++/rsa.h>
#include <crypto++/modes.h>
#include <iostream>
#include <fstream>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>

#include "RsaEncryptor.h"

RsaEncryptor::RsaEncryptor()
{
    CryptoPP::Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9");
    m_PrivateRsaKey.Initialize(n,e,d);
    m_PublicRsaKey.Initialize(e,d);
}

RsaEncryptor::RsaEncryptor(RsaEncryptor &other_):m_PrivateRsaKey(other_.m_PrivateRsaKey),
    m_PublicRsaKey(other_.m_PublicRsaKey){

}

RsaEncryptor &RsaEncryptor::operator=(const RsaEncryptor& other_)
{
    CryptoPP::Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9");
    m_PrivateRsaKey.Initialize(n,e,d);
    m_PublicRsaKey.Initialize(e,d);
    if (this==&other_)
        return *this;
    else
        if ((other_.m_PrivateRsaKey.GetPrime1() == m_PrivateRsaKey.GetPrime1()||
                other_.m_PrivateRsaKey.GetPrime2() == m_PrivateRsaKey.GetPrime2()||
                other_.m_PrivateRsaKey.GetPrivateExponent() == m_PrivateRsaKey.GetPrivateExponent())||
                (other_.m_PublicRsaKey.GetPublicExponent()==m_PublicRsaKey.GetPublicExponent()||
                 other_.m_PublicRsaKey.GetModulus() == m_PublicRsaKey.GetModulus()))
            return *this;


}

RsaEncryptor::~RsaEncryptor()
{
    CryptoPP::Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9");
    m_PrivateRsaKey.Initialize(n,e,d);
    m_PublicRsaKey.Initialize(e,d);
}

void RsaEncryptor::rsaGenerateKey()
{//генерация ключей
    CryptoPP::AutoSeededRandomPool rnd;
    CryptoPP::InvertibleRSAFunction parameters;
    parameters.GenerateRandomWithKeySize (rnd, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::RSA::PrivateKey m_PrivateRsaKey(parameters);
    CryptoPP::RSA::PublicKey m_PublicRsaKey(parameters);
}

void RsaEncryptor::writeKeyInFileForEncryptor(CryptoPP::RSA::PublicKey m_PublicRsaKey, std::string& aesKeyString)
{//сохранение публичного ключа вместе с шифрованным ключом для AES
    std::ofstream fileToRead;
    std::string PublicKeyString = "";
    CryptoPP::StringSource sourse(PublicKeyString,true);
    m_PublicRsaKey.Save(sourse); //сохранение ключа в строку?

    fileToRead.open("aesKey.txt",std::ios::app);// дозапись ключа AES
    if (fileToRead.is_open()){
        fileToRead << PublicKeyString << std::endl;
        fileToRead << aesKeyString;
    }
    fileToRead.close();
}

std::string RsaEncryptor::rsaEncryptKey(std::string& aesKeyString)
{ // шифрование ключа AES
    CryptoPP::AutoSeededRandomPool rng;
    std::string encryptesText;
    CryptoPP::RSAES_OAEP_SHA_Encryptor e(m_PublicRsaKey);
    CryptoPP::StringSource(aesKeyString, true,
                           new CryptoPP::PK_EncryptorFilter(rng,e,new CryptoPP::StringSink(encryptesText)));
    return encryptesText;
}

void RsaEncryptor::savePrivateKey(CryptoPP::RSA::PrivateKey m_PrivateRsaKey)
{//сохранение приватного ключа
    std::ofstream fileToRead;
    std::string PrivateKeyString = "";
    CryptoPP::StringSource sourse(PrivateKeyString,true);
    m_PrivateRsaKey.Save(sourse); //сохранение ключа в строку?

    fileToRead.open("privateRsaKey.txt");
    if (fileToRead.is_open()){
        fileToRead << PrivateKeyString;
    }
    fileToRead.close();

}
