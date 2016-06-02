#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
int main(int argc, char* argv[])
{
    CURL *curl;
    //CURLcode res;           //定义CURLcode类型的变量，保存返回状态码
    if(argc > 2)
    {
        printf("输入./getishadow <us/hk/jp>  后面不加地点名称默认是us\n");
        return 0;
    }

    curl = curl_easy_init();
    if(curl!=NULL)
    {
        //设置curl选项. 其中CURLOPT_URL是让用户指定url.
        //curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_URL, "www.ishadowsocks.net");

        char fileName[128] = {0};
        sprintf(fileName, "%s.txt", "ishadowsocks");

        FILE *file = NULL;
        if ((file = fopen(fileName, "w")) == NULL) {
            curl_easy_cleanup(curl);
            return -1;
        }
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        
        //调用curl_easy_perform 执行我们的设置.并进行相关的操作. 在这里是存到文件中
        curl_easy_perform(curl);
        //res = curl_easy_perform(curl);
        //清除curl操作.
        curl_easy_cleanup(curl);

        fclose(file);

        ifstream in(fileName);
        if (in) {
            ostringstream os;   //加载文件到sstream流
            os << in.rdbuf();
            string content(os.str());   //sstream流转换成字符串类

            string::size_type pos = 0;
            string s1;
            if(argc == 2){
                if(argv[1][0] == 'j' && argv[1][1] == 'p'){
                    pos = content.find("C密码");
                    s1 = "nohup sslocal -s jp3.iss.tf -p 443 -k \"";
                }else if(argv[1][0] == 'h' && argv[1][1] == 'k'){
                    pos = content.find("B密码");
                    s1 = "nohup sslocal -s hk2.iss.tf -p 8989 -k \"";
                }else{
                    std::cout << "输入错误，请重试！节点名称为us/hk/jp" << std::endl;
                    return 0;
                }
            }else if(argc == 1){
                pos = content.find("A密码");
                s1 = "nohup sslocal -s us1.iss.tf -p 443 -k \"";
            }

            //查找关键字
            if (string::npos != pos) {
                string s2 = "\" -l 1080 -t 300 -m aes-256-cfb &";
                s1 = s1 + content.substr(pos + 8, 8) + s2;
                char a[100];
                strcpy(a, s1.c_str());
                //std::cout << a << std::endl;

                FILE *fp;

                char buffer[100];
                fp = popen("pgrep sslocal", "r");
                fgets(buffer, sizeof(buffer), fp);
                if (!feof(fp)) {
                   char cmd[] = "kill ";
                   strcat(cmd, buffer);
                   //std::cout << cmd << std::endl;
                   system(cmd);
                }
                pclose(fp);

                system(a);
            }


            in.close();
        }
        //remove(fileName);
    }
    return 0;
}
