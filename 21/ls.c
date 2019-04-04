#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


void format(char* str, int n){
    int m = strlen(str);
    int i;
    for(i = m; i < n - 1; i++)
        str[i]=' ';
    str[n-1] = 0;
}


int main(int argc, char* argv[]){
    int error;

    char* directory_name;

    if (argc == 2){
        directory_name = argv[1];
    } else{
        directory_name = ".";
    }

    DIR* directory;
    directory = opendir(directory_name);
    if (directory == NULL){
        printf("Cannot open directory %s.\n", directory_name);
        exit(1);
    }

    printf("+-----------+------+----------+----------+--------+-------+-----------+---------------------+\n");
    printf("| NAME      | TYPE | UID      | USERNAME | SIZE   | NLINK | RIGHTS    | ATIME               |\n");
    printf("+-----------+------+----------+----------+--------+-------+-----------+---------------------+\n");

    struct dirent* directory_data = readdir(directory);
    while(directory_data != NULL){
        struct stat directory_type;

        char file_address[100];
        sprintf(file_address, "%s/%s",directory_name, directory_data->d_name);
        error = lstat(file_address, &directory_type); //directory_data->d_name
        if (error < 0){
            printf("Cannot get type of the file %s.\n", directory_data->d_name);
            exit(1);
        }

        char* s = directory_data->d_name;
        format(s, 10);
        printf("| %s |", s);

        // TYPE
        if (S_ISREG(directory_type.st_mode)) {
            char s[4] = "REG";
            format(s, 5);
            printf(" %s |", s);
        }
        if (S_ISDIR(directory_type.st_mode)) {
            char s[4] = "DIR";
            format(s, 5);
            printf(" %s |", s);
        }
        if (S_ISCHR(directory_type.st_mode)) {
            char s[4] = "CHR";
            format(s, 5);
            printf(" %s |", s);
        }
        if (S_ISBLK(directory_type.st_mode)) {
            char s[4] = "BLK";
            format(s, 5);
            printf(" %s |", s);
        }
        if (S_ISFIFO(directory_type.st_mode)) {
            char s[4] = "FIFO";
            format(s, 5);
            printf(" %s |", s);
        }
        if (S_ISLNK(directory_type.st_mode)) {
            char s[4] = "LNK";
            format(s, 5);
            printf(" %s |", s);
        };
        if (S_ISSOCK(directory_type.st_mode)) {
            char s[4] = "SOCK";
            format(s, 5);
            printf(" %s |", s);
        }

        // UID - user-owner ID
        uid_t uid = directory_type.st_uid;
        printf(" %8d |", uid);

        // USERNAME
        struct passwd* u;
        u = getpwuid(directory_type.st_uid);
        printf(" %8s |", u->pw_name);

//        // GID - group-owner ID
//        gid_t gid = directory_type.st_gid;
//        printf(" %8d |", gid);
//
//        // GROUPNAME
//        struct group* g;
//        g = getgrgid(directory_type.st_gid);
//        printf(" %8s |", g->gr_name);

        // SIZE - size in Bytes
        off_t size = directory_type.st_size;
        printf(" %6d |", size);

        // NLINK - number of strong links
        printf(" %5d |", directory_type.st_nlink);

        // RIGHTS
        printf(" ");
        int i;
        for(i = 8; i >= 0; i--) {
            int rights = (directory_type.st_mode >> i) & 1;
            if (rights == 1) {
                switch (i % 3) {
                    case 2: printf("r"); break;
                    case 1: printf("w"); break;
                    case 0: printf("x"); break;
                }
            } else {
                printf("-");
            }
        }
        printf(" |");

        // ATIME - time of the last access
        time_t t = directory_type.st_atime;
        struct tm *tm;
        char buf[200];
        tm = localtime(&t);
        strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", tm);
        format(buf, 20);
        printf(" %s |", buf);

//        // MTIME - time of the last data modification
//        t = directory_type.st_mtime;
//        tm = localtime(&t);
//        strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", tm);
//        format(buf, 20);
//        printf(" %s |", buf);
//
//        // CTIME - time of the last file status change
//        t = directory_type.st_ctime;
//        tm = localtime(&t);
//        strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", tm);
//        format(buf, 20);
//        printf(" %s |", buf);




        char link_buf[1000];
        if (S_ISLNK(directory_type.st_mode)) {
            if (readlink(file_address, link_buf, 1000) < 0) {
                printf("Error while reading link %s.\n", file_address);
                exit(-1);
            }
            printf(" -> %s", link_buf);
            memset(link_buf, 0, 1000);
        };

        printf("\n");
        directory_data = readdir(directory);
    }

    printf("+-----------+------+----------+----------+--------+-------+-----------+---------------------+\n");

    error = closedir(directory);
    if (error < 0){
        printf("Cannot close directory %s.\n", directory_name);
        exit(1);
    }

    return 0;
}
