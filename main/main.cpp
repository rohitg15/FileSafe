#include "threadpool.h"


class ThreadContext
{
public:
    void Execute()
    {
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << " Inside thread - " << this_id << std::endl;
    }
};

int main(int argc, char *argv[])
{
    filesafe::ThreadPool<ThreadContext> threadPool(10);
    ThreadContext t1, t2, t3;
    std::vector<ThreadContext> jobs = {t1, t2, t3};
    for (int i = 0; i < jobs.size(); ++i)
    {
        threadPool.AddJob(jobs[i]);
    }
    std::cout << " ----------------- here ------------------ "<< std::endl;

    return 0;
}
