// #include <stdio.h>
// #include <stdlib.h>
// #include <dirent.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <pwd.h>
// #include <grp.h>
 #include <time.h>
// included in myls.c

void printlong(const char *filename) {
    // print i am here
    printf("line 13d inside printlong\n");
    struct stat fileStat;
    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return;
    }

    // File type and permissions
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

    // Number of hard links
    printf(" %ld", fileStat.st_nlink);

    // Owner and group names
    struct passwd *pw = getpwuid(fileStat.st_uid);
    struct group *gr = getgrgid(fileStat.st_gid);
    if (pw)
        printf(" %s", pw->pw_name);
    else
        printf(" %ld", fileStat.st_uid);
    if (gr)
        printf(" %s", gr->gr_name);
    else
        printf(" %ld", fileStat.st_gid);

    // File size
    printf(" %ld", fileStat.st_size);
    
    // Last modification time
    char time_buf[100];
    strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", localtime(&(fileStat.st_mtime)));
    printf(" %s", time_buf);

    // File name
    printf(" %s\n", filename);

    // printf("line 58 end of function printlong.h\n");
}