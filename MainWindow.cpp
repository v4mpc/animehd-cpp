
#include <iostream>
#include "MainWindow.h"
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

//TODO: default download folder should be home/Videos/Animes
using namespace Poco::JSON;

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
    refBuilder->get_widget("main_window", pWindow);
    Gtk::Main::run(*pWindow);

    return 1;
}



void MainWindow::on_properties_button_clicked() {
    std::cout << "Properties button clicked" << std::endl;
    std::cout<<"User config dir is "<< Glib::get_user_config_dir()<<std::endl;
    std::string json = "{ \"test\" : { \"property\" : \"value\" } }";
    Parser parser;
    Poco::Dynamic::Var result = parser.parse(json);
    Object::Ptr object = result.extract<Object::Ptr>();
    Poco::Dynamic::Var test = object->get("test");
    object = test.extract<Object::Ptr>();
    test = object->get("property");
    std::string value = test.convert<std::string>();
    std::cout<<value<<std::endl;
}

void MainWindow::connect_all_signals(){
    refBuilder->get_widget("properties_button", pProperties_button);
    pProperties_button->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_properties_button_clicked));
    refBuilder->get_widget("stop_button",pStop_button);
    pStop_button->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_stop_button_clicked));
}


void MainWindow::on_play_button_clicked() {
    std::cout<<"Play button clicked"<<std::endl;

}


void MainWindow::on_stop_button_clicked() {
    std::cout<<"Play stop clicked"<<std::endl;

}

