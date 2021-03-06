
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

    auto config_path = get_config_path();
    auto config_dir_path = get_anime_path();
    initialize_config(config_dir_path);
    load_config(config_path, config);
    connect_all_signals();
    setup_anime_popover();
    refBuilder->get_widget("main_window", pWindow);
    refBuilder->get_widget("properties_dialog", pProperties_dialog);
    refBuilder->get_widget("anime_list_tree_view", pAnime_list_tree_view);
    refListStore = Gtk::ListStore::create(m_Columns);
    pAnime_list_tree_view->set_model(refListStore);
    pAnime_list_tree_view->append_column("Id", m_Columns.m_col_id);
    pAnime_list_tree_view->append_column_editable("Name", m_Columns.m_col_name);
    pAnime_list_tree_view->append_column_editable("start at", m_Columns.m_col_start_at);
    refAnime_list_tree_view_Selection = pAnime_list_tree_view->get_selection();
    refAnime_list_tree_view_Selection->signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_anime_list_view_selection_changed)
    );
    pProperties_dialog->set_transient_for(*pWindow);
    pProperties_dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

    refBuilder->get_widget("tree_view",pDownloads_list_tree_view);

    pTree_view_modal_columns.add(tvm_col_id);
    pTree_view_modal_columns.add(tvm_col_name);
    pTree_view_modal_columns.add(tvm_col_progress);
    pTree_view_modal_columns.add(tvm_col_downloaded);
    pTree_view_modal_columns.add(tvm_col_speed);
    pTree_view_modal_columns.add(tvm_col_status);
    refDownloadsListStore=Gtk::ListStore::create(pTree_view_modal_columns);

    pDownloads_list_tree_view->set_model(refDownloadsListStore);

    pDownloads_list_tree_view->append_column("Id",tvm_col_id);
    pDownloads_list_tree_view->append_column("Name",tvm_col_name);
    auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
    pDownloads_list_tree_view->append_column("Progress", *cell);
    auto pColumn =pDownloads_list_tree_view->get_column(2);
    if(pColumn)
    {
        pColumn->add_attribute(cell->property_value(), tvm_col_progress);
    }
//    pDownloads_list_tree_view->append_column("progress",tvm_col_progress);
    pDownloads_list_tree_view->append_column("Downloaded",tvm_col_downloaded);
    pDownloads_list_tree_view->append_column("Speed",tvm_col_speed);
    pDownloads_list_tree_view->append_column("Status",tvm_col_status);
    auto name_column=pDownloads_list_tree_view->get_column(1);
    name_column->set_fixed_width(200);
    auto download_column=pDownloads_list_tree_view->get_column(3);
    download_column->set_fixed_width(100);

    auto progress_column=pDownloads_list_tree_view->get_column(2);
    progress_column->set_fixed_width(120);

    //Fill the TreeView's model
    auto row = *(refDownloadsListStore->append());
    row[tvm_col_id] = "90";
    row[tvm_col_name] = "Dr_Stone_Stone_Wars_Dub_999.mp4";
    row[tvm_col_progress] = 100;
    row[tvm_col_downloaded] = "900MB of 900MB";
    row[tvm_col_speed] = "249Mbps";
    row[tvm_col_status] = "FETCHING META";



    for (int i = 0; i < config.animes.size(); ++i) {
        Gtk::TreeModel::iterator iter = refListStore->append();
        Gtk::TreeModel::Row row = *iter;
        row[m_Columns.m_col_id] = config.animes[i].id;
        row[m_Columns.m_col_name] = config.animes[i].name;
        row[m_Columns.m_col_url] = config.animes[i].url;
        row[m_Columns.m_col_start_at] = config.animes[i].start_at;
    }



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
        pStart_at_entry->set_text(row[m_Columns.m_col_start_at]);
        pAnime_form->show();
    } else{
        pAnime_form->hide();
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
            typedef Gtk::TreeModel::Children type_children; //minimise code length.
            type_children children = refListStore->children();
            config.animes.clear();
//            TODO::try to optimize to many for loops
            vector<type_children::iterator> to_remove;
            for(type_children::iterator iter = children.begin();
                iter != children.end(); ++iter)
            {
                Gtk::TreeModel::Row row = *iter;
                if(row[m_Columns.m_col_name]=="Null"){
//                    refListStore->erase(iter);
                    std::cout<<"its null anime"<<std::endl;
                    to_remove.push_back(iter);
                }
            }

            for (int i = 0; i < to_remove.size(); ++i) {
                refListStore->erase(to_remove[i]);
            }
            type_children children_new = refListStore->children();
            for(type_children::iterator iter = children_new.begin();
                iter != children_new.end(); ++iter)
            {
                Gtk::TreeModel::Row row = *iter;
                ConfigAnime new_anime;
                new_anime.id=static_cast<Glib::ustring>(row[m_Columns.m_col_id]);
                new_anime.name=static_cast<Glib::ustring>(row[m_Columns.m_col_name]);
                new_anime.url= static_cast<Glib::ustring>(row[m_Columns.m_col_url])  ;
                new_anime.start_at= static_cast<Glib::ustring>(row[m_Columns.m_col_start_at]);
                config.animes.push_back(new_anime);
            }
            auto config_path = get_config_path();
            std::cout<<"Saving config"<<std::endl;
            save_config(config_path,config);
            setup_anime_popover();
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
    refBuilder->get_widget("id_entry", pId_entry);
    refBuilder->get_widget("url_entry", pUrl_entry);
    refBuilder->get_widget("anime_form",pAnime_form);
    refBuilder->get_widget("start_at_entry", pStart_at_entry);
    pStop_button->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_stop_button_clicked));
    pUrl_entry->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_url_entry_changed));
    pStart_at_entry->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_start_at_entry_changed));
    refBuilder->get_widget("add_anime_button",pAdd_anime_button);
    pAdd_anime_button->signal_clicked().connect(sigc::mem_fun(this,&MainWindow::on_add_anime_button_clicked));
    refBuilder->get_widget("remove_anime_button",pRemove_anime_button);
    pRemove_anime_button->signal_clicked().connect(sigc::mem_fun(this,&MainWindow::on_remove_anime_button_clicked));
}

