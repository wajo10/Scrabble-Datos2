#include "mainwindow.h"
QGraphicsScene* MainWindow::scene= nullptr;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Bolsa *bolsa = new Bolsa();
    string Iniciales = bolsa->fichas_turno(7);
    char array[7];

    //Crear view
    QGraphicsView * view = new QGraphicsView(scene);
    view->show();
    view-> setFixedSize(1300,700);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,1300,700);

    //Hud
    pantalla * Pantalla = new pantalla();
    scene->addItem(Pantalla);
    int xInicial = 807;
    //Creacion inicial de fichas
    for (int i=0;i<7;i++){
        array[i] = Iniciales[i];
        Ficha * ficha = new Ficha(array[i]);
        ficha->setX(xInicial);
        ficha->setY(237);
        ficha->posInicial = i;
        scene->addItem(ficha);
        ficha->setUnplayed();
        xInicial+=57;
    }
    qDebug()<<scene<<"Main";

    //Boton
    botones *Boton = new botones();
    Boton->setX(1000);
    Boton->setY(404);
    scene->addItem(Boton);
}

void MainWindow::on_lineEdit_editingFinished()
{

}
void MainWindow::request(int cantidad)
{
    string agregar = Bolsa::getInstance().fichas_turno(cantidad);
    char array[7];
    int xInicial = 807;

    for (int i=0;i<cantidad;i++){
        int aux=0;
        int* ptrIniciales = Ficha::ptrPosicionUnplayed;
        array[i] = agregar[i];
        Ficha * ficha = new Ficha(array[i]);
        scene->addItem(ficha);
        while( aux<7){
            qDebug()<<*(ptrIniciales+aux)<<"AUX";
            if (*(ptrIniciales+aux)==0){
                 ficha->setX(57*aux+xInicial);
                 ficha->setY(237);
                 ficha->posInicial = aux;
                 ficha->setUnplayed();
                 break;
            }
            aux++;
        }


    }

}
