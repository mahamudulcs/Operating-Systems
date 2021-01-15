/*
Q3:
Because kirk is the sender here.The spock recieves what kirk sends.
If kirk ends then the message can not be sent anymore.As a result when kirk ends spock elso ends.
Q4:
When starting spock first, I get an error as the output which is “msgget: No such file or directory.”
It's because starting spock instead of kirk.
As kirk is the sender which did not send anything to be received by spock I am getting that output. 
Q5:
Doing that spock will not end. Because it is connected to kirk. It will only end when kirk stop sending any messages.
Q7:
It deletes the message queue by using a particular function which is msgct1().
Q8:
The process scheduling of this runs in a queue.Which one comes first should be done first.
It follows an order in the queue.
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct my_msgbuf {
   long mtype;
   char mtext[200];
};
int main(int argc, char **argv) {
   struct my_msgbuf buf;
   int msqid;
   key_t key;
   if(argc != 2) {
       printf("Arguments missing\n");
       return 0;
   }
   key = atoi(argv[1]);
   if(key == 0 && (argv[1][0] != '0' && argv[1][1] != '\0')) {
       printf("Input not an integer\n");
       return 0;
   }
   if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
       perror("msgget");
       exit(1);
   }
   printf("Enter lines of text, ^D to quit:\n");
   buf.mtype = 1; /* we don't really care in this case */
   while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
       int len = strlen(buf.mtext);
       if (buf.mtext[len-1] == '\n')
           buf.mtext[len-1] = '\0';
       if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
           perror("msgsnd");
   }
   if (msgctl(msqid, IPC_RMID, NULL) == -1) {
       perror("msgctl");
       exit(1);
   }
   return 0;
}

