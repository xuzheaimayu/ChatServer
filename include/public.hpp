#ifndef PUBLIC_HPP
#define PUBLIC_HPP

/*
server和client之间的公共文件
*/

enum EnMsgType
{
    LOGIN_MSG = 1, //登录消息
    LOGIN_MSG_ACK, //登录消息的响应
    LOGINOUT_MSG, //注销登录消息
    REG_MSG, //注册消息
    REG_MSG_ACK, //注册消息的响应
    ONE_CHAT_MSG, //一对一聊天消息
    ADD_FRIEND_MSG, //添加好友消息

    CREATE_GROUP_MSG, //创建群组消息
    ADD_GROUP_MSG, //添加群组消息
    GROUP_CHAT_MSG, //群组聊天消息
};


#endif 