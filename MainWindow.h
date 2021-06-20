
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
#include "ModelColumn.h"


class MainWindow {
public:
    MainWindow(MainWindow const &window);
    Config config;
    Glib::RefPtr<Gtk::Builder> refBuilder;
    Gtk::ApplicationWindow *pWindow = nullptr;
    Gtk::Button *pProperties_button = nullptr;
    Gtk::Button *pPlay_button = nullptr;
    Gtk::Button *pStop_button = nullptr;
    Gtk::MenuButton *pAnime_pop_over_button = nullptr;
    Gtk::Dialog *pProperties_dialog = nullptr;
    Gtk::TreeView *pAnime_list_tree_view = nullptr;
    Glib::RefPtr<Gtk::TreeSelection> refAnime_list_tree_view_Selection;
    Gtk::Entry *pId_entry=nullptr;
    Gtk::Entry *pUrl_entry=nullptr;
    Gtk::Entry *pStart_at_entry=nullptr;
    Glib::RefPtr<Gtk::ListStore> refListStore;
    Gtk::Grid *pAnime_form=nullptr;
    Gtk::Button *pAdd_anime_button= nullptr;
    Gtk::Button *pRemove_anime_button=nullptr;

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

    ModelColumns m_Columns;

    void on_url_entry_changed();
    void on_start_at_entry_changed();
    void on_add_anime_button_clicked();
    void on_remove_anime_button_clicked();


};




#endif //ANIMEHD_MAINWINDOW_H
