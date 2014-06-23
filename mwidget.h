#pragma once

#include <QtGui>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class mwidget : public QWidget{
	Q_OBJECT

public:
   mwidget(QWidget *parent);
   mwidget(){}
   void setcor(QString (&)[128][3]);
   void setnodes(int);
   void setError(bool);
   void selectnode(QString);

private:
   QPainter fore;
   QString cor[128][3],
		   naam;
   int nodes;
   bool err;

protected:
	void paintEvent(QPaintEvent *event);

signals:

};
