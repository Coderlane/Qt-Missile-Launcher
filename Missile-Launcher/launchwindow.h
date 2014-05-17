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

private:
  Ui::LaunchWindow *ui;
  ml_launcher_t **launcher_array;
  uint32_t launcher_count;
};

#endif // LAUNCHWINDOW_H
