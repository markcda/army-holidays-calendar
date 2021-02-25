#include "eventcreator.h"
#include <iostream>

EventCreator::EventCreator(Data *_data, QWidget *parent) : QDialog(parent) {
  data = _data;
  setWindowTitle("Добавление события");
  vclt = new QVBoxLayout();
  auto *evLbl = new QLabel("Добавить событие");
  QFont font;
  font.setPixelSize(16);
  font.setBold(true);
  evLbl->setFont(font);
  vclt->addWidget(evLbl);
  // 1
  auto *typeWidget = new QWidget(this);
  auto *typeLt = getHLt();
  auto *typeLbl = new QLabel("Тип события: ", this);
  cb = new TypeBox(this);
  typeLt->addWidget(typeLbl);
  typeLt->addWidget(cb);
  typeLt->addItem(getHSp());
  typeWidget->setLayout(typeLt);
  vclt->addWidget(typeWidget);
  // 2
  auto *dateWidget = new QWidget(this);
  auto *dateLt = getHLt();
  auto *yearLbl = new QLabel("Год: ");
  yearSpinBox = new QSpinBox(this);
  yearSpinBox->setMinimum(0);
  yearSpinBox->setMaximum(2030);
  yearSpinBox->setValue(2000);
  auto *monthLbl = new QLabel(" Месяц: ");
  monthComboBox = new QComboBox(this);
  monthComboBox->addItems(monthsInRus);
  auto *dayLbl = new QLabel(" День: ", this);
  daySpinBox = new QSpinBox(this);
  daySpinBox->setMinimum(1);
  daySpinBox->setMaximum(31);
  dateLt->addWidget(yearLbl);
  dateLt->addWidget(yearSpinBox);
  dateLt->addWidget(monthLbl);
  dateLt->addWidget(monthComboBox);
  dateLt->addWidget(dayLbl);
  dateLt->addWidget(daySpinBox);
  dateWidget->setLayout(dateLt);
  vclt->addWidget(dateWidget);
  // 3
  auto *repeatingWidget = new QWidget(this);
  auto *repeatingLt = getVLt();
  everyMonth = new QCheckBox("повторяется каждый месяц этого года", this);
  everyYear = new QCheckBox("повторяется каждый год", this);
  everyMonth->setChecked(false);
  everyYear->setChecked(true);
  everyMonth->setDisabled(true);
  everyYear->setDisabled(true);
  repeatingLt->addWidget(everyMonth);
  repeatingLt->addWidget(everyYear);
  repeatingWidget->setLayout(repeatingLt);
  vclt->addWidget(repeatingWidget);
  // 5
  auto *titleWidget = new QWidget(this);
  auto *titleLt = getHLt();
  auto *titleLbl = new QLabel("Название события: ");
  titleLineEdit = new QLineEdit("День рождения ", this);
  titleLt->addWidget(titleLbl);
  titleLt->addWidget(titleLineEdit);
  titleLt->addItem(getHSp());
  titleWidget->setLayout(titleLt);
  vclt->addWidget(titleWidget);
  // 6
  auto *colorWidget = new QWidget(this);
  auto *colorLt = getHLt();
  auto *colorLbl = new QLabel("Цвет события в календаре: ");
  colorComboBox = new QComboBox(this);
  colorComboBox->addItems(colors);
  colorLt->addWidget(colorLbl);
  colorLt->addWidget(colorComboBox);
  colorLt->addItem(getHSp());
  colorWidget->setLayout(colorLt);
  vclt->addWidget(colorWidget);
  // 7
  auto *descWidget = new QWidget(this);
  auto *descLt = getVLt();
  auto *descLbl = new QLabel("Описание события: ");
  descTextEdit = new QTextEdit(this);
  descTextEdit->setTabChangesFocus(true);
  descLt->addWidget(descLbl);
  descLt->addWidget(descTextEdit);
  descWidget->setLayout(descLt);
  vclt->addWidget(descWidget);
  // 7.5
  additionalOptions = new QWidget(this);
  vclt->addWidget(additionalOptions);
  // 8
  auto *addPushButton = new QPushButton("Добавить", this);
  vclt->addWidget(addPushButton);
  // last
  setLayout(vclt);
  setupContacts();
  // Соединения
  connect(cb, &TypeBox::changed, this, &EventCreator::eventTypeChanged);
  connect(addPushButton, &QPushButton::pressed, this, &EventCreator::saveEvent);
}

