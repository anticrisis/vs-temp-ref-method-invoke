// vs-temp-ref-method-invoke.cpp : Defines the entry point for the application.
//

#include <array>
#include <vector>
#include <functional>
#include <gsl/gsl>

#include "vs-temp-ref-method-invoke.h"

using namespace std;

class VectorOwner
{
    int w;
    int h;
    vector<int> v;

public:
    VectorOwner(int w, int h);
    void Check() const;
    void Run(function<void(int)>) const;
};

VectorOwner::VectorOwner(int w, int h) : w{w}, h{h}, v(w * h)
{
}

void VectorOwner::Check() const
{
    if (v.size() != w * h)
        throw runtime_error("'this' value is corrupted.");
}

void VectorOwner::Run(function<void(int)> f) const
{
    Check();

    for (auto x : v)
    {
        f(x);
    }
}

class Handle
{
    VectorOwner vectorOwner;

public:
    Handle(int w, int h);
    const auto &Get() const noexcept { return vectorOwner; }
};

Handle::Handle(int w, int h) : vectorOwner{w, h}
{
}

class App
{
    int x = 0;
    array<int, 4> foos;

    Handle handle;

public:
    App(int w, int h);

    // this version uses gsl::at, and triggers the later corruption error
    const auto& GetFoo(int i) const noexcept { return gsl::at(foos, i); }

    // use this version to prevent corruption in all cases
    //const auto& GetFoo(int i) const noexcept { return foos[i]; }

    int Run() const;
};

App::App(int w, int h) : handle{w, h}
{
}

int App::Run() const
{
    // this call to the gsl::at version of GetFoo causes the corruption
    const auto& foo = GetFoo(2);

    // this next line succeeds in all cases
    handle.Get().Check();

    auto count = 0;
    const auto f = [&](int) {
        ++count;
    };

    // this call to VectorOwner::Run succeeds in all cases, because a
    // temporary is not used
    auto& vo = handle.Get();
    vo.Run(f);

    // this next call fails in its call to Check() if GetFoo uses gsl::at
    handle.Get().Run(f);
    return count;
}

int main()
{
    App app{5, 5};

    auto res = app.Run();

    cout << "res = " << res << endl;

    return 0;
}
