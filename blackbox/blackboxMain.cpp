#include "blackboxHeader.h"

// 시스템 종료
int FLAG=0;

// Thread 의 상태 (실행중/종료)
int T_FLAG=1;

// camera
int WIDTH = 720;
int HEIGHT = 480;
int FPS = 30;
// Define the gstream pipeline
std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);

Mat img_color;

//비디오 캡쳐 초기화
VideoCapture cap(pipeline, CAP_GSTREAMER);

int main(void){
    // 쓰레드 
    pthread_t d_th, m_th1;
    int flag=0;   
    char p1[] = "thread1";

    // 시작 시간
    struct timeval UTCtime_s, UTCtime_e;
    int gap;
    gettimeofday(&UTCtime_s, NULL);

    // 쓰레드 생성
    if(pthread_create(&d_th, NULL, d_function, (void *)0))
	    printf("Thread Error : No Make \n");

    while(!FLAG){
        gettimeofday(&UTCtime_e, NULL);
        gap = disp_runtime(UTCtime_s, UTCtime_e) % STEP;
	    printf(" gap : %d\n",gap);
	    if(gap==0){
		while(T_FLAG==0)
	    		continue;	
		T_FLAG = 0;
		if(pthread_create(&m_th1, NULL, m_function, (void *)p1))
			printf("M-Thread Error : No Make \n");
	        pthread_detach(m_th1);
	    }
	    sleep(1);
    }
    // thread detach 
    pthread_detach(d_th);

}


