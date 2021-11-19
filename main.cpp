#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
    //vector<int> arr = {1, 2, 3, 4, };
    cout << "Hello!" << endl;
    return 0;
}


// Section 1: Warning Up

void ProtectedConstructor()
{
    
}

class InitTest
{
private :
    static int si;
    const int ci;

public :
    InitTest(int ci)
    : ci(ci)
    {

    }

public :
    void Destroy()
    {
        delete this;
    }

protected :
    ~InitTest() 
    {
        // 스택에 객체를 만들 수 없다 대신 힙에서는 가능 (new)
        // delete 직접 호출 불가
        // 멤버 함수를 통해서 삭제 해야함
    }
};
int InitTest::si = 0;



void Upcasting()
{
    // Composite 패턴
}



void Coupling()
{

}



// Section 2: 공통성과 가변성의 분리

// Section 3: 재귀적 포함 - Menu Event

class BaseMenu
{
private :
    string _title;
    int _id;

public :
    BaseMenu(string title, int id) : _title(title), _id(id) {}
    string GetTitme() const { return _title; }

    virtual BaseMenu* GetSubMenu(int idx) = 0;
    virtual void Command() = 0;
};

class PopupMenu : public BaseMenu
{
private :
    vector<BaseMenu*> _menuList;

public :
    PopupMenu(string title, int id) : BaseMenu(title, id) {}
    void AddMenu(BaseMenu* menu) { _menuList.push_back(menu); }

    virtual void Commonad()
    {
        // Draw MenuList
    }
};

struct IMenuListener
{
    virtual void DoCommand() = 0;
    virtual ~IMenuListener() {}
};

class MenuItem : public BaseMenu
{
private :
    list<IMenuListener*> _listenerList;

public :
    MenuItem(string title, int id) : BaseMenu(title, id) {}
    void AddListener(IMenuListener* listener) { _listenerList.push_back(listener); }

    virtual void Commonad()
    {
        for(auto* listener : _listenerList)
        {
            listener->DoCommand();
        }
    }
};

class Dialog : public IMenuListener
{
public :
    virtual void DoCommand()
    {
        // Dialog method
    }
};



// Section 3: 재귀적 포함 - Decorator

class SpaceCraft
{
private :
    int _id;
    float _speed;
    // ...
public :
    void Fire()
    {
        // shot!
    }
};

class LeftMissile // 이걸 컴포넌트로
{
private :
    SpaceCraft* _sc;
public :
    LeftMissile(SpaceCraft* sc)
        : _sc(sc)
    {

    }

    void Fire()
    {
        if(_sc)
        {
            _sc->Fire();
        }

        // left shot!
    }
};

int mainOfSection3 ()
{
    SpaceCraft sc;
    sc.Fire();

    LeftMissile lm(&sc); // 아이템 획득
    lm.Fire();

    // 흠.. 그닥..
    // 아이템 획득하면 Fire 함수 호출 객체를 수정해줘야해..?

    // 컴포넌트 처럼 아이템 획득하면 컴포넌트 추가해주고
    // 아니면 떼는 형태로 가고 나머지는 그대로 두면 더 좋을 듯!
}



// Section 4: 간접층의 원리 - Adapter

// list를 stack 처럼 보이도록 변경 => Stack Adapter!!
template<typename T> class Stack //: public list<T>
{
private :
    list<T> _list;
    // 이것또한 리스트를 쓸 건지 벡터를 쓴건지 템플릿 받아서 처리 가능
    // template<typename T, typename C = deque<T> > class Stack

public :
    void push(const T& a) { _list.pushback(a); }//{ list<T>::pushback(a); }
    void pop() { _list.pop_back; }//{ list<T>::pop_back; }
    T& top() { return _list.back() }// { return list<T>::back() }
};

int mainOfSection4()
{
    Stack<int> s;
    s.push(10);
    s.push(20);

    s.push_front(20); // 이렇게 사용해 버리면 어떻게 처리?
    // list<T> 를 상속받지말고 포함 이럼 이제 error!

    std::cout << s.top() << std::endl;
}


// Section 4: 간접층의 원리 - Proxy

