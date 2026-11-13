#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int res = 0;
    if((argc < 2) || (strcmp("-h", argv[1]) == 0)){
        printf("USAGE--\n");
        printf("-h - shows this\n");
        printf("-g PACKAGE - gets and installs the PACKAGE package\n");
    }
    else if((strcmp("-g", argv[1])) == 0){
        printf("Checking for connection...\n");
        res = system("nc -zv disee.ddns.net 21\n");
        if(res != 0){
            printf("Connection to disee.ddns.net:21 failed\n");
            return 1;
        }
        else{
            printf("Connection Success!\n");
            if(argc < 3){
                printf("Please specify a package\n");
                return 1;
            }
            char sdiasda[231] = "ls /var/log/packages | grep -i ";
            strcat(sdiasda, argv[2]);
            res = system(sdiasda);
            if(res == 0){
                printf("Package: %s already installed.\n", argv[2]);
                return 1;
            };
            system("rm /tmp/*.tar.xz");
            system("rm /tmp/*.tar.xz.*");
            system("rm /tmp/*.tgz");
            char closer[512] = ".tar.xz -P /tmp/";
            char opener[512] = " wget -4 ftp://disee.ddns.net/";


            strcat(opener, argv[2]);
            strcat(opener, closer);
            res = system(opener);
            if(res != 0){
                printf("Download failed.\n");
                return 1;
            }
            else{
                printf("Download Succeeded, continuing...\n");
                system("mkdir /tmp/seatbelt_tmp");
                system("tar xvf /tmp/*.tar.xz -C /tmp/seatbelt_tmp/");

                res = system("find /tmp/seatbelt_tmp/*/depend.sh");
                printf("Resolving Dependencies...\n");
                if(res != 0){
                    printf("WARNING: NO DEPENDANCY FILE FOUND\n");
                    printf("this means that most likely to package you are trying to install was\n made incorrectly, please contact the creator of this package\n");
                    return 1;
                }
                else{
                    system("chmod +x /tmp/seatbelt_tmp/*/depend.sh");
                    system("/tmp/seatbelt_tmp/*/depend.sh");
                    res = system(opener);
                    system("tar xvf /tmp/*.tar.xz -C /tmp/seatbelt_tmp/");
                }           

                system("chmod +x /tmp/seatbelt_tmp/*/build/*.SlackBuild");
                res = system("/tmp/seatbelt_tmp/*/build/*.SlackBuild");
                if(res != 0){
                    printf("Compilation failed for some reason.\n");
                    return 1;
                }
                system("sleep 1");
                res = system("installpkg /tmp/*.tgz");
                if(res != 0){
                    printf("Installation failed for some reason.\n");
                    return 1;
                }
            };
        };
    }
    return 0;
}