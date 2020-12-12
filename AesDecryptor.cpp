#include "AesDecryptor.h"
#include <iostream>

AesDecryptor::AesDecryptor()
{
	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE

	m_isKeyToDecryptReady = false;
	m_parent = nullptr;
}

AesDecryptor::AesDecryptor(QWidget *_parent)
{
	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE

	m_isKeyToDecryptReady = false;
	m_parent = _parent;
}

AesDecryptor::AesDecryptor(AesDecryptor& _other)
{
	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE

	m_isKeyToDecryptReady = _other.m_isKeyToDecryptReady;
	m_parent = _other.m_parent;

	for(int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
	{
		this->m_PrivateAesKey[i] = _other.m_PrivateAesKey[i];
	}

	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
	{
		this->m_PublicInitializationVector[i] = _other.m_PublicInitializationVector[i];
	}
}

AesDecryptor& AesDecryptor::operator=(const AesDecryptor& _other)
{
	if(this == &_other)
	{
		return *this;
	}

	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE

	m_isKeyToDecryptReady = _other.m_isKeyToDecryptReady;
	m_parent = _other.m_parent;

	for(int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
	{
		this->m_PrivateAesKey[i] = _other.m_PrivateAesKey[i];
	}

	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
	{
		this->m_PublicInitializationVector[i] = _other.m_PublicInitializationVector[i];
	}

	return *this;
}

AesDecryptor::~AesDecryptor()
{
	delete m_rsaDecryptor;
}


void AesDecryptor::aesDecryptFile(const std::string& filePath)
{
	std::string encryptText = "";
	std::string decrypTedtext = "";
	readFileForDecryption(filePath, encryptText);

	CryptoPP::AES::Decryption aesDecryption( this->m_PrivateAesKey , CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, this->m_PublicInitializationVector );

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decrypTedtext ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( encryptText.c_str() ), encryptText.size() );
	stfDecryptor.MessageEnd();

	this->writeFileForDecryption(filePath, decrypTedtext);

	// ************************ //
   //   конец aesDecryptFile   //
	// ************************ //
}


void AesDecryptor::readFileForDecryption(const std::string& filePath, std::string& textForDecryption)
{
	std::ifstream readedFile;
	readedFile >> std::noskipws;
	readedFile.open(filePath, std::ifstream::binary);

	std::string encryptedText = "";
	std::string tmpString = "";
	std::string encryptedKey = "";
	byte tmpArray[CryptoPP::AES::DEFAULT_KEYLENGTH];
	memset(tmpArray, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);

	if(readedFile.is_open())
	{
		char temp;
		textForDecryption = "";
		int length = 0;
		readedFile.read((char*)&length, sizeof(int));
		for(int i = 0; i < length; ++i)
		{
			readedFile.read(&temp, sizeof(char));
			encryptedKey.push_back(temp);
		}
		;
		std::string encryptedKey1 = this->m_rsaDecryptor->rsaDecryptKey(encryptedKey);
	;
		for(int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH;++i)
		{
			tmpArray[i] = encryptedKey1[i];
		}
		this->setNewPrivateAesKey(tmpArray);

		for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
		{
			readedFile.read(&temp, sizeof(char));
			m_PublicInitializationVector[i] = static_cast<byte>(temp);
		}
		while (readedFile.read(&temp, sizeof(char)))
		{
			textForDecryption.push_back(temp);
		}
	}
	readedFile.close();


	// ******************************* //
   //   конец readFileForDecryption   //
  // ******************************* //
}

void AesDecryptor::writeFileForDecryption(const std::string& filePath, const std::string& decryptedText)
{

	std::ofstream outFile;

	std::string outFilePath = filePath;
	addDecryptToPath(outFilePath);

	outFile.open(outFilePath);
	if(outFile.is_open())
	{
		outFile<<decryptedText;
	}
	outFile.close();
	QMessageBox msgBox;
	msgBox.setText("Дешифровано.");
	msgBox.exec();


	// ******************************** //
   //   конец writeFileForEncryption   //
	// ******************************** //
}

void AesDecryptor::addDecryptToPath(std::string& filePath)
{
	int i;
	for(i = filePath.length(); i > 0 && filePath[i] != '/'; --i);
	++i;
	std::string path = filePath.substr(0, i);
	std::string name = filePath.substr(i, filePath.length()-1);
	name = "decrypted_" + name;
	filePath = path+name;

}


void AesDecryptor::setRsaDecryptor(RsaDecryptor* _rsaDecryptor)
{
	this->m_rsaDecryptor = _rsaDecryptor;
}

void AesDecryptor::setIsKeyToDecryptReady(bool _isKeyToEncryptReady)
{
	this->m_isKeyToDecryptReady = _isKeyToEncryptReady;

}

bool AesDecryptor::getIsKeyToDecryptReady()
{
	return m_isKeyToDecryptReady;
}

