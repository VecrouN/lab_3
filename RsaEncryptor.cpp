#include <crypto++/rsa.h>
#include <crypto++/modes.h>
#include <iostream>
#include <fstream>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>
#include <cryptopp/files.h>



#include "RsaEncryptor.h"

RsaEncryptor::RsaEncryptor():RsaClass() {

}

RsaEncryptor::~RsaEncryptor() {
    // деструктор
        CryptoPP::Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9");

		//m_PublicRsaKey.Initialize(e,d);
		//m_PrivateRsaKey.Initialize(n,e,d);
}


void RsaEncryptor::readPublicKey(const std::string& filename)
{ // чтение файла с публичным ключом

	std::ifstream readedFile;
	readedFile >> std::noskipws;
	readedFile.open(filename, std::ifstream::binary);

	std:: string tmpString = "";

	if(readedFile.is_open())
	{
		char temp;
		while (readedFile.read(&temp, sizeof(char)))
		{
			tmpString.push_back(temp); // публичный рса ключ
		}
	}

	readedFile.close();

	//this->setPublicRsaKey(tmpString, *this->m_PublicRsaKey);
	this->setPublicRsaKey(tmpString, this->m_PublicRsaKey);


}

void RsaEncryptor::savePublicKey(const std::string &filePath)
{//сохранение публичного ключа

	//std::string PublicKeyString = getStringPublicRsaKey(*this->m_PublicRsaKey); //сохранение ключа в строку
	std::string PublicKeyString = getStringPublicRsaKey(this->m_PublicRsaKey); //сохранение ключа в строку
    
	std::ofstream outFile;
	outFile.open(filePath+"/publicRsaKey.dat", std::ofstream::binary);

	if(outFile.is_open())
	{
		outFile.write(PublicKeyString.c_str(), PublicKeyString.size());
	}
	outFile.close();

}

std::string RsaEncryptor::rsaEncryptKey(const std::string& aesKeyString)
{ // шифрование ключа AES
    CryptoPP::AutoSeededRandomPool rng;
    std::string encryptesText;
    
	//rsaGenerateKey();

	//CryptoPP::RSAES_OAEP_SHA_Encryptor e(*this->m_PublicRsaKey);
	CryptoPP::RSAES_OAEP_SHA_Encryptor e(this->m_PublicRsaKey);
    CryptoPP::StringSource(aesKeyString, true,
						   new CryptoPP::PK_EncryptorFilter(rng, e, new CryptoPP::StringSink(encryptesText)));

	// savePrivateKey(filePath); // сохраним закрытый ключ для дальнейшей расшифровки
	// writeKeyInFileForEncryptor(filePath); // сохраним полученное шифрование в файл
	return encryptesText;
}

void RsaEncryptor::savePrivateKey(const std::string &filePath)
{//сохранение приватного ключа


	std::string PrivateKeyString = getStringRsaPrivateKey(this->m_PrivateRsaKey); //сохранение ключа в строку
	//std::string PrivateKeyString = getStringRsaPrivateKey(*this->m_PrivateRsaKey); //сохранение ключа в строку

	std::ofstream outFile;
	outFile.open(filePath + "/privateRsaKey.dat", std::ofstream::binary);

	if(outFile.is_open())
	{
		outFile.write(PrivateKeyString.c_str(), PrivateKeyString.size());
	}
	outFile.close();
	setPrivateRsaKey(PrivateKeyString, m_PrivateRsaKey); // Из полученной строки записываем в поле закрытый ключ
	//setPrivateRsaKey(PrivateKeyString, *m_PrivateRsaKey); // Из полученной строки записываем в поле закрытый ключ

}
