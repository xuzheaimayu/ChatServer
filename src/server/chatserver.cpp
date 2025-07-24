#include"chatserver.hpp"
#include"chatservice.hpp"
#include"json.hpp"
#include<functional>
#include <iostream>
#include<string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
using json = nlohmann::json;
ChatServer::ChatServer(EventLoop* loop, 
                const InetAddress& listenAddr, 
                const string& nameArg)
                :_server(loop, listenAddr, nameArg),
                _loop(loop)
                {
                    //注册连接回调
                    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this,_1));

                    //注册消息回调
                    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

                    //设置线程池
                    _server.setThreadNum(4); //设置线程池的线程数量为4
                }

void ChatServer::start()
{
    //启动服务器
    _server.start();
    //开启事件循环
    _loop->loop();
}
//上报链接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn); //重置连接
        conn->shutdown(); //如果连接断开，关闭连接
        cout << "ChatServer - " << conn->name() << " has disconnected." << endl;

    }
}
//上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp time)
{
    string buf = buffer->retrieveAllAsString(); //获取缓冲区中的所有数据
    json js = json::parse(buf); //解析JSON数据,数据的反序列化
    //通过js["msgid"]，获取一个业务handler
    auto msgHandler =  ChatService::instance()->getHandler(js["msgid"].get<int>());
    //回调消息绑定好的事件处理器，来执行相应的业务处理
    msgHandler(conn, js, time); 
}