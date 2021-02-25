#include "sqlhandler.h"
#include <iostream>

SQLHandler::SQLHandler() {
  sql = QSqlDatabase::addDatabase("QSQLITE");
  sql.setDatabaseName("events.db");
}

bool SQLHandler::firstSetup() {
  sql.open();
  auto q = QSqlQuery(sql);
  for (quint8 i = 0; i < 12; i++)
    q.exec("CREATE TABLE " + months[i] +
           " (label TEXT, "
           "day INTEGER NOT NULL, "
           "year INTEGER NOT NULL, "
           "desc TEXT, "
           "cyclicByYear INTEGER, "
           "cyclicByMonth INTEGER, "
           "cathegory INTEGER, "
           "color INTEGER);");
  sql.close();
  return true;
}

QList<Event> SQLHandler::getEventsByDay(QDate date) {
  auto l = QList<Event>();
  sql.open();
  auto q = QSqlQuery(sql);
  q.exec("SELECT label, "
         "year, "
         "desc, "
         "cyclicByMonth, "
         "cyclicByYear, "
         "cathegory, "
         "color FROM " +
         months[date.month() - 1] +
         " WHERE day = " + QString::number(date.day()));
  while (q.next()) {
    Event ev;
    ev.name = q.value(0).toString();
    ev.month = date.month();
    ev.day = date.day();
    ev.year = q.value(1).toInt();
    ev.desc = q.value(2).toString();
    ev.cyclicByMonth = q.value(3).toInt();
    ev.cyclicByYear = q.value(4).toInt();
    if ((ev.year != date.year()) and (not ev.cyclicByYear))
      continue;
    ev.cathegory = q.value(5).toInt();
    ev.color = q.value(6).toInt();
    l.append(ev);
  }
  sql.close();
  return l;
}

bool SQLHandler::appendEvent(Event event) {
  sql.open();
  auto q = QSqlQuery(sql);
  if (event.cyclicByMonth)
    for (quint8 i = 0; i < 12; i++)
      q.exec("INSERT INTO " + months[i] + " VALUES (\"" + event.name + "\", " +
             QString::number(event.day) + ", " + QString::number(event.year) +
             ", \"" + event.desc + "\", " +
             QString::number(event.cyclicByYear) + ", " +
             QString::number(event.cyclicByMonth) + ", " +
             QString::number(event.cathegory) + ", " +
             QString::number(event.color) + ");");
  else
    q.exec("INSERT INTO " + months[event.month - 1] + " VALUES (\"" +
           event.name + "\", " + QString::number(event.day) + ", " +
           QString::number(event.year) + ", \"" + event.desc + "\", " +
           QString::number(event.cyclicByYear) + ", " +
           QString::number(event.cyclicByMonth) + ", " +
           QString::number(event.cathegory) + ", " +
           QString::number(event.color) + ");");
  sql.close();
  return q.lastError().isValid();
}

bool SQLHandler::editEvent(Event oe, Event ne) {
  removeEvent(oe);
  return appendEvent(ne);
}

bool SQLHandler::removeEvent(Event event) {
  sql.open();
  auto q = QSqlQuery(sql);
  if (event.cyclicByMonth)
    for (quint8 i = 0; i < 12; i++)
      q.exec("DELETE FROM " + months[i] + " WHERE label = \"" + event.name +
             "\" AND day = " + QString::number(event.day) +
             " AND year = " + QString::number(event.year) + ";");
  else
    q.exec("DELETE FROM " + months[event.month - 1] + " WHERE label = \"" +
           event.name + "\" AND day = " + QString::number(event.day) +
           " AND year = " + QString::number(event.year) + ";");
  sql.close();
  return q.lastError().isValid();
}
