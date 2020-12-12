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
}

std::string RsaEncryptor::rsaEncryptKey(const std::string& aesKeyString)
{ // шифрование ключа AES
    CryptoPP::AutoSeededRandomPool rng;
    std::string encryptesText;
    encryptesText.resize(aesKeyString.size()*2);

    rsaGenerateKey();
    LoadPublicKey("publicKey.key");
    LoadPrivateKey("privateKey.key");

    CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(this->m_PublicRsaKey);

    CryptoPP::ArraySource(aesKeyString, true,
                           new CryptoPP::PK_EncryptorFilter
                          (rng, encryptor, new CryptoPP::StringSink(encryptesText)));

    return encryptesText;
}
