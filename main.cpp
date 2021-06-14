#include <gtkmm.h>
#include <iostream>

int main(int argc, char *argv[]) {
    Gtk::Main kit(argc, argv);
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
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

    Gtk::ApplicationWindow *pWindow = nullptr;
    refBuilder->get_widget("main_window", pWindow);
    Gtk::Main::run(*pWindow);


    return EXIT_SUCCESS;
}