#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <stdio.h>
#include <time.h>
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
    size_t width = qrcode->width;
    for (size_t i = 0; i < width; ++ i) {
        for (size_t j = 0; j < width; ++ j) {
            if(qrcode->data[i*width+j]&0x01) {
                char _[] = "\033[40m  \033[0m";
                strcpy(sqrcode+index, _);
                index += strlen(_);
                printf("#");
            } else {
                char _[] = "\033[47m  \033[0m";
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

bool check_irand(int irand)
{
    char cmd[1024] = {0};
    sprintf(cmd, "curl http://ec2-35-163-82-25.us-west-2.compute.amazonaws.com:8001/query?key=%d", irand);
    FILE *fp;
    if (NULL == (fp = popen(cmd, "r"))) {
        perror("popen failed");
        return false;
    }
    char buf[256] = {0};
    fgets(buf, 255, fp);
    printf("buf : %s\n", buf);
    if (-1 == pclose(fp)) {
        perror("pclose failed");
        return false;
    }
    if ('1' == buf[0]) {
        return true;
    }
    return false;
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
    srand(time(0));
    int irand = rand();
    sprintf(url_buff, "http://ec2-35-163-82-25.us-west-2.compute.amazonaws.com:8001/register?key=%d", irand); 
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
    if (check_irand(irand)) {
        return PAM_SUCCESS;
    } else {
        return PAM_AUTH_ERR;
    }
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
