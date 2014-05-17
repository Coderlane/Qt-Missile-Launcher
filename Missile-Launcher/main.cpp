#include "launchwindow.h"
#include <QApplication>
#include <libmissilelauncher/libmissilelauncher.h>

int main(int argc, char *argv[]) {
  int status = 0;
  // Init the missile launcher
  status = ml_init_library();
  if(status != ML_OK) {
    return status;
  }

  QApplication a(argc, argv);
  LaunchWindow w;
  w.show();
  status = a.exec();

  ml_cleanup_library();
  return status;
}
