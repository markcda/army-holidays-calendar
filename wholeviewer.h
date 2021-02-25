#ifndef WHOLEVIEWER_H
#define WHOLEVIEWER_H

#include "data.h"
#include "event.h"
#include "eventcreator.h"
#include "eventnote.h"
#include "sqlhandler.h"
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class WholeViewer : public QWidget {
  Q_OBJECT
public:
  WholeViewer(Data *_data, QWidget *parent = nullptr);

signals:
  void openCalendar();

private:
  QGridLayout *clt = nullptr;
  QWidget *le = nullptr;
  void openEC();
  void openEW(Event ev);
  void updateEvents();
  Data *data = nullptr;
};

#endif
