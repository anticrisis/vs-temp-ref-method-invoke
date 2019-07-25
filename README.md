# About

This repository demonstrates a code generation bug in Visual Studio C++ 2019
when using an x86-Release build and the `gsl::at` function.

Please see comments in the source file. The bug only occurs with a Release build.

## To reproduce

### Update

Code generation in Visual Studio Version 16.3.0 Preview 1.0 has changed, and the problem no longer occurs.
The problem still does occur in Version 16.2.0.

### Set up dependencies

This uses a bootstrap and `vcpkg` setup that I made. It runs `git submodule update` and then
runs `vcpkg`'s bootstrap script. Then, it installs the dependencies in `packages.txt`

From Powershell:

```powershell
PS> .\bootstrap.ps1
...
PS> .\install-deps.ps1

```

### Run the test

1. Open folder in Visual Studio.
2. Configure CMake.
3. Select `x86-Release` configuration.
4. Run.

The checked in version will either thrown an exception or crash with a memory access
violation inside the `VectorOwner::Check` function.

## Possible factors

1. Use of `gsl:at` on [line 69](https://github.com/anticrisis/vs-temp-ref-method-invoke/blob/6fb24941d253f12248e31b82b32bcc971fe09a9f/vs-temp-ref-method-invoke/vs-temp-ref-method-invoke.cpp#L69).
If this use is replaced with a direct array access,
the bug does not occur.

```cpp
    // this version uses gsl::at, and triggers the later corruption error
    const auto& GetFoo(int i) const noexcept { return gsl::at(foos, i); }

    // use this version to prevent corruption in all cases
    //const auto& GetFoo(int i) const noexcept { return foos[i]; }
```

2. Accessing a member function via a temporary `this` pointer. The crash on line 100
does not occur if the result of calling `handle.Get()` is placed in a local variable
before calling `Run`. A successful case is shown on [lines 96-97](https://github.com/anticrisis/vs-temp-ref-method-invoke/blob/6fb24941d253f12248e31b82b32bcc971fe09a9f/vs-temp-ref-method-invoke/vs-temp-ref-method-invoke.cpp#L96-L97).

```cpp
    // this call to VectorOwner::Run succeeds in all cases, because a
    // temporary is not used
    auto& vo = handle.Get();
    vo.Run(f);

    // this next call fails in its call to Check() if GetFoo uses gsl::at
    handle.Get().Run(f);
```
