#include "eventcalendar.h"

EventCalendar::EventCalendar(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("Календарь Армии России, в/ч 26178");
  setWindowIcon(QIcon(":/arts/64/office-calendar.svg"));
  data = new Data();
  if (data->getSetting("ec-fs").toString() != "no") {
    data->setSetting("ws", QSize(640, 480));
    data->setSetting("ds", QSize(600, 400));
    data->setSetting("ec-fs", "no");
    data->sql->firstSetup();
  }
  resize(data->getSetting("ws").toSize());
  auto *wv = new WholeViewer(data, this);
  view = wv;
  setCentralWidget(wv);
  connect(wv, &WholeViewer::openCalendar, this,
          &EventCalendar::setMonthCalendar);
}

void EventCalendar::setMonthCalendar() {
  QDate date = data->getCurrentDate();
  auto *cw = new MonthViewer(data, date, this);
  setCentralWidget(cw);
  disconnect(view);
  if (view)
    delete view;
  view = cw;
  connect(cw, &MonthViewer::openWV, this, &EventCalendar::setWholeView);
  if (view)
    view->updateGeometry();
}

void EventCalendar::setWholeView() {
  auto *wv = new WholeViewer(data, this);
  setCentralWidget(wv);
  disconnect(view);
  if (view)
    delete view;
  view = wv;
  connect(wv, &WholeViewer::openCalendar, this,
          &EventCalendar::setMonthCalendar);
}

void EventCalendar::resizeEvent(QResizeEvent *event) {
  if (view)
    view->updateGeometry();
  QMainWindow::resizeEvent(event);
}

EventCalendar::~EventCalendar() {
  data->setSetting("ws", size());
  delete data;
}
