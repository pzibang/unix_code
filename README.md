11.5ㄈ章节
内容概述:介绍了三种可以不终止整个进程的情况下退出线程
(1)设置线程的退出码;
(2)线程被同一进程中的其他线程取消;
(3)结束线程pthread_exit.

代码功能描述:
实例一:获得已终止的线程退出码.
thread 1和thread 2退出的方式并不相同,但是都做到了将线程中的数据传到了主线程,通过pthread_join函数可以获得这个数据.ㄎ

实例二:展示了pthread_exit的不正确的使用,ㄍㄋ虽然地址是相同的但是线程结束后,里面的数据已经丢失了.
解决办法是使用全局变量或者使用malloc分配内存.
注意事项:
