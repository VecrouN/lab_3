#include <crypto++/rsa.h>
#include <crypto++/modes.h>
#include <iostream>
#include <fstream>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>

#include "RsaEncryptor.h"

RsaEncryptor::RsaEncryptor():RsaClass() {

}

RsaEncryptor::~RsaEncryptor() {
    // деструктор
        CryptoPP::Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9");

        m_PublicRsaKey.Initialize(e,d);
        m_PrivateRsaKey.Initialize(n,e,d);
}


void RsaEncryptor::readKeyInFileForEncryptor(const std::string& filename)
{ // чтение файла с приватным ключом
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

    setPrivateRsaKey(PrivateKeyString, m_PrivateRsaKey); // Из полученной строки записываем в поле закрытый ключ
}

void RsaEncryptor::writeKeyInFileForEncryptor(CryptoPP::RSA::PublicKey m_PublicRsaKey, std::string& aesKeyString)
{//сохранение публичного ключа вместе с шифрованным ключом для AES
    std::ofstream fileToRead;
    std::string PublicKeyString = getStringPublicRsaKey(m_PublicRsaKey); //сохранение ключа в строку
    
    // запись в файл
    fileToRead.open("aesKey.txt",std::ios::app);
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
    
    rsaGenerateKey();
    CryptoPP::RSAES_OAEP_SHA_Encryptor e(m_PublicRsaKey);
    CryptoPP::StringSource(aesKeyString, true,
                           new CryptoPP::PK_EncryptorFilter(rng,e,new CryptoPP::StringSink(encryptesText)));

    savePrivateKey(m_PrivateRsaKey); // сохраним закрытый ключ для дальнейшей расшифровки
    writeKeyInFileForEncryptor(m_PublicRsaKey, encryptesText); // сохраним полученное шифрование в файл

    return encryptesText;
}

void RsaEncryptor::savePrivateKey(CryptoPP::RSA::PrivateKey m_PrivateRsaKey)
{//сохранение приватного ключа
    std::ofstream fileToRead;
    std::string PrivateKeyString = getStringRsaPrivateKey(m_PrivateRsaKey); //сохранение ключа в строку

    fileToRead.open("privateRsaKey.txt");
    if (fileToRead.is_open()){
        fileToRead << PrivateKeyString;
    }
    
    fileToRead.close();
}
