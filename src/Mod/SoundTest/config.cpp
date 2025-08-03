#include "config.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QCoreApplication>
#include <QDir>

using namespace SoundTest;

Config::Config()
{
    // 获取应用程序所在目录的绝对路径
    QString appDir = QCoreApplication::applicationDirPath();
    // 拼接配置文件完整路径
    QString configPath = QDir(appDir).filePath("config.txt");
    filename = configPath;

    // 读取配置文件
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QString content = stream.readAll();
        list=new QStringList();

        split_str(list,content,'\n');
        // QStringList list = content.split("\n");

        for (int i=0;i<4;i++){
            // QStringList list2=list[i].split(",");
            list2=new QStringList();
            split_str(list2,(*list)[i],',');
            lingmingduList.append((*list2)[0]);
            lingmingduDanweiList.append((*list2)[1]);

        }

        file.close();
        // 使用content进行后续处理
    } else {
        // 文件打开失败处理
    }

}


void Config::split_str(QStringList* qStringList,QString str_file, char c){
    qStringList->clear();
    int cnt=str_file.length();
    int i;
    int l=0;
    for (i=0;i<cnt;i++){
        if (str_file[i]==c){
            qStringList->append(str_file.mid(l,i-l));
            l=i+1;
        }
    }

    qStringList->append(str_file.mid(l,cnt-l));
    // QStringList s=str_file.split(".");
    // QString s="sdf";
    // qStringList->append(s);
}
