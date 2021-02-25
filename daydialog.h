#ifndef DAYDIALOG_H
#define DAYDIALOG_H

#include "data.h"
#include "event.h"
#include "eventnote.h"
#include <QDialog>
#include <QFont>
#include <QGridLayout>
#include <QLabel>
#include <QLocale>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QSpacerItem>

class DayDialog : public QDialog {
  Q_OBJECT
public:
  DayDialog(Data *_data, QDate _date, QList<Event> *_evs,
            QWidget *parent = nullptr);
  ~DayDialog();
signals:
  void updated();
  void callEventWidget();

private:
  Data *data = nullptr;
  void redraw();
  QGridLayout *salt = nullptr;
  QWidget *eso = nullptr;
  QDate date;
  void openEC();
  void openEW(Event ev);
  QList<Event> *events = nullptr;
  const QString eventsString[3] = {"событие", "события", "событий"};

  quint8 getIndex_es_byNum(int numberOfEvents);
};

#endif
