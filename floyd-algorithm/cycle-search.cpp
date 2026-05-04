#include <iostream>
#include <utility>

class ForwardList {
public:
    struct Node {
        int data;
        Node* next;

        Node(int val, Node* nxt = nullptr)
            : data(val), next(nxt) {}
    };

private:
    Node* head;
    size_t count;

public:
    ForwardList() : head(nullptr), count(0) {}

    ForwardList(Node* node) : head(node), count(0) {}

    ~ForwardList() {
   /*     while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }*/
    }

    void push_back(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        count++;
    }

    void pop_back() {
        if (head == nullptr) {
            std::cout << "ошибка! список пуст!" << std::endl;
            return;
        }

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            Node* curr = head;
            while (curr->next->next != nullptr) {
                curr = curr->next;
            }
            delete curr->next;
            curr->next = nullptr;
        }
        count--;
    }

    size_t size() const {
        return count;
    }

    Node* find(int value) const {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == value) {
                return curr;
            }
            curr = curr->next;
        }

        return nullptr;
    }

    void display() const {
        if (head == nullptr) {
            std::cout << "Список пуст!" << std::endl;
            return;
        }
        Node* curr = head;
        int count = 0;

        while (curr != nullptr && count < 20) {
            std::cout << curr->data << " ";
            curr = curr->next;
            count++;
        }

        if (curr != nullptr) std::cout << "... (цикл)";
        std::cout << std::endl;
    }

    //////////////////////////////////////////////////////

    std::pair<Node*, size_t> findCycle() {
            if (head == nullptr) {
                    return {nullptr, 0};
            }

            Node* turtle = head;
            Node* rabbit = head;

            while (rabbit != nullptr && rabbit->next != nullptr) {
                    turtle = turtle->next;
                    rabbit = rabbit->next->next;

                    if (turtle == rabbit) {
                            Node* start = head;
                            while (start != turtle) {
                                    start = start->next;
                                    turtle = turtle->next;
                            }

                            size_t len = 1;
                            Node* curr = start->next;
                            while (curr != start) {
                                    len++;
                                    curr = curr->next;
                            }
                            return {start, len};
                    }
            }
            return {nullptr, 0};
    }
};

int main()
{

    ForwardList list;

    list.push_back(7);
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);
    list.push_back(31);
    std::cout << "список(без цикла): ";
    list.display();
    if (list.findCycle().first == nullptr) {
            std::cout << "в списке нет цикла!" << std::endl;
    }
    else {
            std::cout << "найден цикл!" << std::endl;
    }


    std::cout << std::endl;
    ForwardList::Node* node7 = new ForwardList::Node(7);
    ForwardList::Node* node5 = new ForwardList::Node(5);
    ForwardList::Node* node10 = new ForwardList::Node(10);
    ForwardList::Node* node15 = new ForwardList::Node(15);
    ForwardList::Node* node31 = new ForwardList::Node(31);

    node7->next = node5;
    node5->next = node10;
    node10->next = node15;
    node15->next = node31;
    node31->next = node10;

    ForwardList list2(node7);
    std::cout << "список(уикл в середине): ";
    list2.display();

    auto result2 = list2.findCycle();
    if (result2.first != nullptr) {
        std::cout << "цикл найден!" << std::endl;
        std::cout << "начало цикла: узел со значением " << result2.first->data << std::endl;
        std::cout << "длина цикла: " << result2.second << std::endl;
    } else {
        std::cout << "цикл не найден!" << std::endl;
    }


    std::cout << std::endl;
    ForwardList::Node* nodeA = new ForwardList::Node(1);
    ForwardList::Node* nodeB = new ForwardList::Node(2);
    ForwardList::Node* nodeC = new ForwardList::Node(3);
    ForwardList::Node* nodeD = new ForwardList::Node(4);

    nodeA->next = nodeB;
    nodeB->next = nodeC;
    nodeC->next = nodeD;
    nodeD->next = nodeA;

    ForwardList list3(nodeA);
    std::cout << "список(последний указывает на первый): ";
    list3.display();

    auto result3 = list3.findCycle();
    if (result3.first != nullptr) {
        std::cout << "цикл найден!" << std::endl;
        std::cout << "начало цикла: узел со значением " << result3.first->data << std::endl;
        std::cout << "длина цикла: " << result3.second << std::endl;
    } else {
        std::cout << "цикл не найден!" << std::endl;
    }


    std::cout << std::endl;
    ForwardList list5;
    auto result5 = list5.findCycle();
    if (result5.first == nullptr && result5.second == 0) {
        std::cout << "пустой список: цикла нет" << std::endl;
    }

    return 0;
}
