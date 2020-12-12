#ifndef RSAENCRYPTOR_H
#define RSAENCRYPTOR_H

#include "RsaClass.h"


class RsaEncryptor : public RsaClass
{
	public:
        RsaEncryptor(); // конструктор
        ~RsaEncryptor(); // деструктор

		void readPublicKey(const std::string& filename); // чтение файла открытого ключа
		void savePublicKey(const std::string &filePath); // сохранение публичного ключа вместе с шифрованным ключом для AES
		std::string rsaEncryptKey(const std::string& aesKeyString); // шифрование ключа AES, получение зашифрованного ключа в виде строки
		void savePrivateKey(const std::string &filePath); // сохранение приватного ключа в файл

    protected:

    private:
};

#endif // RSAENCRYPTOR_H
