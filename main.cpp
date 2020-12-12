#include "MainWindow.h"
#include "CreateNewKeys.h"


#include <QApplication>
//#include <crypto++/rsa.h>
#include <crypto++/aes.h>
#include <crypto++/modes.h>
//#include <crypto++/modes.h>
#include <iostream>
//#include <fstream>
#include <AesDecryptor.h>
#include <QFileDialog>

//		int argc, char* argv[]
int main(int argc, char* argv[])
{


	QApplication a(argc, argv);
	MainWindow w;
	w.show();

    return a.exec();
	//*/


}
