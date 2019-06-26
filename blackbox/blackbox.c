#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // mkdir()
#include <unistd.h>

#define size 100

void makeTimeDir(char *name);
int makeDir(char *name, char *path);
void makeTimeFile(char *file_name);
void makeFile(char *path, char *file_name);

void main(){
    char dir_name[size], path[size], file_name[size];
    int result;

    makeTimeDir(dir_name);
    result = makeDir(dir_name, path);
    makeTimeFile(file_name);
    makeFile(path,file_name);
}

void makeFile(char *path, char *file_name){
    FILE *fp;
    char full[size];

    strcpy(full,path);
    strcat(full,"/");
    strcat(full,file_name);
    printf("%s",full);
    fp = fopen(full, "w");
    fclose(fp);
}

void makeTimeFile(char *file_name){
    time_t timer;  // 시간측정
    struct tm *t;

    timer = time(NULL); // 현재 시각을 초 단위로 얻기
    t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

    strftime(file_name,20,"%Y%m%d_%H%M%S",t);
    printf("%s\n",file_name);
}

void makeTimeDir(char *dir_name){
    time_t timer;  // 시간측정
    struct tm *t;

    timer = time(NULL); // 현재 시각을 초 단위로 얻기
    t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

    // printf("%d 년",t->tm_year+1900);
    // printf("%d 월",t->tm_mon+1);
    // printf("%d 일",t->tm_mday);
    // printf("%d 시",t->tm_hour);
    // printf("%d 분",t->tm_min);
    // printf("%d 초",t->tm_sec);
   
    // sprintf(name,"%d%d%d_%d",t->tm_year,t->tm_mon,t->tm_mday,t->tm_hour);

    strftime(dir_name,20,"%Y%m%d_%H",t);
    // printf("%s\n",dir_name);
}

int makeDir(char *name, char *path){
    char p[size] ="/home/seulgi/blackbox/"; 
    
    strcat(p,name);
    strcpy(path,p);
    // printf("%s\n",ptr);

    int result = mkdir(p,0755);
    // printf("%d",result);
    return result;
}
