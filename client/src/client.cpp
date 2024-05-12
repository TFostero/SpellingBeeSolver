#include "client.h"

int main() {   
    struct sockaddr_un addr;
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("Client socket fd = %d\n", sfd);

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_ADDR, sizeof(addr.sun_path) - 1);

    // block until connected
    printf("Client waiting to connect\n");
    for(;;) {
        if(connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == 0) { 
            break;
        }
    }

    for (;;) {
        string optionalChars;
        string requiredChars;
        letters_t letters;
        memset(&letters, 0, sizeof(letters));
        char optionalCharsArray[26 + 1];
        char requiredCharsArray[26 + 1];
        cout << "Input optional characters: ";
        getline(cin, optionalChars);
        cout << "Input required characters: ";
        getline(cin, requiredChars);

        strcpy(letters.optional, optionalChars.c_str());
        strcpy(letters.required, requiredChars.c_str());

        write(sfd, &letters, sizeof(letters));
    }

    return 0;
}
