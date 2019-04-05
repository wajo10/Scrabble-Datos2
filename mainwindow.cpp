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
    Tablero_Cliente::getInstance().readInfo();
    Tablero_Cliente* TabClien = &Tablero_Cliente::getInstance();
    Socket* sock = &Socket::getInstance();
    string nombre = ui->lineEdit->text().toUtf8().constData();
    string codigo = ui->lineEdit_2->text().toUtf8().constData();
    string ip = TabClien->getIp().toUtf8().constData();
    string puertoStr = TabClien->getPuerto().toUtf8().constData();
    int puerto = std::stoi(puertoStr.c_str());
    TraductorCliente* TC=&TraductorCliente::getInstance();
    string unirseSala = TC->SerializarUnirseSala(ip,nombre,codigo);
    qDebug()<<unirseSala.c_str();
    string validacion=sock->enviar(unirseSala,puerto,"192.168.100.11",true);
    qDebug()<<validacion.c_str();
    if (validacion=="0"){
        qDebug()<<"No existe la sala";
        return;
    }
    else if (validacion=="2"){
        qDebug()<<"La sala está llena";
        return;
    }

    string confirmacion = sock->escuchar2(8078);
    qDebug()<<confirmacion.c_str();
    int puerto2;
    int turno;
    int tsala;
    string iniciales;
    TC->DeSerializarRespuestaUnirseSala(confirmacion,&puerto2,&turno,&iniciales,&tsala);
    TabClien->setPuertoServidor(puerto2);
    TabClien->setTurno(turno);
    TabClien->setTsala(tsala);
    crearTablero(iniciales);
    //botones::getInstance().puntaje(0);
    //botones::getInstance().resumen(" ");
}
void MainWindow:: crearTablero(string Iniciales)
{
    char array[7];
    qDebug()<<scene<<"$$$";
    Tablero_Cliente* Tc=&Tablero_Cliente::getInstance();
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
    Ficha::flagTurno=false;
    botones::getInstance().cicloPartida(Tc->getTsala(),Tc->getTurno());
}



void MainWindow::on_lineEdit_editingFinished()
{

}
void MainWindow::request(string agregar)
{
    char array[7];
    int xInicial = 807;

    int cantidad= agregar.length();
    for (int i=0;i<cantidad;i++){
        int aux=0;
        int* ptrIniciales = Ficha::ptrPosicionUnplayed;
        array[i] = agregar[i];
        Ficha * ficha = new Ficha(array[i]);
        scene->addItem(ficha);
        while( aux<7){
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

void MainWindow::on_pushButton_2_clicked()
{
    Tablero_Cliente::getInstance().readInfo();
    Tablero_Cliente* TabClien = &Tablero_Cliente::getInstance();
    Socket* sock = &Socket::getInstance();
    string nombre = ui->lineEdit->text().toUtf8().constData();
    int tsala = stoi(ui->lineEdit_2->text().toUtf8().constData());
    string ip = TabClien->getIp().toUtf8().constData();
    string puertoStr = TabClien->getPuerto().toUtf8().constData();
    int puerto = std::stoi("8080");
    TraductorCliente* TC=&TraductorCliente::getInstance();
    string crearSala = TC->SerializarCrearSala(ip,nombre,tsala);
    string respuesta = sock->enviar(crearSala,puerto,"192.168.100.11",true);
    TabClien->setTurno(0);
    int codigo=0;
    TC->DeSerializarRespuestaCrearSala(respuesta,&codigo);
    qDebug()<<codigo;
    QString A=QString::number(codigo);
    ui->lineEdit_3->setText("Esperando, el código de jugador es: "+A);

    string confirmacion = sock->escuchar2(8078);
    qDebug()<<confirmacion.c_str();
    int puerto2;
    int turno;
    string iniciales;
    TC->DeSerializarRespuestaUnirseSala(confirmacion,&puerto2,&turno,&iniciales,&tsala);
    TabClien->setPuertoServidor(puerto2);
    TabClien->setTurno(turno);
    TabClien->setTsala(tsala);
    crearTablero(iniciales);
    //botones::getInstance().puntaje(0);
    //botones::getInstance().resumen(" ");

}

