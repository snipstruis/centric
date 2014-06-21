#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	MainWindow w;
	//start het programma
	w.start();
	w.show();

	return a.exec();
}
