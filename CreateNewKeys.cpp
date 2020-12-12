#include "CreateNewKeys.h"
#include "ui_createNewKeys.h"

CreateNewKeys::CreateNewKeys(byte *_array,  int *readyIndex, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::createNewKeys)
{
	m_readyIndex = readyIndex;
	m_array = _array;
	ui->setupUi(this);
	scene = new PaintScene(_array, readyIndex, this);

	ui->graphicsView->setScene(scene);
	m_parent = parent;
	connect(scene, &PaintScene::changed, this, &CreateNewKeys::isReady);
}

CreateNewKeys::~CreateNewKeys()
{
	delete ui;
	delete scene;
	delete m_readyIndex;
	delete m_array;
	delete m_parent;
}

void CreateNewKeys::isReady()
{
	this->ui->progressBar->setValue(static_cast<int>((static_cast<double>(*m_readyIndex)/(CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE))*100));

	if(*m_readyIndex == CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE)
	{
		this->ui->okButtonBox->setEnabled(true);
	}
}

void CreateNewKeys::on_okButtonBox_accepted()
{
	//this->m_parent->getAesEncryptor();
}

void CreateNewKeys::on_buttonBox_2_rejected()
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