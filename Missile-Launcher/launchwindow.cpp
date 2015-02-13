/**
 * @file launchwindow.cpp
 * @brief 
 * @author Travis Lane
 * @version 0.1.0
 * @date 2014-05-18
 */

#include "launchwindow.h"
#include "ui_launchwindow.h"

/**
 * @brief Creates a new LaunchWindow.
 *
 * @param parent The parent window.
 */
LaunchWindow::LaunchWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::LaunchWindow) {
  ui->setupUi(this);
  disableLauncherButtons();
  
	// Setup Connections
  connect(ui->leftButton, SIGNAL(pressed()), this, SLOT(moveLeft()));
  connect(ui->rightButton, SIGNAL(pressed()), this, SLOT(moveRight()));
  connect(ui->upButton, SIGNAL(pressed()), this, SLOT(moveUp()));
  connect(ui->downButton, SIGNAL(pressed()), this, SLOT(moveDown()));
  //connect(this, SIGNAL())

  connect(ui->leftButton, SIGNAL(released()), this, SLOT(stopAll()));
  connect(ui->rightButton, SIGNAL(released()), this, SLOT(stopAll()));
  connect(ui->upButton, SIGNAL(released()), this, SLOT(stopAll()));
  connect(ui->downButton, SIGNAL(released()), this, SLOT(stopAll()));

  connect(ui->fireButton, SIGNAL(clicked()), this, SLOT(fireOne()));
  connect(ui->scanButton, SIGNAL(clicked()), this, SLOT(scanForLaunchers()));
  connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
}

/**
 * @brief Destroys the LaunchWindow.
 */
LaunchWindow::~LaunchWindow() {
    if(launcherArray != NULL) {
        for(uint32_t i = 0; i < launcherCount; i++) {
          ml_launcher_unclaim(launcherArray[i]);
        }
      ml_launcher_array_free(launcherArray);
      launcherArray = NULL;
    }
  delete ui;
}

/**
 * @brief handles the key press event
 */
void LaunchWindow::keyPressEvent(QKeyEvent *keyEvent){
  switch(keyEvent->key()) {
  case Qt::Key_W:
  case Qt::Key_Up:
    moveUp();
    break;
  case Qt::Key_S:
  case Qt::Key_Down:
    moveDown();
    break;
  case Qt::Key_A:
  case Qt::Key_Left:
    moveLeft();
    break;
  case Qt::Key_D:
  case Qt::Key_Right:
    moveRight();
    break;
  case Qt::Key_F:
  case Qt::Key_Space:
    fireOne();
    break;
  }
}

/**
 * @brief Handles the key release event
 */
void LaunchWindow::keyReleaseEvent(QKeyEvent *) {
  this->stopAll();
}

/**
 * @brief Scans for new launchers and updates the display.
 */
void LaunchWindow::scanForLaunchers() {
  int16_t result = 0;
  stopAll();
  // Remove all old launchers.
  ui->launcherListWidget->clear();
  if(launcherArray != NULL) {
      for(uint32_t i = 0; i < launcherCount; i++) {
        ml_launcher_unclaim(launcherArray[i]);
      }
    ml_launcher_array_free(launcherArray);
    launcherArray = NULL;
  }
  // Grab new launchers.
  result = ml_launcher_array_new(&launcherArray, &launcherCount);
  if(result != ML_OK) {
    launcherCount = 0;
  }
  // Updated displayed items.
  for(uint32_t i = 0; i < launcherCount; i++) {
    QListWidgetItem *newItem = new QListWidgetItem(QString::number(i, 10));
    ml_launcher_claim(launcherArray[i]);
    newItem->setData(this->listWidgetRole, i);
    ui->launcherListWidget->addItem(newItem);
  }
  if(launcherCount == 0) {
    disableLauncherButtons();
  }
}

/**
 * @brief Disables the launcher control buttons.
 */
void LaunchWindow::disableLauncherButtons() {
  ui->upButton->setEnabled(false);
  ui->downButton->setEnabled(false);
  ui->rightButton->setEnabled(false);
  ui->leftButton->setEnabled(false);
  ui->fireButton->setEnabled(false);
}

/**
 * @brief Enables the launcher control buttons.
 */
void LaunchWindow::enableLauncherButtons() {
  ui->upButton->setEnabled(true);
  ui->downButton->setEnabled(true);
  ui->rightButton->setEnabled(true);
  ui->leftButton->setEnabled(true);
  ui->fireButton->setEnabled(true);
}

/**
 * @brief Handles the update of the selected items
 */
void LaunchWindow::on_launcherListWidget_itemSelectionChanged() {
  stopAll();
  if(ui->launcherListWidget->selectedItems().count() == 0) {
    disableLauncherButtons();
  } else {
    enableLauncherButtons();
  }
}

/**
 * @brief Fires one missile from each of the selected launchers 
 */
void LaunchWindow::fireOne() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      cur_launcher = this->launcherArray[launcher_index];
      ml_launcher_fire(cur_launcher);
    }
  }
}

/**
 * @brief Stops all of the launchers. 
 */
void LaunchWindow::stopAll() {
  for(uint32_t i = 0; i < launcherCount; i++) {
    ml_launcher_stop(launcherArray[i]);
  }
}

/**
 * @brief Moves all of the selected launchers to the left untill told to stop. 
 */
void LaunchWindow::moveLeft() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      cur_launcher = this->launcherArray[launcher_index];
      ml_launcher_move(cur_launcher, ML_LEFT);
    }
  }
}

/**
 * @brief Moves all of the selected launchers to the right untill told to stop. 
 */
void LaunchWindow::moveRight() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      cur_launcher = this->launcherArray[launcher_index];
      ml_launcher_move(cur_launcher, ML_RIGHT);
    }
  }
}

/**
 * @brief Moves all of the selected launchers up untill told to stop. 
 */
void LaunchWindow::moveUp() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      int rv;
      cur_launcher = this->launcherArray[launcher_index];
      rv = ml_launcher_move(cur_launcher, ML_UP);
      std::cerr << "Code: " << rv << std::endl;
    }
  }

}

/**
 * @brief Moves all of the selected launchers down untill told to stop. 
 */
void LaunchWindow::moveDown() {
  stopAll();
  foreach(QListWidgetItem *item, ui->launcherListWidget->selectedItems()) {
    bool ok = false;
    uint launcher_index = 0;
    ml_launcher_t *cur_launcher = NULL;
    launcher_index = item->data(listWidgetRole).toUInt(&ok);
    if(ok) {
      cur_launcher = this->launcherArray[launcher_index];
      ml_launcher_move(cur_launcher, ML_DOWN);
    }
  }
}
