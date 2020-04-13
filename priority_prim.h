#ifndef PRIORITY_PRIM_H
#define PRIORITY_PRIM_H


#include<QVector>
#include<QtAlgorithms>
#include <QString>



struct priority_Preemptive
{
    QString id; // Process ID
    int bt; // Burst Time
    int at; // Arrival Time
    int rmt; // remaning time
    int wt; // waiting time
    int pr; //priority


    priority_Preemptive(QString i, int b, int a, int c)
    {
        id = i;
        bt = b;
        at = a;
        rmt = b;
        wt = 0;
        pr = c;



    }
};
void priority_pree(QVector<QString>&id, QVector<float>&burst, QVector<float>&arrival, QVector<float> &start, QVector<int>&priority, QVector<priority_Preemptive> &v);

void priority_pree_Gantt_Chart(QVector<priority_Preemptive> &sr, QVector<QString>&ids);

float priority_pree_Waiting_time(QVector<priority_Preemptive> &sr);
float priority_pree_Turn_Around(QVector<priority_Preemptive> &sr);





#endif // PRIORITY_PRIM_H
