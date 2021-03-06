#include "priority_prim.h"


bool cmp(priority_Preemptive A, priority_Preemptive B)
{
    if (A.pr != B.pr)
        return A.pr < B.pr;
    else
        return A.at < B.at;
}



void priority_pree_Gantt_Chart(QVector<priority_Preemptive> &sr, QVector<QString>&ids)
{


    int time = 0, flag = 0, num=sr.size();
    while (flag!=1)
    {
        flag = 1;

        for (int i = 0; i < sr.size(); i++)
        {

            if (sr[i].rmt > 0 && sr[i].at <= time)
            {

                //cout << "At " << time << " : process NO. :" << sr[i].id << endl;
                ids.push_back(sr[i].id);
                sr[i].rmt--;
                flag = 0;
                if (sr[i].rmt == 0)
                {
                    num--;
                }


                for (int j = 0; j < sr.size(); j++)
                {
                    if (j != i && sr[j].at <= time && sr[j].rmt > 0)
                    {
                        sr[j].wt++;
                    }

                }
                break;


            }

        }
        if (num != 0 && flag==1)
        {
            flag = 0;
            ids.push_back("-1");
            for (int j = 0; j < sr.size(); j++)
            {
                if ( sr[j].at <= time && sr[j].rmt > 0)
                {
                    sr[j].wt++;
                }

            }

        }
        time++;




    }
    //cout << "the processes take " << time-1 << endl;






}



float priority_pree_Waiting_time(QVector<priority_Preemptive> &sr)
{

    int total = 0;
    for (int i = 0; i < sr.size(); i++)
    {

        total += sr[i].wt;




    }

    //cout<<"avg waiting time" << (1.0*total / sr.size())<<endl;
    return (1.0*total / sr.size()/100) ;


}
float priority_pree_Turn_Around(QVector<priority_Preemptive> &sr)
{

    int total = 0;
    for (int i = 0; i < sr.size(); i++)
    {

        total += sr[i].wt+sr[i].bt;




    }

    return (1.0*total / sr.size()/100);
}



void priority_pree(QVector<QString>&id, QVector<float>&burst, QVector<float>&arrival, QVector<float> &start, QVector<int>&priority, QVector<priority_Preemptive> &v)
{
    QVector<QString>time_line;
    //to put the input in SRFT QVector

    for (int i = 0; i < id.size(); i++)
    {
        v.push_back(priority_Preemptive(id[i], burst[i]*100, arrival[i]*100, priority[i]));
    }
    id.clear();
    burst.clear();
    arrival.clear();
    priority.clear();

    qSort(v.begin(), v.end(), cmp);
    priority_pree_Gantt_Chart(v, time_line);
    QString lastid= time_line[0];
    int gap=0, time=0;

    time_line.push_back("-1");
    for (int i = 0; i < time_line.size(); i++)
    {

        if (time_line[i] == lastid)
        {
            if (time_line[i] != "-1")
            {
                time++;
            }
            else if (time_line[i] == "-1")
            {
                gap++;
            }
        }
        else if (time_line[i] != lastid)
        {
            if (lastid != "-1" && time_line[i] != "-1")
            {
                id.push_back(lastid);
                burst.push_back(1.0*time/100);
                arrival.push_back(1.0*gap/100);
                lastid = time_line[i];
                time = 1;
                gap = 0;
            }
            else if (lastid != "-1" && time_line[i] == "-1")
            {
                id.push_back(lastid);
                burst.push_back(1.0*time/100);
                arrival.push_back(1.0*gap/100);
                lastid = time_line[i];
                time = 0;
                gap = 1;
            }
            else if (lastid == "-1")
            {
                lastid = time_line[i];
                time = 1;
            }

        }







    }




    float sta = 0;
    for (int i = 0; i < burst.size(); i++)
    {
        sta += arrival[i];
        start.push_back(sta);
        sta += burst[i];
    }



}
