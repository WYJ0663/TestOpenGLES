@echo on
title install so

call gradlew.bat compileDebugSources

set dir=%~dp0
set package=com.example.testopengles
set activity=.MainActivity
set abi=armeabi-v7a
set modulefile=libnative-lib

set so_path=%dir%app\build\intermediates\cmake\debug\obj\%abi%\%modulefile%.so
set tem_path=/sdcard/%modulefile%.so

adb install -r %DIRNAME%

echo %so_path%
echo 2.push so to /data/local/tmp 
adb push %so_path% %tem_path%

echo 3.copy so to /data/data/%package%/lib
adb shell "su -c ' cp %tem_path% /data/data/%package%/lib'"

adb shell am force-stop %package%
adb shell am start -n %package%/%activity%

