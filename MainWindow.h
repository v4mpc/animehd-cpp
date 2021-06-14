
#ifndef ANIMEHD_MAINWINDOW_H
#define ANIMEHD_MAINWINDOW_H
#include <gtkmm.h>

class MainWindow {
public:
    Glib::RefPtr<Gtk::Builder> refBuilder;
    Gtk::ApplicationWindow *pWindow= nullptr;
    Gtk::Button *pProperties_button= nullptr;
public:
    MainWindow();

    ~MainWindow();

    int init(int argc, char **argv);

    void on_properties_button_clicked();

    void connect_all_signals();
};


#endif //ANIMEHD_MAINWINDOW_H
