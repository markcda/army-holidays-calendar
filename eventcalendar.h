#ifndef EVENTCALENDAR_H
#define EVENTCALENDAR_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QGridLayout>
#include "eventnote.h"
#include "monthviewer.h"
#include "wholeviewer.h"
#include "data.h"
#include "sqlhandler.h"

class EventCalendar : public QMainWindow {
  Q_OBJECT
public:
  EventCalendar(QWidget *parent = nullptr);
  ~EventCalendar();
private:
  QWidget *view = nullptr;
  void setMonthCalendar();
  void setWholeView();
  virtual void resizeEvent(QResizeEvent *event);
  Data *data = nullptr;
};

#endif
