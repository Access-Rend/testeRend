/*
 * Close-Source Project announce :
 * There's no license or other bullshit
 * Use this fucking tool, fuck your boss extremely when he let you test a program
 * What ever you do such as business or copyright, tobe honest I care more on your mom's boobs.
 * Author: Rend
 * 972809723@qq.com(China) rubbishrend@gmail.com(Global)
 */
#pragma once

#include <queue>
#include <vector>
#include <sys.hpp>
#include <str.hpp>

namespace tester{
    class instruction{
public:
        ~instruction() = default;
        virtual void execute() = 0;
        std::vector<std::string> object;
        int id, line;
        instruction() = default;
    };
    class i_new : public instruction{
        ~i_new() = default;
    public:
        i_new() = default;
        i_new(const std::vector<std::string> &);
        void execute() override;
    };
    class i_compare : public instruction{
        ~i_compare() = default;
    public:
        i_compare() = default;
        i_compare(const std::vector<std::string> &);
        void execute() override;
    };
    class i_run : public instruction{
        ~i_run() = default;
    public:
        i_run() = default;
        i_run(const std::vector<std::string> &);
        void execute() override;
    };
    class parser final {
        std::queue<instruction*> ins;
        parser() = delete;
        ~parser() = default;
        explicit parser(std::string &);
        void parse();
    };
}