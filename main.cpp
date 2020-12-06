#include "MainWindow.h"
#include "createNewKeys.h"


#include <QApplication>
//#include <crypto++/rsa.h>
#include <crypto++/aes.h>
//#include <crypto++/modes.h>
#include <iostream>
//#include <fstream>


int main(int argc, char* argv[])
{
	byte m_PrivateAesKey[ CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE]; // ключ шифрования
	memset( m_PrivateAesKey , 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE); // заполняет key значением 0x00, длина key CryptoPP::AES::DEFAULT_KEYLENGTH
	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE-1; ++i)
		{

			std::cout<<(0xFF & m_PrivateAesKey[i])<<"  ";
		}
	std::cout<<std::endl;
	std::cout<<m_PrivateAesKey<<std::endl;

	//byte *mm_PrivateAesKey = m_PrivateAesKey; // ключ шифрования

	QApplication a(argc, argv);
	int readyIndex = 0;
	int *ptrReadyIndex = &readyIndex;
	createNewKeys *w = new createNewKeys(m_PrivateAesKey, ptrReadyIndex);
	w->show();



	std::cout<<std::endl;
    return a.exec();


}
