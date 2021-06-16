
#include <iostream>
#include "MainWindow.h"
#include <map>
#include <vector>
#include "Poco/File.h"
#include "Poco/Path.h"
#include <algorithm>
#include "Poco/RegularExpression.h"

#include "utils.h"




int main(int argc, char *argv[]) {

    std::string  url = "https://20.manga47.net/Jujutsu_Kaisen_TV/Jujutsu_Kaisen_TV_001.mp4";
    std::string url2 ="https://ot.manga47.net/One_Piece_Dub/001.mp4";

//    Poco::File dir_name {"/home/v4mpc/Videos/testing/Boruto_Dub"};
//    std::vector<std::string> vec;
//    dir_name.list(vec);
//    std::sort(vec.begin(),vec.end());
    std::cout<<get_last_episode("/home/v4mpc/Videos/testing/Dragon_Ball_Super_Dub");




    std::map<std::string,std::vector<std::string>> user_data {
            {"download_folder",{"/home/v4mpc/Videos/testing"}},
            {"animes",{"/home/v4mpc/Videos/testing"}}
    };
//    MainWindow application=MainWindow();
//    application.init(argc,argv);
    return EXIT_SUCCESS;
}