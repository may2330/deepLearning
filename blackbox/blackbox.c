#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // mkdir()
#include <sys/types.h>
#include <unistd.h>
#include <sys/statfs.h>
#include <dirent.h>
#include <time.h>
#include <sys/time.h> // getimeofday( ) 함수에서 사용

#define size 100
#define PATH "/home/js/blackbox/"

void makePathDir();
void makeTimeDir(char *name);
int makeDir(char *name, char *path);
void makeTimeFile(char *file_name);
void makeFile(char *path, char *file_name);
int checkSize();
void delFirstDir();
void delDir(char *dir_name);
void *d_function();
void *m_function(void *data);
int disp_runtime(struct timeval UTCtime_s, struct timeval UTCtime_e);



void main(){

    // 쓰레드 
    pthread_t p_thread;
    pthread_t m_th1, m_th2;
    int flag=0;   
    char c_th1[] = "thread_1"; 
    char c_th2[] = "thread_2";
    struct timeval UTCtime_s, UTCtime_e, UTCtime_r;

    // 시작 시간
    int gap, step = 10; // 10 초마다 동영상 저장
    gettimeofday(&UTCtime_s, NULL);

    // 쓰레드 생성
    if(pthread_create(&p_thread, NULL, d_function, NULL))
	    printf("Thread Error : No Make \n");

    while(1){
            gettimeofday(&UTCtime_e, NULL);
            gap = disp_runtime(UTCtime_s, UTCtime_e) % step;
	    
	    if(gap==0 && flag==0){
		flag = 1;
	    	if(pthread_create(&m_th1, NULL, m_function, (void *)c_th1))
			printf("M-Thread Error : No Make \n");
	        pthread_detach(m_th1);
	    }
	    
	    else if(gap==0){
		flag = 0;
	    	if(pthread_create(&m_th2, NULL, m_function, (void*)c_th2))
			printf("M-Thread Error : No Make \n");
	    	pthread_detach(m_th2);
	    }

	    sleep(1);
    }
    // thread detach 
    pthread_detach(p_thread);

}

int disp_runtime(struct timeval UTCtime_s, struct timeval UTCtime_e)
{
        struct timeval UTCtime_r;
        if((UTCtime_e.tv_usec- UTCtime_s.tv_usec)<0)
                UTCtime_r.tv_sec  = UTCtime_e.tv_sec - UTCtime_s.tv_sec - 1;
        else
                UTCtime_r.tv_sec = UTCtime_e.tv_sec - UTCtime_s.tv_sec;
        printf("runtime : %ld sec\n", UTCtime_r.tv_sec);
	return (int)UTCtime_r.tv_sec;
}


void *m_function(void *data){
        char *thread_name = (char *)data;
	char dir_name[size], path[size], file_name[size];
        int result, check_del;

	printf("\n[%s]====================\n",thread_name);
	makeTimeDir(dir_name);
	result = makeDir(dir_name,path);
	if(result==-1){
		printf("디렉토리 안만들어졌다!!!!!!!!!!!!!!1\n");
		exit(0);
	}

	makeTimeFile(file_name);
	makeFile(path,file_name);
	
	printf("\n\n");
}

void *d_function(){
	int check_del;
	
	while(1){
		check_del = checkSize();
		if(check_del==0){
			printf("--용량 꽉참--\n");
			delFirstDir();
		}
		printf("--용량 체크 완료--\n");
		sleep(4);
	}
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

int checkSize(){
    struct statfs fs;
    size_t diskSize=0, freeSize=0;
    int result=0;
    float percent;

    if (statfs(PATH, &fs) != 0 ){
        printf("%s 파일 사이즈 없음! 헐....\n",PATH);
        exit(0);
    }
    
    diskSize = fs.f_blocks * (fs.f_bsize/1024); // printf 에서 %lu
    freeSize = fs.f_bfree * (fs.f_bsize/1024);

    percent = ((float)freeSize/diskSize)*100;

    // 남은 용량이 20% 이하이면 삭제
    if(percent > 20)
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


