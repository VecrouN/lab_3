#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>

#include <QWidget>
#include <crypto++/aes.h>

class PaintScene : public QGraphicsScene
{

	Q_OBJECT

public:
	 explicit PaintScene(byte *_array, 	int *readyIndex, QObject *parent = 0);
	~PaintScene();

private:
	QPointF previousPoint;      // Координаты предыдущей точки

	// Для рисования используем события мыши
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	//byte *m_array[CryptoPP::AES::BLOCKSIZE+ CryptoPP::AES::DEFAULT_KEYLENGTH];
	byte *m_array;
	int *m_readyIndex;
	int m_step;
	int m_indexStep;

};
#endif // PAINTSCENE_H
