#include "srtf.h"


bool cmp(SRTF_Process A, SRTF_Process B) {
    if (A.bt != B.bt)
        return A.bt < B.bt;
    else
        return A.at < B.at;
}

void SRTF_Gantt_Chart(QVector<SRTF_Process> &sr, QVector<QString> &ids)
{
    int time = 0, flag = 0, num = sr.size();
    while (flag != 1)
    {
        flag = 1;

        for (int i = 0; i < sr.size(); i++) {

            if (sr[i].rmt > 0 && sr[i].at <= time) {

                //cout << "At " << time << " : process NO. :" << sr[i].id << endl;
                ids.push_back(sr[i].id);
                sr[i].rmt--;
                flag = 0;
                if (sr[i].rmt == 0) {
                    num--;
                }

                for (int j = 0; j < sr.size(); j++) {
                    if (j != i && sr[j].at <= time && sr[j].rmt > 0) {
                        sr[j].wt++;
                    }

                }
                break;
            }
        }
        if (num != 0 && flag == 1) {
            flag = 0;
            ids.push_back("-1");
            for (int j = 0; j < sr.size(); j++) {
                if (sr[j].at <= time && sr[j].rmt > 0) {
                    sr[j].wt++;
                }

            }

        }
        time++;
    }
    //cout << "the processes take " << time-1 << endl;

}


float SRTF_Waiting_time(QVector<SRTF_Process> &sr) {

    int total = 0;
    for (int i = 0; i < sr.size(); i++) {

        total += sr[i].wt;
    }
    //cout<<"avg waiting time" << (1.0*total / sr.size())<<endl;
    return ((1.0*total / sr.size()) / 100);
}



float SRTF_Turn_Around(QVector<SRTF_Process> &sr) {

    int total = 0;
    for (int i = 0; i < sr.size(); i++) {
        total += sr[i].wt + sr[i].bt;
    }
    return ((1.0*total / sr.size()) / 100);
}



void SRTF(QVector<QString>&id, QVector<float>&burst, QVector<float>&arival, QVector<float> &start, QVector<SRTF_Process> &v) {
    QVector<QString>time_line;
    //to put the input in SRFT QVector

    for (int i = 0; i < id.size(); i++) {

        v.push_back(SRTF_Process(id[i], burst[i] * 100, arival[i] * 100));
    }
    id.clear();
    burst.clear();
    arival.clear();

    qSort(v.begin(), v.end(), cmp);
    SRTF_Gantt_Chart(v, time_line);
    int  gap = 0, time = 0;
    QString lastid = time_line[0];

    time_line.push_back("-1");
    for (int i = 0; i < time_line.size(); i++) {

        if (time_line[i] == lastid) {
            if (time_line[i] != "-1") {
                time++;
            }
            else if (time_line[i] == "-1") {
                gap++;
            }
        }
        else if (time_line[i] != lastid) {
            if (lastid != "-1" && time_line[i] != "-1") {
                id.push_back(lastid);
                burst.push_back(1.0*time / 100);
                arival.push_back(1.0*gap / 100);
                lastid = time_line[i];
                time = 1;
                gap = 0;
            }
            else if (lastid != "-1" && time_line[i] == "-1") {
                id.push_back(lastid);
                burst.push_back(1.0*time / 100);
                arival.push_back(1.0*gap / 100);
                lastid = time_line[i];
                time = 0;
                gap = 1;
            }
            else if (lastid == "-1") {
                lastid = time_line[i];
                time = 1;
            }

        }







    }
    float sta = 0;
    for (int i = 0; i < burst.size(); i++) {
        sta += arival[i];
        start.push_back(sta);
        sta += burst[i];
    }








}
