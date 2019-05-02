#ifndef MYEVENT_H
#define MYEVENT_H
#include <QString>
#include <QEvent>

class MyEvent : public QEvent
{
public:
    struct data
    {
       QString msg;
       bool eat;
       int id;
    };

    MyEvent(const QString& line, bool status, int philosopherID) : QEvent(QEvent::User)
    {
        _message = line;
        eat = status;
        id = philosopherID;
    }
    ~MyEvent() {} data message() const
    {
        //return _message;
        data state;
        state.id = id;
        state.eat = eat;
        state.msg = _message;
        return state;
    }
private:
    QString _message;
    bool eat;
    int id;
};

#endif // MYEVENT_H
