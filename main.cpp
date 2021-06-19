
#include <iostream>
#include "MainWindow.h"
#include "utils.h"





int main(int argc, char *argv[]) {

//    std::string  url = "https://20.manga47.net/Jujutsu_Kaisen_TV/Jujutsu_Kaisen_TV_001.mp4";
//    std::string url2 ="https://ot.manga47.net/One_Piece_Dub/001.mp4";
//    auto config_path = get_anime_path();
//    initialize_config(config_path);



    MainWindow application=MainWindow();
    application.init(argc,argv);
    return EXIT_SUCCESS;
}