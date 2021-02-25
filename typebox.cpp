#include "typebox.h"

TypeBox::TypeBox(QWidget *parent) : QComboBox(parent) {
  addItems(eventTypes);
  connect(this, QOverload<int>::of(&QComboBox::activated), this, [this]() { emit changed(); });
}
