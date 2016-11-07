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
  initGame();
  show();
}

Gui::~Gui() {
}

void Gui::keyPressEvent(QKeyEvent *event) {
  // 1.) update: move and/or merge block
  // 2.) generate new position every time
}

void Gui::initGame() {
  for (unsigned i=0; i < 2; ++i) {
    unsigned r = rand() % 4;
    unsigned c = rand() % 4;
    std::cout << r << "," << c << std::endl;
    for (unsigned d=0; d< 4; d++) {
      for (unsigned e=0; e<4; ++e) {
	Position *pos =
	  qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(r)->layout())->itemAt(c)->widget());
	if (d == r && e == c) {
	  std::cout << "setting special\n";
	  pos->setColor(GREEN);
	} else {
	  pos->setColor(BLOCK);
	}
      }
    }
  }
}
