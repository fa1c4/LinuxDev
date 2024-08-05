#include "sshClient.h"
#include <unistd.h>
#include <libssh/libssh.h>


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: sshClient <server addr> <port> <login_id>" << std::endl;
        // ./sshClient.elf 127.0.0.1 22 fa1c4
    }

    int mPort = std::stoi(argv[2]);
    int verbosity = SSH_LOG_NOLOG;
    int rc = 0;

    // step1: start a new SSH session
    ssh_session mSession = ssh_new();
    if (mSession == NULL) {
        exit(-1);
    }

    // step2: setup session options
    ssh_options_set(mSession, SSH_OPTIONS_HOST, argv[1]);
    ssh_options_set(mSession, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(mSession, SSH_OPTIONS_PORT, &mPort);

    // step3: session connect to remote
    rc = ssh_connect(mSession);
    if (rc != SSH_OK) {
        std::cout << "Error connecting to localhost: " << ssh_get_error(mSession) << std::endl;
        exit(-2);
    }

    // step4: authenticate login/passwd
    char *pPass = getpass("Password: ");
    rc = ssh_userauth_password(mSession, argv[3], pPass);
    if (rc != SSH_AUTH_SUCCESS) {
        std::cout << "Error authenticating with password: " << ssh_get_error(mSession) << std::endl;
        ssh_disconnect(mSession);
        ssh_free(mSession);
        exit(-3);
    }

    // step5: exec command on remote
    rc = run_remote_cmd(mSession);
    std::cout << "Remote Executing Success" << std::endl;

    // step6: disconnect and free session
    ssh_disconnect(mSession);
    ssh_free(mSession);
    return rc;
}
