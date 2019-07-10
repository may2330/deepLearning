// c
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
#include <sys/time.h> // getimeofday( ) 함수에서 사용

// c++
#include <opencv2/opencv.hpp>
#include <iostream>


#define SIZE 100
#define PATH "/home/js/blackbox/"
#define STEP 60 // 10 초마다 동영상촬영

// 함수 정의
void makePathDir();
void makeTimeDir(char *name);
int makeDir(char *name, char *path);
void makeTimeFile(char *file_name);
void makeFile(char *path, char *file_name);
int checkSize();
void delFirstDir();
void delDir(char *dir_name);
void *d_function(void *data);
void *m_function(void *data);
int disp_runtime(struct timeval UTCtime_s, struct timeval UTCtime_e);

// 
std::string get_tegra_pipeline(int width, int height, int fps) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + ", height=(int)" +
            std::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(fps) +
            "/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

using namespace cv;
using namespace std;


// camera
int WIDTH = 800;
int HEIGHT = 500;
int FPS = 30;

// Define the gstream pipeline
std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);

Mat img_color;

//비디오 캡쳐 초기화
VideoCapture cap(pipeline, CAP_GSTREAMER);


int main(void){

    // 쓰레드 
    pthread_t p_thread;
    pthread_t m_th1, m_th2;
    int flag=0;   
    char p1[] = "thread1";
    char p2[] = "thread2";

    // 시작 시간
    struct timeval UTCtime_s, UTCtime_e;
    int gap, step = 10; // 10 초마다 동영상 저장
    gettimeofday(&UTCtime_s, NULL);

    // 쓰레드 생성
    if(pthread_create(&p_thread, NULL, d_function, (void *)0))
	    printf("Thread Error : No Make \n");

    while(1){
            gettimeofday(&UTCtime_e, NULL);
            gap = disp_runtime(UTCtime_s, UTCtime_e) % STEP;
	    printf("gap : %d\n",gap);
	    if(gap==0 && flag==0){
		flag = 1;
	    	if(pthread_create(&m_th1, NULL, m_function, (void *)p1))
			printf("M-Thread Error : No Make \n");
	        pthread_detach(m_th1);
	    }
	    
	    else if(gap==0){
		flag = 0;
	    	if(pthread_create(&m_th2, NULL, m_function, (void *)p2))
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
	return (int)UTCtime_r.tv_sec;
}


void *m_function(void *data){
        char *thread_name = (char *)data;
	char dir_name[SIZE], path[SIZE], file_name[SIZE];
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

void *d_function(void *data){
	int check_del;
	
	while(1){
		check_del = checkSize();
		if(check_del==0){
			printf("--용량 꽉참--\n");
			delFirstDir();
		}
		printf("--용량 체크 완료--\n");
		sleep(STEP);
	}
}

void delDir(char *dir_name){
    char dir[SIZE], del_filename[SIZE];
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
    char dir_name[SIZE];

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
    if(percent > 30)
        result = 1;
    
    return result;
}

void makeFile(char *path, char *file_name){
	char p[SIZE];
	struct timeval UTCtime_s, UTCtime_e;

	gettimeofday(&UTCtime_s, NULL);

	// 파일 이름 구하기
	strcpy(p,path);
	strcat(p,"/");
	strcat(p,file_name);
	strcat(p,".avi");

        // 동영상 파일을 저장하기 위한 준비  
        Size size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),
                (int)cap.get(CAP_PROP_FRAME_HEIGHT));

        VideoWriter writer;
        double fps = 30.0;
        writer.open(p, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size, true);
        if (!writer.isOpened())
                cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;
        

	do{
		gettimeofday(&UTCtime_e,NULL);

                cap.read(img_color);
                if (img_color.empty()) {
                        cerr << "빈 영상이 캡쳐되었습니다.\n";
                        break;
                }

                //동영상 파일에 한 프레임을 저장함.  
                writer.write(img_color);

                imshow("Color", img_color);
                if (waitKey(30) >= 0)
                        break;

	}while(disp_runtime(UTCtime_s, UTCtime_e)<STEP);

        printf("[%s] 파일 만들었음!\n",p);
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
    char p[SIZE] =""; 
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


