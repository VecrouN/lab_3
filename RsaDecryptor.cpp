#include "RsaDecryptor.h"


RsaDecryptor::RsaDecryptor():RsaClass() {

}

RsaDecryptor::~RsaDecryptor() {

}

std::string RsaDecryptor::rsaDecryptKey(const std::string& aesKeyStringForDescryptor)
{// расшифровка ключа
    CryptoPP::AutoSeededRandomPool rng;
	std::string decryptesText;
    CryptoPP::RSAES_OAEP_SHA_Decryptor d(m_PrivateRsaKey);

	CryptoPP::ArraySource test = new CryptoPP::ArraySource(aesKeyStringForDescryptor, true, new CryptoPP::PK_DecryptorFilter(rng, d,new CryptoPP::StringSink( decryptesText)));

    return decryptesText;
}
