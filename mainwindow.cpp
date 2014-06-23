#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "network.h"
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
}

MainWindow::~MainWindow(){
	delete ui;
}

void MainWindow::start(){
	algorithm();
}

void MainWindow::on_selector_currentTextChanged(const QString &arg1){
	ui->kamer->selectnode(arg1);
}

//gives data to map and draws map
void MainWindow::fillpic(){
	ui->kamer->setnodes(out.number_of_nodes);
	ui->kamer->setcor(tmp);
}

//fills the temporary array and selector dropdown box
void MainWindow::fillbox(){
	for(int i = 0; i < out.number_of_nodes; i++){

		tmp[i][0] = QString::fromStdString("item "+out.xeny[i].mac);
		tmp[i][1] = QString("%1").arg(out.xeny[i].x);
		tmp[i][2] = QString("%1").arg(out.xeny[i].y);

		ui->selector->addItem(tmp[i][0]);
	}
}

//execute the algorithm and continue the program
void MainWindow::algorithm(){

	try{
        ServerConnection server("http://vanriel.eu/devcare/dummy.php");

		auto v = parsejson(server.httpGet());

		vaste_nodes no;
		no.a = v.second[0];
		no.b = v.second[1];
		no.c = v.second[2];

		out = alg.bereken(no, v.first);
	}
	catch(const std::runtime_error e){
		cerr<<"exception: "<<e.what()<<endl;
		exit(-1);
	}


	fillbox();
	fillpic();
}

void MainWindow::on_scanknop_clicked()
{
    algorithm();
}