EventCreator::EventCreator(Data *_data, Event _editing, QWidget *parent)
    : QDialog(parent) {
  data = _data;
  edit = true;
  editing = _editing;
  setWindowTitle("Редактирование события");
  vclt = new QVBoxLayout();
  auto *evLbl = new QLabel("Изменить событие");
  QFont font;
  font.setPixelSize(16);
  font.setBold(true);
  evLbl->setFont(font);
  vclt->addWidget(evLbl);
  // 1
  auto *typeWidget = new QWidget(this);
  auto *typeLt = getHLt();
  auto *typeLbl = new QLabel("Тип события: ", this);
  cb = new TypeBox(this);
  cb->setCurrentIndex(editing.cathegory);
  typeLt->addWidget(typeLbl);
  typeLt->addWidget(cb);
  typeLt->addItem(getHSp());
  typeWidget->setLayout(typeLt);
  vclt->addWidget(typeWidget);
  // 2
  auto *dateWidget = new QWidget(this);
  auto *dateLt = getHLt();
  auto *yearLbl = new QLabel("Год: ");
  yearSpinBox = new QSpinBox(this);
  yearSpinBox->setMinimum(0);
  yearSpinBox->setMaximum(2030);
  yearSpinBox->setValue(editing.year);
  auto *monthLbl = new QLabel(" Месяц: ");
  monthComboBox = new QComboBox(this);
  monthComboBox->addItems(monthsInRus);
  monthComboBox->setCurrentIndex(editing.month - 1);
  auto *dayLbl = new QLabel(" День: ", this);
  daySpinBox = new QSpinBox(this);
  daySpinBox->setMinimum(1);
  daySpinBox->setMaximum(31);
  daySpinBox->setValue(editing.day);
  dateLt->addWidget(yearLbl);
  dateLt->addWidget(yearSpinBox);
  dateLt->addWidget(monthLbl);
  dateLt->addWidget(monthComboBox);
  dateLt->addWidget(dayLbl);
  dateLt->addWidget(daySpinBox);
  dateWidget->setLayout(dateLt);
  vclt->addWidget(dateWidget);
  // 3
  auto *repeatingWidget = new QWidget(this);
  auto *repeatingLt = getVLt();
  everyMonth = new QCheckBox("повторяется каждый месяц этого года", this);
  everyYear = new QCheckBox("повторяется каждый год", this);
  everyMonth->setChecked(editing.cyclicByMonth);
  everyYear->setChecked(editing.cyclicByYear);
  repeatingLt->addWidget(everyMonth);
  repeatingLt->addWidget(everyYear);
  repeatingWidget->setLayout(repeatingLt);
  vclt->addWidget(repeatingWidget);
  // 5
  auto *titleWidget = new QWidget(this);
  auto *titleLt = getHLt();
  auto *titleLbl = new QLabel("Название события: ");
  titleLineEdit = new QLineEdit(editing.name, this);
  titleLt->addWidget(titleLbl);
  titleLt->addWidget(titleLineEdit);
  titleLt->addItem(getHSp());
  titleWidget->setLayout(titleLt);
  vclt->addWidget(titleWidget);
  // 6
  auto *colorWidget = new QWidget(this);
  auto *colorLt = getHLt();
  auto *colorLbl = new QLabel("Цвет события в календаре: ");
  colorComboBox = new QComboBox(this);
  colorComboBox->addItems(colors);
  colorComboBox->setCurrentIndex(editing.color);
  colorLt->addWidget(colorLbl);
  colorLt->addWidget(colorComboBox);
  colorLt->addItem(getHSp());
  colorWidget->setLayout(colorLt);
  vclt->addWidget(colorWidget);
  // 7
  auto *descWidget = new QWidget(this);
  auto *descLt = getVLt();
  auto *descLbl = new QLabel("Описание события: ");
  descTextEdit = new QTextEdit(editing.desc, this);
  descTextEdit->setTabChangesFocus(true);
  descLt->addWidget(descLbl);
  descLt->addWidget(descTextEdit);
  descWidget->setLayout(descLt);
  vclt->addWidget(descWidget);
  // 7.5
  additionalOptions = new QWidget(this);
  vclt->addWidget(additionalOptions);
  // 8
  auto *addPushButton = new QPushButton("Сохранить", this);
  vclt->addWidget(addPushButton);
  // last
  setLayout(vclt);
  if (cb->currentIndex() == 0)
    setupContacts();
  // Соединения
  connect(cb, &TypeBox::changed, this, &EventCreator::eventTypeChanged);
  connect(addPushButton, &QPushButton::pressed, this, &EventCreator::saveEvent);
}

