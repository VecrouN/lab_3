#ifndef CREATENEWKEYS_H
#define CREATENEWKEYS_H

#include <QDialog>
#include <PaintScene.h>
#include <crypto++/aes.h>
#include <iostream>

namespace Ui {
	class createNewKeys;
}

class createNewKeys : public QDialog
{
		Q_OBJECT

	public:
		explicit createNewKeys(byte *_array,  int *readyIndex, QWidget *parent = nullptr);
		~createNewKeys();

	private slots:
		void isReady();

		void on_okButtonBox_accepted();

		void on_buttonBox_2_rejected();

	private:
		Ui::createNewKeys *ui;
		PaintScene *scene;
		int *m_readyIndex;
		byte *m_array;
};

#endif // CREATENEWKEYS_H
