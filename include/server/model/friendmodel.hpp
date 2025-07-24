#ifndef FRIENDMODEL_HPP
#define FRIENDMODEL_HPP
#include"user.hpp"
#include <vector>
#include <string>
using namespace std;
//维护好友信息的操作接口方法
class FriendModel
{
public:
    //添加好友关系
    void insert(int userid, int friendid);
    //删除好友关系
    void remove(int userid, int friendid);
    //返回用户的好友列表
    std::vector<User> query(int userid);

private:
};



#endif
