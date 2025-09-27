#include <iostream>
#include <memory>
#include <sstream>
#include <string>

class LeaveHandler
{
public:
    virtual ~LeaveHandler() = default;  // 关键：基类虚析构
    virtual void handleRequest(const std::string& name, int days) = 0;
};

class Director : public LeaveHandler
{
    static constexpr int MAX_DAYS = 30;

public:
    void handleRequest(const std::string& name, int days) override
    {
        if (days <= MAX_DAYS)
            std::cout << name << " Approved by Director.\n";
        else
            std::cout << name << " Denied by Director\n";
    }
};

class Manager : public LeaveHandler
{
    static constexpr int MAX_DAYS = 7;
    std::shared_ptr<LeaveHandler> next_;

public:
    explicit Manager(std::shared_ptr<LeaveHandler> next) : next_(std::move(next)) {}
    void handleRequest(const std::string& name, int days) override
    {
        if (days <= MAX_DAYS)
            std::cout << name << " Approved by Manager.\n";
        else if (next_)
            next_->handleRequest(name, days);
        else
            std::cout << name << " Denied by Manager\n";
    }
};

class Supervisor : public LeaveHandler
{
    static constexpr int MAX_DAYS = 3;
    std::shared_ptr<LeaveHandler> next_;

public:
    explicit Supervisor(std::shared_ptr<LeaveHandler> next) : next_(std::move(next)) {}
    void handleRequest(const std::string& name, int days) override
    {
        if (days <= MAX_DAYS)
            std::cout << name << " Approved by Supervisor.\n";
        else if (next_)
            next_->handleRequest(name, days);
        else
            std::cout << name << " Denied by Supervisor\n";
    }
};

class LeaveRequest
{
    std::string employeeName_;
    int days_;

public:
    LeaveRequest(std::string name, int days) : employeeName_(std::move(name)), days_(days) {}
    const std::string& getEmployeeName() const { return employeeName_; }
    int getNumberOfDays() const { return days_; }
};

int main()
{
    int n;
    std::cin >> n;
    std::cin.ignore();

    auto director = std::make_shared<Director>();
    auto manager = std::make_shared<Manager>(director);
    auto supervisor = std::make_shared<Supervisor>(manager);  // 头结点

    for (int i = 0; i < n; ++i)
    {
        std::string name;
        int days;
        if (!(std::cin >> name >> days))
            break;
        LeaveRequest req{name, days};
        supervisor->handleRequest(req.getEmployeeName(), req.getNumberOfDays());
    }
    // 全部智能指针，无需手动 delete
    return 0;
}
