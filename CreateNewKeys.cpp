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
	delete this->ui;
	delete scene;
}

void CreateNewKeys::isReady()
{
	this->ui->progressBar->setValue(static_cast<int>((static_cast<double>(*m_readyIndex)/(CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE))*100));

	if(*m_readyIndex == CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE)
	{
		this->ui->okButtonBox->setEnabled(true);
	}
}
/*
void CreateNewKeys::on_okButtonBox_accepted()
{
	//this->m_parent->getAesEncryptor();
}
*/
void CreateNewKeys::on_buttonBox_2_rejected()
{
	this->reject();
}


