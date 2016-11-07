#include <iostream>
#include <QLabel>
#include "gui.hpp"
#include "position.hpp"

Gui::Gui(QWidget* parent) : QWidget(parent) {
  setStyleSheet("background-color: #d4d4d4;");
  m_main_layout = new QVBoxLayout;
  m_block_layout = new QVBoxLayout;
  QPixmap target;
  for (unsigned i=0; i<4; ++i) {
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);
    for (unsigned j=0; j< 4; ++j) {
      layout->addWidget(new Position(i,j,BLOCK));
    }
    m_block_layout->addLayout(layout);
  }
  m_main_layout->addLayout(m_block_layout);
  setLayout(m_main_layout);
  show();
}

Gui::~Gui() {
}

void Gui::keyPressEvent(QKeyEvent *event) {
  std::cout << event->key() << std::endl;
}
