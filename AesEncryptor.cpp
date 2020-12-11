#include "AesEncryptor.h"


AesEncryptor::AesEncryptor()
{
	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE
	memset( m_PrivateTmpArray , 0x00, CryptoPP::AES::BLOCKSIZE+ CryptoPP::AES::DEFAULT_KEYLENGTH);
	m_isNewKey = false;
	m_isKeyToEncryptReady = false;
	m_parent = nullptr;
}


AesEncryptor::AesEncryptor(QWidget *parent)
{
	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE
	memset( m_PrivateTmpArray , 0x00, CryptoPP::AES::BLOCKSIZE+ CryptoPP::AES::DEFAULT_KEYLENGTH);
	m_isNewKey = false;
	m_isKeyToEncryptReady = false;
	m_parent = parent;
}

AesEncryptor::AesEncryptor(AesEncryptor& _other)
{
	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE
	memset( m_PrivateTmpArray , 0x00, CryptoPP::AES::BLOCKSIZE+ CryptoPP::AES::DEFAULT_KEYLENGTH);
	this->setNewPrivateAesKey(_other.m_PrivateAesKey);
	this->setNewInitializationVector(_other.m_PublicInitializationVector);
	this->m_isNewKey = _other.m_isNewKey;
	m_isKeyToEncryptReady = _other.m_isKeyToEncryptReady;
	m_parent = _other.m_parent;
}

AesEncryptor& AesEncryptor::operator=(const AesEncryptor& _other)
{
	if(this == &_other)
	{
		return *this;
	}

	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE
	memset( m_PrivateTmpArray , 0x00, CryptoPP::AES::BLOCKSIZE+ CryptoPP::AES::DEFAULT_KEYLENGTH);

	this->setNewPrivateAesKey(_other.m_PrivateAesKey);
	this->setNewInitializationVector(_other.m_PublicInitializationVector);
	this->m_isNewKey = _other.m_isNewKey;
	m_isKeyToEncryptReady = _other.m_isKeyToEncryptReady;
	m_parent = _other.m_parent;

	return *this;
}

AesEncryptor::~AesEncryptor()
{

}


void AesEncryptor::aesEncryptFile(const std::string& filePath)
{
	if(!this->m_isNewKey)
	{
		this->createNewPublicInitializationVector(this->m_PublicInitializationVector);
	}

	std::string textForEncryption = "";
	this->readFileForEncryption(filePath, textForEncryption);



	memset(m_PrivateAesKey, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);




	CryptoPP::AES::Encryption aesEncryption(m_PrivateAesKey, CryptoPP::AES::DEFAULT_KEYLENGTH); // шифр
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, m_PublicInitializationVector ); // режим работы cbc

	std::string encryptedText= "";
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( encryptedText ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( textForEncryption.c_str() ), textForEncryption.length()); // reinterpret_cast преобразование указателя
	stfEncryptor.MessageEnd();

	writeFileForEncryption(filePath, encryptedText);

	QMessageBox msgBox;
	msgBox.setText("Зашифровано.");
	msgBox.exec();

	// ************************ //
   //   конец aesEncryptFile   //
  // ************************ //
}


void AesEncryptor::createNewPublicInitializationVector(byte (&changedPublicInitializationVector)[ CryptoPP::AES::BLOCKSIZE ])
{
	   // ********************************************** //
	  //   Заполнение вектора инициализации случайными  //
	 //   значениями, исключая служебные символы       //
	// ********************************************** //
	char tmpChar;
	srand(static_cast<unsigned int>(time(0))); //  сид для случайного числа
	memset( changedPublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE );

	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
	{
		do
		{
			tmpChar = rand()% 255 - 128;
		}while( ( static_cast<int>(tmpChar) == 127 ) || ( ( static_cast<int>(tmpChar) >= 0 ) && ( static_cast<int>(tmpChar) <=  31 ) ) );
		changedPublicInitializationVector[i] = 0xFF & static_cast<byte>(tmpChar);
	}

	  // ********************************************* //
	 //   конец createNewPublicInitializationVector   //
	// ********************************************* //
}


void AesEncryptor::readFileForEncryption(const std::string& filePath, std::string& textForEncryption)
{
	std::string tmpString = "";
	std::ifstream fileToRead;
	fileToRead.open(filePath);
	if(fileToRead.is_open())
	{
		textForEncryption.clear();
		while (getline(fileToRead, tmpString))
		{
			textForEncryption.append(tmpString+"\n");
		}
	}
	fileToRead.close();

	  // ******************************* //
	 //   конец readFileForEncryption   //
	// ******************************* //
}

void AesEncryptor::writeFileForEncryption(const std::string& filePath, const std::string& encryptedText)
{
	std::ofstream outFile;

	std::string outFilePath = filePath;
	addEncryptToPath(outFilePath);

	outFile.open(outFilePath, std::ofstream::binary);

	std::string test (CryptoPP::AES::BLOCKSIZE, 'A');


	if(outFile.is_open())
	{
		size_t size=encryptedText.size();
		std::string buffString = "";
		for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
		{
			buffString.push_back(static_cast<char>(m_PublicInitializationVector[i]));
		}
		outFile.write(buffString.c_str(), buffString.size());
		outFile.write(encryptedText.c_str(),size);

	}
	outFile.close();


	  // ******************************* //
	 //   конец writeFileForEncryption  //
	// ******************************* //
}

void AesEncryptor::addEncryptToPath(std::string& filePath)
{
	int i;
	for(i = filePath.length(); i > 0 && filePath[i] != '/'; --i);
	++i;
	std::string path = filePath.substr(0, i);
	std::string name = filePath.substr(i, filePath.length()-1);
	name = "encrypted_" + name + ".dat";
	filePath = path+name;
}

void AesEncryptor::setIsNewKey(bool _newValue)
{
	this->m_isNewKey = _newValue;
}

void AesEncryptor::setNewInitializationVector(const byte _newPublicInitializationVector[])
{
	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
	{
		this->m_PublicInitializationVector[i] = _newPublicInitializationVector[i];
	}
}

void AesEncryptor::setNewPrivateAesKey(const byte _newPrivateAesKey[])
{
	for(int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
	{
		this->m_PrivateAesKey[i] = _newPrivateAesKey[i];
	}
}


void AesEncryptor::setIsKeyToEncryptReady(bool _isKeyToEncryptReady)
{
	this->m_isKeyToEncryptReady = _isKeyToEncryptReady;
}

bool AesEncryptor::getIsKeyToEncryptReady()
{
	return this->m_isKeyToEncryptReady;
}
