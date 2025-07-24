#include"friendmodel.hpp"
#include"db.h"
using namespace std;
//添加好友关系
void FriendModel::insert(int userid, int friendid)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into friend values(%d, '%d')", userid, friendid);
    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql); 
    }
}
//删除好友关系
void FriendModel::remove(int userid, int friendid)
{

}
//返回用户的好友列表
vector<User> FriendModel::query(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "select a.id, a.name, a.state from User a inner join friend b on b.friendid = a.id where b.userid = %d", userid);
    vector<User> vec;
    MySQL mysql;
    if(mysql.connect())
    {
       MYSQL_RES* res = mysql.query(sql); //执行删除操作
       if(res != nullptr)
       {
           
        //把用户的离线消息存储到vec中
        MYSQL_ROW row;
        while((row = mysql_fetch_row(res)) != nullptr)
        {
            User user;
            user.setId(atoi(row[0])); //row[0]是好友id
            user.setName(row[1]); //row[1]是好友名称
            user.setState(row[2]); //row[2]是好友状态
            vec.push_back(user); //存储到vec中
        }
        mysql_free_result(res); //释放结果集
        return vec; //返回查询到的离线消息
        }
    return vec;
}
return vec;
}