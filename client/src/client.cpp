#include "client.h"

void printUsage() {
    cout << "Usage is \"sbsolve [optional character] [required character]\"" << endl;
    cout << "Example: sbsolve afglom b" << endl;
}

int connectToSocket() {
    struct sockaddr_un addr;
    int sfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_ADDR, sizeof(addr.sun_path) - 1);

    // block until connected
    while (true) {
        if(connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == 0) { 
            break;
        }
    }

    return sfd;
}

void processInput(string& input) {
    for (char& c : input) {
        c = tolower(c);
    }

    input.erase(remove_if(input.begin(), input.end(), [](char c) {
        return c < 'a' || c > 'z';
    }), input.end());
}

int main(int argc, char *argv[]) { 
    if (argc != 3) {
        cout << "Invalid arguments." << endl;
        printUsage();
        exit(1);
    }

    int sfd = connectToSocket();

    auto optionalChars = string(argv[1]);
    auto requiredChars = string(argv[2]);
    processInput(optionalChars);
    processInput(requiredChars);

    letters_t letters{};
    char optionalCharsArray[26 + 1];
    char requiredCharsArray[26 + 1];

    strcpy(letters.optional, optionalChars.c_str());
    strcpy(letters.required, requiredChars.c_str());

    write(sfd, &letters, sizeof(letters));

    struct pollfd read_fd;
    read_fd.fd = sfd;
    read_fd.events = POLLIN;
    read_fd.revents = 0;

    vector<char> buffer(10);

    if (poll(&read_fd, 1, -1) > 0) {
        int readed = 0;
        vector<char> results;
        while ((readed = read(sfd, buffer.data(), buffer.size())) > 0) {
            for (int i = 0; i < readed; i++) {
                results.emplace_back(buffer[i]);
            }
        }

        int offset = 0;
        while (offset < results.size()) {
            cout << results.data() + offset << endl; 
            offset += strnlen(results.data() + offset, results.size()) + 1;
        }
        
    }

    return 0;
}
