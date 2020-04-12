#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtDebug>
#include <QMessageBox>

            //Our Classes

#include "fcfs.h"
#include "prioritynone.h"
#include "sjf_nonprim.h"
#include "roundrobin.h"
#include "srtf.h"

/* ---------------------------------------------------- */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabs->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Display()
{

    for(int i = 0 ; i < process.length(); i++)
    {
        if(Gap[i] > 0 )
        {
            // Vertical Box
            auto box = new QVBoxLayout();
            box->setSpacing(0);
            box->setMargin(0);


            // Add Button and label
            auto item = new QPushButton("GAP");
            item->setStyleSheet("color : blue; height : 35px; font-size : 12px; font : bold  ");
            auto timeDiff = new QLabel(QString::number(StartingTime[i]-Gap[i]));
            box->addWidget(item);
            box->addWidget(timeDiff);
            box->setAlignment(Qt::AlignLeft);
            box->setAlignment(Qt::AlignTop);

            // Widget to set Width and Height
            auto wid = new QWidget();
            wid->setFixedWidth((Gap[i]*10)+10);
            wid->setLayout(box);

           ui->GanttChartLayOut->setAlignment(Qt::AlignHCenter);
           ui->GanttChartLayOut->addWidget(wid,0);
        }


            // Vertical Box
            auto box = new QVBoxLayout();
            box->setSpacing(0);
            box->setMargin(0);



            // Add Button and label
            auto item = new QPushButton(process[i]);
            item->setStyleSheet("color : red; height : 35px; font-size : 12px;font : bold ");
            auto timeDiff = new QLabel(QString::number(StartingTime[i]));

            box->addWidget(item);
            box->addWidget(timeDiff);
            box->setAlignment(Qt::AlignLeft);
            box->setAlignment(Qt::AlignTop);

            // Widget to set Width and Height
            auto wid = new QWidget();
            wid->setFixedWidth((BurstTime[i]*10)+10);
            wid->setLayout(box);

           ui->GanttChartLayOut->setAlignment(Qt::AlignHCenter);
           ui->GanttChartLayOut->addWidget(wid,0);
           ui->label_FillTurnAround->setText(QString::number(AvgTurnAroundTime));
           ui->label_FillWaitingTime->setText(QString::number(AvgWaitingTime));

    }
}

bool MainWindow::add_Input(QString proc, QString Arr, QString Burst)
{
     process.push_back(proc);
     bool ArrFlag = true;
     bool BurFlag = true;
    // Check If input is number as it should Be Or we output an error msg
     foreach(QChar c , Arr )
    {
        if(!(c.isNumber()))
        {
            ArrFlag = false;
            break;
        }
    }
    foreach(QChar c , Burst )
    {
        if(!(c.isNumber()))
        {
            BurFlag = false;
            break;
        }
    }
    if(ArrFlag && BurFlag)
    {
        ArrivalTime.push_back( Arr.toInt());
        BurstTime.push_back(Burst.toInt());
        return true;
    }
    else            // One of them or both are wronge input
    {
        QString msg = "You Entered A Wrone input Please Try Again";
        QMessageBox::warning(this,"Wronge Input",msg);
        return false;
    }


}


// Function to Go to the next page and prepare the optional LineEdits Based on the Type

