#include <iostream>
#include <QLabel>
#include "gui.hpp"
#include "position.hpp"

Gui::Gui(QWidget* parent) : QWidget(parent) {
  setStyleSheet("background-color: #d4d4d4;");
  setContentsMargins(0,0,0,0);
  setFixedSize(574,592);
  m_main_layout = new QVBoxLayout;
  m_block_layout = new QVBoxLayout;
  QPixmap target;
  unsigned r = rand() % 4;
  unsigned c = rand() % 4;
  std::cout << "Starting initial at: " << r << "," << c << std::endl;
  for (unsigned i=0; i<4; ++i) {
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);
    for (unsigned j=0; j< 4; ++j) {
      if (i==r && j==c)
	layout->addWidget(new Position(i,j,GREEN));
      else
	layout->addWidget(new Position(i,j,WHITE));
    }
    m_block_layout->addLayout(layout);
  }
  m_locked_pos.append(qMakePair((unsigned int)r,(unsigned int)c));
  m_main_layout->addLayout(m_block_layout);
  setWindowTitle("Move & Merge It!");
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
  } else if (event->key() == ENTER) {
    restart();
    return;
  } else if (event->key() == ASCII_SPACE) {
    print();
    return;
  }
  if (m_locked_pos.size() < 16) {
    generateNew();
  } else {
    restart();
  }
}

void Gui::move(const int direction) {
  if (direction == UP) {
    //column order not important, row order U--->D
    unsigned min=0;
    for (unsigned i=0; i<4; ++i) {
      for (unsigned j=0; j<4; ++j) {
	Position *position = castPosition(j,i);
	if (m_locked_pos.contains(qMakePair(j,i))) {
	  m_locked_pos.replace(m_locked_pos.indexOf(qMakePair(j,i)), qMakePair(min,i));
	  position->lock(min,j);
	  Position *updated = castPosition(min,j);
	  updated->setColor(position->getColor());
	  ++min;
	}
      }
      min=0;
    }
  } else if (direction == DOWN) {
     //column order not important, row order U--->D
    unsigned min=3;
    for (unsigned i=0; i<4; ++i) {
      for (unsigned j=4; j>0; --j) {
	Position *position = castPosition(j-1,i);
	if (m_locked_pos.contains(qMakePair(j-1,i))) {
	  m_locked_pos.replace(m_locked_pos.indexOf(qMakePair(j-1,i)), qMakePair(min,i));
	  position->lock(min,i);
	  Position *updated = castPosition(min,i);
	  updated->setColor(position->getColor());
	  --min;
	}
      }
      min=3;
    }
  } else if (direction == LEFT) {
    //row order not important, column order L--->R
    unsigned min=0;
    for (unsigned i=0; i<4; ++i) {
      for (unsigned j=0; j<4; ++j) {
	Position *position = castPosition(i,j);
	if (m_locked_pos.contains(qMakePair(i,j))) {
	  m_locked_pos.replace(m_locked_pos.indexOf(qMakePair(i,j)), qMakePair(i,min));
	  position->lock(i,min);
	  Position *updated = castPosition(i,min);
	  updated->setColor(position->getColor());
	  ++min;
	}
      }
      min=0;
    }
  } else if (direction == RIGHT) {
    //row order not important, column order L--->R
    unsigned min=3;
    for (unsigned i=0; i<4; ++i) {
      for (unsigned j=4; j>0; --j) {
	Position *position = castPosition(i,j-1);
	if (m_locked_pos.contains(qMakePair(i,j-1))) {
	  m_locked_pos.replace(m_locked_pos.indexOf(qMakePair(i,j-1)), qMakePair(i,min));
	  position->lock(i,min);
	  Position *updated = castPosition(i,min);
	  updated->setColor(position->getColor());
	  --min;
	}
      }
      min=3;
    }
  }
  updateCurrent();
}

void Gui::updateCurrent() {
  for (unsigned i=0; i<4; ++i) {
    for (unsigned j=0; j<4; ++j) {
      Position *position = castPosition(i,j);
      if (m_locked_pos.contains(qMakePair(i,j))) {
	position->setColor(position->getColor());
      } else {
	position->setColor(WHITE);
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
  //and specify a color
  Position *current = castPosition(r,c);
  current->setColor((COLOR)(rand() % 7));
  std::cout << "Generating new at:[" << r << "," << c << "], locked positions: "
	    << m_locked_pos.size() << "\n";
  updateCurrent();
}

void Gui::restart() {
  m_locked_pos.clear();
  updateCurrent();
  std::cout << "Starting again!\n"; 
}

void Gui::print() {
  std::cout << "Locked positions:\n";
  for (unsigned i=0; i<m_locked_pos.size(); ++i) {
    std::cout << "[" << m_locked_pos.at(i).first << ","
	      << m_locked_pos.at(i).second << "] : color: "
	      << castPosition(m_locked_pos.at(i).first, m_locked_pos.at(i).second)->getColorString().toStdString()
	      << "\n";
  }
  std::cout << "----------------\n";
}

bool Gui::merge(const int direction, unsigned int nr) {
  Position *current;
  Position *next;
  unsigned cnt=0;
  if (direction == DOWN) {
    for (unsigned i=0; i < 3; ++i) {
      current = castPosition(i,nr);
      next = castPosition(i+1,nr);
      if (current->getColor() == next->getColor()) {
	//same color, merge
	current->free();
	m_locked_pos.removeAt(m_locked_pos.indexOf(qMakePair(i,nr)));
	next->doubleScore();
	std::cout << "Merging!\n";
	++cnt;
      }
    }
    if (cnt > 0) return true;
  } else if (direction == UP) {
    for (unsigned i=3; i > 0; --i) {
      current = castPosition(i,nr);
      next = castPosition(i-1,nr);
      if (current->getColor() == next->getColor()) {
	//same color, merge
	current->free();
	m_locked_pos.removeAt(m_locked_pos.indexOf(qMakePair(i,nr)));
	next->doubleScore();
	std::cout << "Merging!\n";
	++cnt;
      }
    }
    if (cnt > 0) return true;
  } else if (direction == LEFT) {
    for (unsigned i=3; i > 0; --i) {
      current = castPosition(nr,i);
      next = castPosition(nr,i-1);
      if (current->getColor() == next->getColor()) {
	//same color, merge
	current->free();
	m_locked_pos.removeAt(m_locked_pos.indexOf(qMakePair(nr,i)));
	next->doubleScore();
	std::cout << "Merging!\n";
	++cnt;
      }
    }
    if (cnt > 0) return true;
  } else if (direction == RIGHT) {
    for (unsigned i=0; i<3; ++i) {
      current = castPosition(nr,i);
      next = castPosition(nr,i-1);
      if (current->getColor() == next->getColor()) {
	//same color, merge
	current->free();
	m_locked_pos.removeAt(m_locked_pos.indexOf(qMakePair(nr,i)));
	next->doubleScore();
	std::cout << "Merging!\n";
	++cnt;
      }
    }
    if (cnt > 0) return true;
  }
  return false;
}

Position* Gui::castPosition(unsigned int i, unsigned int j) {
  if (0<=i<=3 || 0<=j<=3)
    return (qobject_cast<Position*>
	    (qobject_cast<QLayout*>(m_block_layout->itemAt(i)->layout())
	     ->itemAt(j)->widget()));
  else return NULL;
}
