#ifndef TYPEBOX_H
#define TYPEBOX_H

#include <QComboBox>

class TypeBox : public QComboBox {
  Q_OBJECT
public:
  TypeBox(QWidget *parent = nullptr);
signals:
  void changed();
private:
  const QStringList eventTypes = {"День рождения", "День воинской славы", "Событие"};
};

#endif
