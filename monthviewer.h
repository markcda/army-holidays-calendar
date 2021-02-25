#ifndef MONTHVIEWER_H
#define MONTHVIEWER_H

#include "data.h"
#include "dayinmonthwidget.h"
#include <QFontMetrics>
#include <QToolButton>
#include <QList>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QWidget>

class MonthViewer : public QWidget {
  Q_OBJECT
public:
  MonthViewer(Data *_data, QDate _date, QWidget *parent = nullptr);
  ~MonthViewer();
  void resizeDays();

  Data *data = nullptr;
  QList<QWidget *> days;
signals:
  void openWV();
private:
  QWidget *gwo = nullptr;
  QVBoxLayout *clt = nullptr;
  QDate date;
  void openEW(Event ev);
  void redraw();
  virtual void resizeEvent(QResizeEvent *event);
  quint8 weeks = 0;
  void setupSizeOfDayWidget(QWidget *qw);
  void goBackAtMonth();
  void goNextMonth();
  void goBackAtYear();
  void goNextYear();
  void goCurrent();
};

#endif
