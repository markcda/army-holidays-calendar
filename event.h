#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDate>

struct Event {
  QString name;
  QString desc;
  int year;
  int month;
  int day;
  bool cyclicByYear;
  bool cyclicByMonth;
  int cathegory;
  int color;
};

#endif
