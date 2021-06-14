
#include <iostream>
#include "MainWindow.h"


MainWindow::MainWindow() {
    std::clog << "Main Window created!"<<std::endl;

};

MainWindow::~MainWindow() {
    std::clog << "Main Window destroyed!"<<std::endl;
};

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
    Gtk::Main::run(*pWindow);
}

