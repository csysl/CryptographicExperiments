#include "func.h"

int main() {
    char key[17];
    printf("请输入长度为16个字符的秘钥：\n");
    int klen;
    while (1) {
        getString(key, 17);
        klen = strlen(key);
        if (klen != 16) {
            printf("请输入16个字符的密钥,当前密钥的长度为%d\n", klen);
        } else {
            printf("你输入的密钥为：%s\n", key);
            break;
        }
    }
    MODEL:
    printf("请输入0或1：\n0----ECB\n1----CBC\n");
    int model;
    scanf("%d",&model);
    if(model==0){
        printf("你选择了在ECB模式下进行加密\n");
        aesStrToFile(key,model);//用AES加密字符串，并将字符串写进文件中
    }
    else if(model==1){
        printf("你选择了在CBC模式下进行加密\n");
        aesStrToFile(key,model);//用AES加密字符串，并将字符串写进文件中
    }
    else{
        printf("请选择正确的模式\n");
        goto MODEL;
    }
    return 0;
}
