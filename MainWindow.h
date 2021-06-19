
#ifndef ANIMEHD_MAINWINDOW_H
#define ANIMEHD_MAINWINDOW_H
//#include <gtkmm/button.h>
//#include <gtkmm/applicationwindow.h>
//#include <gtkmm/menubutton.h>
//#include <gtkmm/main.h>
//#include<gtkmm/builder.h>
//#include <gtkmm/box.h>
//#include <gtkmm/modelbutton.h>
//#include <glibmm/fileutils.h>
//#include <gtkmm/dialog.h>
//#include <gtkmm/liststore.h>
#include <gtkmm.h>
#include "utils.h"


class MainWindow {
public:
    Glib::RefPtr<Gtk::Builder> refBuilder;
    Gtk::ApplicationWindow *pWindow = nullptr;
    Gtk::Button *pProperties_button = nullptr;
    Gtk::Button *pPlay_button = nullptr;
    Gtk::Button *pStop_button = nullptr;
    Gtk::MenuButton *pAnime_pop_over_button = nullptr;
    Gtk::Dialog *pProperties_dialog = nullptr;
    Gtk::TreeView *pAnime_list_tree_view = nullptr;
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

    void on_anime_list_view_selection_changed();

    void on_anime_selected(const Glib::ustring &data);


};


class ModelColumns : public Gtk::TreeModelColumnRecord {
public:

    ModelColumns() {
        add(m_col_id);
        add(m_col_name);
        add(m_col_start_at);
    }

    Gtk::TreeModelColumn<Glib::ustring> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_start_at;

};


#endif //ANIMEHD_MAINWINDOW_H
