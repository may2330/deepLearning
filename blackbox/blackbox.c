#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // mkdir()
#include <sys/types.h>
#include <unistd.h>
#include <sys/statfs.h>
#include <dirent.h>


#define size 100
#define PATH "/home/seulgi/blackbox/"

void makePathDir();
void makeTimeDir(char *name);
int makeDir(char *name, char *path);
void makeTimeFile(char *file_name);
void makeFile(char *path, char *file_name);
int checkSize(char *path);
void delFirstDir();
void delDir(char *dir_name);

void main(){
    char dir_name[size], path[size], file_name[size];
    int result, check_del;

    makeTimeDir(dir_name);
    result = makeDir(dir_name,path);
    if(result==-1){
        printf("디렉토리 안만들어졌다!!!!!!!!!!!!!!1\n");
        exit(0);
    }
    
    makeTimeFile(file_name);
    makeFile(path,file_name);
    check_del = checkSize(path);
    if(check_del==0)
        delFirstDir();
}

void delDir(char *dir_name){
    char dir[size], del_filename[size];
    DIR *dir_ptr = NULL;
    struct dirent *file = NULL;

    strcpy(dir, PATH);
    strcat(dir, dir_name);

    if(rmdir(dir)==-1){
        printf("가장 오래된 파일 삭제 No...안에 파일존재함 !!!\n");
        if((dir_ptr = opendir(dir)) == NULL){
            printf("지울 디렉토리의 파일을 읽을 수 없음...\n");
            exit(1);
        }

        while((file=readdir(dir_ptr)) !=NULL){
            strcpy(del_filename,dir);
            strcat(del_filename,"/");
            strcat(del_filename, file->d_name);
            if(remove(del_filename)==0)
                printf("파일 삭제 성공\n");
        }

        if(rmdir(dir)==0)
            printf("======================= %s 디렉토리 삭제 \n\n",dir);
    }
}

void delFirstDir(){
    struct dirent **namelist;
    int count=0,idx=0;
    char dir_name[size];

    if((count = scandir(PATH, &namelist, NULL, alphasort))==-1){
        printf("Error\n");
        exit(1);
    }

    strcpy(dir_name, namelist[2]->d_name);

    for(idx=0;idx<count;idx++)
        free(namelist[idx]);

    free(namelist);

    delDir(dir_name);
}

int checkSize(char *path){
    struct statfs fs;
    size_t diskSize=0, freeSize=0;
    int result=0;
    float percent;

    if (statfs(path, &fs) != 0 ){
        printf("%s 파일 사이즈 없음! 헐....\n",path);
        exit(0);
    }
    
    diskSize = fs.f_blocks * (fs.f_bsize/1024); // printf 에서 %lu
    freeSize = fs.f_bfree * (fs.f_bsize/1024);

    percent = ((float)freeSize/diskSize)*100;
    if(percent > 10)
        result = 1;
    
    return result;
}

void makeFile(char *path, char *file_name){
    FILE *fp;
    char p[size];

    strcpy(p,path);
    strcat(p,"/");
    strcat(p,file_name);

    if(access(p,F_OK)==0)
        printf("현재 시간 파일 있어영~ \n");
    
    else{
        fp = fopen(p, "w");
        fclose(fp);
        printf("파일 만들었음!\n");
    }
}

void makeTimeFile(char *file_name){
    time_t timer;  // 시간측정
    struct tm *t;

    timer = time(NULL); // 현재 시각을 초 단위로 얻기
    t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

    strftime(file_name,20,"%Y%m%d_%H%M%S",t);
}

void makeTimeDir(char *dir_name){
    time_t timer;  // 시간측정
    struct tm *t;

    timer = time(NULL); // 현재 시각을 초 단위로 얻기
    t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

    strftime(dir_name,20,"%Y%m%d_%H",t);
}

int makeDir(char *name, char *path){
    char p[size] =""; 
    int result;

    strcpy(p,PATH);
    strcat(p,name);
    strcpy(path,p);

    // 같은이름의 디렉토리 있는지 여부 확인
    if(access(p,F_OK)==0){
        printf("현재 시간 디렉토리 있어영~ \n");
        return 0;
    }
    
    return mkdir(p,0755);
}


