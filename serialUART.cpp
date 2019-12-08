#include <iostream>

#include <unistd.h>
#include <fcntl.h>

#include <signal.h>
#include <sys/types.h>

#define DIR "/dev/ttyACM0"

int fd;
int ascii = 65;
char buff[1];

bool serialStop = false;
void ctrlc(int){
    serialStop = true;
}

int main() {

    fd = open(DIR, O_WRONLY, 0666);
    if (fd == -1){
        perror("OPEN ERROR");
        exit(1);
    }

    sleep(5);

    while(1){
        signal(SIGINT, ctrlc);
        if(serialStop) {
            std::cout << "SIGNAL INTERUPT!" << std::endl;
            break;
        }

        buff[0] = char(ascii);

        write(fd, buff, 1);
        
        
        std::cout << "SIGNAL SENT: " << buff[0] << std::endl;
    
        ascii += 1;
        if (ascii > 90) ascii = 65;
        
        usleep(200000);
    }
    std::cout << "SIGNAL CLOSED" << std::endl;

    close(fd);

    return 0;
}