#include "testthreadsafequeue.h"
#include "threadsafequeue.h"
#include <thread>
#include <vector>
#include <unistd.h>

// using ::testing::Return;

ThreadSafeQueueTest::ThreadSafeQueueTest() 
{
};

ThreadSafeQueueTest::~ThreadSafeQueueTest() {};

void ThreadSafeQueueTest::SetUp() 
{
    
}

void ThreadSafeQueueTest::TearDown() {};


void ThreadSafeQueueTest::Schedule(
    filesafe::ThreadSafeQueue<JobTest>* pTsq
)
{
    JobTest testJob;
    ASSERT_TRUE(pTsq->Dequeue(testJob));
    ASSERT_EQ(testJob.m_test, 0x1337);
}

void ThreadSafeQueueTest::ScheduleDelayedExec(
    filesafe::ThreadSafeQueue<JobTest>* pTsq
)
{
    int count = filesafe::ThreadSafeQueue<JobTest>::MAX_QUEUE_ITEMS + 1;
    while(count--)
    {
        JobTest testJob;
        ASSERT_TRUE(pTsq->Dequeue(testJob));
        ASSERT_EQ(testJob.m_test, 0x1337);
    }
}

TEST_F(ThreadSafeQueueTest, SingleThreadQueueOperationsWork) 
{
    filesafe::ThreadSafeQueue<JobTest> tsq;
    std::vector<JobTest> testJobs = {JobTest(), JobTest(), JobTest()};
    for (auto const& testJob : testJobs)
    {
        ASSERT_TRUE(tsq.Enqueue(testJob));
    }

    for (int i = 0; i < testJobs.size(); ++i)
    {
        JobTest testJob;
        ASSERT_TRUE(tsq.Dequeue(testJob));
    }
}

TEST_F(ThreadSafeQueueTest, DequeueBeforeEnqueueBlocks)
{
    filesafe::ThreadSafeQueue<JobTest> tsq;
    std::thread worker( &ThreadSafeQueueTest::Schedule, &tsq);
    ASSERT_TRUE(tsq.IsEmpty());
    
    // add job to queue
    JobTest job;
    job.m_test = 0x1337;
    ASSERT_TRUE(tsq.Enqueue(job));
    worker.join();
}

TEST_F(ThreadSafeQueueTest, EnqueueBeforeDequeueDoesNotBlock)
{
    filesafe::ThreadSafeQueue<JobTest> tsq;

    // add job to queue
    JobTest job;
    job.m_test = 0x1337;
    ASSERT_TRUE(tsq.Enqueue(job));

    std::thread worker( &ThreadSafeQueueTest::Schedule, &tsq);
    worker.join();

    ASSERT_TRUE(tsq.IsEmpty());
}

TEST_F(ThreadSafeQueueTest, EnqueueWithMultipleWorkersBlocksAllButOne)
{
    filesafe::ThreadSafeQueue<JobTest> tsq;
    std::thread worker0( &ThreadSafeQueueTest::Schedule, &tsq);
    std::thread worker1( &ThreadSafeQueueTest::Schedule, &tsq);
    ASSERT_TRUE(tsq.IsEmpty());
    
    // add job to queue
    JobTest job;
    job.m_test = 0x1337;
    ASSERT_TRUE(tsq.Enqueue(job));
    
    for (;;)
    {
        if (tsq.IsEmpty())
        {
            break;
        }
        usleep(2000);
    }
    // unblock worker
    ASSERT_TRUE(tsq.Enqueue(job));

    // if the workers were previously blocked, they 
    // must be unblocked now
    worker0.join();
    worker1.join();

    ASSERT_TRUE(tsq.IsEmpty());
}

TEST_F(ThreadSafeQueueTest, EnqueueBlocksAfterMaxItems)
{
    filesafe::ThreadSafeQueue<JobTest> tsq;

    std::thread specialWorker( &ThreadSafeQueueTest::ScheduleDelayedExec, &tsq);

    JobTest job;
    job.m_test = 0x1337;    
    for(int i = 0; i < filesafe::ThreadSafeQueue<JobTest>::MAX_QUEUE_ITEMS; ++i)
    {
        ASSERT_TRUE(tsq.Enqueue(job));
    }

    bool isSuccess = tsq.Enqueue(job);
    ASSERT_TRUE(isSuccess);

    specialWorker.join();
}


