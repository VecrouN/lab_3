#include "AesClass.h"

AesClass::AesClass()
{

}

AesClass::~AesClass()
{

}

void AesClass::setNewPrivateAesKey(const byte _newPrivateAesKey[])
{
	for(int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
	{
		this->m_PrivateAesKey[i] = _newPrivateAesKey[i];
	}
}
