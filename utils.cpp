//
// Created by v4mpc on 6/15/21.
//

#include "utils.h"
#include <gtkmm.h>
#include <Poco/Exception.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"

using namespace Poco;
using namespace std;

bool path_exists(const string &path) {
    return Glib::file_test(path, Glib::FileTest::FILE_TEST_EXISTS);
}


string get_config_path() {
    return Path::configHome();
}


string get_anime_path() {
    Poco::Path anime_path;
    anime_path.pushDirectory(Poco::Path::configHome());
    anime_path.pushDirectory("animehd");
    return anime_path.toString();
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

void load_config(const string &path, Config &config) {
    Poco::Util::JSONConfiguration config_file;
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

