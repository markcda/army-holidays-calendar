#include "daydialog.h"

DayDialog::DayDialog(Data *_data, QDate _date, QList<Event> *_evs,
                     QWidget *parent)
    : QDialog(parent) {
  setAttribute(Qt::WA_DeleteOnClose);
  data = _data;
  date = _date;
  events = _evs;
  setWindowTitle(QLocale::system().toString(date, "dd MMMM yyyy"));
  resize(data->getSetting("ds").toSize());
  if (data->getSetting("dp-one").toString() == "no")
    move(data->getSetting("dp").toPoint());
  auto *clt = new QGridLayout();
  clt->setMargin(0);
  clt->setContentsMargins(0, 0, 0, 0);
  clt->setSpacing(0);
  auto *sa = new QScrollArea(this);
  sa->setFrameShape(QFrame::NoFrame);
  salt = new QGridLayout();
  redraw();
  sa->setLayout(salt);
  clt->addWidget(sa);
  setLayout(clt);
}

void DayDialog::redraw() {
  auto *es = new QWidget(this);
  es->setContentsMargins(0, 0, 0, 0);
  auto *eslt = new QVBoxLayout();
  QFont font;
  font.setPixelSize(16);
  font.setBold(true);
  auto *todayLbl =
      new QLabel(QString::number(events->length()) + " " +
                     eventsString[getIndex_es_byNum(events->length())],
                 this);
  todayLbl->setAlignment(Qt::AlignHCenter);
  todayLbl->setFont(font);
  eslt->addWidget(todayLbl);
  QList<Event> today = data->sql->getEventsByDay(date);
  if (today.length()) {
    for (const auto &event : qAsConst(today)) {
      auto *en = new EventNote(data, event, this);
      connect(en, &EventNote::callEventWidget, this, [this, event]() { openEW(event); });
      eslt->addWidget(en);
    }
  } else {
    auto *todayThereIsNoEvents = new QLabel("На сегодня нет событий.", this);
    todayThereIsNoEvents->setAlignment(Qt::AlignHCenter);
    eslt->addWidget(todayThereIsNoEvents);
  }
  eslt->addItem(
      new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
  auto *addEvents = new QPushButton("Добавить событие", this);
  addEvents->setIcon(QIcon(":/arts/16/list-add.svg"));
  connect(addEvents, &QPushButton::clicked, this, &DayDialog::openEC);
  eslt->addWidget(addEvents);
  es->setLayout(eslt);
  if (eso) {
    salt->replaceWidget(eso, es);
    delete eso;
  } else
    salt->addWidget(es);
  eso = es;
}

void DayDialog::openEC() {
  auto *ec = new EventCreator(data, this);
  connect(ec, &EventCreator::closed, this, [this]() { emit updated(); redraw(); });
  ec->show();
}

void DayDialog::openEW(Event ev) {
  auto *ew = new EventWidget(data, ev, this);
  connect(ew, &EventWidget::updated, this, [this]() { emit updated(); redraw(); });
  connect(ew, &EventWidget::removed, this, [this]() { emit updated(); redraw(); });
  ew->show();
}

DayDialog::~DayDialog() {
  data->setSetting("ds", size());
  data->setSetting("dp", pos());
  data->setSetting("dp-one", "no");
}

quint8 DayDialog::getIndex_es_byNum(int numberOfEvents) {
  int NOE_mod = numberOfEvents % 100;
  if ((NOE_mod >= 10) and (NOE_mod <= 20))
    return 2;
  else if (NOE_mod % 10 == 1)
    return 0;
  else if ((NOE_mod % 10 == 2) or (NOE_mod % 10 == 3) or (NOE_mod % 10 == 4))
    return 1;
  else
    return 2;
}
