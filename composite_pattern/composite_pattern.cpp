#include <iostream>
#include <string>
#include <vector>
#include <memory>     // For std::shared_ptr
#include <sstream>    // For std::istringstream
#include <stack>      // For std::stack
#include <stdexcept>  // For std::runtime_error

// 抽象组件接口
class Component
{
public:
    virtual ~Component() = default;
    virtual void display(int depth) = 0;
    virtual std::string getName() const = 0;
};

// 组合节点：部门
class Department : public Component
{
private:
    std::string name_;
    std::vector<std::shared_ptr<Component>> children_;  // 私有成员

public:
    Department(const std::string& name) : name_(name) {}

    std::string getName() const override { return name_; }

    void add(std::shared_ptr<Component> component) { children_.push_back(component); }

    // --- 修正1：添加公共方法来获取子组件 ---
    const std::vector<std::shared_ptr<Component>>& getChildren() const { return children_; }
    // --- 修正1 结束 ---

    void display(int depth) override
    {
        for (int i = 0; i < depth; ++i)
        {
            std::cout << "  ";
        }
        std::cout << name_ << std::endl;

        for (const auto& child : children_)
        {
            child->display(depth + 1);
        }
    }
};

// 叶子节点：员工
class Employee : public Component
{
private:
    std::string name_;

public:
    Employee(const std::string& name) : name_(name) {}

    std::string getName() const override { return name_; }

    void display(int depth) override
    {
        for (int i = 0; i < depth; ++i)
        {
            std::cout << "  ";
        }
        std::cout << name_ << std::endl;
    }
};

// 公司类，管理根部门
class Company
{
private:
    std::string name_;
    std::shared_ptr<Department> root_;

public:
    Company(const std::string& name) : name_(name) { root_ = std::make_shared<Department>(name); }

    std::shared_ptr<Department> getRoot() const { return root_; }

    void display() const
    {
        std::cout << "Company Structure:" << std::endl;
        std::cout << root_->getName() << std::endl;  // 打印公司名称
        // --- 修正2：通过 Department 的公共方法访问 children ---
        for (const auto& child : root_->getChildren())
        {
            child->display(1);  // 子元素从深度1开始
        }
        // --- 修正2 结束 ---
    }
};

// 辅助函数：计算前导空格数量
int countLeadingSpaces(const std::string& s)
{
    int count = 0;
    for (char c : s)
    {
        if (c == ' ')
        {
            count++;
        }
        else
        {
            break;
        }
    }
    return count;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string companyName;
    std::getline(std::cin, companyName);
    Company company(companyName);

    int n;
    std::cin >> n;
    std::string dummy;
    std::getline(std::cin, dummy);

    std::stack<std::shared_ptr<Department>> departmentStack;
    departmentStack.push(company.getRoot());

    std::shared_ptr<Department> lastCreatedDepartment = company.getRoot();

    for (int i = 0; i < n; ++i)
    {
        std::string line;
        std::getline(std::cin, line);

        int currentDepth = countLeadingSpaces(line);
        std::string validContent = line.substr(currentDepth);

        std::istringstream iss(validContent);
        std::string type, name;
        iss >> type;
        std::getline(iss, name);
        name = name.substr(name.find_first_not_of(" "));

        // --- 修正3：解决无符号比较警告 ---
        // 将 currentLevel 转换为 size_type 或将 size_type 转换为 int
        // 这里选择将 currentLevel 转换为 size_type，更安全
        size_t currentLevelSize = static_cast<size_t>(currentDepth / 2);
        // --- 修正3 结束 ---

        if (currentDepth == 0)
        {
            if (type == "D")
            {
                std::shared_ptr<Department> department = std::make_shared<Department>(name);
                company.getRoot()->add(department);

                lastCreatedDepartment = department;

                while (!departmentStack.empty())
                {
                    departmentStack.pop();
                }
                departmentStack.push(company.getRoot());
                departmentStack.push(department);
            }
            else if (type == "E")
            {
                std::shared_ptr<Employee> employee = std::make_shared<Employee>(name);
                lastCreatedDepartment->add(employee);
            }
        }
        else
        {
            // --- 修正4：使用修正后的 currentLevelSize 进行比较 ---
            while (currentLevelSize < departmentStack.size() - 1)
            {
                departmentStack.pop();
            }
            // --- 修正4 结束 ---
            std::shared_ptr<Department> currentParent = departmentStack.top();

            if (type == "D")
            {
                std::shared_ptr<Department> department = std::make_shared<Department>(name);
                currentParent->add(department);
                departmentStack.push(department);
                lastCreatedDepartment = department;
            }
            else if (type == "E")
            {
                std::shared_ptr<Employee> employee = std::make_shared<Employee>(name);
                currentParent->add(employee);
            }
        }
    }

    company.display();

    return 0;
}
