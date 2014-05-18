#ifndef LAUNCHWINDOW_H
#define LAUNCHWINDOW_H

#include <QMainWindow>
#include <libmissilelauncher/libmissilelauncher.h>

namespace Ui {
class LaunchWindow;
}

class LaunchWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit LaunchWindow(QWidget *parent = 0);
  ~LaunchWindow();

private slots:
  void on_scanButton_clicked();
  void on_launcherListWidget_itemSelectionChanged();

  void on_fireButton_clicked();
  void on_rightButton_clicked();
  void on_upButton_clicked();
  void on_leftButton_clicked();
  void on_downButton_clicked();

private:
  Ui::LaunchWindow *ui;
  ml_launcher_t **launcher_array = NULL;
  uint32_t launcher_count;
  static const int listWidgetRole = Qt::UserRole + 1;

  void enableLauncherButtons();
  void disableLauncherButtons();

  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
  void fireOne();
  void stopAll();
};

#endif // LAUNCHWINDOW_H
