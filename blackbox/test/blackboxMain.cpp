#include "blackboxHeader.h"

// 시스템 종료
int FLAG=0;

// Thread 의 상태 (실행중/종료)
int T_FLAG=0;

int main(void){
    // 쓰레드 
    pthread_t d_th, m_th1;

    // 쓰레드 생성
    if(pthread_create(&d_th, NULL, delThread_f, (void *)0))
	    printf("Thread Error : No Make \n");

    if(pthread_create(&m_th1, NULL, makeThread_f, (void *)0))
        printf("M-Thread Error : No Make \n");
        
    while(!FLAG)
        continue;

    // thread detach
    pthread_detach(d_th);
    pthread_detach(m_th);

}
