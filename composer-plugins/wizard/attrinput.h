#ifndef ATTRINPUT_H
#define ATTRINPUT_H

#include <QWidget>

class AttrInput : public QWidget
{
    Q_OBJECT

protected:
    QString _name;
    QString _type;
    QString _value;
    QString _question;


public:
    explicit AttrInput (QWidget *parent = 0) : QWidget (parent) {}

    explicit AttrInput(QString question, QString name, QString type, QString value, QWidget *parent = 0);

    inline QString name () const { return _name; }
    inline QString type () const { return _type; }
    inline QString value () const { return _value; }
    inline QString question () const { return _question; }

    virtual QString answer () const = 0;
    virtual void setAnswer (QString) = 0;
    virtual AttrInput * clone () const = 0;
//    virtual void computeAnswer () = 0;
};

#endif // ATTRINPUT_H