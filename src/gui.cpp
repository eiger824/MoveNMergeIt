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
  for (unsigned i=0; i<4; ++i) {
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);
    for (unsigned j=0; j< 4; ++j) {
      if (i==0 && j==0)
	layout->addWidget(new Position(i,j,GREEN));
      else
	layout->addWidget(new Position(i,j,WHITE));
    }
    m_block_layout->addLayout(layout);
  }
  m_locked_pos.append(qMakePair((unsigned int)0,(unsigned int)0));
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
  if (m_locked_pos.size() < 16)
    generateNew();
  else
    restart();
}

void Gui::move(const int direction) {
  if (direction == UP) {
    unsigned min=0;
    for (unsigned i=0; i<4; ++i) { // columns
      for (unsigned j=0; j<4; ++j) { //rows
	if (m_locked_pos.contains(qMakePair(j,i))) {
	  std::cout << "[UP]Replacing (" << j << "," << i << ") -----> ("
		    << min << "," << i <<")\n";
	  m_locked_pos.replace(m_locked_pos.indexOf(qMakePair(j,i)), qMakePair(min,i));
	  //and update coordinates in position object
	  
	  ++min;
	}
      }
      if (merge(UP,i)) {
	std::cout << "merge occurring in current column\n";
      }
      min=0;
    }
  } else if (direction == DOWN) {
    unsigned min=3;
    for (unsigned i=0; i<4; ++i) { //columns
      for (int j=3; j>=0; --j) { //rows
	if (m_locked_pos.contains(qMakePair((unsigned int)j,i))) {
	  std::cout << "[DOWN]Replacing (" << j << "," << i << ") -----> ("
		    << min << "," << i <<")\n";
	  m_locked_pos.replace(m_locked_pos.indexOf(qMakePair((unsigned int)j,i)), qMakePair(min,(unsigned int)i));
	  //and update coordinates in position object
	  
	  --min;
	}
      }
      if (merge(DOWN,i)) {
	std::cout << "merge occurring in current column\n";
      }
      min=3;
    }
  } else if (direction == LEFT) {
    unsigned min=0;
    for (unsigned i=0; i<4; ++i) { //rows
      for (unsigned j=0; j<4; ++j) { //columns
	if (m_locked_pos.contains(qMakePair(i,j))) {
	  std::cout << "[LEFT]Replacing (" << i << "," << j << ") -----> ("
		    << i << "," << min <<")\n";
	  m_locked_pos.replace(m_locked_pos.indexOf(qMakePair(i,j)), qMakePair(i,min));
	  //and update coordinates in position object
	  
	  ++min;
	}
      }
      if (merge(LEFT,i)) {
	std::cout << "merge occurring in current column\n";
      }
      min=0;
    }
  } else if (direction == RIGHT) {
    unsigned min=3;
    for (unsigned i=0; i<4; ++i) { //rows
      for (int j=3; j>=0; --j) { //columns
	if (m_locked_pos.contains(qMakePair(i,(unsigned int)j))) {
	  std::cout << "[RIGHT]Replacing (" << i << "," << j << ") -----> ("
		    << i << "," << min <<")\n";
	  m_locked_pos.replace(m_locked_pos.indexOf(qMakePair(i,(unsigned int)j)), qMakePair(i,min));
	  //and update coordinates in position object
	  
	  --min;
	}
      }
      if (merge(RIGHT,i)) {
	std::cout << "merge occurring in current column\n";
      }
      min=3;
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

void Gui::restart() {
  m_locked_pos.clear();
  updateCurrent();
  std::cout << "Starting again!\n"; 
}

void Gui::print() {
  std::cout << "Locked positions:\n";
  for (unsigned i=0; i<m_locked_pos.size(); ++i) {
    std::cout << "[" << m_locked_pos.at(i).first << ","
	      << m_locked_pos.at(i).second << "]\n";
  }
  std::cout << "----------------\n";
}

bool Gui::merge(const int direction, unsigned int nr) {
  Position *current;
  Position *next;
  unsigned cnt=0;
  if (direction == DOWN) {
    for (unsigned i=0; i < 3; ++i) {
      current =
	qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(i)->layout())->itemAt(nr)->widget());
      next =
	qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(i+1)->layout())->itemAt(nr)->widget());
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
      current =
	qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(i)->layout())->itemAt(nr)->widget());
      next =
	qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(i-1)->layout())->itemAt(nr)->widget());
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
      current =
	qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(nr)->layout())->itemAt(i)->widget());
      next =
	qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(nr)->layout())->itemAt(i-1)->widget());
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
      current =
	qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(nr)->layout())->itemAt(i)->widget());
      next =
	qobject_cast<Position*>(qobject_cast<QLayout*>(m_block_layout->itemAt(nr)->layout())->itemAt(i-1)->widget());
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
