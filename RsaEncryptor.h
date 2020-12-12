#ifndef RSAENCRYPTOR_H
#define RSAENCRYPTOR_H

#include "RsaClass.h"

#include <crypto++/modes.h>
#include <crypto++/rsa.h>


class RsaEncryptor : public RsaClass
{
	public:
        RsaEncryptor(); // конструктор
        ~RsaEncryptor(); // деструктор

        // шифрование ключа AES, получение зашифрованного ключа в виде строки
        std::string rsaEncryptKey(std::string& aesKeyString);

    protected:

    private:
};

#endif // RSAENCRYPTOR_H
