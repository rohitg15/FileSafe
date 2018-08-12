#ifndef _THREAD_SAFE_QUEUE_H_
#define _THREAD_SAFE_QUEUE_H_

#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace filesafe
{
    template<class T>
    class ThreadSafeQueue
    {
    public:
        ThreadSafeQueue()
        {
            m_isValid = true;
        }

        ThreadSafeQueue(
            ThreadSafeQueue&
        )   =   delete;

        ThreadSafeQueue& operator=(
            ThreadSafeQueue&
        ) = delete;

        bool Enqueue(
            T job
        )
        {
            std::unique_lock<std::mutex> lock(m_qLock);     //  acquire lock
            m_cndReleaseJob.wait(lock, [this] {         //  wait until queue has space
                return (m_q.size() <= MAX_QUEUE_ITEMS) || !m_isValid;
            });
            if (!m_isValid)                                 //  Received exit signal
            {
                return false;
            }
            m_q.emplace(job);
            m_cndAcquireJob.notify_one();                   //  notify one thread that a job has been added
            return true;
        }                                                   //  release lock here

        bool Dequeue(T& job)
        {
            std::unique_lock<std::mutex> lock(m_qLock);     //  acquire lock
            std::thread::id this_id = std::this_thread::get_id();
           
            m_cndAcquireJob.wait(lock, [this] {
                return !m_q.empty() || !m_isValid;
            });                                             //  give up lock and wait until a job is added to the queue

            if (!m_isValid)                                 //  Received Exit signal
            {
                return false;
            }
           
            job = std::move(m_q.front());
            size_t oldSize = m_q.size();
            m_q.pop();

            if (oldSize == MAX_QUEUE_ITEMS)               // notify producer thread if the queue was previously full
            {
                m_cndReleaseJob.notify_one();
            }
            return true;
        }                                               //  release lock

        bool IsEmpty() const
        {
            std::unique_lock<std::mutex> lock(m_qLock);     //  acquire lock
            return m_q.empty();
        }                                                   //  release lock

        size_t Count() const
        {
            std::unique_lock<std::mutex> lock(m_qLock);     //  acquire lock
            return m_q.size();                              
        }                                                   //  release lock

        void ReleaseQueue()
        {
            m_isValid = false;
            m_cndAcquireJob.notify_all();
            m_cndReleaseJob.notify_all();
        }

    private:
        std::queue<T> m_q;
        std::mutex m_qLock;
        std::condition_variable m_cndAcquireJob; 
        std::condition_variable m_cndReleaseJob;
        std::atomic_bool m_isValid;
        static constexpr size_t MAX_QUEUE_ITEMS = 1024;
    };
}

#endif  //  _THREAD_SAFE_QUEUE_H_