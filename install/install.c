//
// Created by chorm on 2020-08-08.
//

#include <unistd.h>
#include <sys/stat.h>
#include <chmod-parse.h>

enum backup_mode{
    None,
    Simple,
    Existing,
    Numbered
};

enum create_mode{
    Single,
    IntoDirectory,
    CreateDirectory
};

int main(int argc,char** argv){
    uid_t uid = geteuid();
    gid_t gid = getegid();
    mode_t md = 0755;
    mode_t um = umask(0);
    enum backup_mode backup = None;
    enum create_mode mode = Single;
    _Bool strip = 0;
    const char* strip_prg = NULL;
    const char* target;

}