// Calc Proxy : 원격지의 서버를 대신 하는 클래스
class Calc
{
    int server;
public :
    Calc() {} //{ server = ec_find_server(3333); }

    int Add(int a, int b)//{ return ec_send_server(server, 1, a, b); }
    {
        // 서버 1 명령어 실행
    }
    int Sub(int a, int b)//{ return ec_send_server(server, 2, a, b); }
    {
        // 서버 2 명령어 실행
    }
    //자주 사용되는 요청에 대한 캐시 기능도 추가 가능

    // Proxy <-> Stub
    // Proxy는 함수 호출을 명령 코드로 변경해서 서버에 전달
    // Stub은 명령 코드를 다시 함수 호출로 변경
    // Proxy는 stub과 통신
};

int mainOfProxy()
{
    Calc* c = new Calc();
    c->Add(10, 8); // ec_send_server(server, 1, 10, 8);
    c->Sub(10, 8); // ec_send_server(server, 2, 10, 8);
    // 명령 1, 2 번 신경 xxx                      
}

// Section 4: 간접층의 원리 - facade
// 서브 시스템을 합성하는 다수의 객체들의 인터페이스 집합에 관해
// 일관된 하나의 인터페이스를 제공할 수 있게 한다.
// Facade는 서브시스템을 사용하기 위한 포괄적 개념의 인터페이스를 제공한다


// Section 4: 간접층의 원리 - bridge & PIMPL
// Pointer to IMPlementation 의 장점
// 컴파일 속도를 향상 시킨다.
// 완벽한 정보 은닉이 가능하다 - 헤더파일을 감출 수 있다.

// 인터페이스의 변경        Adapter
// 대행자                   Proxy
// 서브시스템의 복잡한 과정을 감추기 위해   Facade
// Update를 독립적으로 수행하기 위해        Bridge



// Section 5: 통보, 열거, 방문 - Observer

struct IGraph // Observer
{
    virtual void Update(Subject*) = 0;
    virtual ~IGraph() {}
};

// 관찰의 대상을 서브젝트라고 부름
// Suvject -> Object에게 통보
class Subject
{
    vector<IGraph*> _graphList;
public :
    void Attach(IGraph* graph)
    {
        _graphList.push_back(graph);
    }
    void Detach(IGraph* graph)
    {
        //
    }
    void Notify()
    {
        for (auto graph : _graphList)
        {
            graph->Update(this);
        }
    }
};

class Table : public Subject
{
    int _data;
    int _color;
public :
    int GetData() { return _data; }
    int GetColor() { return _color; }
    void SetData(int d)
    {
        _data = d;
        Notify();
    }
    void SetColor(int c)
    {
        _color = c;
        Notify();
    }
};

// class Table3D : public Subject
// {
//     int data[3][4];

//     void SetData(int d)
//     {
//         data = d;
//         Notify(data);
//     }
// };

class PieGraph : public IGraph
{
public :
    virtual void Update(Subject* subject)
    {
        int n = static_cast<Table*>(subject)->GetData();
        Draw(n);
    }
    void Draw(int n)
    {
        for(int i = 0; i < n; ++i)
        {
            // Draw
        }
    }
};

class BarGraph : public IGraph
{
public :
    virtual void Update(int n)
    {
        Draw(n);
    }
    void Draw(int n)
    {
        for(int i = 0; i < n; ++i)
        {
            // Draw
        }
    }
};

int mainOfObserver()
{
    BarGraph bg;
    PieGraph pg;

    Table t;
    t.Attach(&bg);
    t.Attach(&pg);

    // 입력받고
    t.SetData(20);
}



// Section 5: 통보, 열거, 방문 - Container

struct Node
{
    // int data;
    // Node* next;
    // Node( int d, Node* n) : data(d), next(n) {}
    Object* data;
    Node* next;
    Node(Object* d, Node* n) : data(d), next(n) {}
};
// int뿐만 아니라 다양하게 담고 싶을 경우
// -> 템플릿
// 하지만 템플릿이 아닌 다른 기법을 사용할 수 있다
// -> 기반 클래스 생성
struct Object
{
    virtual ~Object() {}
};
// 모든 클래스는 Object에서 파생되어야 한다.
class Dialog : public Object {};
class Rect : public Object {};
class Circle : public Object {};
class Point : public Object {};

