#include "blackboxHeader.h"

int disp_runtime(struct timeval UTCtime_s, struct timeval UTCtime_e)
{
    struct timeval UTCtime_r;
    if((UTCtime_e.tv_usec- UTCtime_s.tv_usec)<0)
            UTCtime_r.tv_sec  = UTCtime_e.tv_sec - UTCtime_s.tv_sec - 1;
    else
            UTCtime_r.tv_sec = UTCtime_e.tv_sec - UTCtime_s.tv_sec;
	return (int)UTCtime_r.tv_sec;
}

void *makeThread_f(void *data){
	char dir_name[SIZE], path[SIZE], file_name[SIZE];
    int result,gap;
    struct timeval UTCtime_s, UTCtime_e;

    // 프로그램 시작시작
    gettimeofday(&UTCtime_s, NULL);

    // Define the gstream pipeline
    std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);

    //비디오 캡쳐 초기화
    VideoCapture cap(pipeline, CAP_GSTREAMER);

    while(!FLAG){
        // 1분마다 실행
        if(!T_FLAG){
            T_FLAG = 1;
            makeTime(0,dir_name);
            result = makeDir(dir_name,path);
            if(result==-1){
                printf("디렉토리 안만들어졌다!!!!!!!!!!!!!!1\n");
                exit(0);
            }
            makeTime(1,file_name);
            makeFile(path,file_name, &cap);
            
            printf("\n");
        }
        // sleep(1);
    }
}

void *delThread_f(void *data){
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
    int result=0;
    float percent;

    if (statfs(PATH, &fs) != 0 ){
        printf("%s 파일 사이즈 없음! 헐....\n",PATH);
        exit(0);
    }

    percent = ((float)fs.f_bfree/fs.f_blocks)*100; // printf 에서 %lu
    printf("    percent : %f",percent);

    // 남은 용량이 35% 이하이면 삭제
    if(percent > 35)
        result = 1;
    
    return result;
}

void makeFile(char *path, char *file_name, VideoCapture *cap){
	char p[SIZE];
	struct timeval UTCtime_s, UTCtime_e;
    Mat img_color;

	gettimeofday(&UTCtime_s, NULL);

	// 파일 이름 구하기
	strcpy(p,path);
	strcat(p,"/");
	strcat(p,file_name);
	strcat(p,".avi");

        // 동영상 파일을 저장하기 위한 준비  
        Size size = Size((int)cap->get(CAP_PROP_FRAME_WIDTH),
                (int)cap->get(CAP_PROP_FRAME_HEIGHT));

        VideoWriter writer;
        writer.open(p, VideoWriter::fourcc('D', 'I', 'V', 'X'), FPS, size, true);
        if (!writer.isOpened())
                cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;
        

	do{
		gettimeofday(&UTCtime_e,NULL);
		
                cap->read(img_color);
                if (img_color.empty()) {
                        cerr << "빈 영상이 캡쳐되었습니다.\n";
                        break;
                }

                //동영상 파일에 한 프레임을 저장함.  
                writer.write(img_color);

                imshow("Color", img_color);
                if (waitKey(10) >= 0){
                	FLAG=1;
			break;
		}
	}while(disp_runtime(UTCtime_s, UTCtime_e)<STEP);

	writer.release();
	T_FLAG = 0;
	printf("[%s] 파일 만들었음!\n",p);
}

void makeTime(int time_flag,char *name){
    time_t timer;  // 시간측정
    struct tm *t;

    timer = time(NULL); // 현재 시각을 초 단위로 얻기
    t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

    if(time_flag)
        strftime(name,20,"%Y%m%d_%H%M%S",t);
    else
        strftime(name,20,"%Y%m%d_%H",t);
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


string get_tegra_pipeline(int width, int height, int fps) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + patch::to_string(width) + ", height=(int)" +
            patch::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + patch::to_string(fps) +
            "/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}