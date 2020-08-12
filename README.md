# simple webserver

处理简单HTTP请求的Web Server，只处理请求行，忽略首部。

使用wrk请求1KiB文件，测试对比性能。

```shell
./wrk -c 80 -t 4 --latency -d 60 http://127.0.0.1:5005/1KiB.txt
```



## 单进程

![image-20200811005929331](img/image-20200811005929331.png)

## 多进程

![image-20200811011816731](img/image-20200811011816731.png)

## 多线程

![image-20200812221840443](img/image-20200812221840443.png)

## 单进程select

![image-20200811012025817](img/image-20200811012025817.png)

## 单进程poll

![image-20200812231128288](img/image-20200812231128288.png)

## 单进程epoll

![image-20200813001924223](img/image-20200813001924223.png)

## 线程池

![image-20200811012903708](img/image-20200811012903708.png)
