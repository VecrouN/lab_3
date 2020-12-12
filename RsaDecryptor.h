#ifndef RSADECRYPTOR_H
#define RSADECRYPTOR_H

#include "RsaClass.h"


class RsaDecryptor : public RsaClass
{
public:
    RsaDecryptor(); // конструктор
    ~RsaDecryptor(); // деструктор

	void readPrivateKey(const std::string& filename); // чтение файла с закрытым ключом RSA
	std::string rsaDecryptKey(const std::string& aesKeyStringForDescryptor); // расшифровка ключа AES, получение зашифрованного ключа в виде строки

protected:

private:

};

#endif // RSADECRYPTOR_H
