#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H
#include <QVector>
#include <QString>

class Round_Robin {
public:
    static void erase(QVector <QString> &process, QVector <int>&ArrivalTime, QVector <int> &BurstTime, int &size, int i) {
        //function to erase one element from each QVector with index i
        for (int j = i; j<size - 1; j++)
        {
            process[j] = process[j + 1];
            ArrivalTime[j] = ArrivalTime[j + 1];
            BurstTime[j] = BurstTime[j + 1];
        }
        size--;
        process.resize(size);
        ArrivalTime.resize(size);
        BurstTime.resize(size);
    }
public:
    static void sort_process(QVector <QString> &process, QVector <int>&ArrivalTime, QVector <int> &BurstTime, int &size) {
        //function to sort processes according to arrival time.
        int temp_int;
        QString temp_process;
        for (int i = 0; i<size; i++) {
            for (int j = i; j<size; j++) {
                if (ArrivalTime[j]<ArrivalTime[i]) {
                    //swape arrival time
                    temp_int = ArrivalTime[j];
                    ArrivalTime[j] = ArrivalTime[i];
                    ArrivalTime[i] = temp_int;
                    //swape burst time
                    temp_int = BurstTime[j];
                    BurstTime[j] = BurstTime[i];
                    BurstTime[i] = temp_int;
                    //swape processes
                    temp_process = process[j];
                    process[j] = process[i];
                    process[i] = temp_process;
                }
            }
        }
    }
public:
    static void round_robin_editing(QVector <QString> &process, QVector <int>&ArrivalTime, QVector <int> &BurstTime, int &size, int Q) {
        int temp_size = 0, adder = 0;
        QVector <QString> rr_process;
        QVector <int> rr_ArrivalTime;
        QVector <int>  rr_BurstTime;
        QVector <int>  rr_GapTime;
        int  rr_size;
        //calculating new number of processes according to RR and resizing the new QVectors.
        for (int i = 0; i<size; i++) {
            if (BurstTime[i] % Q == 0)
            {
                temp_size = temp_size + (BurstTime[i] / Q);
            }
            else
            {
                temp_size = temp_size + (BurstTime[i] / Q) + 1;
            }
        }
        rr_size = temp_size + 1;
        rr_process.resize(rr_size);
        rr_ArrivalTime.resize(rr_size);
        rr_BurstTime.resize(rr_size);
        //cutting the old processes accroding to the RR and placing them in the new QVectors
        int j = 0, total_burst = 0;
        while (size >0) {
            for (int i = 0; i<size; i++) {
                for (int k = 0; k<j; k++) {
                    total_burst += rr_BurstTime[k];
                }
                if (((ArrivalTime[i]>total_burst) && (i != 0)) && (ArrivalTime[i]>(total_burst + ArrivalTime[0])))
                {
                    total_burst = 0;
                    continue;
                }
                total_burst = 0;
                rr_process[j] = process[i];
                rr_ArrivalTime[j] = ArrivalTime[i];
                if (BurstTime[i] >= Q)
                {
                    rr_BurstTime[j] = Q;
                    BurstTime[i] = BurstTime[i] - Q;
                    if (BurstTime[i] == 0)
                    {
                        erase(process, ArrivalTime, BurstTime, size, i);
                        i--;
                    }

                }
                else
                {
                    rr_BurstTime[j] = BurstTime[i];
                    erase(process, ArrivalTime, BurstTime, size, i);
                    i--;

                }
                j++;

            }
        }
        //returning the new processes to old QVectors
        size = rr_size - 1;
        process.resize(size);
        ArrivalTime.resize(size);
        BurstTime.resize(size);
        for (int i = 0; i<size; i++) {
            process[i] = rr_process[i];
            ArrivalTime[i] = rr_ArrivalTime[i];
            BurstTime[i] = rr_BurstTime[i];
        }

    }
public:
    static void adding_starting_gap_time(QVector <QString> &process, QVector <int>&ArrivalTime, QVector <int> &BurstTime, QVector <int> &StartingTime, QVector <int> &GapTime, int &size)
    {
        int temp = 0;
        //resizing new QVectors to the new number of processes after modifying them.
        StartingTime.resize(size);
        GapTime.resize(size);
        //placing first element as is
        StartingTime[0] = ArrivalTime[0];
        GapTime[0] = ArrivalTime[0];
        //calculating starting time and Burst time by comparing with last element.
        for (int i = 1; i<size; i++)
        {
            if ((StartingTime[i - 1] + BurstTime[i - 1]) >= ArrivalTime[i])
            {
                StartingTime[i] = StartingTime[i - 1] + BurstTime[i - 1];
                GapTime[i] = 0;
            }
            else
            {

                GapTime[i] = ArrivalTime[i] - (StartingTime[i - 1] + BurstTime[i - 1]);
                StartingTime[i] = StartingTime[i - 1] + BurstTime[i - 1] + GapTime[i];
            }

        }
    }
public: static void RR(QVector <QString> &process, QVector <int>&ArrivalTime, QVector <int> &BurstTime, QVector <int> &StartingTime, QVector <int> &GapTime, int &size, int Q) {
    //sorting processes according to arrival time.
    sort_process(process, ArrivalTime, BurstTime, size);
    //making RR slices.
    round_robin_editing(process, ArrivalTime, BurstTime, size, Q);
    //adding starting and gap times to the processes.
    adding_starting_gap_time(process, ArrivalTime, BurstTime, StartingTime, GapTime, size);
}
public: static float AVG_waiting(QVector <int>&ArrivalTime, QVector <int> &StartingTime, int &size) {

    int total_wait = 0;
    for (int i = 0; i<size; i++) {
        total_wait += StartingTime[i] - ArrivalTime[i];
    }
    return ((float)total_wait / (float)size);
}
public: static float AVG_TurnAround(QVector <QString> &process, QVector <QString> &old_process, QVector <int>&ArrivalTime, QVector <int> &BurstTime, QVector <int> &StartingTime, int &size, int &old_size) {

    QVector <int> turn_around(old_size);
    int turn_aroundd = 0, sum = 0;
    for (int i = 0; i<old_size; i++) {
        for (int j = 0; j<size; j++) {
            if (old_process[i] == process[j])
            {
                turn_aroundd = StartingTime[j] + BurstTime[j] - ArrivalTime[j];
            }
        }
        turn_around[i] = turn_aroundd;
    }

    for (int i = 0; i<old_size; i++)
        sum += turn_around[i];
    return ((float)sum / (float)old_size);
}
};


#endif // ROUNDROBIN_H
