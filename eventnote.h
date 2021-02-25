#ifndef EVENTNOTE_H
#define EVENTNOTE_H

#include <QLabel>
#include <QMouseEvent>
#include "eventwidget.h"
#include "data.h"

class EventNote : public QLabel {
  Q_OBJECT
public:
  EventNote(Data *_data, Event _event, QWidget *parent = nullptr);
signals:
  void updated();
  Event callEventWidget(Event ev);
private:
  Data *data = nullptr;
  void redraw(Event ev);
  Event event;
  virtual void mouseReleaseEvent(QMouseEvent *e);
};

#endif
