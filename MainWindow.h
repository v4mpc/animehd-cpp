
#ifndef ANIMEHD_MAINWINDOW_H
#define ANIMEHD_MAINWINDOW_H

#include <gtkmm.h>


class MainWindow {
public:
    Glib::RefPtr<Gtk::Builder> refBuilder;
    Gtk::ApplicationWindow *pWindow = nullptr;
    Gtk::Button *pProperties_button = nullptr;
    Gtk::Button *pPlay_button=nullptr;
    Gtk::Button *pStop_button=nullptr;
    Gtk::MenuButton *pAnime_pop_over_button=nullptr;
//    Gtk::Popover *Anime_pop_over= nullptr;
public:
    MainWindow();

    ~MainWindow();

    int init(int argc, char **argv);

    void on_properties_button_clicked();

    void connect_all_signals();

    void on_play_button_clicked();

    void on_stop_button_clicked();

    void setup_anime_popover();

    void on_anime_selected(const Glib::ustring& data);


};


#endif //ANIMEHD_MAINWINDOW_H
