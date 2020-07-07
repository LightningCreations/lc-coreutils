//
// Created by chorm on 2020-07-06.
//

#include "select_hash.h"

#include <cstddef>
#include <cstdio>
#include <cctype>
#include <cstring>

#include <unordered_map>
#include <string_view>
#include <string>
#include <iostream>
#include <fstream>

#include <vector>
#include <algorithm>



struct KnownHashFn{
    const char* name;
    std::size_t outsz;
    void(*hash_fn)(char* out,std::FILE* f);
};

static std::unordered_map<std::string_view,KnownHashFn> map{};

extern"C" void register_known_hash(const char* name,size_t outSz,void(*apply)(char[outSz],std::FILE*)){
    map.emplace(name,KnownHashFn{name,outSz,apply});
}

enum class FormatErrorMode{
    Silent,
    Warn,
    Fatal
};

enum class CheckMode{
    Verbose,
    Quiet,
    Status
};

bool check(std::istream& from,char l_sep,const char* _sp,bool ignore_missing,CheckMode chkmd,const KnownHashFn* fn){
    std::string line;
    std::string_view sp{_sp};
    bool ok{true};
    while(std::getline(from,line,l_sep)) {
        auto lbegin = line.begin();
        auto lend = line.end();
        auto hend = line.begin()+line.find(sp);
        auto fbegin = hend+sp.length();
        FILE* f = fopen(&*fbegin,"r");
        if(!f){
            if(ignore_missing)
                continue;
            else{
                if(chkmd!=CheckMode::Status)
                    std::cout << &*fbegin << ": NOT FOUND" << std::endl;
                ok = false;
            }
        }
        std::transform(lbegin,hend,lbegin,[](char c){return std::tolower(c);});
        std::string hash{};
        hash.resize(fn->outsz);
        fn->hash_fn(hash.data(),f);
        std::fclose(f);
        if(!std::equal(lbegin,hend,hash.begin(),hash.end())){
            if(chkmd!=CheckMode::Status)
                std::cout << &*fbegin << ": Hash Mismatch" << std::endl;
            ok = false;
        }
        if(chkmd==CheckMode::Verbose)
            std::cout << &*fbegin << ": OK" << std::endl;
    }
    return ok;
}

std::string escape_name(std::string st){
    return std::move(st); // For now, lets not deal with shell escaping names
}

void hash(const std::string& fname,const char* sp,bool escape_fname,const KnownHashFn* fn){
    std::string out_hash{};
    FILE* open = fopen(fname.c_str(),"r");
    if(!open)
        return;
    out_hash.resize(fn->outsz);
    fn->hash_fn(out_hash.data(),open);
    fclose(open);
    std::cout << out_hash << sp <<  (escape_fname?escape_name(fname):fname);
}

