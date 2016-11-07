#include <QApplication>
#include <iostream>
#include "gui.hpp"

int help(int code) {
  std::cout << "Falling Blocks - The Game!\n";
  std::cout << "[USAGE]: fblocks [OPTIONS]\n";
  std::cout << "OPTIONS:\n";
  std::cout << "-c <n>\t\tSet column count to n\n";
  std::cout << "-d <level>\tEnable debug controls\n";
  std::cout << "   (level: HIGH,MEDIUM,LOW)\n";
  std::cout << "-h\t\tPrint this help and exit\n";
  std::cout << "-r <n>\t\tSet row count to n\n";
  std::cout << "-s\t\tSkip login page\n";
  std::cout << "-t <ms>\t\tSet falling block refresh rate (in ms.)\n";
  std::cout << "-u\t\tUpdate timer every 10 points\n";
  if (code == 0) {
    return 0;
  } else {
    return -1;
  }
}

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Gui gui;
  return app.exec();
}
