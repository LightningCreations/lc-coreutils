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
    const char* HELP =
            "Usage: install [OPTIONS]... [-T] SOURCE DESTINATION\n"
            "\tor: install [OPTIONS]... SOURCE... DIRECTORY\n"
            "\tor: install [OPTIONS]... -t DIRECTORY SOURCE...\n"
            "\tor: install [OPTIONS]... -d DIRECTORY\n"
            "Installs programs (which are often just compiled), to a given destination.\n"
            "install is not a package manager frontend or backend. If you are installing premade packages, you should be using a program like apt(1), or lcupm-cli(1).\n"
            "In the first 3 forms, one or more sources are copied to a destination (which may be a directory)\n"
            "In the last form, install creates a new directory, like mkdir(1)\n\n"
            "Options:\n"
            "\t--backup[=control]: Controls whether backups are created, and how they are created\n"
            "\t-b: Same as --backup (does not accept any argument)\n"
            "\t-c: Ignored for compatibility with other install tools\n"
            "\t-C, --compare: Compares the source and destination\n"
            "\t-d, --directory: Treats all paths as directories, and creates all components of such.\n"
            "\t-D: Creates all components of the DESTINATION, except the last. If --target-directory is used, creates all components of that directory.\n"
            "\t-g, --group=GROUP: Sets the owner gid of the file to GROUP. Only works for privileged processes, or if GROUP is a supplementary group of the process\n"
            "\t-m, --mode=MODE: The mode, as provided to chmod(1), to use instead of the default rwxr-xr-x.\n"
            "\t-o, --owner=OWNER: Sets the owner uid of the file to OWNER. Only works for privileged processes.\n"
            "\t-p, --preserve-timestamps: Preserve the access and modification timestamps in the SOURCE in each DESTINATION\n"
            "\t-s, --strip: Strips ELF files after installing\n"
            "\t--strip-program=PROGRAM: The program to use for --strip\n"
            "\t-S, --suffix=SUFIX: Overrides the default backup suffix\n"
            "\t-t, --target-directory=DIRECTORY: Uses DIRECTORY as the destination, and installs each SOURCE into the DIRECTORY\n"
            "\t-T, --no-target-directory: Treat DEST as a normal file\n"
            "\t-v, --verbose: Prints the name of each directory as it is created\n"
            "\t--help: Prints this message and exits\n"
            "\t--version: Prints version information and exits\n";

    uid_t uid = -1;
    gid_t gid = -1;
    mode_t md = 0755;
    mode_t um = umask(0);
    enum backup_mode backup = None;
    enum create_mode mode = Single;
    _Bool strip = 0;
    const char* strip_prg = NULL;
    const char* target;
    char** files_start;
    int files_cnt = 0;
    _Bool preserve_times = 0;
}
