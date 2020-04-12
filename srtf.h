#ifndef SRTF_H
#define SRTF_H


#include<QVector>
#include<QtAlgorithms>
#include<QString>


struct SRTF_Process {
    QString id; // Process ID
    int bt; // Burst Time
    int at; // Arrival Time
    int rmt; // remaning time
    int wt; // waiting time
    SRTF_Process(QString i, int b, int a) {
        id = i;
        bt = b;
        at = a;
        rmt = b;
        wt = 0;
    }
};
void SRTF(QVector<QString>&id, QVector<int>&burst, QVector<int>&arival, QVector<int> &start, QVector<SRTF_Process> &v);

void SRTF_Gantt_Chart(QVector<SRTF_Process> &sr, QVector<int> &ids);

float SRTF_Waiting_time(QVector<SRTF_Process> &sr);
float SRTF_Turn_Around(QVector<SRTF_Process> &sr);



#endif // SRTF_H
