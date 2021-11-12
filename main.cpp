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

// list를 stack 처럼 보이도록 변경
template<typename T> class Stack //: public list<T>
{
private :
    list<T> _list;
    // 이것또한 리스트를 쓸 건지 벡터를 쓴건지 템플릿 받아서 처리 가능

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