
#ifndef ANIMEHD_UTILS_H
#define ANIMEHD_UTILS_H

#include "iostream"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/RegularExpression.h"


using namespace std;
using namespace Poco;


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

#endif //ANIMEHD_UTILS_H