QHBoxLayout *EventCreator::getHLt() {
  auto *lt = new QHBoxLayout();
  lt->setContentsMargins(0, 0, 0, 0);
  lt->setSpacing(1);
  return lt;
}

QVBoxLayout *EventCreator::getVLt() {
  auto *lt = new QVBoxLayout();
  lt->setContentsMargins(0, 0, 0, 0);
  lt->setSpacing(1);
  return lt;
}

QSpacerItem *EventCreator::getHSp() {
  return new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void EventCreator::eventTypeChanged() {
  if (cb->currentIndex() == 0) {
    everyMonth->setChecked(false);
    everyYear->setChecked(true);
    everyMonth->setDisabled(true);
    everyYear->setDisabled(true);
    if (titleLineEdit->text().indexOf("День рождения ") == -1)
      titleLineEdit->setText("День рождения " + titleLineEdit->text());
    setupContacts();
  } else if (cb->currentIndex() == 1) {
    everyMonth->setChecked(false);
    everyYear->setChecked(true);
    everyMonth->setDisabled(true);
    everyYear->setDisabled(true);
    if (titleLineEdit->text() == "День рождения ")
      titleLineEdit->clear();
    setupPlain();
  } else if (cb->currentIndex() == 2) {
    everyMonth->setChecked(false);
    everyYear->setChecked(false);
    everyMonth->setDisabled(false);
    everyYear->setDisabled(false);
    if (titleLineEdit->text() == "День рождения ")
      titleLineEdit->clear();
    setupPlain();
  }
}

void EventCreator::setupPlain() {
  auto *ao = new QWidget(this);
  vclt->replaceWidget(additionalOptions, ao);
  delete additionalOptions;
  additionalOptions = ao;
}

void EventCreator::setupContacts() {
  auto *ao = new QWidget(this);
  auto *aoLt = getVLt();
  auto *cLbl = new QLabel("Контакты военнослужащего:", this);
  auto *contactsTextEdit = new QTextEdit(this);
  if (edit) {
    QString text = editing.desc;
    contactsTextEdit->setText(ejectCs(text));
    descTextEdit->setText(ejectDesc(text));
    setWindowTitle(ejectDesc(text));
  }
  contactsTextEdit->setObjectName("contacts");
  aoLt->addWidget(cLbl);
  aoLt->addWidget(contactsTextEdit);
  ao->setLayout(aoLt);
  vclt->replaceWidget(additionalOptions, ao);
  delete additionalOptions;
  additionalOptions = ao;
}

void EventCreator::saveEvent() {
  Event event;
  event.name = titleLineEdit->text();
  titleLineEdit->clear();
  event.desc = descTextEdit->toPlainText();
  descTextEdit->clear();
  event.cathegory = cb->currentIndex();
  if (cb->currentIndex() == 0) {
    auto *contacts = additionalOptions->findChild<QTextEdit *>("contacts");
    event.desc +=
        "<br><p><b>Контакты:<br>" + contacts->toPlainText() + "</b></p>";
    contacts->clear();
    titleLineEdit->setText("День рождения ");
  }
  event.year = yearSpinBox->value();
  event.month = monthComboBox->currentIndex() + 1;
  event.day = daySpinBox->value();
  event.cyclicByMonth = everyMonth->isChecked();
  event.cyclicByYear = everyYear->isChecked();
  event.color = colorComboBox->currentIndex();
  if (cb->currentIndex() == 0) {
    auto *contacts = additionalOptions->findChild<QTextEdit *>("contacts");
    contacts->clear();
  }
  titleLineEdit->clear();
  descTextEdit->clear();
  if (not edit) {
    data->sql->appendEvent(event);
    emit closed();
  }
  else {
    data->sql->editEvent(editing, event);
    emit edited(event);
    emit closed();
    close();
  }
}
