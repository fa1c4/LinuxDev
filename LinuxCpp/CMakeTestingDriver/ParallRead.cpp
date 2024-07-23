#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
// #include <thread>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

using namespace std;
#define MAX_THREADS 2

struct threadParam {
    int thread_id;
    char thread_buf[32];
};


void *ReadFile(void* Param) {
    struct threadParam *Param_t = (struct threadParam *)Param;
    // cout << (struct threadParam *)Param == Param_t << endl;
    // cout << Param_t->thread_buf <<endl;
    ifstream filein;
    string last_line = "";
    string tmp_line = "";

    filein.open(Param_t->thread_buf, std::ios::in);
    if (!filein.is_open()) {
        cout << "can't open the file" << endl;
        exit(0);
    }

    bool is_first_line = true;
    while (getline(filein, tmp_line)) {
        last_line = tmp_line;
        if (is_first_line) {
            cout << "thread " << Param_t->thread_id << " - first line of file is: " << tmp_line << endl;
            is_first_line = false;
        }
    }
    cout << "thread " << Param_t->thread_id << " - last line of file is: " << last_line << endl;

    filein.close();
    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    pthread_t threads[MAX_THREADS];
    struct threadParam TDS[MAX_THREADS];
    int cnt = 0, rc = 0;

    if (argc != 2) {
        std::cout << "usage: ParallRead <file_name>" << endl;
        return 1;
    }

    for (cnt = 0; cnt < MAX_THREADS; ++cnt) {
        TDS[cnt].thread_id = cnt;
        memset(TDS[cnt].thread_buf, '\0', sizeof(TDS[cnt].thread_buf));
        memcpy(TDS[cnt].thread_buf, argv[1], strlen(argv[1]));
        // cout << argv[1] << " " << sizeof(argv[1]) << endl;
        rc = pthread_create(&threads[cnt], NULL, ReadFile, (void *)&TDS[cnt]);

        // rc != 0 then error
        if (rc) {
            std::cout << "can not create new thread, error code: " << rc << endl;
            exit(-1);
        }
    }
    
    pthread_exit(NULL);
    return 0;
}