#ifndef AESDECRYPTOR_H
#define AESDECRYPTOR_H

#include "AesClass.h"


class AesDecryptor : public AesClass
{

	  // ************* //
	 //    public     //
	// ************* //
	public: AesDecryptor();
	public: AesDecryptor(QWidget *_parent);
	public: AesDecryptor(AesDecryptor& _other);
	public: AesDecryptor& operator=(const AesDecryptor& _other);
	public: ~AesDecryptor();
	public: void aesDecryptFile(const std::string& filePath);
	public: void readFileForDecryption(const std::string& filePath, std::string& textForDecryption);
	public: void writeFileForDecryption(const std::string& filePath, const std::string& encryptedText);
	public: void addDecryptToPath(std::string& filePath);
	public: void setRsaDecryptor(RsaDecryptor *_rsaDecryptor);

	public: void setIsKeyToDecryptReady(bool _isKeyToEncryptReady);
	public: bool getIsKeyToDecryptReady();

	  // ************* //
	 //    private    //
	// ************* //
	private: RsaDecryptor *m_rsaDecryptor = nullptr;

	bool m_isKeyToDecryptReady;
};

#endif // AESDECRYPTOR_H
