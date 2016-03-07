//C++11风格的资源管理类
class ScopeGuard
{
public:
    explicit ScopeGuard(std::function<void()> onExitScope)
        : onExitScope_(onExitScope), dismissed_(false)
    { }

    ~ScopeGuard()
    {
        if(!dismissed_)
        {
            onExitScope_();
        }
    }

    void Dismiss()
    {
        dismissed_ = true;
    }

private:
    std::function<void()> onExitScope_;
    bool dismissed_;

private:
// noncopyable
    ScopeGuard(ScopeGuard const&);
    ScopeGuard& operator=(ScopeGuard const&);
};

//基本使用

HANDLE h = CreateFile(...);
ScopeGuard onExit([&] { CloseHandle(h); });

// 带rollback场景

ScopeGuard onFailureRollback([&] {
/* rollback */
 });
...
// do something that could fail
onFailureRollback.Dismiss();

