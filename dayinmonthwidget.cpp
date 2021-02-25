#include "dayinmonthwidget.h"
#include <iostream>

DayInMonthWidget::DayInMonthWidget(Data *_d, QWidget *parent)
    : QWidget(parent) {
  data = _d;
  setAttribute(Qt::WA_StyledBackground);
  setObjectName("day");
  auto *lt = new QGridLayout();
  lt->setSpacing(0);
  lt->setContentsMargins(3, 3, 3, 3);
  setLayout(lt);
}

void DayInMonthWidget::setupData(QDate _date, int dayOfMonth) {
  date = _date;
  bool notThatMonth = false;
  if (dayOfMonth < 1) {
    notThatMonth = true;
    if (date.month() < 2)
      date.setDate(date.year() - 1, 12, 1);
    else
      date.setDate(date.year(), date.month() - 1, 1);
    dayOfMonth += date.daysInMonth();
  } else if (dayOfMonth > date.daysInMonth()) {
    notThatMonth = true;
    dayOfMonth -= date.daysInMonth();
    if (date.month() > 11)
      date.setDate(date.year() + 1, 1, 1);
    else
      date.setDate(date.year(), date.month() + 1, 1);
  }
  date.setDate(date.year(), date.month(), dayOfMonth);
  if (data->getCurrentDay() == dayOfMonth)
    setStyleSheet(
        "#day { " + border +
        " background-color: rgb(185, 185, 185); color: rgb(0, 0, 0); }");
  else
    setStyleSheet(
        "#day { " + border +
        " background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); }");
  if (notThatMonth) {
    setStyleSheet("#day { border: 1px solid grey; border-radius: 10px; "
                  "background-color: rgb(145, 145, 145); }");
    setDisabled(true);
  }
  events.append(data->sql->getEventsByDay(date));
}

void DayInMonthWidget::resizeEvent(QResizeEvent *event) {
  if (width() < 100) {
    if (dt != shortened)
      setupShortLayout();
  } else {
    if (dt != full)
      setupFullLayout();
  }
  QWidget::resizeEvent(event);
}

void DayInMonthWidget::redrawForce() {
  events.clear();
  events.append(data->sql->getEventsByDay(date));
  if (width() < 100)
    setupShortLayout();
  else
    setupFullLayout();
}

void DayInMonthWidget::setupShortLayout() {
  if (cw)
    delete cw;
  auto *lt = qobject_cast<QGridLayout *>(layout());
  cw = new QWidget();
  cw->setContentsMargins(0, 0, 0, 0);
  auto *cl = new QGridLayout();
  cl->setSpacing(0);
  cl->setContentsMargins(0, 0, 0, 0);
  auto *lbl = new QLabel(this);
  lbl->setStyleSheet(textColor);
  lbl->setObjectName("llt");
  lbl->setText(QLocale::system().toString(date, "d\nMMMM\nyyyy"));
  lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  cl->addWidget(lbl);
  cw->setLayout(cl);
  lt->addWidget(cw);
  dt = shortened;
}

void DayInMonthWidget::setupFullLayout() {
  if (events.length() == 0) {
    setupShortLayout();
    dt = full;
    return;
  }
  if (cw)
    delete cw;
  auto *lt = qobject_cast<QGridLayout *>(layout());
  cw = new QWidget();
  cw->setContentsMargins(0, 0, 0, 0);
  auto *cl = new QGridLayout();
  cl->setSpacing(0);
  cl->setContentsMargins(0, 0, 0, 0);
  auto *lbl = new QLabel(this);
  lbl->setStyleSheet(textColor);
  lbl->setObjectName("llt");
  lbl->setText(QLocale::system().toString(date, "d\nMMMM\nyyyy"));
  lbl->setMinimumWidth(
      QFontMetrics(lbl->font())
          .boundingRect(QLocale::system().toString(date, "MMMM"))
          .width());
  lbl->setMaximumWidth(50);
  lbl->setTextFormat(Qt::PlainText);
  lbl->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
  cl->addWidget(lbl, 0, 0);
  if (events.length() > 0) {
    auto *ew = new QWidget(this);
    auto *vbl = new QVBoxLayout();
    auto *en1 = new EventNote(data, events[0], this);
    connect(en1, &EventNote::callEventWidget, this,
            &DayInMonthWidget::openEventWidget);
    vbl->addItem(
        new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Preferred));
    vbl->addWidget(en1);
    if (events.length() > 1) {
      auto *en2 = new EventNote(data, events[1], this);
      connect(en2, &EventNote::callEventWidget, this,
              &DayInMonthWidget::openEventWidget);
      vbl->addWidget(en2);
    }
    if (events.length() > 2) {
      auto *plusLbl = new QLabel("+" + QString::number(events.length() - 2));
      plusLbl->setObjectName("llt");
      plusLbl->setStyleSheet(textColor);
      plusLbl->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
      plusLbl->setMaximumHeight(20);
      vbl->addWidget(plusLbl);
    }
    vbl->addItem(
        new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Preferred));
    ew->setLayout(vbl);
    cl->addWidget(ew, 0, 1);
  }
  cw->setLayout(cl);
  lt->addWidget(cw);
  dt = full;
}

void DayInMonthWidget::openEventWidget(Event ev) { emit callEventWidget(ev); }

void DayInMonthWidget::mouseReleaseEvent(QMouseEvent *event) {
  auto *dayDialog = new DayDialog(data, date, &events, this);
  connect(dayDialog, &DayDialog::updated, this, &DayInMonthWidget::redrawForce);
  dayDialog->show();
  QWidget::mouseReleaseEvent(event);
}