class SingleList
{
    Node* head = nullptr;
public :
    void Push_back(Object* o) { head = new Node()}
    Object* front() { return head->data; }
};

int mainOfContainer()
{
    SingleList list;
    list.Push_back(new Point);
    list.Push_back(new Point);

    SingleList list2;
    list2.Push_back(new Circle);
    list2.Push_back(new Point);
    // 템플릿을 사용했을 때와 비교하면

    // 단점 1 : 
    // 실수로 잘못 넣었는데 모를 수 있다.
    // => 타입 안정성이 덜어진다.
    // 단점 2 : data를 떠낼 때 캐스팅 필요
    // 단점 3 : 프리미티브 타입들은 저장 할 수 x

    // 장점 1 : 코드 메모리 증가는 없다
}

// 템플릿으로 했을 경우의 담점
// 코드 메모리 증가
// 이 부분을 해결해 보면 어떨까?
// => data 처리를 void*로 가버렷!
// 하지만 넣고뺄때 매번 캐스팅 해야함..

class SingleListImp
{
    Node* head = nullptr;
public :
    void Push_back(Object* o) { head = new Node()}
    Object* front() { return head->data; }
};

// thin template : 캐스팅을 위해 존재

// to reduce object code duplication
// when a class template is instanticated
// for many types

// 타입별로 생으로 코드가 생성되는 것보다
// 코드 메모리 down
template<typename T>
class SingleList2 : public SingleListImp
{
public :
    inline void Push_back(T o) { SingleListImp::Push_back((void*)n); }
    inline T front() { return (T)SingleListImp::front(); }
};

// 이렇게하면 캐스팅 자동으로 가능
int mainOfContainer2()
{
    SingleList2<int> list;
    list.Push_back(10);
    list.Push_back(20);

    int n = list.front();
}


// Section 5: 통보, 열거, 방문 - Iterator

// Section 5: 통보, 열거, 방문 - Visitor


// std::accumulate
//https://en.cppreference.com/w/cpp/algorithm/accumulate
//http://www.soen.kr/lecture/ccpp/cpp4/42-4-1.htm
// #include <iostream>
// #include <vector>
// #include <numeric>

// using namespace std;

// int main()
// {
//     std::vector<int> v{ 1, 1, 1, 1, 1 };
// 	int sum = std::accumulate(v.begin(), v.end(), 0);

// 	string sumString = std::accumulate(v.begin(), v.end(), std::to_string(v[0]), [](std::string a, int b) mutable
//     {
//         return std::move(a) + '-' + std::to_string(b);
//     });
// }


// Section 6: 객체를 생성하는 방법 - Singleton
//
// 싱글콘 뮤텍스 락 -> 이미 할당되어 있을 경우에도 락을 걸어야함
// => Doluble Check Locking Pattern (DCLP)

#include <mutex>
#include <atomic>

template<typename TYPE> class DCLPSingleton
{
private :
    DCLPSingleton() {}
    DCLPSingleton(const DCLPSingleton&) = delete;
    void operator=(const DCLPSingleton&) = delete;

    static TYPE*    _instance;
    static mutex     _m;

public :
    static TYPE* GetInstance()
    {
        if(_instance == nullptr)
        {
            _m.lock();
            if(_instance == nullptr)
            {
                _instance = new TYPE();
                // 1. temp = sizeof(DCLPSingleton) 메모리 할당
                // 2. DCLPSingleton::DCLPSingleton() 생성자 호출
                // 3. _instance = temp

                // 하지만 일부 컴파일러에서는 최적화를 위해
                // 아래처럼 시행

                // 1. _instance = sizeof(DCLPSingleton) 메모리 할당  <--- 두 번째 스레드에서 (_instance == nullptr) 이 아니라고 판단하고 바로 싱글톤 리턴할 수 있다
                // 2. DCLPSingleton::DCLPSingleton() 생성자 호출

                // 리오더링 하지 않게 명령어 가능 => atomic
            }
            _m.unlock();
        }
        return _instance;
    }
};
template<typename TYPE> TYPE* DCLPSingleton<TYPE>::_instance = nullptr;

// Section 6: 객체를 생성하는 방법 - Factory
