echo off
setlocal
call %~dp0dev_settings.cmd

FOR /d %%D in (%CD%) DO (
  IF EXIST %%D\.git (
    ECHO == %%D
    echo.
    pushd %%D
    %GIT% git gc
    popd
  )
  ECHO.
)
PAUSE
