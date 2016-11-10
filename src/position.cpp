#include <iostream>
#include "position.hpp"

Position::Position(unsigned int i,
		   unsigned int j,
		   COLOR color,
		   QWidget* parent): QWidget(parent),
				     m_x(i),
				     m_y(j),
				     m_color(color),
				     m_score(2),
				     m_locked(false) {
  setContentsMargins(0,0,0,0);
  m_main_layout = new QVBoxLayout;
  QPixmap target;
  m_label = new QLabel("2");
  m_label->setStyleSheet("font: 40px arial bold;");
  m_label->setAlignment(Qt::AlignCenter);
  m_main_layout->addWidget(m_label);
  setColor(color);
  if (color != WHITE)
    m_locked = true;
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
  switch (color) {
  case RED:
    this->setStyleSheet("background-color: red;");
    break;
  case GREEN:
    this->setStyleSheet("background-color: green;");
    break;
  case BLUE:
    this->setStyleSheet("background-color: blue;");
    break;
  case YELLOW:
    this->setStyleSheet("background-color: yellow;");
    break;
  case PINK:
    this->setStyleSheet("background-color: pink;");
    break;
  case BLACK:
    this->setStyleSheet("background-color: black;");
    break;
  case ORANGE:
    this->setStyleSheet("background-color: orange;");
    break;
  case WHITE:
    m_label->setText("");
    this->setStyleSheet("background-color: white;");
    break;
  default:
    this->setStyleSheet("background-color: white;");
    break;
  }
  m_color = color;
}

QPair<unsigned int,unsigned int> Position::getXY() {
  return qMakePair(m_x,m_y);
}

void Position::doubleScore() {
  m_score*=2;
  m_label->setText(QString::number(m_score));
}

void Position::free() {
  setColor(WHITE);
  m_score = 2;
  m_label->setText("");
  m_locked = false;
}

QString Position::getColorString() {
  switch (m_color) {
  case RED:
    return "red";
  case GREEN:
    return "green";
  case BLUE:
    return "blue";
  case YELLOW:
    return "yellow";
  case PINK:
    return "pink";
  case BLACK:
    return "black";
  case ORANGE:
    return "orange";
  case WHITE:
    return "white";
  case BLOCK:
    return "block";
  default:
    return "unknown";
  }
}
