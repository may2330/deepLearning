#ifndef BLAKCBOXHEADER_H
#define BLACKBOXHEADER_H

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

using namespace cv;
using namespace std;

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
string get_tegra_pipeline(int width, int height, int fps);

// to_string 오류 
namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

// 전역변수 정의
extern int FLAG, T_FLAG;
extern int WIDTH, HEIGHT, FPS;
extern string pipeline;
extern Mat img_color;
extern VideoCapture cap; 

#endif