
#include <iostream>
#include "MainWindow.h"
#include <map>
#include <vector>
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/RegularExpression.h"

#include "utils.h"




int main(int argc, char *argv[]) {

    std::string  url = "https://20.manga47.net/Jujutsu_Kaisen_TV/Jujutsu_Kaisen_TV_001.mp4";
    std::string url2 ="https://ot.manga47.net/One_Piece_Dub/001.mp4";
    std::vector<string> host= generate_host_uri(url);
    std::cout<<host[1]<<"==="<<host[2] <<std::endl;
    std::cout<<get_remote_size(host[1],host[2])<<std::endl;



    std::map<std::string,std::vector<std::string>> user_data {
            {"download_folder",{"/home/v4mpc/Videos/testing"}},
            {"animes",{"/home/v4mpc/Videos/testing"}}
    };
//    MainWindow application=MainWindow();
//    application.init(argc,argv);
    return EXIT_SUCCESS;
}