void MainWindow::on_ToIndex_1_clicked()
{
    if(type == "FCFS")
      {
           ui->tabs->setCurrentIndex(1);
           ui->Input->findChild<QLabel*>("Dep_Label")->hide();
           ui->Input->findChild<QLineEdit*>("lineEdit_Dep")->hide();
      }
    else if (type == "Priority_Prim")
    {
             ui->tabs->setCurrentIndex(1);
             ui->Input->findChild<QLabel*>("Dep_Label")->setText("Priority ");
    }
    else if (type == "PriorityNone")
    {
       ui->tabs->setCurrentIndex(1);
       ui->Input->findChild<QLabel*>("Dep_Label")->setText("Priority ");
    }
    else if (type == "RoundRobin")
    {
        ui->tabs->setCurrentIndex(1);
        type = "RoundRobin";
        ui->Input->findChild<QLabel*>("Dep_Label")->setText("Q ");
    }
    else if(type == "SJF_Non" || type == "SJF_Prim")
    {
        ui->tabs->setCurrentIndex(1);
        ui->Input->findChild<QLabel*>("Dep_Label")->hide();
        ui->Input->findChild<QLineEdit*>("lineEdit_Dep")->hide();
    }
}
// Function to call the exact class based on the type
void MainWindow::on_pushButton_ToIndex_2_clicked()
{
    ui->tabs->setCurrentIndex(2);
    int size = process.size();

    if(type == "FCFS")
    {
        FCFS::find_total_average_time(process,ArrivalTime,BurstTime,size,WaitingTime,TurnAroundTime,AvgWaitingTime,AvgTurnAroundTime);
        FCFS::Gant_chart(process,ArrivalTime,BurstTime,size,StartingTime,Gap);
        Display();
    }
    else if(type == "PriorityNone" )
    {
        PriorityNone::sort_process_nonpre(process,BurstTime, ArrivalTime, Priority, size);
        PriorityNone::calc_waiting_starting_gap(BurstTime, ArrivalTime, StartingTime, WaitingTime, Gap, size);
        AvgWaitingTime = PriorityNone::waiting_avg(WaitingTime, size);
        AvgTurnAroundTime = PriorityNone::turnaround_avg(BurstTime, WaitingTime, size);
        Display();
    }
    else if (type == "SJF_Non")
    {
        SJF_NonPrim::sort_process_sjf_nonpre(process,BurstTime, ArrivalTime, size);
        PriorityNone::calc_waiting_starting_gap(BurstTime, ArrivalTime, StartingTime, WaitingTime, Gap, size);
        AvgWaitingTime = PriorityNone::waiting_avg(WaitingTime, size);
        AvgTurnAroundTime = PriorityNone::turnaround_avg(BurstTime, WaitingTime, size);
        Display();
    }
    else if (type == "RoundRobin")
    {
       Gap.resize(size);
       StartingTime.resize(size);
       int Original_Size = size;
       QVector<QString> Fixed_Process = process;

       Round_Robin::RR(process, ArrivalTime, BurstTime, StartingTime, Gap, size, Q);
       AvgWaitingTime = Round_Robin::AVG_waiting(ArrivalTime, StartingTime, size);
       AvgTurnAroundTime = Round_Robin::AVG_TurnAround(process, Fixed_Process, ArrivalTime, BurstTime, StartingTime, size, Original_Size);
       Display();
    }
    else if(type == "SJF_Prim")
    {
        QVector<SRTF_Process> sr;
        SRTF(process,BurstTime,ArrivalTime,StartingTime,sr);
        Gap = ArrivalTime;
        AvgTurnAroundTime = SRTF_Turn_Around(sr);
        AvgWaitingTime = SRTF_Waiting_time(sr);
        qDebug() << AvgWaitingTime;
        qDebug() << AvgTurnAroundTime;

        Display();
    }
    else if (type == "Priority_Prim")
    {
    }

}

void MainWindow::on_pushButton_Add_clicked()
{
    // Get Child Pointer  by the child id
    auto Name =  ui->Input->findChild<QLineEdit*>("line_Proc_Name");
    auto Arrival =  ui->Input->findChild<QLineEdit*>("lineArrTime");
    auto total =  ui->Input->findChild<QLineEdit*>("lineTotTime");
    // Optional will be Q or Priority
    auto var =  ui->Input->findChild<QLineEdit*>("lineEdit_Dep");

    QString msg = "You Added : " + Name->text() + "    \n" + "Arrival Time : " + Arrival->text() + "    \n" + "BurstTime : " + total->text();

    // Add Text Input to Vectors
    bool flag =  add_Input(Name->text(),Arrival->text(),total->text());
    //Add Optional Input
   if((type == "PriorityNone"|| type == "Priority_Prim" )&& flag)
   {
       foreach(QChar c ,var->text() )
       {
           if(!(c.isNumber()))
           {
               flag =false;
               break;
           }
       }
       if(flag)
       {
           Priority.push_back(var->text().toInt());
           msg += "\n Priority : "+ var->text();

       }
       else
       {
           // Remove the Name and time already added
           ArrivalTime.pop_back();
           process.pop_back();
           BurstTime.pop_back();
           msg = "You Entered A Wrone input For Priority Please Try Again";
           QMessageBox::warning(this,"Wronge Input",msg);
       }
   }
   else if (type == "RoundRobin" && flag)
   {
        if (var->text() != "")
        {
            foreach(QChar c ,var->text() )
            {
                if(!(c.isNumber()))
                {
                    flag =false;
                    break;
                }
            }
            if(flag)
            {
                Q= var->text().toInt();
                var->setEnabled(false);
            }
            else
            {
                QString msg2 = "You Entered A Wrone input For Q Please Try Again";
                QMessageBox::warning(this,"Wronge Input",msg2);
                flag = true;
            }
        }
   }
    // Confirm With a Msg
   if(flag)
   {
      QMessageBox::information(this,"Process Added",msg);
   }
   // Clear the LineEdit for a New Input
    Name->setText("");
    Arrival->setText("");
    total->setText("");
    if(type != "RoundRobin")
           var->setText("");
}



void MainWindow::on_FCFS_clicked()
{
    type="FCFS";
}

void MainWindow::on_RoundRobin_clicked()
{
    type="RoundRobin";
}

void MainWindow::on_PriorityNone_clicked()
{
    type = "PriorityNone";
}

void MainWindow::on_Priority_clicked()
{
   type= "Priority";
}

void MainWindow::on_SJF_Non_clicked()
{
    type = "SJF_Non";
}


void MainWindow::on_SJF_Prim_clicked()
{
    type = "SJF_Prim";
}


void MainWindow::on_Priority_Prim_clicked()
{
    type = "Priority_Prim";
}






// Discard this Functions just made to remove an error
void MainWindow::on_pushButton_clicked()
{

}
void MainWindow::on_pushButton_2_clicked()
{

}
void MainWindow::on_pushButton_3_clicked()
{

}
