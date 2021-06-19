
#include <iostream>
#include <gtkmm/stock.h>
#include "MainWindow.h"


//TODO: default download folder should be home/Videos/Animes


MainWindow::MainWindow() {
    std::clog << "Main Window created!" << std::endl;

};

MainWindow::~MainWindow() {
    std::clog << "Main Window destroyed!" << std::endl;
};

int MainWindow::init(int argc, char **argv) {
    Gtk::Main kit(argc, argv);
    refBuilder = Gtk::Builder::create();
//    TODO: use Gio::Resource to efficiently load user data and to be included in final executable
    try {
        refBuilder->add_from_file("../../main.glade");
    }
    catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }
    connect_all_signals();
    setup_anime_popover();
    refBuilder->get_widget("main_window", pWindow);
    refBuilder->get_widget("properties_dialog", pProperties_dialog);

    refBuilder->get_widget("anime_list_tree_view", pAnime_list_tree_view);
    refAnime_list_tree_view_Selection = pAnime_list_tree_view->get_selection();

    refAnime_list_tree_view_Selection->signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_anime_list_view_selection_changed)
    );

    pProperties_dialog->set_transient_for(*pWindow);
    pProperties_dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

    Glib::RefPtr<Gtk::ListStore> refListStore = Gtk::ListStore::create(m_Columns);
    pAnime_list_tree_view->set_model(refListStore);
    pAnime_list_tree_view->append_column("Id", m_Columns.m_col_id);
    pAnime_list_tree_view->append_column("Name", m_Columns.m_col_name);
    pAnime_list_tree_view->append_column("start at", m_Columns.m_col_start_at);


    Config config;
    auto config_path = get_config_path();
    auto config_dir_path = get_anime_path();
    initialize_config(config_dir_path);
    load_config(config_path, config);


    for (int i = 0; i < config.animes.size(); ++i) {
        Gtk::TreeModel::iterator iter = refListStore->append();
        Gtk::TreeModel::Row row = *iter;
        row[m_Columns.m_col_id] = config.animes[i].id;
        row[m_Columns.m_col_name] = config.animes[i].name;
        row[m_Columns.m_col_url] = config.animes[i].url;
        row[m_Columns.m_col_start_at] = config.animes[i].start_at;
    }



//    setup the anime list view here from file








    Gtk::Main::run(*pWindow);

    return 1;
}

void MainWindow::on_anime_list_view_selection_changed() {
    std::cout << "selection changed" << std::endl;
    Gtk::TreeModel::iterator iter = refAnime_list_tree_view_Selection->get_selected();
    if (iter) //If anything is selected
    {
        Gtk::TreeModel::Row row = *iter;
        //Do something with the row.
        pId_entry->set_text(row[m_Columns.m_col_id]);
        pUrl_entry->set_text(row[m_Columns.m_col_url]);
        pStart_at->set_text(row[m_Columns.m_col_start_at]);

        std::cout<<"row selected"<<std::endl;
    }
}

void MainWindow::on_properties_button_clicked() {
    std::cout << "Properties button clicked" << std::endl;
    int result = pProperties_dialog->run();
    //Handle the response:
    switch (result) {
        case (Gtk::RESPONSE_OK): {
            std::cout << "OK clicked." << std::endl;
            break;
        }
        case (Gtk::RESPONSE_CANCEL): {
            std::cout << "Cancel clicked." << std::endl;
            break;
        }
        default: {
            pProperties_dialog->hide();
            std::cout << "Unexpected button clicked." << std::endl;
            break;
        }
    }

}

void MainWindow::connect_all_signals() {

    refBuilder->get_widget("properties_button", pProperties_button);
    pProperties_button->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_properties_button_clicked));
    refBuilder->get_widget("play_button", pPlay_button);
    pPlay_button->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_play_button_clicked));
    refBuilder->get_widget("stop_button", pStop_button);
    refBuilder->get_widget("id_entry",pId_entry);
    refBuilder->get_widget("url_entry",pUrl_entry);
    refBuilder->get_widget("start_at_entry",pStart_at);
    pStop_button->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_stop_button_clicked));
    pUrl_entry->signal_changed().connect(sigc::mem_fun(this,&MainWindow::on_url_entry_changed));
    pStart_at->signal_changed().connect(sigc::mem_fun(this,&MainWindow::on_start_at_entry_changed));
}


void MainWindow::on_play_button_clicked() {
    std::cout << "Play button clicked" << std::endl;

}


void MainWindow::on_stop_button_clicked() {
    std::cout << "Play stop clicked" << std::endl;

}

void MainWindow::setup_anime_popover() {
    auto *pop_over = new Gtk::Popover();
    auto *vbox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
    auto *btn = new Gtk::ModelButton();
    btn->set_label("nartuto");
    btn->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &MainWindow::on_anime_selected), "naruto"));
    vbox->pack_start(*btn, true, true, 1);
    vbox->show_all();
    pop_over->add(*vbox);
    pop_over->set_position(Gtk::POS_BOTTOM);
    refBuilder->get_widget("animes_button", pAnime_pop_over_button);
    pAnime_pop_over_button->set_label("Anime");
    pAnime_pop_over_button->set_popover(*pop_over);
    std::cout << "Play stop clicked" << std::endl;
}

void MainWindow::on_anime_selected(const Glib::ustring &data) {
    std::cout << "Anime is " << data << std::endl;
}

void MainWindow::on_url_entry_changed() {
    std::cout<<"Url changed"<<std::endl;
}

void MainWindow::on_start_at_entry_changed() {
    std::cout<<"Start at changed"<<std::endl;
}

MainWindow::MainWindow(MainWindow const &window) {
    std::clog << "Main Window created!" << std::endl;
}


