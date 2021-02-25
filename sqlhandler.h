#ifndef SQLHANDLER_H
#define SQLHANDLER_H

#include <QDate>
#include <QList>
#include <QObject>
#include <QSqlDatabase>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include "event.h"

class SQLHandler {
public:
  SQLHandler();
  QList<Event> getEventsByDay(QDate date);
  bool appendEvent(Event event);
  bool editEvent(Event oe, Event ne);
  bool removeEvent(Event event);
  bool firstSetup();
private:
  QSqlDatabase sql;
  const QString months[12] = {"january", "february", "march", "april",
                              "may", "june", "july", "august",
                              "september", "october", "november", "december"};
};

#endif
