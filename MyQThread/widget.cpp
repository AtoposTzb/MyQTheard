#include "widget.h"
#include "ui_widget.h"
#include "MyQthread.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //1 创建子线程对象
    Generate *gen = new Generate;
    BubbleSort *bubbl = new BubbleSort;
    QuickSort *quicks = new QuickSort;
    //2 启动子线程
    connect(this,&Widget::sendNum,gen,&Generate::getNum);
    connect(ui->startBt,&QPushButton::clicked,this,[=](){
        emit sendNum(10000);
        gen->start();
    });

     connect(gen,&Generate::sendArray,bubbl,&BubbleSort::getNum);
     connect(gen,&Generate::sendArray,quicks,&QuickSort::getNum);
    //子线程启动后生成的随机数需要发送到主线程并由ui显示
    connect(gen,&Generate::sendArray,this,[=](QVector<int> list){
        bubbl->start();
        quicks->start();
        for(int i=0;i<list.size();++i)
        {
            ui->randList->addItem(QString::number(list.at(i)));
        }
    });
    connect(bubbl,&BubbleSort::sendArray,this,[=](QVector<int> list){
        for(int i=0;i<list.size();++i)
        {
            ui->bubbleSortList->addItem(QString::number(list.at(i)));
        }
    });
    connect(quicks,&QuickSort::sendArray,this,[=](QVector<int> list){
        for(int i=0;i<list.size();++i)
        {
            ui->quickSortList->addItem(QString::number(list.at(i)));
        }
    });


}

Widget::~Widget()
{
    delete ui;
}

