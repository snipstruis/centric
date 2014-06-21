#include "mwidget.h"

mwidget::mwidget(QWidget *parent) :
	QWidget(parent){

}

void mwidget::paintEvent(QPaintEvent *event){
	QString x = "images/room.png";
	QPixmap kamergrond(x),
			punt(202,202);
	punt.fill("transparent");
	QPainter back(this),
			fore(&punt);

	//de punten tekenen op de pixmap
	fore.setPen(Qt::black);
	for(int i=0;i<nodes;i++){
		fore.drawEllipse(cor[i][1].toInt(),cor[i][2].toInt(),1,1);
	}

	//geselcteerde punt andere kleur geven
	for(int i=0;i<nodes;i++){
		if(naam==cor[i][0]){
			fore.setPen(Qt::red);
			fore.drawEllipse(cor[i][1].toInt(),cor[i][2].toInt(),1,1);
		}
	}

	//de plattegrond van de kamer tekenen en daarna de punten er overheen
	back.drawPixmap(rect(),kamergrond);
	back.drawPixmap(rect(),punt);
}

void mwidget::setcor(QString (&x)[128][3]){
	for(int i=0;i<128;i++)
		for(int j=0;j<3;j++)
			cor[i][j]=x[i][j];
}

void mwidget::setnodes(int x){
	nodes = x;
}

void mwidget::selectnode(QString in){
	naam = in;
	repaint();
}
