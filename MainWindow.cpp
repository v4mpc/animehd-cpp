
#include <iostream>
#include "MainWindow.h"


MainWindow::MainWindow() {
    std::clog << "Main Window created!" << std::endl;

};

MainWindow::~MainWindow() {
    std::clog << "Main Window destroyed!" << std::endl;
};

//self.builder.connect_signals(self)
//self.properties_button = self.builder.get_object('properties_button')
//self.properties_button.connect('clicked', self.on_properties_clicked)
//self.add_anime_button = self.builder.get_object('add_anime_button')
//self.remove_anime_button = self.builder.get_object('remove_anime_button')
//self.anime_form_container = self.builder.get_object('anime_form_container')
//self.id_entry = self.builder.get_object('id_entry')
//self.id_entry.connect('changed', self.on_id_changed)
//self.url_entry = self.builder.get_object('url_entry')
//self.url_entry.connect('changed', self.on_url_changed)
//self.start_at_entry = self.builder.get_object('start_at_entry')
//self.start_at_entry.connect('changed', self.on_start_at_changed)
//self.start_at_entry: Gtk.Entry = self.builder.get_object('start_at_entry')
//self.anime_form = self.builder.get_object('anime_form')
//Gtk.Widget.hide(self.anime_form)
//self.remove_anime_button.connect('clicked', self.on_remove_anime_button_clicked)
//Gtk.Widget.set_sensitive(self.remove_anime_button, True)
//
//self.add_anime_button.connect('clicked', self.on_add_anime_button_clicked)
//
//self.store = DownloadsModel(self.downloads_mutex)
//self.anime_store = AnimesModel(self.anime_mutex)
//self.anime_enum, _ = generate_enum()
//self.anime_store_enum, _ = generate_enum(anime_store)
//self.tree_view = self.builder.get_object('tree_view')
//# self.tree_view.set_has_tooltip(True)
//self.tree_view.set_tooltip_column(self.anime_enum.EPISODE_NAME)
//# self.tree_view.connect('query-tooltip',self.on_show_tooltip)
//self.anime_list_tree_view = self.builder.get_object('anime_list_tree_view')
//self.anime_list_tree_view_selection = self.anime_list_tree_view.get_selection()
//self.anime_list_tree_view_selection.connect('changed', self.on_anime_list_tree_view_selection_changed)
//self.tree_view.set_model(self.store)
//self.anime_list_tree_view.set_model(self.anime_store)
//self.setup_tree_view()
int MainWindow::init(int argc, char **argv) {
    Gtk::Main kit(argc, argv);
    refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_file("../main.glade");
    }
    catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }
    refBuilder->get_widget("main_window", pWindow);
    connect_all_signals();
    Gtk::Main::run(*pWindow);



}

void MainWindow::on_properties_button_clicked() {
    std::cout << "Properties button clicked" << std::endl;
}

void MainWindow::connect_all_signals(){
    refBuilder->get_widget("properties_button", pProperties_button);
    pProperties_button->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_properties_button_clicked));
}

