/*
 *  search_test.c
 *  Created on: 2018-7-19
 *  Author: MK
 *  usage:四种字符串匹配算法的实现（Sunday、KMP、Boyer-Moore、horspool）的测试
 */
#include "search_string.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define My_TXTMAX 1000
#define times 1  //运行次数
#define MAXCH 256
int main()
{	//初始化一些变量
	char* pattern="MY_TEST_string";//模式串
	int lenp,len_txt;
	lenp=strlen(pattern);
	len_txt=strlen(My_TXT);//My_TXT为文本串，具体内容在"search_character.h"中
	int sun_shift[MAXCH];//Sunday辅助数组
	int KMP_next[lenp];//KMP辅助数组
	int bmBc[MAXCH];//BM坏字符数组
	int bmGs[lenp];//BM好后缀数组
	int hors_d[MAXCH];//horspool辅助数组
	struct timeval start,end;//用来记录时间
	long dif_sec, dif_usec;//存储时间差
	int i;
	char *temp[5],test[5][256];
	//四种算法的预处理工作
    SundayPre(sun_shift,pattern,lenp);
    KMPPre(pattern,KMP_next);
    PreBmBc(pattern,lenp,bmBc);
    PreBmGs(pattern,lenp,bmGs);
    horspoolPre(hors_d,pattern,lenp);
    //测试开始
	///////////KmpSearch///////////
	gettimeofday(&start,NULL);//起始时间
	for(i=0;i<times;i++){//为运行次数
		if(i==0){
			temp[0]=KmpSearch(My_TXT,len_txt,pattern,lenp,KMP_next);//返回结果，可用来验证是否真的找到了模式串pattern所在位置
		}
		else
			KmpSearch(My_TXT,len_txt,pattern,lenp,KMP_next);//循环调用
	}
	gettimeofday(&end,NULL);//结束时间
	dif_sec=end.tv_sec-start.tv_sec;//相差的秒数
	dif_usec=end.tv_usec-start.tv_usec;//相差的微秒数
	printf("KMP running time  is %ld 秒 (%ld 微秒)\n",dif_sec, dif_sec*1000000+dif_usec);//最终时间换算，欲知详情请自行查询结构体struct timeval
		
	////////////BM//////////////
	gettimeofday(&start,NULL);
	for(i=0;i<times;i++){
		if(i==0){
			temp[1]=BoyerMoore(My_TXT,len_txt,pattern,lenp,bmBc,bmGs);
		}
		else
			BoyerMoore(My_TXT,len_txt,pattern,lenp,bmBc,bmGs);
	}
	gettimeofday(&end,NULL);
	dif_sec=end.tv_sec-start.tv_sec;
	dif_usec=end.tv_usec-start.tv_usec;
	printf("BM running time  is %ld 秒 (%ld 微秒)\n",dif_sec, dif_sec*1000000+dif_usec);
		
	////////////Sunday//////////////
	gettimeofday(&start,NULL);
	for(i=0;i<times;i++){
		if(i==0){
			temp[2]=Sunday(My_TXT,len_txt,pattern,lenp,sun_shift);
		}
		else
			Sunday(My_TXT,len_txt,pattern,lenp,sun_shift);
	}
	gettimeofday(&end,NULL);
	dif_sec=end.tv_sec-start.tv_sec;
	dif_usec=end.tv_usec-start.tv_usec;
	printf("Sunday running time  is %ld 秒 (%ld 微秒)\n",dif_sec, dif_sec*1000000+dif_usec);

	///////////horspool//////////////
	gettimeofday(&start,NULL);
	for(i=0;i<times;i++){
		if(i==0){
			temp[3]=horspool(My_TXT,len_txt,pattern,lenp,hors_d);
		}
		else
			horspool(My_TXT,len_txt,pattern,lenp,hors_d);
	}
	gettimeofday(&end,NULL);
	dif_sec=end.tv_sec-start.tv_sec;
	dif_usec=end.tv_usec-start.tv_usec;
	printf("horspool running time  is %ld 秒 (%ld 微秒)\n",dif_sec, dif_sec*1000000+dif_usec);

	////////////strstr//////////////
	gettimeofday(&start,NULL);
	for(i=0;i<times;i++){
		if(i==0){
			temp[4]=strstr(My_TXT,pattern);
		}
		else{
			strstr(My_TXT,pattern);
		}
	}
	gettimeofday(&end,NULL);
	dif_sec=end.tv_sec-start.tv_sec;
	dif_usec=end.tv_usec-start.tv_usec;
	printf("strstr running time  is %ld 秒 (%ld 微秒)\n",dif_sec, dif_sec*1000000+dif_usec);	
	/////打印验证结果是否正确///////////////
	printf("*********************\n");
	if(temp[0]){
		strncpy(test[0],temp[0],lenp+1);//只复制关键词的部分
		test[0][lenp]='\0';             //手动加上结束符
		printf("KMP: %s\n",test[0]); //打印
	}
	if(temp[1]){
		strncpy(test[1],temp[1],lenp+1);
		test[1][lenp]='\0';
		printf("BM: %s\n",test[1]);
	}
	if(temp[2]){
		strncpy(test[2],temp[2],lenp+1);
		test[2][lenp]='\0';
		printf("Sunday: %s\n",test[2]);
	}
	if(temp[3]){
		strncpy(test[3],temp[3],lenp+1);
		test[3][lenp]='\0';
		printf("Horspool: %s\n",test[3]);
	}
	if(temp[4]){
		strncpy(test[4],temp[4],lenp+1);
		test[4][lenp]='\0';
		printf("strstr: %s\n",test[4]);
	}
	printf("*********************\n");
    return 0;
}
