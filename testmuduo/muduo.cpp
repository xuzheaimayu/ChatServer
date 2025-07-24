/**
 *muduo网络库提供给用户两个主要的类
 TcpServer和TcpClient。
 *TcpServer用于实现服务器端的功能，TcpClient用于实现客户端的功能。
 */
#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include<iostream>
#include<functional>
#include<string>
using namespace std;
using namespace muduo;
using namespace muduo::net;

//基于muduo网络库开发服务器程序
/*1.组合TCPSERVER对象
  2.创建EventLoop事件循环对象的指针
  3.明确Tcpserver构造函数需要什么参数，输出ChatServer的构造函数  
  4.在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数
  5.设置合适的服务器线程池大小
*/
class ChatServer
{
public:
    ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg)
        : _server(loop, listenAddr, nameArg) //传入EventLoop对象的引用
    {
        //给服务器注册用户连接的创建和断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
        //给服务器注册用户读写事件的回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        //设置服务器的线程池大小 一个I/O线程和 三个工作线程
        _server.setThreadNum(4); //设置线程池的大小为3
    }
    //启动服务器
    void start()
    {
        //启动服务器
        _server.start();
    }
private:
    //处理用户的连接创建和断开
    void onConnection(const TcpConnectionPtr &conn)
    {
        cout<<conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<endl;
        if (conn->connected())
        {
            cout<<conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<" is connected" << endl;
        }
        else
        {
            cout<<conn->peerAddress().toIpPort()<<"->"<<conn->localAddress().toIpPort()<<" isn't connected" << endl;
        }
        //如果连接断开了，关闭连接
        if (!conn->connected())
        {
            conn->shutdown(); //关闭连接
        }
    }
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
    {
        string msg = buf->retrieveAllAsString(); //获取消息
        cout << "Received message: " << msg << " at " << time.toString() << endl;
        //回显消息给客户端
        conn->send(msg); //将消息发送回客户端
    }
    TcpServer _server;
    //EventLoop _loop; //epoll
    //TcpServer对象的构造函数需要传入EventLoop对象的引用

};

int main()
{
    //创建EventLoop对象
    EventLoop loop;
    //创建InetAddress对象，指定服务器监听的IP地址和端口号
    InetAddress addr("127.0.0.1",6000); //监听8888端口
    //创建ChatServer对象
    ChatServer server(&loop, addr, "ChatServer");
    //启动服务器
    server.start();
    //进入事件循环
    loop.loop();
    return 0;
}