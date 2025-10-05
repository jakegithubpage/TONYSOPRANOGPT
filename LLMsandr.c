#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winhttp.h>




HINTERNET tsSession = NULL;
HINTERNET tsConnect = NULL;
HINTERNET tsRequest = NULL;

int init_http() {
    tsSession = WinHttpOpen(L"TonyGPT_V1.0",
                           WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                           WINHTTP_NO_PROXY_NAME,
                           WINHTTP_NO_PROXY_NAME, 0);

    if (!tsSession) {
        printf("failed to init sessions, sorry cock sucka :(");
        return 0;
    }
    
}

void cleanHTTP(){
    if (tsRequest) WinHttpCloseHandle(tsRequest);
    if (tsConnect) WinHttpCloseHandle(tsConnect);
    if (tsSession) WinHttpCloseHandle(tsSession);
}


void send_http_request(char* json_data){
    tsConnect = WinHttpConnect(tsSession,L"api.aimlapi.com", 443, 0);

    if(!tsConnect){
        printf("not connecting, what the f**k is wrong wit dis huh?");
        return;
    }

    tsRequest = WinHttpOpenRequest(tsConnect, L"POST", L"/chat/completions",
                                         NULL, NULL, NULL, WINHTTP_FLAG_SECURE);

    if(!tsRequest){
        printf("im unable to create ur damn request");
        return;
    }

    WinHttpAddRequestHeaders(tsRequest,
         L"Content-Type: application/json\r\nAuthorization: Bearer b7159cc8f7434e9e93ed2b25b46b89e1\r\n",
          -1, WINHTTP_ADDREQ_FLAG_ADD);

    WinHttpSendRequest(tsRequest, NULL, 0, json_data, strlen(json_data), strlen(json_data), 0);
}

//input string - FIX to get directly from user
char userInput[512] = "fill for users entered response";

//for sending prompt to LLM
void send_LLM(char* userMessage){
    

    userMessage[strcspn(userMessage, "\n")] = 0;

    char json_data[1000];
    sprintf(json_data, "{"
        "\"model\":\"gpt-3.5-turbo\","
            "\"messages\":["
                "{\"role\":\"system\",\"content\":\"You are Tony Soprano, and talk very new jersey and your kinda an asshole\"},"
                "{\"role\":\"user\",\"content\":\"%s\"}"
            "]"
        "}", userMessage);
        printf("gimme a second, i gotta think.");
        send_http_request(json_data);
} 

//for receiving the response to then go into wrapping
char* receive_LLM(){

    //D WORD use for data reading detection
    //For data size
    DWORD dwSize;
    //Use to see how much data was collected
    DWORD dwDownload;

    //Allocate response size based on data size
   

    
    if(!(WinHttpReceiveResponse(tsRequest, NULL))){
        return NULL; 

    }

    if((!(WinHttpQueryDataAvailable(tsRequest, &dwSize))) || dwSize == 0){
        return NULL;
    }

    char* response = malloc(dwSize + 500);
    //Read data from tony saprano request HINTERNET
    if(WinHttpReadData(tsRequest, response, dwSize, &dwDownload)){
        response[dwDownload] = '\0';
        return response;

    }
    else{
        printf("prompt failed");

    }
    
    //end memory alloc
    free(response);

    return NULL;
}

int main() {
//main interface thing
    printf("Tony Sap Wrappa 1.0\n");
    printf("starting the damn system...\n");

    if(!init_http()){
        return 1;
    }
    //open/done load prompt
    printf("alright whats up, watcha got for me?!\n");
    //create input var and catch users input
    //store it
    char output[512];
    char input[512];
    fgets(input, sizeof(input), stdin);
    //char globalprompt = input;
    //send to the LLM 
    send_LLM(input);

    //Recieve back from API, THEORETICAL TEST
    char* response = receive_LLM();
    

    if (response) { 
        char* content = strstr(response, "\"content\":\"");
        if(content) {
            content += 11;
            char* end = strchr(content, '"');
            if (end) *end = '\0';
            printf("\nTony: %s\n", content);
            
        }
    
    free(response);
    }else{
        printf("Tony aint workin");
    }

    cleanHTTP();
    return 0;


}

