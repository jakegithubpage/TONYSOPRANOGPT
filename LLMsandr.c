#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winhttp.h>


HINTERNET tsSession = NULL;
HINTERNET tsConnect = NULL;
HINTERNET tsRequest = NULL;

int init_http() {
    hsession = WinHttpOpen(L"TonyGPT_V1.0",
                           WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                           WINHTTP_NO_PROXY_NAME,
                           WINHTTP_NO_PROXY_NAME, 0);

    if (!hSession) {
        printf("failedt o init sessions, sorry :(");
        return 0;
    }
    else{
        return 1;
    }
}

int main() {
//main interface thing
    printf("Tony Sap Wrappa 1.0\n");
    printf("starting the damn system...\n");

    if(!init_http()){
        return 1;
    }
    else{
        cleanHTTP();
        return 0;
    }


    


}

void cleanHTTP(){
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hRequest) WinHttpCloseHandle(hRequest);
}
//for sending prompt to LLM
void send_LLM(){
} 
//for receiving the response to then go into wrapping
void recieve_LLM(){

}



