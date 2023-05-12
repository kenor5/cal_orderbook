## 关于分支
* v1 读算存解耦版本
* v2 为方便部署到k8，将进程间通信部分去掉，单体版本
* v3 在v2的基础上，计算单位为一个文件夹

## 关于目录

.  
├── bin                    启动文件生成目录   
├── data                   数据目录  
├── include  
│   ├── basic.h            定义基本数据结构，如 instrument_t、trade_t、order_t  
│   ├── calculate.h        计算过程中的存储结构，如 orderbook_t  
│   ├── getbasic.h         从csv文件中读取的接口  
│   ├── RapidCSV.h         引用的库文件  
│   ├── skipList.h         skiplist 用在 calculate.h 中    
│   └── utils.h            工具函数    
├── Makefile    
├── README.md  
├── src  
│   ├── calculate.cpp  
│   ├── datatocalculate.cpp 计算模块，同时和读取和存储交互    
│   ├── getbasic.cpp          
│   ├── main.cpp            读取模块，从 csv 中读数据  
│   └── mongodbstorage.cpp  存储模块，向 mondodb 数据库中写入  
└── sub-pub                 模块间通信用到的工具 redis pub-sub模式  
    ├── Makefile  
    ├── publisher.cpp  
    ├── redis_publisher.cpp  
    ├── redis_publisher.h  
    ├── redis_subscriber.cpp  
    ├── redis_subscriber.h  
    └── subscriber.cpp  
  
5 directories, 26 files 

