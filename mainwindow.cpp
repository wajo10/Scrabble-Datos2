#include "mainwindow.h"
QGraphicsScene* MainWindow::scene= nullptr;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
}

void MainWindow::fichaAdversario(char *letra, int *fila, int *columna, int tam)
{
    int contador=0;
    char *ptrLetra=letra;
    int *ptrFila = fila;
    int *ptrColumna = columna;
    while(contador<tam){
        Ficha *fichaAdv = new Ficha(*(ptrLetra+contador));
        fichaAdv->setX((*(ptrColumna+contador)*43.65)+42);
        fichaAdv->setY((*(ptrFila+contador)*43.65)+44);
        fichaAdv->setSejugo(true);
        fichaAdv->flagMove=false;
        scene->addItem(fichaAdv);
        Tablero_Cliente::getInstance().ColocarFicha(fila,columna,tam);
        contador++;
    }
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
    string confirmacion = sock->enviar(unirseSala,puerto,"192.168.100.18",true);
    bool val;
    int puerto2;
    int turno;
    TC->DeSerializarRespuestaUnirseSala(confirmacion,&val,&puerto2,&turno);
    if (val){
        TabClien->setPuertoServidor(puerto2);
        TabClien->setTurno(turno);
    }
}
void MainWindow:: crearTablero()
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

void MainWindow::on_pushButton_2_clicked()
{
    Tablero_Cliente::getInstance().readInfo();
    Tablero_Cliente* TabClien = &Tablero_Cliente::getInstance();
    Socket* sock = &Socket::getInstance();
    string nombre = ui->lineEdit->text().toUtf8().constData();
    string ip = TabClien->getIp().toUtf8().constData();
    string puertoStr = TabClien->getPuerto().toUtf8().constData();
    int puerto = std::stoi("8080");
    TraductorCliente* TC=&TraductorCliente::getInstance();
    string crearSala = TC->SerializarCrearSala(ip,nombre);
    string respuesta = sock->enviar(crearSala,puerto,"192.168.100.18",true);
    TabClien->setTurno(1);
    int codigo=0;
    TC->DeSerializarRespuestaCrearSala(respuesta,&codigo);
    qDebug()<<codigo;
    QString A=QString::number(codigo);
    ui->lineEdit_3->setText("Esperando jugadores, el código de jugador es: "+A);

}
