#ifndef GUI_HPP_
#define GUI_HPP_

#include <QWidget>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>

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
private:
  QVBoxLayout *m_main_layout;
  QVBoxLayout *m_block_layout;
  QList<QPair<unsigned int,unsigned int> >m_locked_pos;
};

#endif /*GUI_HPP_*/
