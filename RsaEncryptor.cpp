#include <crypto++/rsa.h>
#include <crypto++/modes.h>
#include <iostream>
#include <fstream>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>

#include "RsaEncryptor.h"

RsaEncryptor::RsaEncryptor()
{

}

RsaEncryptor::RsaEncryptor(RsaEncryptor &other_)
{

}

RsaEncryptor &RsaEncryptor::operator=(const RsaEncryptor &other_)
{
    if (this==&other_)
        return *this;


}

RsaEncryptor::~RsaEncryptor()
{

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
