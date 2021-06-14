
#ifndef ANIMEHD_MAINWINDOW_H
#define ANIMEHD_MAINWINDOW_H
#include <gtkmm.h>

class MainWindow {
public:
    Glib::RefPtr<Gtk::Builder> refBuilder;
    Gtk::ApplicationWindow *pWindow= nullptr;
public:
    MainWindow();

    ~MainWindow();

    int init(int argc, char **argv);

};


#endif //ANIMEHD_MAINWINDOW_H
