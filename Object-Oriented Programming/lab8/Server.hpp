//
//  Server.hpp
//  lab8
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 21.11.2020.
//

#ifndef LAB8_SERVER_HPP
#define LAB8_SERVER_HPP


template<class MESSAGE_T>
class Server {
public:
    using subscriber_t = std::function<void(const MESSAGE_T &)>;

private:
    std::vector<subscriber_t> subscribers;
    std::queue<MESSAGE_T> message_queue;
    std::mutex mtx;
    bool finish{false};
    std::mutex mtx2;

    Server() {};

public:
    static Server &get() {
        static Server instance;
        return instance;
    }

    void register_subscriber(const subscriber_t &subs) {
        subscribers.push_back(subs);
    }

    void publish(const MESSAGE_T &msg) {
        std::lock_guard<std::mutex> lck(mtx);
        message_queue.push(msg);
    }

    void stop() {
        std::lock_guard<std::mutex> lck(mtx2);
        finish = true;
    }

    void run() {
        while (true) {
            if (!message_queue.empty()) {
                std::lock_guard<std::mutex> lck(mtx);
                MESSAGE_T val = message_queue.front();
                message_queue.pop();
                for (const auto &sub : subscribers) {
                    try {
                        sub(val);
                    } catch (std::exception &ex) {
                        std::cerr << "Exception in subscriber:" << ex.what() << std::endl;
                    }
                }
            } else {
                std::lock_guard<std::mutex> lck(mtx2);
                if (finish) {
                    finish = false;
                    break;
                }
            }
        }
    }
};


#endif //LAB8_SERVER_HPP
