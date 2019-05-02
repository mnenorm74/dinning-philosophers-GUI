#include "mainwindow.h"
#include "myevent.h"
#include <QCoreApplication>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <conio.h>
#include <sstream>
using namespace std;


bool work;
const int philosophersCount = 5;
thread philosophers[philosophersCount];
bool isFreeForks[] = { true, true, true, true, true };
mutex mtx;

struct Data
{
    int id;
    MainWindow *w;
};

int GetNumberLeftFork(int number)
{
    return number == 0 ? philosophersCount - 1 : number - 1;
}


void Eat(Data data)
{
    while(work)
    {
        int leftFork = GetNumberLeftFork(data.id);
        unique_lock<mutex> ul(mtx);

        if (isFreeForks[leftFork] == true && isFreeForks[data.id] == true)
        {
            isFreeForks[leftFork] = isFreeForks[data.id] = false;

            stringstream ss;
            ss << this_thread::get_id();
            QString threadID = QString::fromUtf8((ss.str()).c_str());
            QString philosopherID = QString::number(data.id);

            QString message;
            message
                .append("Philosoper ")
                .append(philosopherID)
                .append(" EATS! Thread: ")
                .append(threadID);
            MyEvent* myEvent = new MyEvent(message, true, data.id);
            QCoreApplication::postEvent(data.w, myEvent);

            cout <<"Philosopher "<< data.id << " EATS! " << "Thread: " << this_thread::get_id() << endl;
            ul.unlock();

            this_thread::sleep_for(chrono::milliseconds(rand() % 4001 + 1000));		// ест

            ul.lock();
            isFreeForks[leftFork] = isFreeForks[data.id] = true;
            message.clear();
            message
                .append("Philosoper ")
                .append(philosopherID)
                .append(" thinks! Thread: ")
                .append(threadID);
            myEvent = new MyEvent(message, false, data.id);
            QCoreApplication::postEvent(data.w, myEvent);

            cout << "Philosopher " << data.id << " thinks! " << "Thread: " << this_thread::get_id() << endl;
            ul.unlock();

            this_thread::sleep_for(chrono::milliseconds(rand() % 3001 + 1000));			//думает
        }
    }
}

void Start(MainWindow *window)
{
    srand(time(NULL));
    work = true;

    for (int i = 0; i < philosophersCount; i++)
    {
        auto data = Data();
        data.w = window;
        data.id = i;
        philosophers[i] = thread(Eat, data);
    }
}

void Finish()
{
    work = false;
    for (int i = 0; i < philosophersCount; i++)
    {
        philosophers[i].join();
    }
}
