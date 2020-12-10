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

    void readPrivateKey(const std::string& filename); // чтение файла с закрытым ключом RSA
    std::string readKeyInFileForDecryptor(const std::string& filename); // чтение публичного ключа вместе с шифрованным ключом для AES
    std::string rsaDecryptKey(std::string& aesKeyStringForDescryptor); // расшифровка ключа AES, получение зашифрованного ключа в виде строки

protected:

private:

};

#endif // RSADECRYPTOR_H
