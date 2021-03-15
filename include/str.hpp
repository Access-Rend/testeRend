/*
 * Close-Source Project announce :
 * There's no license or other bullshit
 * Use this fucking tool, fuck your boss extremely when he let you test a program
 * What ever you do such as business or copyright, tobe honest I care more on your mom's boobs.
 * Author: Rend
 * 972809723@qq.com(China) rubbishrend@gmail.com(Global)
 */
#pragma once
#include <vector>
#include <string>

namespace str{
    std::vector<std::string> split(const std::string &);
    std::vector<std::string> split(const std::string &, const std::string &);
    std::string lower_case(const std::string &);
    std::string upper_case(const std::string &);
    std::string upper_first(const std::string &);
    std::string lower_first(const std::string &);
    bool path_char(const char &);
    bool is_path(const std::string &);
    bool path_compare(std::string , std::string );
    bool weak_equal(const std::string &, const std::string &);
    std::string to_dir_path(const std::string &);
    std::string to_file_path(const std::string &);
}