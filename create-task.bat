@echo off
setlocal
call %~dp0dev_settings.cmd

schtasks /delete ^
/tn %TASK_NAME% ^
/f

schtasks /create ^
/sc daily ^
/tn %TASK_NAME% ^
/tr %GIT_GC_BAT% ^
/st %TASK_TIME% ^
/ru %USER% ^
/rp %PWS% ^
/v1



endlocal
