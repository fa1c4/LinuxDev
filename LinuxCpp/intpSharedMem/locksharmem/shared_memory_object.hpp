#ifndef FA_MUTEX
#define FA_MUTEX

#include <boost/interprocess/sync/interprocess_mutex.hpp>

struct shared_memory_message {
    boost::interprocess::interprocess_mutex mutex;
    char items[1024];
};

#endif
