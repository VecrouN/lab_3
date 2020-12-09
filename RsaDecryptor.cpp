#include "RsaDecryptor.h"

RsaDecryptor::RsaDecryptor()
{

}
#include "RsaDecryptor.h"


#include <iostream>
#include <fstream>
#include <crypto++/modes.h>
#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>

RsaDecryptor::RsaDecryptor()
{

}

RsaDecryptor::RsaDecryptor(RsaDecryptor &other_)
{

}

RsaDecryptor &RsaDecryptor::operator=(const RsaDecryptor &other_)
{

}

RsaDecryptor::~RsaDecryptor()
{

}

RsaDecryptor::RsaDecryptor()
{

}

RsaDecryptor::RsaDecryptor(RsaDecryptor &other_)
{

}

RsaDecryptor &RsaDecryptor::operator=(const RsaDecryptor &other_)
{

}

RsaDecryptor::~RsaDecryptor()
{

}

void RsaDecryptor::rsaGenerateKey()
{//генерация ключей
    CryptoPP::AutoSeededRandomPool rnd;
    CryptoPP::InvertibleRSAFunction parameters;
    parameters.GenerateRandomWithKeySize (rnd, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::RSA::PrivateKey m_PrivateRsaKey(parameters);
    CryptoPP::RSA::PublicKey m_PublicRsaKey(parameters);

}

void RsaDecryptor::readPrivateKey(const std::string &filename)
{// чтение файла с приватным ключом

    std::string tmpString ="";
    std::string PrivateKeyString = "";
    std::ifstream fileToRead;
    fileToRead.open(filename);

    if (fileToRead.is_open()){
        while (getline(fileToRead,tmpString)){
            PrivateKeyString.append(tmpString+"\n");
        }
    }
    fileToRead.close();
    
    // Из строки получаем закрытый ключ и записываем в соответствующее поле класса
    CryptoPP::StringSource sourse(PrivateKeyString,true);
    m_PrivateRsaKey.Load(sourse);
}

std::string RsaDecryptor::readKeyInFileForDecryptor(const std::string &filename)
{// чтение публичного ключа вместе с шифрованным ключом для AES
    int i = 0;
    std::string tmpString[2];
    std::string PublicKeyString = "";
    std::string aesKeyStringForDescryptor = "";
    std::ifstream fileToRead;
    fileToRead.open(filename);

    if (fileToRead.is_open()){
        while (!fileToRead.eof()){
            getline(fileToRead,tmpString[i]);
            i++;
        }
    }
    fileToRead.close();

    PublicKeyString.append(tmpString[0]+"\n");
    // Из строки получаем открытый ключ и записываем в соответствующее поле класса
    CryptoPP::StringSource sourse(PublicKeyString,true);
    m_PublicRsaKey.Load(sourse);

    aesKeyStringForDescryptor.append(tmpString[1]+"\n");

    return aesKeyStringForDescryptor;

}

std::string RsaDecryptor::rsaDecryptKey(std::string &aesKeyStringForDescryptor)
{// расшифровка ключа
    CryptoPP::AutoSeededRandomPool rng;
    std::string decryptesText;
    CryptoPP::RSAES_OAEP_SHA_Decryptor e(m_PublicRsaKey);
    CryptoPP::StringSource(aesKeyStringForDescryptor, true,
                           new CryptoPP::PK_DecryptorFilter(rng,e,new CryptoPP::StringSink(decryptesText)));
    return decryptesText;

}
