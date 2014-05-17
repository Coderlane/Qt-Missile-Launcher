#include "launchwindow.h"
#include "ui_launchwindow.h"

LaunchWindow::LaunchWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::LaunchWindow) {
  ui->setupUi(this);
}

LaunchWindow::~LaunchWindow() {
  delete ui;
}

void LaunchWindow::on_scanButton_clicked() {
  ml_get_launcher_array(&launcher_array, &launcher_count);
  //TODO check for bad status
}
