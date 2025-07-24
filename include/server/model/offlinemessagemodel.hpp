#ifndef OFFLINEMESSAGEMODEL_HPP
#define OFFLINEMESSAGEMODEL_HPP
#include <string>
#include <vector>
using namespace std;
//提供离线消息表的操作接口类
class offlineMsgModel
{
    public:
    //存储用户的离线消息
    void insert(int userid, const string& msg);
    //删除用户的离线消息
    void remove(int userid);
    //查询用户的离线消息
    vector<string> query(int userid);


    private:
};


#endif