#include "createNewKeys.h"
#include "ui_createNewKeys.h"

createNewKeys::createNewKeys(byte *_array,  int *readyIndex, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::createNewKeys)
{
	m_readyIndex = readyIndex;
	m_array = _array;
	ui->setupUi(this);
	scene = new PaintScene(_array, readyIndex, this);

	ui->graphicsView->setScene(scene);

	connect(scene, &PaintScene::changed, this, &createNewKeys::isReady);
}

createNewKeys::~createNewKeys()
{
	delete ui;
	delete  scene;
	delete m_readyIndex;
	delete m_array;
}

void createNewKeys::isReady()
{
	this->ui->progressBar->setValue(static_cast<int>((static_cast<double>(*m_readyIndex)/(CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE))*100));

	if(*m_readyIndex == CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE)
	{
		this->ui->okButtonBox->setEnabled(true);
	}
}

void createNewKeys::on_okButtonBox_accepted()
{
	std::cout<<"new: "<<std::endl;

	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE + CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
	{

		std::cout<<(0xFF & m_array[i])<<"  ";
	}
	std::cout<<std::endl;
	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE + CryptoPP::AES::DEFAULT_KEYLENGTH ; ++i)
	{

		std::cout<<static_cast<char>(m_array[i])<<"  ";
	}
	std::cout<<std::endl;
}

void createNewKeys::on_buttonBox_2_rejected()
{

	std::cout<<"new: "<<std::endl;

	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE + CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
	{

		std::cout<<(0xFF & m_array[i])<<"  ";
	}
	std::cout<<std::endl;
	for(int i = 0; i < CryptoPP::AES::BLOCKSIZE + CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
	{

		std::cout<<static_cast<char>(m_array[i])<<"  ";
	}
	std::cout<<std::endl;
}
