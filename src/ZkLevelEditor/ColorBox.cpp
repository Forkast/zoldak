#include "ColorBox.h"
#include "ColorPaletteWidget.h"

#include <QtCore>
#include <QtGui>

using namespace Zk::LevelEditor;

ColorBox::ColorBox(QWidget * parent)
	: QWidget(parent)
{
	selected = false;
}

ColorBox::~ColorBox()
{
	
}

void ColorBox::select()
{
	emit colorSelected(color);
	selected = true;
	update();
}

void ColorBox::setColor(QColor color)
{
	this->color = color;
}

QColor ColorBox::getColor() const
{
	return color;
}

QSize ColorBox::sizeHint() const
{
	return QSize(32, 32);
}

void ColorBox::deselect()
{
	selected = false;
	update();
}

void ColorBox::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.fillRect(rect(), color);
	
	if (selected)
	{
		painter.setPen(QPen(Qt::black, 2.0));
		painter.drawRect(rect().adjusted(1, 1, -1, -1));
		
		painter.setPen(QPen(QBrush(Qt::white, Qt::Dense4Pattern), 2.0));
		painter.drawRect(rect().adjusted(1, 1, -1, -1));
	}
}

void ColorBox::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		select();
		event->accept();
	}
	else if (event->button() == Qt::RightButton)
	{
		QColor c = QColorDialog::getColor(color, this);
		if (c.isValid())
		{
			color = c;
			update();
		}
		
		event->accept();
	}
	
	QWidget::mousePressEvent(event);
}
