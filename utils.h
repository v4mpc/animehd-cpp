
#ifndef ANIMEHD_UTILS_H
#define ANIMEHD_UTILS_H

#include "iostream"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/RegularExpression.h"
#include <algorithm>
#include <vector>
#include "Poco/Logger.h"
#include <Poco/Exception.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"
#include <fstream>
#include <gtkmm.h>



using namespace std;
using namespace Poco;


const int SIZE_UNIT = 1024;
const string USER_AGENT = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.120 Safari/537.36";

struct ConfigAnime {
    string id;
    string name;
    string url;
    string start_at;
};
struct Config {
    string download_folder;
    vector<ConfigAnime> animes;
};

string convert_to_three_digits(string number);

string generate_anime_name(const string &url);

string generate_url(string url, string episode);

string generate_episode_name(string &url);

bool path_exists(const string &path);

int kb(const int &byt);

int mb(const int &byt);

string to_episode_name(const string &anime_name, const string &episode_name);

string get_config_path();

string get_anime_path();

bool create_dir(const string &path);

int get_file_size(const string &path);

bool is_number(const std::string &s);

std::vector<string> generate_host_uri(string url);

int get_remote_size(const string &host, const string &uri);


string get_last_episode(const string &path);

void initialize_config();

string to_percentatge(const int &numerator, const int &denominator);

void load_config(const string &path, Config &config);

void save_config(const string &path, Config &config);

void initialize_config(const string &path);


bool create_dir(const string &path);

bool file_exists(const string &path,const string &file_name);

bool dir_exists(const string &path);



#endif //ANIMEHD_UTILS_H
