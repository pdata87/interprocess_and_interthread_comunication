#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <zconf.h>

#define MY_SOCK_PATH "/tmp/socket/s"


int main(){

    int sfd, cfd;
    struct sockaddr_un my_addr, peer_addr;
    socklen_t peer_addr_size;
    // TODO : Sprawdzenie czy socket istnieje

    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if (sfd==-1){
        printf("%s\n", "Couldnt create socket");
    }

    my_addr.sun_family = AF_UNIX;
    strcpy(my_addr.sun_path, MY_SOCK_PATH);


    if (bind(sfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr_un))==-1){
        printf("%s\n", "Couldnt bind to");

    }
    if(listen(sfd,50)== -1){\
      // Wczesniej miałem socket RAW i program nie działał.
        // mailto : karol.barski@tieto,com
        //TODO: Nasłuchiwanie wielu klientów
        printf("%s\n", "Couldnt listen to connection");

    }
    else {
        // TODO: nasłuchwianie
        printf("%s\n", "Listning ...");

        while(1){
                cfd = accept(sfd,(struct sockaddr *)&peer_addr,&peer_addr_size);
                if(cfd == -1){
                    printf("%s\n", "Not Accepted");

                } else {

                    printf("%s\n", "Accepted");
                    write(cfd,"test",strlen("test"));

                }
            }


    }




    return (0);
}
