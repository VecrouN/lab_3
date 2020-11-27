#include "AesEncryptor.h"


AesEncryptor::AesEncryptor()
{
	memset( m_CipherAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE

	return;
}

void AesEncryptor::AesEncryptFile()
{

}
int main()
{
	srand(static_cast<unsigned int>(time(0))); //  сид для случайного числа
	// byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
	//memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH ); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	//memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE

	/*
	*
	* заполнение iv случайными значениями
	*
	*/

	char tmp_char;
	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE-1; ++i)
	{
		tmp_char = rand()% 255 - 128;
		iv[i] = 0xFF & static_cast<byte>(tmp_char);
	}
	std::cout << "iv =\n"<<iv<<std::endl;
	std::cout << "hex iv =\n";

	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
	{
		std::cout << "0x" << std::hex << (0xFF & static_cast<byte>(iv[i])) << " ";
	}
	std::cout<<std::endl;
	/*
	*
	* объявление переменных
	*
	*/

	std::string plaintext = "Тестовый Текст нА случай отсутивия входного файла";
	std::string tmpString;
	std::ifstream readedFile;
	std::string ciphertext; // переменная для зашифрованного текста
	std::string decryptedtext; // переменная для расшифрованного текста



	/*
	 *
	 * чтение файла
	 *
	 */
	readedFile.open("test.txt");
	if(readedFile.is_open())
	{
		plaintext = "";
		while (getline(readedFile, tmpString))
		{
			plaintext.append(tmpString+"\n");
		}
	}
	readedFile.close();




	/*
	 *
	 * вывод текста для шифрования
	 *
	 */

	std::cout << "Текст для шифрования = " << std::endl;
	std::cout << plaintext<< std::endl;


	/*
	 *
	 * шифрование текста
	 *
	 */

	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH); // шифр
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv ); // режим работы cbc

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length()); // reinterpret_cast преобразование указателя
	stfEncryptor.MessageEnd();


	/*
	 *
	 * вывод шифрованного текста
	 *
	 */

	std::cout << "Cipher Text (" << ciphertext.size() << " bytes)" << std::endl;
	std::cout<<"Cipher Text = "<<ciphertext<<"\n";
	std::cout<<"hex Cipher Text = "<<std::endl;
	for( int i = 0; i < ciphertext.size(); ++i)
	{
		std::cout << "0x" << std::hex << (0xFF & static_cast<byte>(ciphertext[i])) << " ";
	}



	/*
	*
	* сохранение в файл
	*
	*/

	std::ofstream outFile;
	outFile.open("out.txt");
	if(outFile.is_open())
	{
		outFile<<iv<<"\n";
		outFile<<ciphertext;
	}
	outFile.close();

	std::cout << std::endl << std::endl;

	//
	// Decrypt
	//



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
