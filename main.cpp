
#include <iostream>
#include "MainWindow.h"
#include <map>
#include <vector>
#include "Poco/File.h"
#include "Poco/Path.h"
#include <algorithm>
#include "utils.h"

#include <fstream>




int main(int argc, char *argv[]) {

    std::string  url = "https://20.manga47.net/Jujutsu_Kaisen_TV/Jujutsu_Kaisen_TV_001.mp4";
    std::string url2 ="https://ot.manga47.net/One_Piece_Dub/001.mp4";

    Config config;

    load_config("../../config.json.bak",config);

    cout<<config.download_folder<<endl;
    cout<<config.animes.size()<<endl;






//    MainWindow application=MainWindow();
//    application.init(argc,argv);
    return EXIT_SUCCESS;
}