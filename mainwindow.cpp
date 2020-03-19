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
            wid->setFixedWidth(Gap[i]*10);
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
            wid->setFixedWidth(BurstTime[i]*10);
            wid->setLayout(box);

           ui->GanttChartLayOut->setAlignment(Qt::AlignHCenter);
           ui->GanttChartLayOut->addWidget(wid,0);
           ui->label_FillTurnAround->setText(QString::number(AvgTurnAroundTime));
           ui->label_FillWaitingTime->setText(QString::number(AvgWaitingTime));

    }
}

void MainWindow::add_Input(QString proc, int Arr, int Burst)
{
    process.push_back(proc);
    ArrivalTime.push_back(Arr);
    BurstTime.push_back(Burst);
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
    else if (type == "Priority")
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
    else if(type == "SJF_Non")
    {
        ui->tabs->setCurrentIndex(1);
        ui->Input->findChild<QLabel*>("Dep_Label")->hide();
        ui->Input->findChild<QLineEdit*>("lineEdit_Dep")->hide();
    }
}


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
    else if(type == "PriorityNone")
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
    add_Input(Name->text(),Arrival->text().toInt(),total->text().toInt());
    //Add Optional Input
   if(type == "PriorityNone")
   {
       Priority.push_back(var->text().toInt());
       msg += "\n Priority : "+ var->text();
       qDebug() << var->text();
       var->setText("");
   }
    // Confirm With a Msg
    QMessageBox::information(this,"Process Added",msg);
    // Clear the LineEdit for a New Input
    Name->setText("");
    Arrival->setText("");
    total->setText("");
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
