#include <iostream>
#include "HIMC_API.h"
#include <string>

void EventCallBackFunction(int);
void ErrorCallBackFunction(int);

int main(){
    int ctrl_id = -1;
    ComInfo com_setting;
    com_setting.type = COM_TYPE_TCPIP;
    memcpy(com_setting.TCP_IP.ip, "169.254.188.20", strlen("169.254.188.20") + 1);
    memcpy(com_setting.TCP_IP.port, "5555", strlen("5555") + 1);

     // connect to HIMC
    HIMC_ConnectCtrl(com_setting, &ctrl_id);
     // HIMC_ConnectToSimulator(&ctrl_id);

    HIMC_SetHmplEvtCallback(ctrl_id,EventCallBackFunction);
    HIMC_SetErrorCallback(ctrl_id,ErrorCallBackFunction);

    HIMC_Enable(ctrl_id, 0);
    std::cout << "Hello World..." << std::endl;
    system("pause");
    HIMC_DisconnectCtrl(ctrl_id);

    return 0;
}  

void EventCallBackFunction(int event_id)
{
    std::cout<<"Get event ID: "<< event_id << "\n";
}
// Handle Error Message Callback
void ErrorCallBackFunction(int event_id)
{
    char name[512];
    int name_len=0;
    char description[512];
    int description_len;
    HIMC_GetErrorInformation(event_id,name,512,&name_len,description,512,&description_len);

    std::cout<<name<<"\n"<<description<<"\n";
}
