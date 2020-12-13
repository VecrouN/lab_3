#include "RsaDecryptor.h"

#include <iostream>
#include <fstream>
#include <crypto++/modes.h>
#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>
#include <cryptopp/files.h>

RsaDecryptor::RsaDecryptor():RsaClass() {

}

RsaDecryptor::~RsaDecryptor() {

}

std::string RsaDecryptor::rsaDecryptKey(const std::string& aesKeyStringForDescryptor)
{// расшифровка ключа
    CryptoPP::AutoSeededRandomPool rng;
	std::string decryptesText;
	//decryptesText.resize(aesKeyStringForDescryptor.size(), 'a');
    CryptoPP::RSAES_OAEP_SHA_Decryptor d(m_PrivateRsaKey);

	CryptoPP::PK_DecryptorFilter *der = new CryptoPP::PK_DecryptorFilter(rng, d,new CryptoPP::StringSink( decryptesText));

	CryptoPP::ArraySource test = new CryptoPP::ArraySource(aesKeyStringForDescryptor, true, new CryptoPP::PK_DecryptorFilter(rng, d,new CryptoPP::StringSink( decryptesText)));


	std::cout<<"\n**********\nRsaDecryptor.cpp 31\ndecrypted key\n**********"<<std::endl;
	for(int i = 0; i < decryptesText.length(); ++i)
	{
		std::cout<<"i = \t"<<i<<"\tkey[i] = \t"<<decryptesText[i]<<"\tstatic_cast<int>(m_PrivateAesKey[i])\t"<< static_cast<int>(decryptesText[i])<<std::endl;
	}



    return decryptesText;
}
