#ifndef EVENTCREATOR_H
#define EVENTCREATOR_H

#include "typebox.h"
#include "data.h"
#include "event.h"
#include <QCheckBox>
#include <QDate>
#include <QDialog>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExp>
#include <QSpacerItem>
#include <QSpinBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QTextEdit>
#include <QVBoxLayout>
#include <iostream>

class EventCreator : public QDialog {
  Q_OBJECT
public:
  EventCreator(Data *_data, QWidget *parent = nullptr);
  EventCreator(Data *_data, Event _editing, QWidget *parent = nullptr);

signals:
  void closed();
  Event edited(Event editedEvent);

private:
  Data *data = nullptr;
  QVBoxLayout *vclt = nullptr;
  TypeBox *cb = nullptr;
  QWidget *eew = nullptr;
  QSpinBox *yearSpinBox = nullptr;
  QComboBox *monthComboBox = nullptr;
  QSpinBox *daySpinBox = nullptr;
  QCheckBox *everyMonth = nullptr;
  QCheckBox *everyYear = nullptr;
  QLineEdit *titleLineEdit = nullptr;
  QComboBox *colorComboBox = nullptr;
  QTextEdit *descTextEdit = nullptr;
  QWidget *additionalOptions = nullptr;

  const QStringList months = {"january",   "february", "march",    "april",
                              "may",       "june",     "july",     "august",
                              "september", "october",  "november", "december"};
  const QStringList monthsInRus = {"Январь",   "Февраль", "Март",   "Апрель",
                                   "Май",      "Июнь",    "Июль",   "Август",
                                   "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
  const QStringList colors = {"Желтый", "Зеленый", "Красный", "Синий"};

  void eventTypeChanged();
  void saveEvent();

  void setupPlain();
  void setupContacts();

  bool edit = false;
  Event editing;

  QString ejectDesc(QString descAndCs) {
    QString s = descAndCs;
    int pos = s.indexOf("<br><p><b>Контакты:<br>");
    if (pos == -1)
      return s;
    s.truncate(pos);
    return s;
  }

  QString ejectCs(QString descAndCs) {
    QString s = descAndCs;
    int pos1 = s.indexOf("<br><p><b>Контакты:<br>");
    int pos2 = s.indexOf("</b></p>");
    if ((pos1 == -1) or (pos2 == -1))
      return s;
    QString es = "";
    for (int i = pos1 + QString("<br><p><b>Контакты:<br>").length(); i < pos2; i++)
      es.append(s[i]);
    return es;
  }

  QHBoxLayout *getHLt();
  QVBoxLayout *getVLt();
  QSpacerItem *getHSp();
};
#endif
