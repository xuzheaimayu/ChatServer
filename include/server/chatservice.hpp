#ifndef CHATSERVICE_HPP
#define CHATSERVICE_HPP
#include<unordered_map>
#include<functional>
#include<mutex>
#include<muduo/net/TcpConnection.h>

#include"redis.hpp"
#include"groupmodel.hpp"
#include "friendmodel.hpp"
#include"usermodel.hpp"
#include"offlinemessagemodel.hpp"
#include"json.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;
//表示处理消息的事件的回调类型
using MsgHandler = std::function<void(const TcpConnectionPtr& conn, json& js, Timestamp)>;
//聊天服务器业务类
class ChatService
{

public:
    // 获取单例对象的接口函数
    static ChatService *instance();
    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    // 服务器异常，业务重置方法
    void reset();
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    void handleRedisSubscribeMessage(int userid, string msg);

private:
    ChatService();
    //存储消息id和对应的业务处理器
    unordered_map<int, MsgHandler> _msgHandlerMap; 

    //存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    //单例对象的互斥锁,保证线程安全
    mutex _connMutex;

    //数据操作类对象
    UserModel _userModel;

    //离线消息操作类对象
    offlineMsgModel _offlineMsgModel;

    //好友关系操作类对象
    FriendModel _friendModel;

    //群组操作类对象
    GroupModel _groupModel;

    //redis操作对象
    Redis _redis;
};







#endif