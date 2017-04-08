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

static char sqrcode[1024*1024];
int create_qr_code(const char *str)
{
    memset(sqrcode, 0, sizeof(sqrcode));
    size_t index = 0;
    QRcode *qrcode=QRcode_encodeString(str, 2, QR_ECLEVEL_L, QR_MODE_8, 0);
    for (size_t i = 0; i < 25; ++ i) {
        for (size_t j = 0; j < 25; ++ j) {
            if(qrcode->data[i*25+j]&0x01) {
                char _[] = "\033[45m  \033[0m";
		strcpy(sqrcode+index, _);
		index += strlen(_);
                printf("#");
            } else {
                char _[] = "\033[46m  \033[0m";
		strcpy(sqrcode+index, _);
		index += strlen(_);
                printf("_");
            }
        }
        sqrcode[index++] = '\n';
        printf("\n");
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
    char url_buff[1024] = {0};
    sprintf(url_buff, 'http://ec2-35-163-82-25.us-west-2.compute.amazonaws.com:8001/register?key=%d', rand()); 
    create_qr_code(url_buff);
    resp_message.msg = sqrcode;
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
