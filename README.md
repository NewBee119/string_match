# string_match
对比了各类字符串匹配算法
/*
 *  search_test.c
 *  Created on: 2018-7-19
 *  Author: MK
 *  usage:四种字符串匹配算法的实现（Sunday、KMP、Boyer-Moore、horspool）的测试
 */
 各文件说明：
	search_string.h 头文件，包含了对各个函数的声明；
	search_string.c 包含了头文件中所有函数的具体实现；
	search_string.o 由search_string.c编译得到（命令:gcc -c search_string.c）
	search_test.c   主函数，即测试
	search_test		linux下可执行程序，即最终的测试程序，由search_test.c编译链接而得（命令:gcc -o search_test search_test.c search_string.o）

说明：
	本测试是在centos6.4下进行的实验，运行时的截图在文件夹my_image里，可供使用者参考；
	
使用指导：
	（1）、可直接在Linux下运行search_test（命令：./search_test	）进行测试；
	（2）、也可自行修改关键字符串和文本串来进行自己的测试，修改步骤如下：
			a、在search_string.h中将My_TXT修改成自己的文本串（注意换行问题）；
			b、在search_test.c中将pattern修改成自己的关键字符串；
			c、编译链接（具体命令在下一步）；
	（3）、自行编译的命令步骤：
			a、将所有文件放在同一目录下，通过命令行进入该目录，先将search_string.c编译为search_string.o（命令:gcc -c search_string.c）（若未修改search_string.c的内容，这一步可不用，可直接使用所给的search_string.o）；
			b、上一步完成后，输入（命令:gcc -o search_test search_test.c search_string.o）；
			c、完成；

			
详细解说的博文地址：https://blog.csdn.net/qq_33515733/article/details/81163135