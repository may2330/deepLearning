#include "blackboxHeader.h"

// 시스템 종료
int FLAG=0;

// Thread 의 상태 (실행중/종료)
int T_FLAG=1;

// int main(void){
//     // 쓰레드 
//     pthread_t d_th, m_th1;
//     int flag=0;   
//     char p1[] = "thread1";

//     // 시작 시간
//     struct timeval UTCtime_s, UTCtime_e;
//     int gap;
//     gettimeofday(&UTCtime_s, NULL);

//     // 쓰레드 생성
//     if(pthread_create(&d_th, NULL, delThread_f, (void *)0))
// 	    printf("Thread Error : No Make \n");

//     printf("시간 : ");
//     while(!FLAG){
//         gettimeofday(&UTCtime_e, NULL);
//         gap = disp_runtime(UTCtime_s, UTCtime_e) % STEP;
// 	    printf(" %d",gap);
// 	    if(gap==0){
//             while(T_FLAG==0)
//                     continue;	
//             T_FLAG = 0;
//             if(pthread_create(&m_th1, NULL, makeThread_f, (void *)p1))
//                 printf("M-Thread Error : No Make \n");
//             pthread_detach(m_th1);
// 	    }
// 	    sleep(1);
//         printf("\n시간 : ");
//     }
//     // thread detach 
//     pthread_detach(d_th);
// }

int main(void){
    // 쓰레드 
    pthread_t d_th, m_th1;
    int flag=0;   
    char p1[] = "thread1";

    // 시작 시간
    struct timeval UTCtime_s, UTCtime_e;
    int gap;
    

    // 쓰레드 생성
    if(pthread_create(&d_th, NULL, delThread_f, (void *)0))
	    printf("Thread Error : No Make \n");

    if(pthread_create(&m_th1, NULL, makeThread_f, (void *)p1))
            printf("M-Thread Error : No Make \n");
        
    // thread detach
    if(FLAG){ 
        pthread_detach(d_th);
        pthread_detach(m_th1);
    }
}
