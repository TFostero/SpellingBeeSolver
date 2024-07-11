#include "Solver.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include <vector>
#include <string>
#include <thread>

#define SOCKET_PATH "/tmp/sbsolver.sock"

using namespace std;

typedef struct letters_s {
    char required[26 + 1];
    char optional[26 + 1];
} letters_t;

bool socketExists() {
    struct stat socketStat;
    if (stat(SOCKET_PATH, &socketStat) == 0) {
        if (S_ISSOCK(socketStat.st_mode)) {
            return true; 
        }
    }
    return false;
}

int createServerSocket() {
    struct sockaddr_un server_addr{};
    int sfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (sfd < 0) {
        perror("socket");
        exit(1);
    }

    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (socketExists()) {
        remove(SOCKET_PATH);
    }

    if (bind(sfd, (struct sockaddr *) &server_addr, sizeof(server_addr))) {
        perror("bind");
        close(sfd);
        exit(1);
    }

    if (listen(sfd, 1)) {
        perror("listen");
        close(sfd);
        exit(1);
    }

    chmod(SOCKET_PATH, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    
    return sfd;
}

int awaitClientConnection(int sfd) {
    struct sockaddr_un  client_addr{};
    printf("Waiting to accept a connection...\n");
    socklen_t client_len = sizeof(client_addr);
    int cfd = accept(sfd, (struct sockaddr *) &client_addr, &client_len);
    if (cfd < 0) {
        perror("accept");
        close(sfd);
        exit(1);
    }
    printf("Accepted socket fd = %d\n", cfd);
    return cfd;
}

int main() {  
    const unsigned int buf_length = 4096; 
    unsigned int threads = thread::hardware_concurrency(); 
    Solver solver(threads);

    int sfd = createServerSocket();

    while (true) {
        int cfd = awaitClientConnection(sfd);
        int read_result;
        letters_t letters;
        while ((read_result = read(cfd, &letters, sizeof(letters))) <= 0) {
            
        }
        cout << "Server optional letters: " << letters.optional << endl;
        cout << "Server required letters: " << letters.required << endl;
        string optional(letters.optional);
        string required(letters.required);

        solver.solve(optional, required);

        vector<string> results = solver.solve(optional, required);

        sort(results.begin(), results.end());

        vector<char> chars;

        for (auto& result : results) {
            for (char c : result) {
                chars.emplace_back(c);
            }
            chars.emplace_back(0);
        }

        cout << "Write size: " << chars.size() << endl;
        write(cfd, chars.data(), chars.size());

        close(cfd);
    }

    return 0;
}
