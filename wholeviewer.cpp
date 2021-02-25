#include "wholeviewer.h"

WholeViewer::WholeViewer(Data *_data, QWidget *parent) : QWidget(parent) {
  data = _data;
  clt = new QGridLayout();
  clt->setMargin(0);
  clt->setContentsMargins(0, 0, 0, 0);
  clt->setSpacing(0);
  updateEvents();
  setLayout(clt);
}

void WholeViewer::openEC() {
  auto *ec = new EventCreator(data, this);
  connect(ec, &EventCreator::closed, this, &WholeViewer::updateEvents);
  ec->show();
}

void WholeViewer::openEW(Event ev) {
  auto *ew = new EventWidget(data, ev, this);
  connect(ew, &EventWidget::updated, this, &WholeViewer::updateEvents);
  connect(ew, &EventWidget::removed, this, &WholeViewer::updateEvents);
  ew->show();
}

void WholeViewer::updateEvents() {
  auto *len = new QWidget(this);
  len->setContentsMargins(0, 0, 0, 0);
  auto *lelt = new QGridLayout();
  auto *sa = new QScrollArea(this);
  sa->setFrameShape(QFrame::NoFrame);
  auto *salt = new QVBoxLayout();
  QFont font;
  font.setPixelSize(16);
  font.setBold(true);
  auto *todayLbl =
      new QLabel("Сегодня, " + QLocale::system().toString(
                                   data->getCurrentDate(), "dd MMMM yyyy"),
                 this);
  todayLbl->setAlignment(Qt::AlignHCenter);
  todayLbl->setFont(font);
  salt->addWidget(todayLbl);
  QList<Event> today = data->sql->getEventsByDay(data->getCurrentDate());
  if (today.length()) {
    for (const auto &event : qAsConst(today)) {
      auto *en = new EventNote(data, event, this);
      connect(en, &EventNote::updated, this, &WholeViewer::updateEvents);
      connect(en, &EventNote::callEventWidget, this,
                    &WholeViewer::openEW);
      salt->addWidget(en);
    }
  } else {
    auto *todayThereIsNoEvents = new QLabel("На сегодня нет событий.", this);
    todayThereIsNoEvents->setAlignment(Qt::AlignHCenter);
    salt->addWidget(todayThereIsNoEvents);
  }
  auto *tomorrowLbl = new QLabel(
      "Завтра, " + QLocale::system().toString(data->getCurrentDate().addDays(1),
                                              "dd MMMM yyyy"),
      this);
  tomorrowLbl->setAlignment(Qt::AlignHCenter);
  tomorrowLbl->setFont(font);
  salt->addWidget(tomorrowLbl);
  QList<Event> tomorrow =
      data->sql->getEventsByDay(data->getCurrentDate().addDays(1));
  if (tomorrow.length()) {
    for (const auto &event : qAsConst(tomorrow)) {
      auto *en = new EventNote(data, event, this);
      connect(en, &EventNote::updated, this, &WholeViewer::updateEvents);
      connect(en, &EventNote::callEventWidget, this,
                    &WholeViewer::openEW);
      salt->addWidget(en);
    }
  } else {
    auto *tomThereIsNoEvents = new QLabel("На завтра нет событий.", this);
    tomThereIsNoEvents->setAlignment(Qt::AlignHCenter);
    salt->addWidget(tomThereIsNoEvents);
  }
  auto *spacer =
      new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
  salt->addItem(spacer);
  auto *openOthers = new QPushButton("Открыть календарь", this);
  openOthers->setIcon(QIcon(":/arts/16/view-calendar-month.svg"));
  connect(openOthers, &QPushButton::clicked, this,
          [this]() { emit openCalendar(); });
  salt->addWidget(openOthers);
  auto *addEvents = new QPushButton("Добавить событие", this);
  addEvents->setIcon(QIcon(":/arts/16/list-add.svg"));
  connect(addEvents, &QPushButton::clicked, this, &WholeViewer::openEC);
  salt->addWidget(addEvents);
  sa->setLayout(salt);
  lelt->addWidget(sa);
  len->setLayout(lelt);
  if (le) {
    clt->replaceWidget(le, len);
    delete le;
    le = len;
  } else {
    clt->addWidget(len);
    le = len;
  }
}
