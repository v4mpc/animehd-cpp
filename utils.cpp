//
// Created by v4mpc on 6/15/21.
//

#include "utils.h"

using namespace Poco;
using namespace std;




bool path_exists(const string &path) {
    Poco::File path_string{path};
    return path_string.exists();
}


string get_config_path() {
    Poco::Path anime_path{get_anime_path(),"config.json"};
    return anime_path.toString();
}



string get_anime_path() {
    Poco::Path anime_path{Poco::Path::configHome()};
    return Poco::Path(anime_path,"animehd").toString();
}


bool create_dir(const string &path) {
    Poco::File dir_path(path);
    return dir_path.createDirectory();
}

int get_file_size(const string &path) {
    try {
        Poco::File file_path(path);
        return file_path.getSize();
    } catch (Poco::FileNotFoundException &e) {
        cout << "Standard exception: " << e.what() << endl;
        return 0;
    }

}


string convert_to_three_digits(string number) {
    while (number.length() != 3) {
        number = "0" + number;
        return number;
    }
}


string generate_anime_name(const string &url) {
    Poco::RegularExpression re1(R"(https://[a-z.0-9]+\/([a-z_]+)/)", Poco::RegularExpression::RE_CASELESS);
    std::vector<std::string> vec;
    RegularExpression::MatchVec posVec;
    re1.match(url, 0, posVec);
    if (posVec[1].length < 0)
        throw "Name_Not_Found";
    re1.split(url, 0, vec);
    std::cout<<vec[1]<<std::endl;
    return vec[1];
}


string generate_url(string url, string episode) {
    Poco::RegularExpression re1(R"((\d+)(\.mp4))", Poco::RegularExpression::RE_CASELESS);
    episode = episode + "$2";
    re1.subst(url, episode);
    return url;
}

string generate_episode_name(string &url) {
    Poco::RegularExpression re1(R"(https://[a-z.0-9]+\/([a-z_]+)/(.+))", Poco::RegularExpression::RE_CASELESS);
    std::vector<std::string> vec;
    RegularExpression::MatchVec posVec;
    re1.match(url, 0, posVec);
    if (posVec[2].length < 0) {
        throw "Could generate episode name";
    }
//    check if episode name is only numbers
    re1.split(url, 0, vec);
    std::string episode_string = vec[2];
    Poco::RegularExpression re2(R"(([a-z_0-9]+)(\.mp4))", Poco::RegularExpression::RE_CASELESS);
    std::vector<std::string> vec2;
    re2.split(episode_string, 0, vec2);
    std::cout << "am here " << vec2[1] << std::endl;
    if (is_number(vec2[1]))
        return vec[1] + "_" + vec2[1] + vec2[2];
    return vec[2];
};


bool is_number(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}


int get_remote_size(const string &host, const string &uri) {
    Net::HTTPSClientSession s(host);
    Net::HTTPRequest request(Net::HTTPRequest::HTTP_HEAD, uri);
    request.add("User-Agent", USER_AGENT);
    s.sendRequest(request);
    Net::HTTPResponse response;
    std::istream &rs = s.receiveResponse(response);
    if (response.getStatus() != Net::HTTPResponse::HTTP_OK)
        throw "Geting remote size return with non 200 status";
    return response.getContentLength64();


};

std::vector<string> generate_host_uri(string url) {
    Poco::RegularExpression re1(R"(https://([a-z.0-9]+)(/.+))", Poco::RegularExpression::RE_CASELESS);
    std::vector<std::string> vec;
    RegularExpression::MatchVec posVec;
    re1.match(url, 0, posVec);
    if (posVec[1].length < 0)
        throw "Name_Not_Found";
    re1.split(url, 0, vec);
    return vec;
}

int kb(const int &byt) {

    return (int) (byt / (SIZE_UNIT));
};

int mb(const int &byt) {

    return (int) (byt / (SIZE_UNIT * SIZE_UNIT));
};


string get_last_episode(const string &path) {
    Poco::File dir_name{path};
    std::vector<std::string> vec;
    dir_name.list(vec);
    if (vec.size() <= 0)
        return "0";
    std::sort(vec.begin(), vec.end());
    return vec.back();
}

void initialize_config(const string &path) {
    std::clog<<"Initializing config"<<endl;
    Config config;

    config.download_folder = "/home/v4mpc/Videos/testing2";
//    if download folder not exit create it
    if (!path_exists(config.download_folder)){
        std::clog<<config.download_folder<<" Does not exist. Creating..."<<std::endl;
        create_dir(config.download_folder);
    }
    if (!path_exists(path)){
        std::clog<<path<<" Anime config folder Does not exist. Creating..."<<std::endl;
        create_dir(path);
    }
    auto anime_file_path=Poco::Path(path,"config.json").toString();
    if(!path_exists(anime_file_path)){
        auto file_path=anime_file_path;
        std::clog<<path<<" Anime config.json file Does not exist. Creating..."<<std::endl;
        Poco::File (anime_file_path);
        save_config(file_path, config);
    }
};

void load_config(const string &path, Config &config) {
    Poco::Util::JSONConfiguration config_file;
    std::cout<<path<<std::endl;
    config_file.load(path);
    config.download_folder = config_file.getString("download_folder");
    std::string animes = config_file.getString("animes");
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(animes);
    Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();
    for (int i = 0; i < arr->size(); ++i) {
        Poco::JSON::Object::Ptr object = arr->getObject(i);
        ConfigAnime anime;
        anime.id = object->get("id").toString();
        anime.name = object->get("name").toString();
        anime.url = object->get("url").toString();
        anime.start_at = object->get("start_at").toString();
        config.animes.push_back(anime);

    }
}

void save_config(const string &path, Config &config) {

    Poco::JSON::Object object;
    Poco::JSON::Array arr;
    for (int i = 0; i < config.animes.size(); ++i) {
        Poco::JSON::Object arr_obj;
        arr_obj.set("id", config.animes[i].id);
        arr_obj.set("name", config.animes[i].name);
        arr_obj.set("url", config.animes[i].url);
        arr_obj.set("start_at", config.animes[i].start_at);
        arr.add(arr_obj);
    }
    Poco::Dynamic::Var value;
    value = config.download_folder;
    object.set("download_folder", value);
    object.set("animes", arr);
    ofstream out_file;
    out_file.open(path);
    if (!out_file.is_open())
        throw "Could not open file for write";
    object.stringify(out_file);
    out_file.close();
};


