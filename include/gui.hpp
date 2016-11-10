#ifndef GUI_HPP_
#define GUI_HPP_

#include <QWidget>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "position.hpp"

class Gui : public QWidget {
  Q_OBJECT
public:
  Gui(QWidget* parent=0);
  ~Gui();
protected:
  void keyPressEvent(QKeyEvent* event);
private:
  void move(const int direction);
  void updateCurrent();
  void generateNew();
  void restart();
  void print();
  void printScores();
  bool merge(const int direction, unsigned int nr);
  Position* castPosition(unsigned int i, unsigned int j);
  int getNrMergeable(bool direction,
		     unsigned int nr);
private:
  QVBoxLayout *m_main_layout;
  QVBoxLayout *m_block_layout;
  QList<QPair<unsigned int,unsigned int> >m_locked_pos;
};

#endif /*GUI_HPP_*/
