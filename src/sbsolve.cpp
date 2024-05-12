#include "ui.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>


using namespace std;

typedef struct letters_s {
    char required[26 + 1];
    char optional[26 + 1];
} letters_t;

int main() {  
    const unsigned int buf_length = 4096; 
    unsigned int threads = thread::hardware_concurrency(); 
    Solver solver(threads);
    //ui ui;
    //ui.startUI(solver);

    struct sockaddr_un server_addr, client_addr;
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("socket");
    }
    printf("Server socket fd = %d\n", sfd);

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, "/tmp/unix_socket", sizeof(server_addr.sun_path) - 1);
    if (bind(sfd, (struct sockaddr *) &server_addr, sizeof(server_addr))) {
        perror("bind");
        close(sfd);
        exit(1);
    }

    listen(sfd, 1);

    printf("Waiting to accept a connection...\n");
    socklen_t client_len = sizeof(client_addr);
    int cfd = accept(sfd, (struct sockaddr *) &client_addr, &client_len);
    if (cfd < 0) {
        perror("accept");
        close(sfd);
        exit(1);
    }
    printf("Accepted socket fd = %d\n", cfd);

    for (;;) {
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

        for (auto& result : results) {
            cout << result << endl;
        }
    }

    return 0;
}
