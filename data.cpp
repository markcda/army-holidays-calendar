#include "data.h"

Data::Data() {
  st = new QSettings(QSettings::IniFormat, QSettings::UserScope, "CCLC", "ArmyCalendar");
  sql = new SQLHandler();
}

Data::~Data() {
  delete st;
  delete sql;
}

QDate Data::getCurrentDate() {
  return QDate::currentDate();
}

quint8 Data::getCurrentDay() {
  return QDate::currentDate().day();
}

quint8 Data::getCurrentMonth() {
  return QDate::currentDate().month();
}

quint8 Data::getCurrentYear() {
  return QDate::currentDate().year();
}

quint8 Data::getDayOfWeek(QDate date) {
  return date.dayOfWeek();
}

quint8 Data::getWeeksInMonth(QDate date) {
  date.setDate(date.year(), date.month(), 1);
  quint8 dim = date.daysInMonth();
  quint8 wim = dim / 7;
  if (dim % 7 > 0) wim += 1;
  if ((dim % 7 + date.dayOfWeek() > 8) or ((dim == 28) and (date.dayOfWeek() != 1))) wim += 1;
  return wim;
}

quint8 Data::firstDayOfMonth(QDate date) {
  date.setDate(date.year(), date.month(), 1);
  return date.dayOfWeek();
}

quint8 Data::daysInMonth(QDate date) {
  date.setDate(date.year(), date.month(), 1);
  return date.daysInMonth();
}

QVariant Data::getSetting(QString key) {
  return st->value(key);
}

void Data::setSetting(QString key, QVariant value) {
  st->setValue(key, value);
}
