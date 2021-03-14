/*
 * Close-Source Project announce :
 * There's no license or other bullshit
 * Use this fucking tool, fuck your boss extremely when he let you test a program
 * What ever you do such as business or copyright, tobe honest I care more on your mom's boobs.
 * Author: Rend
 * 972809723@qq.com(China) rubbishrend@gmail.com(Global)
 */
#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <memory>
#include <vector>
#include <string>
#include <cstdio>
#include <str.hpp>

#ifdef _WIN32
#include <direct.h>        //for mkdir rmdir
#include <io.h>            //for access
#elif __linux__
#include <unistd.h>		//for mkdir rmdir
#include <sys/stat.h>	//for access
#include <dirent.h>		//for DIR remove
#endif

namespace sys {
    bool exist(std::string );
    namespace dir{
        bool create(std::string );
        bool remove(std::string );
    }
    namespace file{
        bool create(std::string );
        bool remove(std::string );
        std::string compare(const std::string , const std::string );
    }
}