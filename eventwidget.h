#ifndef EVENTWIDGET_H
#define EVENTWIDGET_H

#include "data.h"
#include "event.h"
#include "eventcreator.h"
#include <QDate>
#include <QDialog>
#include <QLabel>
#include <QLocale>
#include <QPushButton>
#include <QScrollArea>
#include <QSpacerItem>
#include <QVBoxLayout>

class EventWidget : public QDialog {
  Q_OBJECT
public:
  EventWidget(Data *_data, Event _ev, QWidget *parent = nullptr);
  ~EventWidget();
signals:
  void removed();
  Event updated(Event ev);

private:
  Data *data = nullptr;
  Event event;
  QGridLayout *cl = nullptr;
  QWidget *le = nullptr;
  void openEE();
  void eeUpdated(Event ev);
  void updateEvents(Event ev);
  QDate getDateFromEvent(Event ev) {
    QDate date = QDate::currentDate();
    if (not event.cyclicByYear)
      date.setDate(ev.year, ev.month, ev.day);
    else
      date.setDate(date.year(), ev.month, ev.day);
    return date;
  }
};

#endif
