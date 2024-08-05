#ifndef SSH_CLIENT_H
#define SSH_CLIENT_H

#include <iostream>
#include <sys/statvfs.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>
#include <libssh/libsshpp.hpp>
#include <libssh/sftp.h>


int run_remote_cmd(ssh_session session) {
    ssh_channel channel;
    int rc;
    char buffer[256];
    int nbytes;

    // step1: start new channel
    channel = ssh_channel_new(session);

    // step2: channel open new sub-session
    rc = ssh_channel_open_session(channel);

    // step3: send remote command request
    rc = ssh_channel_request_exec(channel, "ls");

    // step4: read remote resoonse back
    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    while (nbytes > 0) {
        std::cout << buffer << std::endl;
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    }

    // step5: send channel EOF to remote
    ssh_channel_send_eof(channel);

    // step6: close channel
    ssh_channel_close(channel);

    // step7: free channel
    ssh_channel_free(channel);

    rc = SSH_OK;
    return rc;
}

#endif
