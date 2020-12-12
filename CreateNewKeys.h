#ifndef CREATENEWKEYS_H
#define CREATENEWKEYS_H

#include <QDialog>
#include <PaintScene.h>
#include <crypto++/aes.h>
#include <iostream>

namespace Ui {
	class createNewKeys;
}

class CreateNewKeys : public QDialog
{
		Q_OBJECT

	public:
		explicit CreateNewKeys(byte *_array,  int *readyIndex, QWidget *parent = nullptr);
		~CreateNewKeys();


	private slots:
		void isReady();

		void on_okButtonBox_accepted();

		void on_buttonBox_2_rejected();

	private:
		Ui::createNewKeys *ui = nullptr;
		PaintScene *scene = nullptr;
		int *m_readyIndex = nullptr;
		byte *m_array = nullptr;
		QWidget *m_parent = nullptr;
};

#endif // CREATENEWKEYS_H