int main(int argc,char** argv){
    register_sha_hashes();
    char* end;
    const KnownHashFn* fn = nullptr;
    std::vector<std::string> files{};
    bool escape_strings{};
    bool done_opts{};
    bool check{};
    char l_sep{'\n'};
    const char* sp{"  "};
    bool ignore_missing{};
    FormatErrorMode err_mode{};
    CheckMode ck_mode{CheckMode::Verbose};
    std::string_view name{argv[0]};
    if(auto pos = name.find("sum");pos!=std::string_view::npos){
        name.substr(0,pos);
        pos = name.find_last_of('/');
        if(pos!=std::string_view::npos)
            name = name.substr(pos);
        if(map.count(name))
            fn = &map[name];
    }
    for(char** c = argv+1;c<(argv+argc);c++){
        const char* opt = *c;
        if(done_opts)
            files.emplace_back(opt);
        else if(*opt=='-'){
            opt++;
            if(!*opt){
                break;
            }else {
                if(*opt=='-'){
                    opt++;
                    if(strcmp(opt,"binary")==0)
                        sp = "*";
                    else if(strcmp(opt,"zero")==0) {
                        l_sep = 0;
                        escape_strings = true;
                    }else if(strcmp(opt,"text")==0)
                        sp = "  ";
                    else if(strcmp(opt,"ignore-missing")==0)
                        ignore_missing = true;
                    else if(strcmp(opt,"check")==0)
                        check = true;
                    else if(strcmp(opt,"quiet")==0)
                        ck_mode = CheckMode::Quiet;
                    else if(strcmp(opt,"status")==0)
                        ck_mode = CheckMode::Status;
                    else if(strcmp(opt,"strict")==0)
                        err_mode = FormatErrorMode::Fatal;
                    else if(strcmp(opt,"warn")==0)
                        err_mode = FormatErrorMode::Warn;
                    else if(strcmp(opt,"version")==0){
                        std::cout << "Lightning Creations " << argv[0] << " version 0.1" << std::endl
                            << "Part of lc-coreutils, included in lcnix" << std::endl
                            << "This program is a free software, distributed under the Terms of the GNU General Public License v3, or (at your option) any later version" << std::endl
                            << "This program is provided on an AS IS Basis, without any warranty of any kind, any implied warranties which may otherwise apply" << std::endl
                            << "If you have not recieved a copy of the GNU General Public License along with this program, you may view it on the GNU Website" << std::endl
                            << "\thttps://www.gnu.org/licenses/gpl-3.0.en.html (html)" << std::endl
                            << "\thttps://www.gnu.org/licenses/gpl-3.0.txt (Plain Text)" << std::endl;
                        return 0;
                    }else if(strcmp(opt,"help")==0){
                        std::cout << "Usage: " << argv[0] << "[OPTIONS]... [FILES]..." << std::endl
                                  << "Valid Options: " << std::endl
                                  << "\t--binary, -b: Output or read the hashes in binary format" << std::endl
                                  << "\t--text, -t: Undoes the effect of --binary" << std::endl
                                  << "\t--zero, -z: Outputs a NUL character between lines, instead of a newline." << std::endl
                                  << "\t--check, -c: Reads hashes from the given files, and verifies files in the current directory, instead of hashing the input files. " << std::endl
                                  << "\t--help: Print this message and exit" << std::endl
                                  << "\t--version: Print version information and exit" << std::endl
                                  << "\t--algorithm <algorithm>: Selects the algorithm to use. Not available when invoked in the form <algorithm>sum" << std::endl
                                  << "\t-: Treated as a file, not an option. If any file is -, or all files are omitted, stdin is used" << std::endl
                                  << "\tWhen Checking Hashes, the following options apply" << std::endl
                                  << "\t\t--ignore-missing: If a named file does not exist, silently ignore it instead of erroring" << std::endl
                                  << "\t\t--quiet: Only print status messages for mismatching files" << std::endl
                                  << "\t\t--status: Do not print status messages" << std::endl
                                  << "\t\t--warn, -w: Warn if an input file is in an invalid format" << std::endl
                                  << "\t\t--strict: Fail if an input file is in an invalid format" << std::endl;
                        return 0;
                    }else if(strncmp(opt,"algorithm",9)==0){
                        const char* algorithm{};
                        opt+=9;
                        if(!*opt)
                            algorithm = *++c;
                        else if(*opt++=='=')
                            algorithm = opt;
                        if(!algorithm){
                            std::cout << "Usage: " << argv[0] << "[OPTIONS]... [FILES]..." << std::endl
                                      << "Valid Options: " << std::endl
                                      << "\t--binary, -b: Output or read the hashes in binary format" << std::endl
                                      << "\t--text, -t: Undoes the effect of --binary" << std::endl
                                      << "\t--zero, -z: Outputs a NUL character between lines, instead of a newline." << std::endl
                                      << "\t--check, -c: Reads hashes from the given files, and verifies files in the current directory, instead of hashing the input files. " << std::endl
                                      << "\t--help: Print this message and exit" << std::endl
                                      << "\t--version: Print version information and exit" << std::endl
                                      << "\t--algorithm <algorithm>: Selects the algorithm to use. Not available when invoked in the form <algorithm>sum" << std::endl
                                      << "\t-: Treated as a file, not an option. If any file is -, or all files are omitted, stdin is used"
                                      << "\tWhen Checking Hashes, the following options apply" << std::endl
                                      << "\t\t--ignore-missing: If a named file does not exist, silently ignore it instead of erroring" << std::endl
                                      << "\t\t--quiet: Only print status messages for mismatching files" << std::endl
                                      << "\t\t--status: Do not print status messages" << std::endl
                                      << "\t\t--warn, -w: Warn if an input file is in an invalid format" << std::endl
                                      << "\t\t--strict: Fail if an input file is in an invalid format" << std::endl;
                            return 1;
                        }

                        if(fn){
                            std::cout << "Cannot select algorithm: "<< algorithm << fn->name << " is already selected" << std::endl;
                            return 1;
                        }
                        if(map.count(algorithm))
                            fn = &map[algorithm];
                        else{
                            std::cout << "Unknown Algorithm: " << algorithm << std::endl;
                            return 1;
                        }
                    }else{
                        std::cout << "Usage: " << argv[0] << "[OPTIONS]... [FILES]..." << std::endl
                                  << "Valid Options: " << std::endl
                                  << "\t--binary, -b: Output or read the hashes in binary format" << std::endl
                                  << "\t--text, -t: Undoes the effect of --binary" << std::endl
                                  << "\t--zero, -z: Outputs a NUL character between lines, instead of a newline." << std::endl
                                  << "\t--check, -c: Reads hashes from the given files, and verifies files in the current directory, instead of hashing the input files. " << std::endl
                                  << "\t--help: Print this message and exit" << std::endl
                                  << "\t--version: Print version information and exit" << std::endl
                                  << "\t--algorithm <algorithm>: Selects the algorithm to use. Not available when invoked in the form <algorithm>sum" << std::endl
                                  << "\t-: Treated as a file, not an option. If any file is -, or all files are omitted, stdin is used"
                                  << "\tWhen Checking Hashes, the following options apply" << std::endl
                                  << "\t\t--ignore-missing: If a named file does not exist, silently ignore it instead of erroring" << std::endl
                                  << "\t\t--quiet: Only print status messages for mismatching files" << std::endl
                                  << "\t\t--status: Do not print status messages" << std::endl
                                  << "\t\t--warn, -w: Warn if an input file is in an invalid format" << std::endl
                                  << "\t\t--strict: Fail if an input file is in an invalid format" << std::endl;
                        return 1;
                    }
                }else{
                    for(;*opt;opt++){
                        char c0 = *opt;
                        if(c0=='b')
                            sp = "*";
                        else if(c0=='t')
                            sp = "  ";
                        else if(c0=='z')
                            l_sep = 0;
                        else if(c0=='c')
                            check = true;
                        else{
                            std::cout << "Usage: " << argv[0] << "[OPTIONS]... [FILES]..." << std::endl
                                      << "Valid Options: " << std::endl
                                      << "\t--binary, -b: Output or read the hashes in binary format" << std::endl
                                      << "\t--text, -t: Undoes the effect of --binary" << std::endl
                                      << "\t--zero, -z: Outputs a NUL character between lines, instead of a newline." << std::endl
                                      << "\t--check, -c: Reads hashes from the given files, and verifies files in the current directory, instead of hashing the input files. " << std::endl
                                      << "\t--help: Print this message and exit" << std::endl
                                      << "\t--version: Print version information and exit" << std::endl
                                      << "\t--algorithm <algorithm>: Selects the algorithm to use. Not available when invoked in the form <algorithm>sum" << std::endl
                                      << "\t-: Treated as a file, not an option. Must appear without any other files. When FILE is - or omitted, reads from stdin"
                                      << "\tWhen Checking Hashes, the following options apply" << std::endl
                                      << "\t\t--ignore-missing: If a named file does not exist, silently ignore it instead of erroring" << std::endl
                                      << "\t\t--quiet: Only print status messages for mismatching files" << std::endl
                                      << "\t\t--status: Do not print status messages" << std::endl
                                      << "\t\t--warn, -w: Warn if an input file is in an invalid format" << std::endl
                                      << "\t\t--strict: Fail if an input file is in an invalid format" << std::endl;
                            return 1;
                        }
                    }

                }
            }
        }else{
            files.emplace_back(opt);
            done_opts = false;
        }
    }

    if(!fn){
        std::cout << "Unrecognized or no algorithm specified. Please specify --algorithm <algorithm>" <<std::endl;
        return 1;
    }

    if(files.empty()){
        if(!check) {
            std::string out;
            out.resize(fn->outsz);
            fn->hash_fn(out.data(),stdin);
            std::cout << out << std::endl;
        }else{
            if(!::check(std::cin,l_sep,sp,ignore_missing,ck_mode,fn))
                return 1;
            else
                return 0;
        }
    }else for(const auto& file: files){
        if(!check) {
            FILE* f = std::fopen(file.c_str(),"r");
            if(!f) {
                std::cout << "File " << file << "was not found. Exiting. "<<std::endl;
                return 1;
            }
            std::string out;
            out.resize(fn->outsz);
            fn->hash_fn(out.data(), f);
            std::cout << out << sp << file << l_sep;
        }else{
            std::ifstream fstrm{file};
            if(!::check(fstrm,l_sep,sp,ignore_missing,ck_mode,fn))
                return 1;
            else
                continue;
        }
    }
}