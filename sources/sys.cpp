#include <sys.hpp>

#ifdef _WIN32
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#define RMDIR(a) _rmdir((a))
#define delimiter '\\'
#elif __linux__
#define ACCESS access
#define MKDIR(a) mkdir((a),0755)
#define RMDIR(a) rmdir((a))
#define delimiter '/'
#endif
bool sys::exist(std::string path) {
    path = str::to_platform_path(path);
    return ACCESS(path.c_str(), 0) == 0;
}

namespace sys::file{
    std::string compare(std::string file_1, std::string file_2){
        file_1 = str::to_platform_path(file_1); file_2 = str::to_platform_path(file_2);
        std::ifstream ifs_1(file_1), ifs_2(file_2);
        std::string l1,l2;
        int line = 0;
        while(getline(ifs_1,l1) && getline(ifs_2,l2)){
            ++line;
            if(l1!=l2){
                ifs_1.close(); ifs_2.close();
                return "in line " + std::to_string(line) + ": \n"
                       + "\t" + file_1 + ": " + l1 + "\n"
                       + "\t" + file_2 + ": " + l2 + "\n";
            }

        }
        ifs_1.close(); ifs_2.close();
        return "nothing different.";
    }
    bool create(std::string path){
        path = str::to_platform_path(path);
        std::ofstream ofs;
        for(int i = path.size()-1; i>=0 ; i--)
            if(path[i]==delimiter){
                sys::dir::create(path.substr(0,i));
                ofs.open(path);
                break;
            }
        ofs.close();
        ofs.open(path);
        if(!ofs.is_open()){
            ofs.close();
            return false;
        }
        ofs.close();
        return true;
    }
    bool rm(std::string path) {
        path = str::to_platform_path(path);
        return remove(path)==0;
    }
    bool remove(std::string path){
        return rm(path);
    }
}

namespace sys::dir {
    bool create(std::string path) { // 存在则不建立
        path = str::to_platform_path(path);
        for (int i = 0; i < path.size(); i++) {
            if (path[i] != delimiter)
                continue;
            std::string tmp = path.substr(0, i + 1).c_str();
            int status = ACCESS(tmp.c_str(), 0);
            if (status != 0) {
                status = MKDIR(tmp.c_str());
                if (status != 0)
                    return false;
            }
        }
        return true;
    }

    bool rm(std::string path) {
        std::string strPath = str::to_platform_path(path);
#ifdef _WIN32
        struct _finddata_t fb;
        if (strPath.at(strPath.length() - 1) != '\\' || strPath.at(strPath.length() - 1) != '/')
            strPath.append("\\");
        std::string findPath = strPath + "*";
        intptr_t handle;
        handle = _findfirst(findPath.c_str(), &fb);
        if (handle != -1L) {
            std::string pathTemp;
            do {
                if (strcmp(fb.name, "..") != 0 && strcmp(fb.name, ".") != 0) {
                    pathTemp.clear();
                    pathTemp = strPath + std::string(fb.name);
                    if (fb.attrib == _A_SUBDIR)//_A_SUBDIR=16
                        rm(pathTemp.c_str());
                    else
                        remove(pathTemp.c_str());
                }
            }
            while (0 == _findnext(handle, &fb));
            _findclose(handle);
        }
        return rm(strPath.c_str()) == 0 ? true : false;

#elif __linux__
    if (strPath.at(strPath.length() - 1) != '\\' || strPath.at(strPath.length() - 1) != '/')
    strPath.append("/");
	DIR *d = opendir(strPath.c_str());
	if (d != NULL) {
		struct dirent *dt = NULL;
		while (dt = readdir(d)) {
			if (std::strcmp(dt->d_name, "..")!=0 && strcmp(dt->d_name, ".")!=0) {
				struct stat st;
				std::string fileName;
				fileName = strPath + std::string(dt->d_name);
				stat(fileName.c_str(), &st);
				if (S_ISDIR(st.st_mode))
					rm(fileName);
				else
					remove(fileName.c_str());
			}
		}
		closedir(d);
	}
	return rm(strPath.c_str())==0?true:false;
#endif
    }
    bool remove(std::string path){
        return sys::dir::rm(path);
    }
}
