#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QDate>
#include <QSettings>
#include "sqlhandler.h"

class Data {
public:
  Data();
  ~Data();
  QDate getCurrentDate();
  quint8 getCurrentDay();
  quint8 getCurrentMonth();
  quint8 getCurrentYear();
  quint8 getWeeksInMonth(QDate date);
  quint8 getDayOfWeek(QDate date);
  quint8 firstDayOfMonth(QDate date);
  quint8 daysInMonth(QDate date);
  QSettings *st = nullptr;
  SQLHandler *sql = nullptr;
  QVariant getSetting(QString key);
  void setSetting(QString key, QVariant value);
};

#endif
