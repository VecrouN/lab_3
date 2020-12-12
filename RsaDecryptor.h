#ifndef RSADECRYPTOR_H
#define RSADECRYPTOR_H

#include "RsaClass.h"

#include <crypto++/modes.h>
#include <crypto++/rsa.h>

class RsaDecryptor : public RsaClass
{
public:
    RsaDecryptor(); // конструктор
    ~RsaDecryptor(); // деструктор

    // расшифровка ключа AES, получение зашифрованного ключа в виде строки
    std::string rsaDecryptKey(const std::string& aesKeyStringForDescryptor);

protected:

private:

};


#endif // RSADECRYPTOR_H
