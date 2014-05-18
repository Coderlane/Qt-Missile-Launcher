#include "launchwindow.h"
#include "ui_launchwindow.h"

LaunchWindow::LaunchWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::LaunchWindow) {
  ui->setupUi(this);
  disableLauncherButtons();
}

LaunchWindow::~LaunchWindow() {
  delete ui;
}

void LaunchWindow::on_scanButton_clicked() {
  ui->launcherListWidget->clear();
  if(launcher_array != NULL) {
    ml_free_launcher_array(launcher_array);
    launcher_array = NULL;
  }
  ml_get_launcher_array(&launcher_array, &launcher_count);
  for(uint32_t i = 0; i < launcher_count; i++) {
    QListWidgetItem *newItem = new QListWidgetItem(QString::number(i, 10));
    newItem->setData(this->listWidgetRole, i);
    ui->launcherListWidget->addItem(newItem);
  }
  //TODO check for bad status
}

void LaunchWindow::disableLauncherButtons() {
  ui->upButton->setEnabled(false);
  ui->downButton->setEnabled(false);
  ui->rightButton->setEnabled(false);
  ui->leftButton->setEnabled(false);
  ui->fireButton->setEnabled(false);
}

void LaunchWindow::enableLauncherButtons() {
  ui->upButton->setEnabled(true);
  ui->downButton->setEnabled(true);
  ui->rightButton->setEnabled(true);
  ui->leftButton->setEnabled(true);
  ui->fireButton->setEnabled(true);
}

void LaunchWindow::on_launcherListWidget_itemSelectionChanged() {
  stopAll();
  if(ui->launcherListWidget->selectedItems().count() == 0) {
    disableLauncherButtons();
  } else {
    enableLauncherButtons();
  }
}

void LaunchWindow::on_fireButton_clicked() {
  fireOne();
}

void LaunchWindow::on_rightButton_clicked() {
  moveRight();
}

void LaunchWindow::on_leftButton_clicked() {
  moveLeft();
}

void LaunchWindow::on_downButton_clicked() {
  moveDown();
}

void LaunchWindow::on_upButton_clicked() {
  moveUp();
}

void LaunchWindow::fireOne() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      cur_launcher = this->launcher_array[launcher_index];
      ml_fire_launcher(cur_launcher);
    }
  }
}

void LaunchWindow::stopAll() {

}

void LaunchWindow::moveLeft() {
  stopAll();

}

void LaunchWindow::moveRight() {
  stopAll();

}

void LaunchWindow::moveUp() {
  stopAll();

}

void LaunchWindow::moveDown() {
  stopAll();

}
