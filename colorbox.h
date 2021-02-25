#ifndef COLORBOX_H
#define COLORBOX_H

#include <QComboBox>

class ColorBox : public QComboBox {
  Q_OBJECT
public:
  ColorBox(QWidget *parent = nullptr);
signals:
  void changed();
private:
  const QStringList eventTypes = {"День рождения", "День воинской славы", "Событие"};
};

#endif
