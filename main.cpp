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

// Section 3: 재귀적 포함

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