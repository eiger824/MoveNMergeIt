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
      if (i==0 && j==0)
	layout->addWidget(new Position(i,j,GREEN));
      else
	layout->addWidget(new Position(i,j,BLOCK));
    }
    m_block_layout->addLayout(layout);
  }
  m_locked_pos.append(qMakePair((unsigned int)0,(unsigned int)0));
  m_main_layout->addLayout(m_block_layout);
  setLayout(m_main_layout);
  show();
}

Gui::~Gui() {
}

void Gui::keyPressEvent(QKeyEvent *event) {
  // 1.) update: move and/or merge block
  // 2.) generate new position every time
  if (event->key() == LEFT) {
    move(LEFT);
  } else if (event->key() == RIGHT) {
    move(RIGHT);
  } else if (event->key() == UP) {
    move(UP);
  } else if (event->key() == DOWN) {
    move(DOWN);
  }
  generateNew();
}

void Gui::move(const int direction) {
  if (direction == UP) {
    for (unsigned i=0; i< m_locked_pos.size(); ++i) {
      m_locked_pos.replace(i, qMakePair((unsigned int)0, m_locked_pos.at(i).second));
    }
  } else if (direction == DOWN) {
    for (unsigned i=0; i< m_locked_pos.size(); ++i) {
      m_locked_pos.replace(i, qMakePair((unsigned int)3, m_locked_pos.at(i).second));
    }
  } else if (direction == LEFT) {
    for (unsigned i=0; i< m_locked_pos.size(); ++i) {
      m_locked_pos.replace(i, qMakePair(m_locked_pos.at(i).first, (unsigned int)0));
    }
  } else if (direction == RIGHT) {
    for (unsigned i=0; i< m_locked_pos.size(); ++i) {
      m_locked_pos.replace(i, qMakePair(m_locked_pos.at(i).first, (unsigned int)3));
    }
  }
  updateCurrent();
}

void Gui::updateCurrent() {
  for (unsigned i=0; i<4; ++i) {
    for (unsigned j=0; j<4; ++j) {
      Position *position =
	qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(i)->layout())->itemAt(j)->widget());
      if (m_locked_pos.contains(qMakePair(i,j))) {
	position->setColor(GREEN);
      } else {
	position->setColor(BLOCK);
      }
    }
  }
}

void Gui::generateNew() {
  unsigned int c;
  unsigned int r;
  do {
    r = rand() % 4;
    c = rand() % 4;
  } while(m_locked_pos.contains(qMakePair(r,c)));
  m_locked_pos.append(qMakePair(r,c));
  std::cout << "Generating new at:[" << r << "," << c << "], locked positions: "
	    << m_locked_pos.size() << "\n";
  updateCurrent();
}
