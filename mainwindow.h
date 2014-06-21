#pragma once

#include <QMainWindow>
#include "mwidget.h"
#include "algo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	Ui::MainWindow *ui;
	void start();

private:
	QString tmp[128][3];
	mwidget kamer;
	Algo alg;
	vaste_nodes no;
	naar_gui out;

	void algorithm();
	void fillpic();
	void fillbox();

private slots:
	void on_selector_currentTextChanged(const QString &arg1);

};
