#ifndef SSH_CMD_H
#define SSH_CMD_H

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


int run_remote_cmd(ssh_session session, char* inCmd) {
    ssh_channel channel;
    int rc;
    char rdBuffer[256];
    int nbytes;

    channel = ssh_channel_new(session);
    rc = ssh_channel_open_session(channel);
    rc = ssh_channel_request_exec(channel, inCmd);

    memset(rdBuffer, '\0', sizeof(rdBuffer));
    nbytes = ssh_channel_read(channel, rdBuffer, sizeof(rdBuffer), 0);
    while (nbytes > 0) {
        printf("%s", rdBuffer);
        memset(rdBuffer, '\0', sizeof(rdBuffer));
        nbytes = ssh_channel_read(channel, rdBuffer, sizeof(rdBuffer), 0);
    }

    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
     (channel);

    rc = SSH_OK;
    return rc;
}

int verify_knownhost(ssh_session session) {
    enum ssh_known_hosts_e state;
    unsigned char *hash = NULL;
    ssh_key srv_pubkey = NULL;
    size_t hlen;
    char buf[16];
    char *hexa, *p;
    int cmp = 0, rc = 0;

    rc = ssh_get_server_publickey(session, &srv_pubkey);
    if (rc < 0) return -1;

    // rc = ssh_get_publickey_hash(srv_pubkey, SSH_PUBLICKEY_HASH_SHA1);
}

#endif
