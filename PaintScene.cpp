#include "PaintScene.h"
#include <iostream>
PaintScene::PaintScene(byte *_array, int *readyIndex, QObject *parent) : QGraphicsScene(parent)
{
	//m_readyIndex = 0;
	m_array = _array;
	m_readyIndex = readyIndex;
	m_step = 5;
	m_indexStep = 0;
}


PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	;
	previousPoint = event->scenePos();

	// При нажатии кнопки мыши отрисовываем эллипс
	addEllipse(previousPoint.x() - 5,
			   previousPoint.y() - 5,
			   10,
			   10,
			   QPen(Qt::NoPen),
			   QBrush(Qt::black));
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	// Отрисовываем линии с использованием предыдущей координаты
	char tmpChar;
	addLine(previousPoint.x(),
			previousPoint.y(),
			event->scenePos().x(),
			event->scenePos().y(),
			QPen(Qt::black,10,Qt::SolidLine,Qt::RoundCap));
	// Обновляем данные о предыдущей координате
		previousPoint = event->scenePos();
		++m_indexStep;
		if(m_indexStep == m_step)
		{
			m_indexStep = 0;
			tmpChar = static_cast<int>(previousPoint.x()+previousPoint.y()) % 255 - 128;
			if(*m_readyIndex < CryptoPP::AES::DEFAULT_KEYLENGTH + CryptoPP::AES::BLOCKSIZE)
			{
				if(( static_cast<int>(tmpChar) != 127 ) && ( ( static_cast<int>(tmpChar) < 0 ) || ( static_cast<int>(tmpChar) >  31 ) ))
				{

					m_array[*m_readyIndex] = tmpChar;
					++(*m_readyIndex);
				}

			}
			else
			{
				if(( static_cast<int>(tmpChar) != 127 ) && ( ( static_cast<int>(tmpChar) < 0 ) || ( static_cast<int>(tmpChar) >  31 ) ))
				{
					for (int i = 0; i < CryptoPP::AES::BLOCKSIZE + CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
					{
						m_array[i] = m_array[i+1];
					}
					;
					m_array[*m_readyIndex] = tmpChar;
				}
			}
		}
}
