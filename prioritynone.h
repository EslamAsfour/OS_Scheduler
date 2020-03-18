#ifndef PRIORITYNONE_H
#define PRIORITYNONE_H

#include <QString>
#include <QVector>

class PriorityNone
{

public:
    //this function is for internal usage only , never mind.
    int static bt_comparison(QVector <int> &v, int count) {

        //note for me : this function is also used to calculate the starting time from previous burst time of processes.

        int sum = 0;
        for (int i = 0; i < count; i++) {
            sum += v[i];
        }
        return sum;
    }


    //This function sort all processes names,burst time,arrival time and priority for non preemptive.

    void static sort_process_nonpre(QVector <QString> &proc_name, QVector <int> &bt, QVector <int> &arr, QVector <int> &priority, int &size) {

        int temp, index;
        QString temp_str;

        for (int i = 0; i < size; i++) {

            index = i;

            if (i == 0) {
                for (int j = i + 1; j < size; j++) {
                    if (arr[j] < arr[index]) {

                        index = j;

                    }
                    else if (arr[j] == arr[index]) {
                        if (priority[j] < priority[index]) {

                            index = j;

                        }

                        //we can handle if priorities are equal by process name.
                    }
                }
            }
            else {

                for (int j = i + 1; j < size; j++) {
                    if (arr[j] <= bt_comparison(bt, index) && priority[j] < priority[index]) {

                        index = j;

                        //we can handle if priorities are equal by process name.

                    }

                }


            }


            temp_str = proc_name[i];
            proc_name[i] = proc_name[index];
            proc_name[index] = temp_str;

            temp = bt[i];
            bt[i] = bt[index];
            bt[index] = temp;


            temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;


            temp = priority[i];
            priority[i] = priority[index];
            priority[index] = temp;
        }


    }


    //this function calculates waiting time and starting time and gap for each process and stores them in QVectors.

    void static calc_waiting_starting_gap(QVector <int> &bt, QVector <int> &arr, QVector <int> &starting, QVector <int> &waiting, QVector <int> &gap, int &size) {
        starting.resize(size);
        waiting.resize(size);
        gap.resize(size);
        for (int i = 0; i < size; i++) {

            if (i == 0) {
                starting[i] = arr[i];
                waiting[i] = 0;
            }
            else {
                starting[i] = bt_comparison(bt, i) + arr[0];
                if (arr[i] > starting[i]) {
                    gap[i] = arr[i] - starting[i];
                    starting[i] = arr[i];
                    waiting[i] = starting[i] - arr[i];

                }

                else {
                    waiting[i] = starting[i] - arr[i];
                }
            }
        }

    }

    // this function simply return average turnaround time.

    float static turnaround_avg(QVector <int> &bt, QVector <int> &waiting, int &size) {

        float ta_avg = 0;

        for (int i = 0; i < size; i++) {

            ta_avg += (bt[i] + waiting[i]);

        }

        ta_avg = ta_avg / size;

        return ta_avg;
    }

    // this function simply return average waiting time.

    float static waiting_avg(QVector <int> &waiting, int &size) {
        float avg = 0;
        for (int i = 0; i < size; i++) {
            avg += waiting[i];
        }
        avg = avg / size;

        return avg;
    }


    void static sort_process_sjf_nonpre(QVector <QString> &proc_name , QVector <int> &bt , QVector <int> &arr , int &size) {

            int temp , index;
            QString temp_str;

            for (int i = 0; i < size ; i++) {

                index = i;

                if(i == 0){
                for (int j = i + 1; j < size; j++) {
                    if (arr[j] < arr[index]) {

                            index = j;

                    }
                    else if (arr[j] == arr[index]) {
                        if(bt[j] < bt[index]){

                            index = j;

                        }

                        //we can handle if burst are equal by process name.
                    }
                }
                }
                else {

                    for (int j = i + 1; j < size; j++) {
                        if (arr[j] <= bt_comparison(bt,index) && bt[j] < bt[index]) {

                            index = j;

                            //we can handle if burst are equal by process name.

                        }

                    }


                }


                temp_str = proc_name[i];
                proc_name[i] = proc_name[index];
                proc_name[index] = temp_str;

                temp = bt[i];
                bt[i] = bt[index];
                bt[index] = temp;


                temp = arr[i];
                arr[i] = arr[index];
                arr[index] = temp;
            }
        }
};

#endif // PRIORITYNONE_H
