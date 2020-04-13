#ifndef FCFS_H
#define FCFS_H


#include <QVector>
#include <QString>

class FCFS {

public:static void Sort_arriaval_time(QVector <QString> &Process, QVector <float>&ArrivalTime, QVector <float> &BurstTime, int &size) {
    float temp_at;
    float temp_bt;
    QString temp_Process;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            if (ArrivalTime[i] < ArrivalTime[j]) {
                // swaping arrival time
                temp_at = ArrivalTime[i];
                ArrivalTime[i] = ArrivalTime[j];
                ArrivalTime[j] = temp_at;
                //swaping bt
                temp_bt = BurstTime[i];
                BurstTime[i] = BurstTime[j];
                BurstTime[j] = temp_bt;
                //swaping process
                temp_Process = Process[i];
                Process[i] = Process[j];
                Process[j] = temp_Process;
            }
        }
    }
}

public:static void find_waiting_time(QVector <QString> &Process, QVector <float>&ArrivalTime, QVector <float> &BurstTime, int &size, QVector <float>&WaitingTime) {
    Sort_arriaval_time(Process, ArrivalTime, BurstTime, size);
    float *service_time = new float[size];
    service_time[0] = 0;
    WaitingTime.resize(size); // change
    WaitingTime[0] = 0 ;
    for (int i = 1; i < size; i++) {  // Change
        //Add all burst time
        service_time[i] = service_time[i - 1] + BurstTime[i - 1];
        // find wait time
        WaitingTime[i] = service_time[i] - ArrivalTime[i];
        if (WaitingTime[i] < 0)
            WaitingTime[i] = 0;
    }

}

public:static void find_total_arround_time(QVector <QString> &Process, QVector <float>&ArrivalTime, QVector <float> &BurstTime, int &size, QVector <float>&WaitingTime, QVector <float>&TurnAroundTime) {
    find_waiting_time(Process, ArrivalTime, BurstTime, size, WaitingTime);
    TurnAroundTime.resize(size);   //Change
    for (int i = 0; i < size; i++) {
        TurnAroundTime[i] = WaitingTime[i] + BurstTime[i];
    }
}

public:static void find_total_average_time(QVector <QString> &Process, QVector <float>&ArrivalTime, QVector <float> &BurstTime, int size, QVector<float> &WaitingTime,
    QVector<float> &TurnAroundTime, float &AvgWaitingTime, float &AvgTurnAround)  {
    int sumOfTurnAround = 0;
    find_total_arround_time(Process, ArrivalTime, BurstTime, size, WaitingTime, TurnAroundTime);
    float sumOfWaitingTime = 0;
    find_waiting_time(Process, ArrivalTime, BurstTime, size, WaitingTime);
    for (int i = 0; i < size; i++)
    {
        sumOfTurnAround += TurnAroundTime[i];
        sumOfWaitingTime += WaitingTime[i];
    }
    AvgWaitingTime = (float)sumOfWaitingTime / (float)size;
    AvgTurnAround = (float)sumOfTurnAround / (float)size;
}

public:static void Gant_chart(QVector <QString> &Process, QVector <float>&ArrivalTime, QVector <float> &BurstTime, int size,
    QVector <float> &starting_time, QVector <float> &gap) {
    gap.resize(size);
    starting_time.resize(size);
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            starting_time[0] = ArrivalTime[0];
            if (ArrivalTime[0] > 0) {
                gap[0] = ArrivalTime[0];
            }
            gap[0] = 0;
        }
        else if (i == size) {
            starting_time[i] = ArrivalTime[i - 1] + BurstTime[i - 1];
        }
        else if (starting_time[i - 1] + BurstTime[i - 1] < ArrivalTime[i]) {
            starting_time[i] = ArrivalTime[i];
            gap[i] = ArrivalTime[i] - (starting_time[i - 1] + BurstTime[i - 1]);
        }
        else {
            starting_time[i] = starting_time[i - 1] + BurstTime[i - 1];
            gap[i] = 0;
        }

    }
}

};







#endif // FCFS_H
