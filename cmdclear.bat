REM https://rio-kim.github.io/jenkins/windows/2019/02/12/kill_specific_process_in_windows_batch/
REM FOR /F "tokens=5 delims= " %%P IN ('netstat -ano ^| findstr :5000 ^| findstr LISTENING) DO taskkill /F /PID %%P

REM FOR /F "tokens=5 delims= " %%P IN ('netstat -ano ^| findstr :5000 ^| findstr LISTENING') DO taskkill /F /PID %%P

FOR /F "tokens=2 skip=3 delims= " %%P IN ('tasklist /fi "imagename eq myapp*"') DO taskkill /F /PID %%P 
