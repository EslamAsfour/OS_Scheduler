#ifndef SJF_NONPRIM_H
#define SJF_NONPRIM_H

#include <QVector>
#include <QString>
#include "prioritynone.h"




class SJF_NonPrim
{

 public:   void static sort_process_sjf_nonpre(QVector <QString> &proc_name , QVector <float> &bt , QVector <float> &arr , int &size, QVector <float> &gap) {

            float temp ; int index;
            QString temp_str;
            gap.resize(proc_name.size());
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
                        if (arr[j] <= PriorityNone::bt_comparison(bt,index,gap) && bt[j] < bt[index]) {

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

#endif // SJF_NONPRIM_H
