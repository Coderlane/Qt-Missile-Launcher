#ifndef LAUNCHWINDOW_H
#define LAUNCHWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
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
  void on_launcherListWidget_itemSelectionChanged();

  void scanForLaunchers();
  void fireOne();
  void stopAll();
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();

private:
  Ui::LaunchWindow *ui;
  ml_launcher_t **launcherArray = NULL;
  uint32_t launcherCount = 0;
  static const int listWidgetRole = Qt::UserRole + 1;

  void keyPressEvent(QKeyEvent*);
  void keyReleaseEvent(QKeyEvent*);

  void enableLauncherButtons();
  void disableLauncherButtons();
};

#endif // LAUNCHWINDOW_H
