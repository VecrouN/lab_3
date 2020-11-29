#include "AesEncryptor.h"


AesEncryptor::AesEncryptor()
{
	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE
}

AesEncryptor::~AesEncryptor()
{
	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE
}


void AesEncryptor::aesEncryptFile(const std::string& filePath)
{

	this->createNewPublicInitializationVector(this->m_PublicInitializationVector);

	std::string textForEncryption = "";
	this->readFileForEncryption(filePath, textForEncryption);


	CryptoPP::AES::Encryption aesEncryption(m_PrivateAesKey, CryptoPP::AES::DEFAULT_KEYLENGTH); // шифр
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, m_PublicInitializationVector ); // режим работы cbc

	std::string encryptedText= "";
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( encryptedText ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( textForEncryption.c_str() ), textForEncryption.length()); // reinterpret_cast преобразование указателя
	stfEncryptor.MessageEnd();

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
		textForEncryption = "";
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

	int i;
	for(i = filePath.length(); i > 0 && filePath[i] != '/'; --i);
	++i;
	std::string path = filePath.substr(0, i);
	std::string name = filePath.substr(i, filePath.length()-1);
	name = "encrypted_" + name;
	std::string outFilePath = path+name;

	outFile.open(outFilePath);
	if(outFile.is_open())
	{
		outFile<<this->m_PublicInitializationVector<<"\n";
		outFile<<encryptedText;
	}
	outFile.close();


	// ******************************* //
   //   конец writeFileForEncryption  //
  // ******************************* //
}
