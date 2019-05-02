#include "philo.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *w1 = new QWidget();
    setCentralWidget(w1);
    isActive = false;

    text = new QPlainTextEdit();
    table = new QLabel();
    table->setPixmap(QPixmap("C:\\GitHub\\dinning-philosophers-GUI\\0.png").scaled(200, 200, Qt::KeepAspectRatio));
    firstPhilosoph =  new QLabel();
    firstPhilosoph->setPixmap(QPixmap("C:\\GitHub\\dinning-philosophers-GUI\\2.png").scaled(100, 100, Qt::KeepAspectRatio));
    secondPhilosoph =  new QLabel();
    secondPhilosoph->setPixmap(QPixmap("C:\\GitHub\\dinning-philosophers-GUI\\3.png").scaled(100, 100, Qt::KeepAspectRatio));
    thirdPhilosoph =  new QLabel();
    thirdPhilosoph->setPixmap(QPixmap("C:\\GitHub\\dinning-philosophers-GUI\\4.png").scaled(100, 100, Qt::KeepAspectRatio));
    fourthPhilosoph =  new QLabel();
    fourthPhilosoph->setPixmap(QPixmap("C:\\GitHub\\dinning-philosophers-GUI\\5.png").scaled(100, 100, Qt::KeepAspectRatio));
    fifthPhilosoph =  new QLabel();
    fifthPhilosoph->setPixmap(QPixmap("C:\\GitHub\\dinning-philosophers-GUI\\6.png").scaled(100, 100, Qt::KeepAspectRatio));
    text->setReadOnly(true);

    QPushButton *startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()), this, SLOT(clickedStartSlot()));
    QPushButton *finishButton = new QPushButton("Finish");
    connect(finishButton, SIGNAL(clicked()), this, SLOT(clickedFinishSlot()));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(table, 1, 1, 1, 2, Qt::AlignCenter);
    layout->addWidget(firstPhilosoph, 1,0, Qt::AlignCenter);
    layout->addWidget(secondPhilosoph, 0,1, 1, 2, Qt::AlignCenter);
    layout->addWidget(thirdPhilosoph, 1,3, Qt::AlignCenter);
    layout->addWidget(fourthPhilosoph, 2,2, Qt::AlignCenter);
    layout->addWidget(fifthPhilosoph, 2,1, Qt::AlignCenter);
    layout->addWidget(startButton, 0, 3, Qt::AlignCenter);
    layout->addWidget(finishButton, 2, 3, Qt::AlignCenter);
    layout->addWidget(text, 0, 4, 3, 2);

    w1 -> setLayout(layout);
    w1 ->show();
}


void MainWindow::clickedStartSlot()
{
    if (!isActive)
    {
        Start(this);
        isActive = true;
    }
}

void MainWindow::clickedFinishSlot()
{
    completeProgram();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    completeProgram();
    event->accept();
}

void MainWindow::completeProgram()
{
    if (isActive)
    {
        Finish();
        table->setStyleSheet("background-color: red");
        table->repaint();
        isActive = false;
    }
}

bool MainWindow::event(QEvent* event)
{
    if (event->type() == QEvent::User)
    {
        MyEvent* postedEvent = static_cast<MyEvent*>(event);
        text->appendPlainText(postedEvent->message().msg);

        if (postedEvent->message().id == 0)
        {
            RepaintPhilosopher(postedEvent->message().eat, firstPhilosoph);
        }
        if (postedEvent->message().id == 1)
        {
            RepaintPhilosopher(postedEvent->message().eat, secondPhilosoph);
        }
        if (postedEvent->message().id == 2)
        {
            RepaintPhilosopher(postedEvent->message().eat, thirdPhilosoph);
        }
        if (postedEvent->message().id == 3)
        {
            RepaintPhilosopher(postedEvent->message().eat, fourthPhilosoph);
        }
        if (postedEvent->message().id == 4)
        {
            RepaintPhilosopher(postedEvent->message().eat, fifthPhilosoph);
        }
    }
    return QWidget::event(event);
}

void MainWindow::RepaintPhilosopher(bool eat, QLabel *philosopher)
{
    if (eat)
    {
       philosopher->setStyleSheet("background-color: green");
    }
    else
    {
       philosopher->setStyleSheet("background-color: yellow");
    }
    philosopher->repaint();
}

