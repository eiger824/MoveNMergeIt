#include <iostream>
#include "position.hpp"

const QString& PREFIX = "images/";

Position::Position(unsigned int i,
		   unsigned int j,
		   COLOR color,
		   QWidget* parent): QWidget(parent),
				     m_x(i),
				     m_y(j),
				     m_color(color),
				     m_locked(false) {
  //setFixedSize(50,50);
  setContentsMargins(0,0,0,0);
  m_main_layout = new QVBoxLayout;
  QPixmap target;
  m_label = new QLabel();
  m_main_layout->addWidget(m_label);
  setColor(color);
  setLayout(m_main_layout);
}

Position::~Position() {}

void Position::lock(unsigned int i,
		    unsigned int j) {
  m_x = i;
  m_y = j;
  m_locked = true;
}

void Position::unLock() {
  m_locked = false;
}

bool Position::isLocked() {
  return m_locked;
}

COLOR Position::getColor() {
  return m_color;
}
void Position::setColor(COLOR color) {
  QString path;
  QPixmap target;
  switch (color) {
  case RED:
    path="red.png";
    this->setStyleSheet("background-color: red;");
    break;
  case GREEN:
    path="block2.png";
    this->setStyleSheet("background-color: green;");
    break;
  case BLUE:
    path="block1.png";
    this->setStyleSheet("background-color: blue;");
    break;
  case YELLOW:
    path="block3.png";
    this->setStyleSheet("background-color: yellow;");
    break;
  case PINK:
    path="pink.png";
    this->setStyleSheet("background-color: pink;");
    break;
  case BLACK:
    path="black.png";
    this->setStyleSheet("background-color: black;");
    break;
  case ORANGE:
    path="orange.png";
    this->setStyleSheet("background-color: orange;");
    break;
  case WHITE:
    path="white.png";
    this->setStyleSheet("background-color: white;");
    break;
  default:
    path="block.png";
    this->setStyleSheet("background-color: white;");
    break;
  }
  if (target.load(PREFIX+path)) {
    //m_label->setPixmap(target);
  } else {
    std::cerr << "Failed\n";
  }
  m_color = color;
}

QPair<unsigned int,unsigned int> Position::getXY() {
  return qMakePair(m_x,m_y);
}
