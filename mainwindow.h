#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QVector>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void  Display();
    void add_Input(QString proc,int Arr ,int Burst);

private slots:
    void on_pushButton_clicked();

    void on_ToIndex_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_ToIndex_2_clicked();

    void on_pushButton_Add_clicked();

    void on_FCFS_clicked();

    void on_RoundRobin_clicked();

    void on_PriorityNone_clicked();

    void on_Priority_clicked();

    void on_SJF_Non_clicked();

private:
    Ui::MainWindow *ui;

    QString type;           // First Input  From Index [0]

    QVector<QString> process;   //Index[1]
    QVector<int> BurstTime;     //Index[1]
    QVector<int> ArrivalTime;   //Index[1]
    QVector<int> TurnAroundTime;
    QVector<int> WaitingTime;
    QVector<int> Gap;
    QVector<int> StartingTime;
    QVector<int>Priority;

    float AvgWaitingTime;
    float AvgTurnAroundTime;
    int Q;      // RoundRobin

};
#endif // MAINWINDOW_H
