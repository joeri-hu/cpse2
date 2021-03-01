@echo off

if /i "%~1" == "confirm" (
    set confirm=-1
    shift
) else (
    set confirm=0
)
if /i "%~1" == "rebuild" 1>&2(
    make clean 2>&1

    if errorlevel 1 (
        call :show_error "unable to clean build" %confirm%
        exit /b 1
    )
    shift
)
if /i "%~1" == "limit" 1>&2(
    (make 2>&1 && doskey /="%~f0") | more
    doskey /m | findstr /c:"%~f0"
) else 1>&2(
    make 2>&1
)
if errorlevel 1 (
    call :show_error "unable to build target" %confirm%
    exit /b 2
)
for %%e in ("*.exe") do 1>&2(
    start "" /b "%%~e"
)
exit /b 0


:show_error (__in msg, __in confirm)
1>&2(
    echo;
    set /p "=%~1 :(" 0<nul
    timeout /t "%~2" 1>nul
    exit /b
)
