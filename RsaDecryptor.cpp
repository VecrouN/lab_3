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

	//m_PublicRsaKey.Initialize(e,d);
	//m_PrivateRsaKey.Initialize(n,e,d);
}


void RsaDecryptor::readPrivateKey(const std::string &filename)
{// чтение файла с приватным ключом


	std::ifstream readedFile;
	readedFile >> std::noskipws;
	readedFile.open(filename, std::ifstream::binary);

	std:: string tmpString = "";

	if(readedFile.is_open())
	{
		char temp;
		while (readedFile.read(&temp, sizeof(char)))
		{
			tmpString.push_back(temp);
		}
	}
	readedFile.close();
	// Из строки получаем закрытый ключ и записываем в соответствующее поле класса
	this->setPrivateRsaKey(tmpString, *this->m_PrivateRsaKey);

}

std::string RsaDecryptor::rsaDecryptKey(const std::string& aesKeyStringForDescryptor)
{// расшифровка ключа
    CryptoPP::AutoSeededRandomPool rng;
    std::string decryptesText;

	CryptoPP::RSAES_OAEP_SHA_Decryptor e(*m_PublicRsaKey);
    CryptoPP::StringSource(aesKeyStringForDescryptor, true,
                           new CryptoPP::PK_DecryptorFilter(rng,e,new CryptoPP::StringSink(decryptesText)));
    return decryptesText;

}
