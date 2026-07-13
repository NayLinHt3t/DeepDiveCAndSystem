#ifndef MYSHELL_H
#define MYSHELL_H

void my_cp(const char *source, const char *destination);
void my_cat(const char *filename);
void my_ls(const char *path);
void my_mkdir(const char *path);
void my_rmdir(const char *path);
void my_rm(const char *path);
void my_touch(const char *path);
void my_cd(const char *path);
void my_pwd();
void my_echo(const char *message);
void my_grep(const char *pattern, const char *filename);
void my_wc(const char *filename);
#endif // MYSHELL_H