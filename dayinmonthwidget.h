#ifndef DAYINMONTHWIDGET_H
#define DAYINMONTHWIDGET_H

#include <QList>
#include <QLayout>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include "data.h"
#include "event.h"
#include "eventnote.h"
#include "daydialog.h"

enum dim_type {
  shortened,
  full,
  no
};

class DayInMonthWidget : public QWidget {
  Q_OBJECT
public:
  DayInMonthWidget(Data *_d, QWidget *parent = nullptr);
  void setupData(QDate _date, int dayOfMonth);
signals:
  Event callEventWidget(Event ev);
private:
  virtual void resizeEvent(QResizeEvent *event);
  void setupShortLayout();
  void setupFullLayout();
  virtual void mouseReleaseEvent(QMouseEvent *event);
  void eventWidgetClosed();
  void openEventWidget(Event ev);
  void redrawForce();

  QList<Event> events;
  Data *data = nullptr;
  QDate date;
  dim_type dt = no;
  QWidget *cw = nullptr;
  const QString border = "border: 1px solid black; border-radius: 5px;";
  const QString textColor = "#llt {color: rgb(0, 0, 0);}";
};

#endif
