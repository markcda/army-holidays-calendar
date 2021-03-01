#ifndef MONTHVIEWER_H
#define MONTHVIEWER_H

#include "data.h"
#include "dayinmonthwidget.h"
#include <QComboBox>
#include <QFontMetrics>
#include <QList>
#include <QResizeEvent>
#include <QSpinBox>
#include <QToolButton>
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
  QSpinBox *yearSpinBox = nullptr;
  QComboBox *monthComboBox = nullptr;
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
  void goMonth(int month);
  void goYear(int year);
  void updateHeader();
  const QStringList monthsInRus = {"1. Январь",   "2. Февраль", "3. Март",
                                   "4. Апрель",   "5. Май",     "6. Июнь",
                                   "7. Июль",     "8. Август",  "9. Сентябрь",
                                   "10. Октябрь", "11. Ноябрь", "12. Декабрь"};
};

#endif
