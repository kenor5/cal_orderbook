## 关于分支
* v1 读算存解耦版本
* v2 为方便部署到k8，将进程间通信部分去掉，单体版本
* v3 在v2的基础上，计算单位为一个文件夹

## 关于目录

.
├── bin                    启动文件生成目录 
├── data                   数据目录
├── dockerfile             应用程序打包成docker镜像，当你更新程序内容后，打包命令为 `docker build -t [目标镜像名称，e.g. csob:v1.0] .`
├── include
│   ├── basic.h            定义基本数据结构，如 instrument_t、trade_t、order_t
│   ├── calculate.h        计算过程中的存储结构，如 orderbook_t
│   ├── getbasic.h         从csv文件中读取的接口
│   ├── RapidCSV.h         引用的库文件
│   ├── skipList.h         skiplist 用在 calculate.h 中
│   └── utils.h            工具函数
├── Makefile
├── README.md
├── script                 脚本
│   ├── kc.sh              kubectl 的快捷操作
│   ├── start.sh           计算任务在 k8s 集群上的启动脚本
│   └── test.sh            运行时间统计
├── src
│   ├── calculate.cpp      
│   ├── getbasic.cpp       
│   └── main.cpp
└── yaml                   声明k8s pod的配置等，部署方式为`kubectl apply -f [*.yaml]`,因为其中有环境变量，所以搭配start.sh 使用
    ├── csob_pod.yaml      将计算任务启动为 Pod，特点为：运行完即结束，batch job
    └── csob.yaml          将计算任务启动为 Deployment，特点为：多备份、容错

6 directories, 23 files


## 如何启动

### 在本地启动
* `make all` 生成可执行文件
* `./csob [dir path]` 执行

### 在集群中启动
* `docker build -t csob:v1.0 .` 构建镜像
* `./script/start.sh` 在集群中启动，在start.sh中，需要指订的内容有
    * `ImageName` 镜像名称
    * `YamlName` yaml文件路径
    * `ProJN` 计算任务在集群中的名称（不同计算任务不能重复）