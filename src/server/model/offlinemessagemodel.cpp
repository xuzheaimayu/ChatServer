#include"offlinemessagemodel.hpp"
#include"db.h"
#include<iostream>
using namespace std;


//存储用户的离线消息
void offlineMsgModel::insert(int userid, const string& msg)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemessage values(%d, '%s')", userid, msg.c_str());
    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql); //执行插入操作
    }

}
//删除用户的离线消息
void offlineMsgModel::remove(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "delete from offlinemessage where userid = %d", userid);
    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql); //执行删除操作
    }
}
//查询用户的离线消息
vector<string> offlineMsgModel::query(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "select message from offlinemessage where userid = %d", userid);
    vector<string> vec;
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
            vec.push_back(row[0]); //row[0]是离线消息
        }
        mysql_free_result(res); //释放结果集
        return vec; //返回查询到的离线消息
        

       }
    }
    return vec;
}

