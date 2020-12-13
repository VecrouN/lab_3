#ifndef RSAENCRYPTOR_H
#define RSAENCRYPTOR_H

#include <iostream>
#include <fstream>

#include "RsaClass.h"

#include <crypto++/modes.h>
#include <crypto++/rsa.h>
#include <crypto++/aes.h>

class RsaEncryptor : public RsaClass
{
	public:
        RsaEncryptor(); // конструктор
        ~RsaEncryptor(); // деструктор

        // шифрование ключа AES, получение зашифрованного ключа в виде строки
		std::string rsaEncryptKey(const std::string& aesKeyString);

    protected:

    private:
};

#endif // RSAENCRYPTOR_H

