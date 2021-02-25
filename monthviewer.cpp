#include "monthviewer.h"

MonthViewer::MonthViewer(Data *_data, QDate _date, QWidget *parent)
    : QWidget(parent) {
  date = _date;
  data = _data;
  clt = new QVBoxLayout();
  clt->setContentsMargins(0, 9, 0, 0);
  clt->setSpacing(0);
  QFont font;
  font.setPixelSize(18);
  font.setBold(true);
  auto *hw = new QWidget(this);
  hw->setContentsMargins(0, 0, 0, 0);
  auto *headLt = new QHBoxLayout();
  auto *backBtn = new QToolButton(this);
  backBtn->setIcon(QIcon(":/arts/16/view-calendar-upcoming-days.svg"));
  backBtn->setFocusPolicy(Qt::NoFocus);
  connect(backBtn, &QToolButton::clicked, this, [this]() { emit openWV(); });
  headLt->addWidget(backBtn);
  auto *titleLbl =
      new QLabel("Календарь воинских событий войсковой части 26178", this);
  titleLbl->setFont(font);
  titleLbl->setIndent(9);
  titleLbl->setMaximumHeight(
      QFontMetrics(titleLbl->font())
          .boundingRect("Календарь событий в войсковой части 26178")
          .height() -
      1);
  headLt->addWidget(titleLbl);
  auto *backAtYear = new QToolButton(this);
  backAtYear->setFocusPolicy(Qt::NoFocus);
  backAtYear->setText("<<");
  connect(backAtYear, &QToolButton::clicked, this, &MonthViewer::goBackAtYear);
  headLt->addWidget(backAtYear);
  auto *backAtMonth = new QToolButton(this);
  backAtMonth->setFocusPolicy(Qt::NoFocus);
  backAtMonth->setText("<");
  connect(backAtMonth, &QToolButton::clicked, this, &MonthViewer::goBackAtMonth);
  headLt->addWidget(backAtMonth);
  auto *cur = new QToolButton(this);
  cur->setFocusPolicy(Qt::NoFocus);
  cur->setIcon(QIcon(":/arts/16/calendar-go-today.svg"));
  connect(cur, &QToolButton::clicked, this, &MonthViewer::goCurrent);
  headLt->addWidget(cur);
  auto *nextMonth = new QToolButton(this);
  nextMonth->setFocusPolicy(Qt::NoFocus);
  nextMonth->setText(">");
  connect(nextMonth, &QToolButton::clicked, this, &MonthViewer::goNextMonth);
  headLt->addWidget(nextMonth);
  auto *nextYear = new QToolButton(this);
  nextYear->setFocusPolicy(Qt::NoFocus);
  nextYear->setText(">>");
  connect(nextYear, &QToolButton::clicked, this, &MonthViewer::goNextYear);
  headLt->addWidget(nextYear);
  hw->setLayout(headLt);
  hw->setMaximumHeight(32);
  clt->addWidget(hw);
  redraw();
  setLayout(clt);
}

void MonthViewer::redraw() {
  days.clear();
  auto *gw = new QWidget(this);
  gw->setContentsMargins(0, 0, 0, 0);
  auto *glt = new QGridLayout();
  glt->setSpacing(1);
  weeks = data->getWeeksInMonth(date);
  for (int i = 1; i <= weeks; i++) {
    for (int j = 1; j <= 7; j++) {
      auto *w = new DayInMonthWidget(data, this);
      connect(w, &DayInMonthWidget::callEventWidget, this,
              &MonthViewer::openEW);
      days.append(w);
      int dayNumber =
          (i - 1) * 7 - data->firstDayOfMonth(date) + j + 1;
      QDate dayDate = date;
      dayDate.setDate(dayDate.year(), dayDate.month(), 1);
      w->setupData(dayDate, dayNumber);
      setupSizeOfDayWidget(w);
      glt->addWidget(w, i - 1, j - 1);
    }
  }
  gw->setLayout(glt);
  if (gwo) {
    clt->replaceWidget(gwo, gw);
    delete gwo;
  } else
    clt->addWidget(gw);
  gwo = gw;
}

void MonthViewer::openEW(Event ev) {
  auto *ew = new EventWidget(data, ev, this);
  connect(ew, &EventWidget::updated, this, &MonthViewer::redraw);
  connect(ew, &EventWidget::removed, this, &MonthViewer::redraw);
  ew->show();
}

MonthViewer::~MonthViewer() { days.clear(); }

void MonthViewer::resizeDays() {
  for (int i = 0; i < days.length(); i++)
    setupSizeOfDayWidget(days[i]);
}

void MonthViewer::resizeEvent(QResizeEvent *event) {
  resizeDays();
  QWidget::resizeEvent(event);
}

void MonthViewer::setupSizeOfDayWidget(QWidget *qw) {
  if (not qw)
    return;
  qw->setMaximumWidth(width() / 7);
  qw->setMaximumHeight(height() / weeks);
}

void MonthViewer::goBackAtMonth() {
  date = date.addMonths(-1);
  redraw();
}

void MonthViewer::goBackAtYear() {
  date = date.addYears(-1);
  redraw();
}

void MonthViewer::goNextMonth() {
  date = date.addMonths(1);
  redraw();
}

void MonthViewer::goNextYear() {
  date = date.addYears(1);
  redraw();
}

void MonthViewer::goCurrent() {
  date = QDate::currentDate();
  redraw();
}
