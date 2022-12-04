#include "MyQthread.h"
#include <QElapsedTimer>
#include <QDebug>

Generate::Generate(QObject *parent)
    : QThread{parent}
{

}

void Generate::getNum(int num)
{
    m_num = num;
}

//子线程执行生成随数
void Generate::run()
{
    QVector<int> list;
    //记录生成随机数的时间和线程地址
    QElapsedTimer times;
    times.start();
    qDebug()<<"生成随机数的线程地址："<<QThread::currentThread();
    for(int i = 0 ;i<m_num;++i)
    {
        list.push_back(rand()%10000);
    }
    int milce = times.elapsed();
    qDebug()<<"生成随机数的时间："<<milce<<"毫秒";
    emit sendArray(list);
}


//冒泡排序的类
BubbleSort::BubbleSort(QObject *parent):QThread{parent}
{

}

void BubbleSort::getNum(QVector<int> list)
{
    m_list = list;
}
void BubbleSort::run()
{
    int temp;
    QElapsedTimer times;
    times.start();
    qDebug()<<"冒泡排序的线程地址："<<QThread::currentThread();
    //进行冒泡排序操作
    for(int i = 0;i<m_list.size();++i)
        for(int j = 0;j<m_list.size()-i-1;++j)
        {
            if(m_list[j]>m_list[j+1])
            {
                temp=m_list[j];
                m_list[j]=m_list[j+1];
                m_list[j+1] = temp;
            }
        }
    int milce = times.elapsed();
    qDebug()<<"冒泡排序的时间："<<milce<<"毫秒";
    emit sendArray(m_list);
}

//快速排序
QuickSort::QuickSort(QObject *parent):QThread{parent}
{

}

void QuickSort::getNum(QVector<int> list)
{
    m_list = list;
}

void QuickSort::quick_sort(QVector<int> &s, int l, int r)
{
    if (l < r)
    {
        //Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                s[i++] = s[j];

            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用
        quick_sort(s, i + 1, r);
    }
}

void QuickSort::run()
{
    QElapsedTimer times;
    times.start();
    qDebug()<<"快速排序的线程地址："<<QThread::currentThread();
    quick_sort(m_list, 0,m_list.size()-1);
    int milce = times.elapsed();
    qDebug()<<"快速排序的时间："<<milce<<"毫秒";
    emit sendArray(m_list);

}
