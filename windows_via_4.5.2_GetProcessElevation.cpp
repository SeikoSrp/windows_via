#include <iostream>
#include <windows.h>
#include <Shlobj.h>
#include <winnt.h>

BOOL GetProcessElevation(TOKEN_ELEVATION_TYPE* pELevationType,BOOL* pIsAdmin)
{
    //创建一个令牌句柄
    HANDLE hToken = NULL;
    DWORD dwSize;

    //1、将当前进程的令牌句柄赋值给hToken
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
        return FALSE;


    BOOL bResult = FALSE;
    printf("pELevationType : %x\n", *pELevationType);
    //GetTokenInformation被执行后会将pELevationType修改为当前进程使用的令牌
    if (GetTokenInformation(
        hToken, //Token句柄
        TokenElevationType, //TokenElevationType这个值指的是缓冲区接收一个TOKEN_ELEVATION_TYPE值，该值指定令牌的提升级别。
        pELevationType, //上一个参数指定的TOKEN_ELEVATION_TYPE类型的值存入当前变量
        sizeof(TOKEN_ELEVATION_TYPE), //TOKEN_ELEVATION_TYPE的大小
        &dwSize) )//返回值：指向一个变量dwSize，这个变量接收pELevationType指向的缓冲区的字节数
    {
        printf("TokenElevationType : %d\n", TokenElevationType);
        printf("pELevationType : %x\n", *pELevationType);
        printf("dwSize : %x\n", dwSize);
        BYTE adminSID[SECURITY_MAX_SID_SIZE];//安全标识符（SID）值的最大长度。目前是68
        dwSize = sizeof(adminSID);// 68


        //创建一个用于预定义别名的SID
        CreateWellKnownSid(
            WinBuiltinAdministratorsSid, //WELL_KNOWN_SID_TYPE枚举的成员，WinBuiltinAdministratorsSid的意思是与管理员组匹配的SID
            NULL, //指向SID的指针，该指针标识创建SID时要使用的域。传递NULL以使用本地计算机
            &adminSID, //指向内存的指针，CreateWellKnownSid将在其中存储新的SID
            &dwSize//向dwSize变量，该包含pSid处可用的字节数
        );
        for (int i = 0; i < SECURITY_MAX_SID_SIZE; i++)
        {
            printf("adminSID : %d\n", adminSID[i]);
        }
        

        //判断是否为筛选过的token，如果是，则执行，如果不是，则直接判断（这一步只判断令牌类型，不判断是否为管理员）
        if (*pELevationType == TokenElevationTypeLimited) {
            //创建一个令牌句柄
            HANDLE hUnfilteredToken = NULL;

            GetTokenInformation(
                hToken, 
                TokenLinkedToken, //这个字段表示将链接到此令牌的另一个令牌的句柄写入到下面一个参数hUnfilteredToken中
                (VOID*)&hUnfilteredToken, 
                sizeof(HANDLE), 
                &dwSize);

            //确定token中是否存在某一个SID?
            if (CheckTokenMembership(
                hUnfilteredToken, //访问令牌的句柄。
                &adminSID, //指向SID结构的指针 。所述CheckTokenMembership函数检查上一个token中是否有这个SID
                pIsAdmin//指向接收检查结果的变量的指针。如果SID存在并且具有SE_GROUP_ENABLED属性，则IsMember返回TRUE；否则，返回FALSE。
            )) {
                bResult = TRUE;
            }
            CloseHandle(hUnfilteredToken);
        }
        else {
            *pIsAdmin = IsUserAnAdmin();//直接测试当前用户是否为管理员组的成员
            bResult = TRUE;
        }
    }
    CloseHandle(hToken);
    return(bResult);
}
//判断是否为筛选过的令牌，是，则直接判断是不是管理员组，如果不是，则判断另一个令牌中是否有管理员的SID

int main()
{   //
    TOKEN_ELEVATION_TYPE tokenStruct = TokenElevationTypeDefault;
    BOOL admin = FALSE;
    if (GetProcessElevation(&tokenStruct, &admin))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    BOOL aaa = IsUserAnAdmin();
    if (aaa)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    printf("a: %x\n",_osver);

}

