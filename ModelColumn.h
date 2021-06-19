//
// Created by v4mpc on 6/20/21.
//

#ifndef ANIMEHD_MODELCOLUMN_H
#define ANIMEHD_MODELCOLUMN_H
#include <gtkmm.h>


class ModelColumns : public Gtk::TreeModelColumnRecord {
public:
    ModelColumns();
    Gtk::TreeModelColumn<Glib::ustring> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_url;
    Gtk::TreeModelColumn<Glib::ustring> m_col_start_at;

};




#endif //ANIMEHD_MODELCOLUMN_H
