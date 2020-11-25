#ifndef AESENCRYPTOR_H
#define AESENCRYPTOR_H

#include "Encryptor.h"

#include <crypto++/aes.h>

class AesEncryptor : public Encryptor
{
	public:
		AesEncryptor();
};

#endif // AESENCRYPTOR_H
