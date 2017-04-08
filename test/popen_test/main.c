#include <stdlib.h>
int main(int argc, char * argv[])
{
    if (argc < 2) {
        printf("too few arguments.\n");
        return -1;
    }
    const char *url = argv[1];
    char cmd[1024] = "curl ";
    strcpy(cmd+5, url);
    FILE *fp;
    if (NULL == (fp = popen(cmd, "r"))) {
        perror("popen failed");
        return -1;
    }
    char buf[256] = {0};
    fgets(buf, 255, fp);
    printf("buf : %s\n", buf);
    if (-1 == pclose(fp)) {
        perror("pclose failed");
        return -2;
    }
    return 0;
}