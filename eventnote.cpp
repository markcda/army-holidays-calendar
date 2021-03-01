#include "eventnote.h"

EventNote::EventNote(Data *_data, Event _event, QWidget *parent)
    : QLabel(parent) {
  data = _data;
  setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  redraw(_event);
  setIndent(2);
  setMargin(2);
  setWordWrap(true);
  setScaledContents(true);
}

void EventNote::redraw(Event ev) {
  event = ev;
  setText(event.name);
  setObjectName("en");
  if (event.color == 0)
    setStyleSheet("#en { background-color: rgb(255, 231, 93); color: rgb(0, 0, "
                  "0); border-radius: 5px; }");
  else if (event.color == 1)
    setStyleSheet("#en { background-color: rgb(91, 255, 82); color: rgb(0, 0, "
                  "0); border-radius: 5px; }");
  else if (event.color == 2)
    setStyleSheet("#en { background-color: rgb(255, 60, 63); color: rgb(0, 0, "
                  "0); border-radius: 5px; }");
  else if (event.color == 3)
    setStyleSheet("#en { background-color: rgb(17, 41, 255); color: rgb(255, "
                  "255, 255); border-radius: 5px; }");
}

void EventNote::mouseReleaseEvent(QMouseEvent *e) {
  Q_UNUSED(e)
  emit callEventWidget(event);
}
