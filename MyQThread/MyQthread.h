#ifndef MYQTHREAD_H
#define MYQTHREAD_H

#include <QThread>
#include <QVector>

//生成随机数的类
class Generate : public QThread
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void getNum(int num);

protected:
    void run();

signals:
    void sendArray(QVector<int> num);

private:
    int m_num;

};

//冒泡排序的类
class BubbleSort : public QThread
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void getNum(QVector<int> list);

protected:
    void run();

signals:
    void sendArray(QVector<int> num);

private:
    QVector<int> m_list;
};

//快速排序的类
class QuickSort : public QThread
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void getNum(QVector<int> list);
    void quick_sort(QVector<int> &s, int l, int r);

protected:
    void run();

signals:
    void sendArray(QVector<int> num);

private:
    QVector<int> m_list;

};

#endif // MYQTHREAD_H
