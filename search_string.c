/*
 *  search_string.c
 *  Created on: 2018-7-19
 *  Author: MK
 *  usage:四种字符串匹配算法的实现（Sunday、KMP、Boyer-Moore、horspool）
 */
#include<stdio.h>
#include<string.h>
#define maxNum 256
#define MAX(x, y) (x)>(y) ? (x):(y)
//////////////////////////Sunday//////////////////////////////////////
void SundayPre(int sun_shift[],char* P,int lenP)
{
    int i;
    for(i=0;i<maxNum;i++){
       sun_shift[i]=lenP+1;
    }
    // 模式串P中每个字母出现的最后的下标
    // 所对应的主串参与匹配的最末位字符的下一位字符移动到该位，所需要的移动位数
    for(i=0;i<lenP;i++){
        sun_shift[P[i]]=lenP-i;
    }
}
/*
function:
		Sunday字符匹配算法
Param:
@T 文本内容
@TLen 文本内容长度
@p 需要匹配的字符串
@lenP 需要匹配的字符串长度
*/
char* Sunday(char* T,int lenT,char* P,int lenP,int shift[]){
    // 默认值，移动m+1位
	int i;
    // 模式串开始位置在主串的哪里
    int pos=0;
	//printf("Sunday pos %d\n",pos);
    //模式串已经匹配到的位置
    int j,count=0;
    while(pos<=lenT-lenP) {
        j=0;
        while(T[pos+j]==P[j]&&j<lenP) j++;
            // 匹配成功
        if(j>=lenP){
			//printf("Sunday Find it. the position is %d  jump %d time\n",pos,count);
            return &T[pos];
        }
        else{
			// 找到主串中当前跟模式串匹配的最末字符的下一个字符
			// 在模式串中出现最后的位置
			// 所需要从(模式串末尾+1)移动到该位置的步数
			//printf("Sunday current step: %d jump num: %d\n",count++,shift[T[pos+lenP]]);
			pos+=shift[T[pos+lenP]];
            //count++;
			//printf("pos %d\n",pos);
		}
    }
	//printf("Sunday not Find. jump %d time\n",count);
    return NULL;
}

