#ChatServer
一个工作在nginx tcp负载均衡环境下的集群聊天服务器和客户端源码 基于muduo网络库实现


编译方式
cd build
rm -rf *
cmake ..
make

需要nginx的负载均衡
