#include "mconnectrun.h"


mConnectRun::mConnectRun()
{

}

void mConnectRun::run() {
    QByteArray inBuffer;
    if (!socketdescriptor) return;

    QTcpSocket mSocket;
    mSocket.setSocketDescriptor(socketdescriptor);
    if (mSocket.isOpen()) {
        mSocket.write("This is from server");
        mSocket.waitForBytesWritten();
        mSocket.flush();
        // loop for sending and receiving messages
        while (mSocket.waitForReadyRead()) {
            inBuffer = mSocket.readAll();
            qInfo() << socketdescriptor << ": " << inBuffer;
            // break loop when receive "quit"
            if (!strncmp(inBuffer, "quit", 4)) {
                break;
            }
            // print out message replied
            mSocket.write("Server Reply: ");
            mSocket.write(inBuffer);
            mSocket.waitForBytesWritten();
            mSocket.flush();
        }
        // close socket before return
        mSocket.close();
    }
}
