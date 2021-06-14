
#ifndef ANIMEHD_UTILS_H
#define ANIMEHD_UTILS_H

#include "iostream"

using namespace std;

string get_user_config_dir();

void create_folder(const string &folder_location, const string &folder_name);

string convert_to_three_digits(string number);

string generate_anime_name(const string &url);

string generate_url(const string &url, const string &episode);

string generate_episode_name(const string &url);

int kb(const int &byt);

int mb(const int &byt);

int get_remote_size(const string &url);

int get_local_size(const string &folder_name, const string &file_name);

string to_episode_name(const string &anime_name, const string &episode_name);

#endif //ANIMEHD_UTILS_H
