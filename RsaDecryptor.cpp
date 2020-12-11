#include "RsaDecryptor.h"

#include <iostream>
#include <fstream>
#include <crypto++/modes.h>
#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>

RsaDecryptor::RsaDecryptor():RsaClass() {

}

RsaDecryptor::~RsaDecryptor()
{
    CryptoPP::Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9");

    m_PublicRsaKey.Initialize(e,d);
    m_PrivateRsaKey.Initialize(n,e,d);
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
    setPrivateRsaKey(PrivateKeyString,m_PrivateRsaKey);
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
    setPublicRsaKey(PublicKeyString,m_PublicRsaKey);

    aesKeyStringForDescryptor.append(tmpString[1]+"\n");

    return aesKeyStringForDescryptor;

}

std::string RsaDecryptor::rsaDecryptKey(const std::string& aesKeyStringForDescryptor)
{// расшифровка ключа
    CryptoPP::AutoSeededRandomPool rng;
    std::string decryptesText;

    CryptoPP::RSAES_OAEP_SHA_Decryptor e(m_PublicRsaKey);
    CryptoPP::StringSource(aesKeyStringForDescryptor, true,
                           new CryptoPP::PK_DecryptorFilter(rng,e,new CryptoPP::StringSink(decryptesText)));
    return decryptesText;

}
