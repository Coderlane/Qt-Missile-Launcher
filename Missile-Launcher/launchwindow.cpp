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
  for(uint32_t i = 0; i < launcher_count; i++) {

    //ml_stop_launcher(launcher_array[i]);
  }
}

void LaunchWindow::moveLeft() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      cur_launcher = this->launcher_array[launcher_index];
      ml_move_launcher(cur_launcher, ML_LEFT);
    }
  }
}

void LaunchWindow::moveRight() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      cur_launcher = this->launcher_array[launcher_index];
      ml_move_launcher(cur_launcher, ML_RIGHT);
    }
  }
}

void LaunchWindow::moveUp() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      cur_launcher = this->launcher_array[launcher_index];
      ml_move_launcher(cur_launcher, ML_UP);
    }
  }

}

void LaunchWindow::moveDown() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      cur_launcher = this->launcher_array[launcher_index];
      ml_move_launcher(cur_launcher, ML_DOWN);
    }
  }
}
