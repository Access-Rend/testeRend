#include <../include/parser.hpp>

namespace tester{
    i_new::i_new(const std::vector<std::string> &args) {
        try{
            if (args.empty())
                throw std::invalid_argument("syntax error.");
            if (args[0] != "dir" && args[0] != "file")
                throw std::invalid_argument("syntax error.");
            for (auto &x:args) {
                if (!str::is_path(x))
                    throw std::invalid_argument("\"" + x + "\" is not a correct path.");
                if (!sys::exist(x)) {
                    if (args[0] == "dir")
                        sys::dir::create(x);
                    else if (args[0] == "file")
                        sys::file::create(x);
                    continue;
                }
            }
            object = args;
        }
        catch (std::exception &e) {
            throw std::logic_error("compiling: line "+std::to_string(line)+": "+e.what());
        }
    }
    i_run::i_run(const std::vector<std::string> &args) {
        try{
            if (args.empty())
                throw std::invalid_argument("syntax error.");
            if (!sys::exist(args[0]))
                throw std::invalid_argument("\"" + args[0] + "\" is not exist.");
            object = args;
        }
        catch (std::exception &e) {
            throw std::logic_error("compiling: line "+std::to_string(line)+": "+e.what());
        }
    }
    i_compare::i_compare(const std::vector<std::string> &args) {
        try{
            if (args.empty() || args.size() != 2)
                throw std::invalid_argument("syntax error.");
            for (auto &file : args)
                if (!sys::exist(file))
                    throw std::invalid_argument("\"" + file + "\" is not exist.");
            object = args;
        }
        catch (std::exception &e) {
            throw std::logic_error("compiling: line "+std::to_string(line)+": "+e.what());
        }
    }
    void i_new::execute() {
        try{
            if(object[0]=="dir"){
                for(int i = 1; i < object.size() ; i++) {
                    sys::dir::create(object[i]);
                    std::cout<<"creating \"" + object[i] + "\" successfully."<<std::endl;
                }
            }
            else if(object[0]=="file"){
                for(int i = 1; i < object.size() ; i++){
                    sys::file::create(object[i]);
                    std::cout<<"creating \"" + object[i] + "\" successfully."<<std::endl;
                }
            }

        }
        catch(const std::exception &e){
            throw std::logic_error("executing: line"+std::to_string(line)+": "+e.what());
        }
    }
    void i_run::execute() {
        try{

        }
        catch (const std::exception &e) {
            throw std::logic_error("executing: line"+std::to_string(line)+": "+e.what());
        }
    }
    void i_compare::execute() {
        try{
            std::cout<<sys::file::compare(object[0],object[1])<<std::endl;
        }
        catch (const std::exception &e) {
            throw std::logic_error("executing: line"+std::to_string(line)+": "+e.what());
        }
    }
}

namespace tester {
    parser::parser(std::string &path) {
        try {
            path = str::to_dir_path(path);

            if (!sys::exist(path))
                throw std::invalid_argument("path \"" + path + "\" not exist.");

            std::ifstream ifs(path);
            if (!ifs.is_open())
                throw std::runtime_error("open \"" + path + "\" failed.");

            std::string s;
            int line = 0;
            while (std::getline(ifs, s)) {
                static std::vector<std::string> v_s = str::split(s);
                ++line;

                if (v_s.empty() || s[0] == '#')
                    continue;

                std::vector<std::string> args(v_s.begin() + 1, v_s.end());
                if (false) {}
                else if (v_s[0] == "new")
                    ins.push(new tester::i_new(args));
                else if (v_s[0] == "run")
                    ins.push(new tester::i_run(args));
                else if (v_s[0] == "compare")
                    ins.push(new tester::i_compare(args));
                else
                    throw std::invalid_argument("in line " + std::to_string(line) + ": no such grammar.");
            }
        }
        catch(const std::exception &e){
            throw std::invalid_argument(std::string("compiling: ") + e.what());
        }
    }
    void parser::parse() {
        try{
            while (!ins.empty()) {
                auto &i = ins.front();
                i->execute();
            }
        }
        catch (std::exception &e) {
            throw e;
        }
    }
}