void MainWindow::on_add_anime_button_clicked(){
    std::cout<<"add anime button clicked"<<std::endl;
    auto anime_size=refListStore->children().size();
    Gtk::TreeModel::iterator iter = refListStore->append();
    Gtk::TreeModel::Row row = *iter;

    ++anime_size;
    row[m_Columns.m_col_id] =static_cast<Glib::ustring>(to_string(anime_size));
    row[m_Columns.m_col_name] ="Null" ;
    row[m_Columns.m_col_url] ="https://ot.manga47.net/Null/001.mp4" ;
    row[m_Columns.m_col_start_at] = "1";
    if(iter)
        refAnime_list_tree_view_Selection->select(row);
}

void MainWindow::on_remove_anime_button_clicked(){
    std::cout<<"remove anime button clicked"<<std::endl;
    Gtk::TreeModel::iterator iter = refAnime_list_tree_view_Selection->get_selected();
    if (iter) //If anything is selected
    {
        refListStore->erase(iter);
    }
}

void MainWindow::on_play_button_clicked() {
    std::cout << "Play button clicked" << std::endl;
}


void MainWindow::on_stop_button_clicked() {
    std::cout << "Play stop clicked" << std::endl;
}

void MainWindow::setup_anime_popover() {
//   TODO:: make all pointers here as smart Pointers
    auto *pop_over = new Gtk::Popover();
    auto *vbox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
    for (int i = 0; i < config.animes.size(); ++i) {
        auto *btn = new Gtk::ModelButton();
        btn->set_label(config.animes[i].name);
        btn->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &MainWindow::on_anime_selected),config.animes[i].name ));
        vbox->pack_start(*btn, true, true, 1);
    }
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
    std::cout << "Url changed" << std::endl;
    auto url = pUrl_entry->get_text();
    if (url.empty()) {
        std::cout << "No text" << std::endl;
        return;
    }
    Gtk::TreeModel::iterator iter = refAnime_list_tree_view_Selection->get_selected();
    if (iter) //If anything is selected
    {
        std::cout << "setting row" << std::endl;
        Gtk::TreeModel::Row row = *iter;
        row[m_Columns.m_col_name] = static_cast<Glib::ustring>(generate_anime_name(url));
        row[m_Columns.m_col_url] = url;
    }
}

void MainWindow::on_start_at_entry_changed() {
    std::cout << "Start at changed" << std::endl;
    std::cout << "Url changed" << std::endl;
    auto start_at = pStart_at_entry->get_text();
    if (start_at.empty()) {
        std::cout << "No text" << std::endl;
        return;
    }
    Gtk::TreeModel::iterator iter = refAnime_list_tree_view_Selection->get_selected();
    if (iter) //If anything is selected
    {
        std::cout << "setting row" << std::endl;
        Gtk::TreeModel::Row row = *iter;
        row[m_Columns.m_col_start_at] = start_at;
//        TODO::should dispatch a thread to go add write the io so as to not block ui whe animes scale
//when write is complete should emit a signal
        for (int i = 0; i < config.animes.size(); ++i) {
            if (config.animes[i].id==row[m_Columns.m_col_id]){
                std::cout<<"found the id"<<std::endl;
            }
        }

    }
}

MainWindow::MainWindow(MainWindow const &window) {
    std::clog << "Main Window created!" << std::endl;
}


