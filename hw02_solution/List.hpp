/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-21 10:17:13
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-21 22:18:15
 * @@Email: 8211180515@csu.edu.cn
 */
#include <memory>

struct Node {
    // 这两个指针会造成什么问题？请修复
    // shared 可能会导致循环引用。
    std::unique_ptr<Node> next = nullptr;
    Node* prev = NULL;
    // 如果能改成 unique_ptr 就更好了!

    int value;

    // 这个构造函数有什么可以改进的？
    Node(int val) : value(val) {}

    void insert(int val) {
        auto node = std::make_unique<Node>(val);
        if (next) {
            next->prev = node.get();
            node->next = std::move(next);
        }
        node->prev = this;
        this->next = std::move(node);
    }

    void erase() {
        if (next)
            next->prev = prev;
        if (prev)
            prev->next = std::move(next);
    }

    ~Node() {
        printf("~Node()\n");   // 应输出多少次？为什么少了？
    }
};

struct List {
    std::unique_ptr<Node> head = nullptr;

    List() = default;

    List(List const &other) {
        printf("List 被拷贝！\n");
        // 请实现拷贝构造函数为 **深拷贝**
        head.reset();
        if (!other.front()) return;
        head = std::make_unique<Node>(other.head->value);        
        for (auto cur = front(), cur_next = other.head->next.get(); 
        cur_next; cur = cur->next.get(), cur_next = cur_next->next.get()) {
            cur->insert(cur_next->value);
        }
    }

    List &operator=(List const &) = delete;  // 为什么删除拷贝赋值函数也不出错？
    // 区别List a = b; 和 a = b;
    // 前者调用拷贝构造函数，后者调用拷贝赋值函数，如果程序中包含a = b;语句会报错
    // a = {};调用的是a的移动赋值函数List &operator=(List &&) = default;，相当于a.operator=(List{nullptr, nullptr, 0});

    List(List &&) = default;
    List &operator=(List &&) = default;

    Node *front() const {
        return head.get();
    }

    int pop_front() {
        int ret = head->value;
        head = std::move(head->next);
        return ret;
    }

    void push_front(int value) {
        auto node = std::make_unique<Node>(value);
        if (head) {
            head->prev = node.get();
            node->next = std::move(head);
        }
        head = std::move(node);
    }

    Node *at(size_t index) const {
        auto curr = front();
        for (size_t i = 0; i < index; i++) {
            if (!curr) {
                printf("Error: Exceed List!\n");
                return NULL;
            }
            curr = curr->next.get();
        }
        return curr;
    }
};