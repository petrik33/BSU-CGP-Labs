#ifndef QTABLEWIDGETINTITEM_H
#define QTABLEWIDGETINTITEM_H
#include <QTableWidgetItem>

class QTableWidgetIntItem
    : public QTableWidgetItem
{
public:
    // with possible decorations
    //
    QTableWidgetIntItem(QString const & text)
        : QTableWidgetItem(text)
        , f_value(textToDouble(text))
    {
    }

    QTableWidgetIntItem(long n, QString const & text)
        : QTableWidgetItem(text)
        , f_value(n)
    {
    }

    QTableWidgetIntItem(double n, QString const & text)
        : QTableWidgetItem(text)
        , f_value(n)
    {
    }

    QTableWidgetIntItem(long n)
        : QTableWidgetItem(QString("%1").arg(n))
        , f_value(n)
    {
    }

    QTableWidgetIntItem(double n)
        : QTableWidgetItem(QString("%1").arg(n))
        , f_value(n)
    {
    }

    bool operator < (QTableWidgetItem const & rhs) const
    {
        QTableWidgetIntItem const * r(dynamic_cast<QTableWidgetIntItem const *>(&rhs));
        if(r == nullptr)
        {
            throw std::runtime_error("mixed QTableWidgetItem types is not supported by QTableWidgetIntItem.");
        }
        return f_value < r->f_value;
    }

    virtual double textToDouble(QString t)
    {
        // clean the beginning of the string of whatever
        // introducers
        //
        int const sp(t.indexOf(QRegExp("[0-9.]"), 0));
        if(sp > 0)
        {
            t = t.mid(sp);
        }

        // clean the end of the string of whatever postfix
        //
        int const ep(t.indexOf(QRegExp("[^0-9. ,]"), 0));
        if(ep > 0)
        {
            t = t.mid(ep);
        }

        // now remove commas and spaces
        //
        // note: replace() happens in place so we don't have to
        //       save the result in the variable itself
        //
        t.replace(QRegExp("[, ]+"), "");

        return t.toDouble();
    }

private:
    double  f_value = 0.0;
};

#endif // QTABLEWIDGETINTITEM_H
