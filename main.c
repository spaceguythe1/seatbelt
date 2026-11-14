#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int res = 0;
    if((argc < 2) || (strcmp("-h", argv[1]) == 0)){
        printf("USAGE--\n");
        printf("-h - shows this\n");
        printf("-g PACKAGE - gets and installs the PACKAGE package\n");
        printf("-v - shows your version and build date\n");
        printf("-r PACKAGE - removes PACKAGE package, can be useful for updates.");
    };

    if((strcmp("-v", argv[1])) == 0){
        printf("SEATBELT - Slackware compiling package manager.\n");
        printf("v1.57 - 14/11/2026\n");
    };

    if((strcmp("-r", argv[1])) == 0){
        if(argc < 3){
                printf("Please specify a package\n");
                return 1;
        }
        printf("Searching for %s in /var/log/packages...\n", argv[2]);
        char sdiasda[231] = "ls /var/log/packages | grep ";
        strcat(sdiasda, argv[2]);
        res = system(sdiasda);
        if(res == 0){
            printf("Removing %s...\n", argv[2]);
            char removepkg[512] = "removepkg ";
            strcat(removepkg, argv[2]);
            res = system(removepkg);
            if(res != 0){
                printf("Package removal failed for some reason.\n");
                return 1;
            }
            return 0;
        }
        else{
            printf("Package %s not installed.\n", argv[2]);
            return 1;
        }
    }

    if((strcmp("-g", argv[1])) == 0){

        res = system("cd /root/");
        if(res != 0){
            printf("You must be root to run -g!\n");
            return 1;
        }

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
            char sdiasda[231] = "ls /var/log/packages | grep ";
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
                printf("Download failed, This package might not be avaliable or you spelt it wrong.\n");
                return 1;
            }
            else{
                printf("Download Succeeded, continuing...\n");

                char dir[512] = "/tmp/";
                strcat(dir, argv[2]);


                char tar[512] = "tar xvf /tmp/";
                strcat(tar, argv[2]);
                strcat(tar, ".tar.xz -C /tmp/");
                system(tar);

                char rmtar[512] = "rm -f /tmp/";
                strcat(rmtar, argv[2]);
                strcat(rmtar, ".tar.xz");

                char find[512] = "find /tmp/";
                strcat(find, argv[2]);
                strcat(find, "/depend.sh");
                res = system(find);
                
                if(res != 0){
                    printf("WARNING: NO DEPENDANCY FILE FOUND\n");
                    printf("this means that most likely to package you are trying to install was\n made incorrectly, please contact the creator of this package\n");
                    return 1;
                }
                else{

                    char chmod[512] = "chmod +x ";
                    strcat(chmod, dir);
                    strcat(chmod, "/depend.sh");
                    char depend[512] = "";
                    strcat(depend, dir);
                    strcat(depend, "/depend.sh");

                    system(chmod);
                    res = system(depend);
                    if(res != 0){
                        printf("Error occured when dealing with dependencies!");
                        return 1;
                    }
                    
                    char compilemod[512] = "chmod +x ";
                    strcat(compilemod, dir);
                    strcat(compilemod, "/build/*.SlackBuild");
                    char acccompile[512] = "cd ";
                    strcat(acccompile, dir);
                    strcat(acccompile, " && ");
                    strcat(acccompile, dir);
                    strcat(acccompile, "/build/*.SlackBuild");

                    
                    system(compilemod);
                    res = system(acccompile);
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
                    char remove[512] = "rm -r /tmp/";
                    strcat(remove, argv[2]);
                    system(remove);
                }
            };

        };
    }
    return 0;
}