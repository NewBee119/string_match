/*
 *  search_string.h
 *  Created on: 2018-7-19
 *  Author: MK
 *  usage:四种字符串匹配算法的实现（Sunday、KMP、Boyer-Moore、horspool）的声明
 */
#ifndef __SEARCH_CHA__
#define __SEARCH_CHA__
#include <stdio.h>
#include <string.h>
//匹配的文本内容  在里面填上自己的特定字符MY_TEST_string
char* My_TXT="LOCALGX=%u6210%u90FD%7C%36%36%39%33%7C%u6210%u90FD%7C%36%36%39%33; Hm_lvt_e9e114d958ea263de46e080563e254c4=1531471439,1531472197,"
			"1531537654,1531618652; BAIDUID=3ACF228CE89D0C2D28B1B3DA5C56C138:FG=1; Hm_lpvt_e9e114d958ea263de46e080563e254c4=1531629911;"
			 "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			 "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			 "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			 "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860;MY_TEST_string H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			 "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			 "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			 "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; MY_TEST_MYringH_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			 "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			  "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			  "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/"
			  "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/" "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/" "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/" "BIDUPSID=C18478BCF075BCE0D2D0149D77980B8B; PSTM=1531620860; H_PS_PSSID=26523_1451_25810_21106_22159 Mozilla/5.0 (X11; Linux x86_64; rv:10.0.12)"
			 " Gecko/20130109 Firefox/10.0.12 http://news.baidu.com/mil AndroidDownloadManager/7.1.2 (Linux; U; Android 7.1.2; MI 5X Build/N2G47H)  http://switch.pcfg.cache."
			 "wpscdn.cn/wps_assets/cfg/ad/switch/load_bubblehttp://notify.wps.cn/notifyserver/notify?v=qidVrBsEjwqbMd%2F4ydmZ5CRKfbUlVq11EGkClTHeWH%2B5msXpw%2BQJC0oEFK%2FB8vu2bNj"
			 "aDZpcjl1wviBMWPHuYA==  http://tile-service.weather.microsoft.com/zh-CN/livetile/preinstall?region=CN&appid=C98EA5B0842DBB9405BBF071E1DA76512D21FE36&FORM=Threshold"
			 "http://res.res.res.res:80/";

//预处理函数声明
void SundayPre(int sun_shift[],char* P,int lenP);
void KMPPre(char* p, int KMP_next[]);
void PreBmBc(char *pattern,int m,int bmBc[]);
void PreBmGs(char *pattern,int m,int bmGs[]);
void horspoolPre(int hors_d[],char* P,int lenP);
/*
function:
		Sunday字符匹配算法
Param:
@T 文本内容
@TLen 文本内容长度
@p 需要匹配的字符串
@lenP 需要匹配的字符串长度
*/
char* Sunday(char* T,int lenT,char* P,int lenP,int shift[]);
/*
function:
		KMP字符匹配算法
Param:
@s 文本内容
@sLen 文本内容长度
@p 需要匹配的字符串
@pLen 需要匹配的字符串长度
*/
char* KmpSearch(char* s,int sLen,char* p,int pLen,int next[]);
/*
function:
		Boyer-Moore字符匹配算法
Param:
@text 文本内容
@n 文本内容长度
@pattern 需要匹配的字符串
@m 需要匹配的字符串长度
*/
char* BoyerMoore(char *text,int n,char *pattern,int m,int bmBc[],int bmGs[]);
/*
function:
		horspool字符匹配算法
Param:
@T 文本内容
@lenT 文本内容长度
@P 需要匹配的字符串
@lenP 需要匹配的字符串长度
*/
char* horspool(char *T, int lenT, char *P, int lenP,int hors_d[]);
#endif