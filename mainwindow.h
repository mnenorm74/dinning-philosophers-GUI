#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QObject>
#include <QMessageBox>
#include <QThread>
#include <QProcess>
#include <QTextStream>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QLabel *table;
    QLabel *firstPhilosoph;
    QLabel *secondPhilosoph;
    QLabel *thirdPhilosoph;
    QLabel *fourthPhilosoph;
    QLabel *fifthPhilosoph;
    QLabel *status;
    QPlainTextEdit *text;
    void RepaintPhilosopher(bool eat, QLabel *philosopher);
    void completeProgram();
    bool event(QEvent* event);
    void closeEvent(QCloseEvent *event);
    bool isActive;

private slots:
    void clickedStartSlot();
    void clickedFinishSlot();
};

