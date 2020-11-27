#include "MainWindow.h"

#include <QApplication>
//#include <crypto++/rsa.h>
//#include <crypto++/aes.h>
//#include <crypto++/modes.h>
//#include <iostream>
//#include <fstream>

int main(int argc, char* argv[])
{
	/*
	srand(static_cast<unsigned int>(time(0))); //  сид для случайного числа

	byte m_PublicInitializationVector[ CryptoPP::AES::BLOCKSIZE ]; // вектор инициализации для шифровки 1ого блока, не скрывается

	memset( m_PublicInitializationVector , 0x00, CryptoPP::AES::BLOCKSIZE ); // заполняет iv значением 0x00, длина iv CryptoPP::AES::BLOCKSIZE
	std::ofstream testout;
	testout.open("testout.txt");


	const int length = 10;
	const int num = 10;

	char tmp_char;
	std::string tmp_string;
	for(int j = 0; j < num; ++j)
	{
		tmp_string = "";
		for(int i = 0; i < length; ++i)
		{
			do
			{
				//srand(static_cast<unsigned int>(time(0)));
				tmp_char = rand()% 255 - 128;
			}while( ( static_cast<int>(tmp_char) == 127 ) || ( ( static_cast<int>(tmp_char) >= 0 ) && ( static_cast<int>(tmp_char) <=  31 ) ) );

			// if(i == 2) tmp_char = -18;
			//m_PublicInitializationVector[i] = 0xFF & static_cast<byte>(tmp_char);
			tmp_string.push_back(tmp_char);
			// std::cout<<"i = "<<i<<"\t\tchar = "<<tmp_char<<"\t\tcode = "<<static_cast<int>(tmp_char)<<std::endl;
		}

		std::cout<<"j = "<<j<<"\tstring = \t\""<<tmp_string<<"\"\tstring length = "<<tmp_string.length()<<std::endl;
		// testout<<tmp_string<<"КОНЕЦ"<<std::endl;
		testout<<tmp_string<<std::endl;
	}
	testout.close();
	std::cout<<std::endl;
	std::cout<<std::endl;
	std::ifstream in;
	in.open("testout.txt");
	//ifstream in(FName);     //открыли для чтения  файл
	tmp_string = "";

	for(int j = 0; j < num; ++j)
	{
		tmp_string = "";
		for(int i = 0; i < length; ++i)
		{
			tmp_char = in.get();
			if(tmp_char != '\n')
				tmp_string.push_back(tmp_char);

		}
		in.get();
		std::cout<<"j = "<<j<<"\tstring = \t\""<<tmp_string<<"\"\tstring length = "<<tmp_string.length()<<std::endl;

	}
	in.close();


	return 0;
	*/
	QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


}

// ЗАМЕТКИ
// QFileDialog для файлового менеджера
// crypto++ для работы с ключами и шифрованием
//

// TODO
