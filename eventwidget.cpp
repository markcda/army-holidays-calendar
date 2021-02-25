#include "eventwidget.h"
#include <iostream>

EventWidget::EventWidget(Data *_data, Event _ev, QWidget *parent)
    : QDialog(parent) {
  data = _data;
  event = _ev;
  setAttribute(Qt::WA_DeleteOnClose);
  resize(data->getSetting("ds").toSize());
  if (data->getSetting("dp-one").toString() == "no")
    move(data->getSetting("dp").toPoint());
  QDate date = getDateFromEvent(event);
  setWindowTitle(event.name + " - " +
                 QLocale::system().toString(date, "dd MMMM yyyy"));
  cl = new QGridLayout();
  updateEvents(event);
  setLayout(cl);
}

void EventWidget::openEE() {
  auto *ee = new EventCreator(data, event, this);
  connect(ee, &EventCreator::edited, this, &EventWidget::updateEvents);
  ee->show();
}

void EventWidget::updateEvents(Event ev) {
  event = ev;
  QDate date = getDateFromEvent(event);
  setWindowTitle(event.name + " - " +
                 QLocale::system().toString(date, "dd MMMM yyyy"));
  auto *len = new QWidget(this);
  len->setContentsMargins(0, 0, 0, 0);
  auto *llt = new QVBoxLayout();
  llt->setContentsMargins(0, 0, 0, 0);
  auto *eventNameLbl = new QLabel(event.name, this);
  QFont font;
  font.setBold(true);
  font.setPixelSize(20);
  eventNameLbl->setFont(font);
  eventNameLbl->setWordWrap(true);
  llt->addWidget(eventNameLbl);
  auto *si = new QScrollArea(this);
  si->setFrameShape(QFrame::NoFrame);
  auto *slt = new QVBoxLayout(this);
  auto *descLbl = new QLabel(event.desc, this);
  descLbl->setTextFormat(Qt::RichText);
  descLbl->setWordWrap(true);
  slt->addWidget(descLbl);
  slt->addItem(
      new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding));
  si->setLayout(slt);
  llt->addWidget(si);
  auto *editBtn = new QPushButton("Редактировать", this);
  editBtn->setIcon(QIcon(":/arts/16/edit.svg"));
  connect(editBtn, &QPushButton::clicked, this, &EventWidget::openEE);
  llt->addWidget(editBtn);
  auto *removeBtn = new QPushButton("Удалить", this);
  removeBtn->setIcon(QIcon(":/arts/16/edit-delete.svg"));
  connect(removeBtn, &QPushButton::clicked, this, [this]() {
    data->sql->removeEvent(event);
    emit removed();
    close();
  });
  llt->addWidget(removeBtn);
  len->setLayout(llt);
  if (le) {
    cl->replaceWidget(le, len);
    delete le;
    le = len;
  } else {
    cl->addWidget(len);
    le = len;
  }
  emit updated(event);
}

EventWidget::~EventWidget() {
  data->setSetting("ds", size());
  data->setSetting("dp-one", "no");
  data->setSetting("dp", pos());
}
