template<typename T>
class RealTimeQueue {
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    size_t max_size_;
    
public:
    explicit RealTimeQueue(size_t max_size) : max_size_(max_size) {}
    
    bool push(T&& item, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (cv_.wait_for(lock, timeout, 
            [this] { return queue_.size() < max_size_; })) {
            queue_.push(std::move(item));
            cv_.notify_one();
            return true;
        }
        return false;
    }
    
    bool pop(T& item, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (cv_.wait_for(lock, timeout, 
            [this] { return !queue_.empty(); })) {
            item = std::move(queue_.front());
            queue_.pop();
            cv_.notify_one();
            return true;
        }
        return false;
    }
};

