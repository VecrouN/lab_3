#include "RsaDecryptor.h"

#include <iostream>
#include <fstream>
#include <crypto++/modes.h>
#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/aes.h>


}

RsaDecryptor::~RsaDecryptor() {

}

std::string RsaDecryptor::rsaDecryptKey(const std::string& aesKeyStringForDescryptor)
{// расшифровка ключа
    CryptoPP::AutoSeededRandomPool rng;
    std::string decryptesText;

    CryptoPP::byte tmpArray[CryptoPP::AES::DEFAULT_KEYLENGTH];
    memset(tmpArray, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    for(int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
    {
        tmpArray[i] = static_cast<CryptoPP::byte>(aesKeyStringForDescryptor[i]);
    }

    LoadPublicKey("publicKey.key");
    LoadPrivateKey("privateKey.key");

    CryptoPP::RSAES_OAEP_SHA_Decryptor d(m_PrivateRsaKey);

    CryptoPP::StringSource(aesKeyStringForDescryptor, true,
                           new CryptoPP::PK_DecryptorFilter(rng, d,new CryptoPP::StringSink(decryptesText)));

    return decryptesText;
}
