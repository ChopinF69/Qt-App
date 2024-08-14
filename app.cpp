//
// Created by lazar on 25.04.2024.
//
#include "ui.h"
#include "validator/validator.h"
#include <QApplication>

#include "newGui.h"
#include "storeGUImodele.h"
// #include "gui.h"
int main(int argc, char *argv[]) {
  // testAllDomain();
  std::cout << "All tests for domain passed!\n";
  // testAllRepo();
  std::cout << "All tests for repo passed!\n";
  // testAllService();
  std::cout << "All tests for service passed!\n";
  // testAllValidator();
  std::cout << "All tests for validator passed!\n";

  // UI ui;
  // ui.run();

  Service service;
  QApplication app(argc, argv);

  // BookGUI bookGUI(service);
  StoreGUIModele bookGUI(service);
  std::cout << "GUI1\n";
  bookGUI.show();

  /*
  GUI gui(service);
  gui.show();

   */
  return app.exec();
}
/*
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("Simple Qt Window");
    window.setGeometry(100, 100, 400, 200);
    window.show();

    return app.exec();
}*/
