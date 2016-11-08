#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "definitions.hpp"

class Position : public QWidget {
  Q_OBJECT
public:
  Position(unsigned int i,
	   unsigned int j,
	   COLOR color = WHITE,
	   QWidget* parent=0);
  ~Position();
  void lock(unsigned int i, unsigned int j);
  bool isLocked();
  void unLock();
  void setColor(COLOR color);
  COLOR getColor();
  QPair<unsigned int,unsigned int> getXY();
  void doubleScore();
  void free();
private:
  unsigned int m_x;
  unsigned int m_y;
  COLOR m_color;
  bool m_locked;
  unsigned m_score;
  QLabel *m_label;
  QVBoxLayout *m_main_layout;
};

#endif /*POSITION_HPP_*/
