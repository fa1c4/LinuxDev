#include "sshCMD.h"
#include <unistd.h>
#include <libssh/libssh.h>
#include <future>
#include <vector>


struct TH_PARAM
{
    int tid;
    char tServer[32];
    int tPort;
    char tLogin[32];
    char tPassWd[32];
    char tCommand[256];
    TH_PARAM(): tid(0), tPort(0) {
        memset(tServer, '\0', sizeof(tServer));
        memset(tLogin, '\0', sizeof(tLogin));
        memset(tPassWd, '\0', sizeof(tPassWd));
        memset(tCommand, '\0', sizeof(tCommand));
    }
};

int ssh_session_function(const struct TH_PARAM& inParam) {
    int rc = 0;
    struct TH_PARAM mParam;
    char mCmd[256];

    std::cout << "[" << inParam.tid << "]" << inParam.tLogin << "@" << inParam.tServer;
    std::cout << ":" << inParam.tPort << " " << inParam.tCommand << std::endl;

    // step1: start a new SSH session
    rc = ssh_init();
    ssh_session mSession = ssh_new();
    if (mSession == NULL) {
        exit(-1);
    }

    // step2: setup session options
    int verbosity = SSH_LOG_NOLOG;
    ssh_options_set(mSession, SSH_OPTIONS_HOST, inParam.tServer);
    ssh_options_set(mSession, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(mSession, SSH_OPTIONS_PORT, &inParam.tPort);

    // step3: session connect to remote
    rc = ssh_connect(mSession);
    if (rc != SSH_OK) {
        std::cout << "Error connecting to localhost: " << ssh_get_error(mSession) << std::endl;
        exit(-2);
    }

    // step4: authenticate login/password and knownhost
    rc = verify_knownhost(mSession);
    rc = ssh_userauth_password(mSession, inParam.tLogin, inParam.tPassWd);
    if (rc != SSH_AUTH_SUCCESS) {
        std::cout << "Error authenticating with password: " << ssh_get_error(mSession) << std::endl;
        ssh_disconnect(mSession);
        ssh_free(mSession);
        exit(-3);
    }

    // step5: exec command on remote
    memset(mCmd, '\0', sizeof(mCmd));
    memcpy(mCmd, inParam.tCommand, strlen(inParam.tCommand));
    rc = run_remote_cmd(mSession, mCmd);

    // step6: disconnect and free session
    ssh_disconnect(mSession);
    ssh_free(mSession);
    ssh_finalize();

    return rc;
}

int main(int argc, char* argv[]) {
    int rc = 0;
    char mCommand[256];

    if (argc < 5) {
        std::cout << "Usage: sshCmd <server> <port> <login_id> <command> [commands ...]" << std::endl;
        exit(-1);
    }

    struct TH_PARAM mParam;
    std::vector<std::string> cmdVec;

    memcpy(mParam.tServer, argv[1], strlen(argv[1]));
    mParam.tPort = std::stoi(argv[2]);
    memcpy(mParam.tLogin, argv[3], strlen(argv[3]));
    // memcpy(mParam.tCommand, argv[4], strlen(argv[4]));

    // push all commands from argc
    for (int i = 4; i < argc; ++i) {
        cmdVec.push_back(std::string(argv[i]));
    }

    rc = ssh_getpass("Password: ", mParam.tPassWd, sizeof(mParam.tPassWd), 0, 0);
    unsigned int totCmd = cmdVec.size();
    for (unsigned int i = 0; i < totCmd; ++i) {
        mParam.tid = i;
        std::string sCmd = cmdVec.at(i);
        memset(mParam.tCommand, '\0', sizeof(mCommand));
        memcpy(mParam.tCommand, sCmd.c_str(), sCmd.length());
        rc = ssh_session_function(mParam);
    }

    cmdVec.clear();
    return rc;
}
