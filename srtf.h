#ifndef SRTF_H
#define SRTF_H


#include<QVector>
#include<QtAlgorithms>
#include<QString>


struct SRTF_Process {
    QString id; // Process ID
    float bt; // Burst Time
    float at; // Arrival Time
    float rmt; // remaning time
    float wt; // waiting time
    SRTF_Process(QString i, float b, float a) {
        id = i;
        bt = b;
        at = a;
        rmt = b;
        wt = 0;
    }
};
void SRTF(QVector<QString>&id, QVector<float>&burst, QVector<float>&arival, QVector<float> &start, QVector<SRTF_Process> &v);

void SRTF_Gantt_Chart(QVector<SRTF_Process> &sr, QVector<QString> &ids);

float SRTF_Waiting_time(QVector<SRTF_Process> &sr);
float SRTF_Turn_Around(QVector<SRTF_Process> &sr);



#endif // SRTF_H
