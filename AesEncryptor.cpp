#include "AesEncryptor.h"


AesEncryptor::AesEncryptor()
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
	std::string path = filePath.substr(0, i-1), name = filePath.substr(i, filePath.length()-1);
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

	/*
	std::string textForEncryption = "Тестовый Текст нА случай отсутивия входного файла";
	std::string tmpString;
	std::ifstream readedFile;
	std::string ciphertext; // переменная для зашифрованного текста
	std::string decryptedtext; // переменная для расшифрованного текста
	*/


	/*
	 *
	 * вывод шифрованного текста
	 *


	std::cout << "Cipher Text (" << ciphertext.size() << " bytes)" << std::endl;
	std::cout<<"Cipher Text = "<<ciphertext<<"\n";
	std::cout<<"hex Cipher Text = "<<std::endl;
	for( int i = 0; i < ciphertext.size(); ++i)
	{
		std::cout << "0x" << std::hex << (0xFF & static_cast<byte>(ciphertext[i])) << " ";
	}




	*
	* сохранение в файл
	*
	*/



	//
	// Decrypt
	//


	/*
	readedFile.open("out.txt");
	plaintext = "";
	tmpString = "";
	memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE

	if(readedFile.is_open())
	{
		getline(readedFile, tmpString);
		for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
		{
			iv[i] = tmpString[i];
		}

		while (getline(readedFile, tmpString))
		{

			plaintext.append(tmpString+"\n");
		}
	}
	readedFile.close();


	std::cout<<"прочтенный iv = \n"<<iv<<std::endl;
	std::cout<<"\nпрочтенный шифрованный файл = \n"<<plaintext<<std::endl;


	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
	stfDecryptor.MessageEnd();

	//
	// Dump Decrypted Text
	//
	std::cout << "Расшифрованный текст = \n";
	std::cout << decryptedtext<< std::endl;

	return 0;
}
	*/