////////////////////////////////KMP//////////////////////////////////////////////
//优化过后的next 数组求法
/*
function:
        KMP的next数组求解（预处理）
Param:
@p 需要匹配的字符串
@next 需要匹配的字符串对应的next数组
*/
void KMPPre(char* p, int KMP_next[])
{
    int pLen=strlen(p);
    KMP_next[0]=-1;
    int k=-1;
    int j=0;
    while(j<pLen-1){
        //p[k]表示前缀，p[j]表示后缀  
        if(k==-1||p[j]==p[k]){
            ++j;
            ++k;
            if(p[j]!=p[k])
                KMP_next[j]=k;
            else if(KMP_next[k]!=-1)//若是k是0的话，它的next[0]是-1，
                KMP_next[j]=KMP_next[k];
            else
                KMP_next[j]=0;
        }
        else{
            k=KMP_next[k];
        }
    }
}
/*
function:
        KMP字符匹配算法
Param:
@s 文本内容
@sLen 文本内容长度
@p 需要匹配的字符串
@pLen 需要匹配的字符串长度
@next[] 辅助数组
*/
char* KmpSearch(char* s,int sLen,char* p,int pLen,int next[])
{
    int i=0;
    int j=0;
    while(i<sLen&&j<pLen){
        //①如果j=-1（代表又回到了P串的开头第一个字符，因为next[0]=-1），或者当前字符匹配成功（即S[i]==P[j]），都令i++，j++    
        if(j==-1||s[i]==p[j]){
            i++;
            j++;
        }
        else{
            //②如果j!=-1，且当前字符匹配失败，则令i不变(当前s串失配的地方)，j=next[j]    
            //next[j]即为j所对应的next值（其实就是和它含有相同前缀的地方，比如P为"AFHKAFOIU"，则next[6]=2,即第7个字符“O”的前两个字符"AF"(第五、六个字符)有相同前缀"AF"(第一、二个字符))
            j=next[j];
        }
    }
    if(j==pLen){
        return &s[i-j];
    }
    else{
        return NULL;
    }
}
////////////////////////////////////BoyerMoore//////////////////////////////////////
/*
function:
        求解坏字符数组
Param:
@pattern 需要匹配的字符串
@bmBc 坏字符数组
@m 需要匹配的字符串长度
@
*/
void PreBmBc(char *pattern,int m,int bmBc[])
{
    int i;
    for(i=0;i<256;i++){//一个字符占八位，共256个字符，把所有字符都覆盖到，这里的初始化是将所有字符失配时的移动距离都赋值为m
        bmBc[i]=m;
    }
    for(i=0;i<m-1;i++){//针对模式串pattern中存在的每一个字符，计算出它们最靠右的（非最后一个字符）地方距离串末尾的距离，即它们失配时该移动的距离,这一操作更新了初始化中一些字符的移动距离
        bmBc[pattern[i]]=m-1-i;
    }
}
/*
function:
		旧版的好后缀辅助数组（好后缀长度）求解方法
Param:
@pattern 需要匹配的字符串
@suff 好后缀辅助数组
@m 需要匹配的字符串长度
*/
void suffix_old(char *pattern,int m,int suff[])
{
    int i,j;
    suff[m-1]=m;
    for(i=m-2;i>=0;i--){
        j = i;
        while(j>=0&&pattern[j]==pattern[m-1-i+j]) j--; 
        suff[i]=i-j;
    }
}
/*
function:
		新版的好后缀辅助数组（好后缀长度）求解方法
Param:
@pattern 需要匹配的字符串
@suff 好后缀辅助数组
@m 需要匹配的字符串长度
*/
void suffix(char *pattern,int m,int suff[]) {
   int f, g, i;
   suff[m-1]=m;
   g=m-1;
   for(i=m-2;i>=0;--i){
      if(i>g&&suff[i+m-1-f]<i-g)
         suff[i]=suff[i+m-1-f];
      else {
         if(i< g)
            g=i;
         f=i;
         while(g>=0&&pattern[g]==pattern[g+m-1-f])
            --g;
         suff[i]=f-g;
      }
   }
}
/*
function:
		好后缀数组求解方法
Param:
@pattern 需要匹配的字符串
@bmGs 好后缀数组
@m 需要匹配的字符串长度
*/
void PreBmGs(char *pattern,int m,int bmGs[])
{
    int i, j;
    int suff[maxNum];  
    // 计算后缀数组
    suffix(pattern,m,suff);
    // 先全部赋值为m，包含Case3
    for(i=0;i<m;i++){
        bmGs[i]=m;
    }
    // Case2
    j=0;
    for(i=m-1;i>=0;i--){
        if(suff[i]==i+1){
            for(;j<m-1-i;j++){
                if(bmGs[j]==m)
                    bmGs[j]=m-1-i;
            }
        }
    }
    // Case1
    for(i=0;i<=m-2;i++){
        bmGs[m-1-suff[i]]=m-1-i;
    }
}
/*
function:
		Boyer-Moore字符匹配算法
Param:
@text 文本内容
@n 文本内容长度
@pattern 需要匹配的字符串
@m 需要匹配的字符串长度
*/
char* BoyerMoore(char *text,int n,char *pattern,int m,int bmBc[],int bmGs[])
{
    int i,pos;
    
    pos=0;
    while(pos<=n-m){
        for(i=m-1;i>=0&&pattern[i]==text[i+pos];i--);
        if(i < 0){
            return &text[pos];
        }
        else{
            pos+=MAX(bmBc[text[i+pos]]-m+1+i,bmGs[i]);
        }
    }
    return NULL;
}
//////////////////////////horspool////////////////////////////////
/*
function:horspool字符匹配算预处理
Param:
@P 需要匹配的字符串
@lenP 需要匹配的字符串长度
*/
void horspoolPre(int hors_d[],char* P,int lenP)
{
    int i;
    for(i=0;i<maxNum;i++){
        hors_d[i]=lenP;
    }
    for(i=0;i<(lenP-1);i++){
        hors_d[P[i]]=lenP-i-1;
    }
}
/*
function:horspool字符匹配算法
Param:
@T 文本内容
@lenT 文本内容长度
@P 需要匹配的字符串
@lenP 需要匹配的字符串长度
@hors_d[] 辅助数组
*/
char* horspool(char *T, int lenT, char *P, int lenP,int hors_d[])  
{  
    int i,pos,j; 
    pos=0;  
    while(pos<=(lenT-lenP)){  
        j=lenP-1;  
        while(j>=0&&T[pos+j]==P[j]) j--;  
        if(j==-1){
            return &T[pos];
        }            
        else{  
            pos+=hors_d[T[pos+lenP-1]];
        }
    }  
    return NULL;  
}