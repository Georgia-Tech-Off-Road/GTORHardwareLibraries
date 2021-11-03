@echo off
    echo NOTICE: Make sure to run batch file as administrator    
    set source= %~dp0.
    set /p target= "Enter the path to the Arduino libraries directory: "
    set exclude= 


    forfiles /P "%source%" /C "cmd /c if @isdir==TRUE ( mklink /d \"%target%\@file\" @path )"
    forfiles /P "%source%\Sensors" /C "cmd /c if @isdir==TRUE ( mklink /d \"%target%\@file\" @path )"
    forfiles /P "%source%\ExternalLibraries" /C "cmd /c if @isdir==TRUE ( mklink /d \"%target%\@file\" @path )"
    forfiles /P "%source%\Utility" /C "cmd /c if @isdir==TRUE ( mklink /d \"%target%\@file\" @path )"

    cmd /c rmdir %target%\Sensors
    cmd /c rmdir %target%\ExternalLibraries
    cmd /c rmdir %target%\Utility
    cmd /c rmdir %target%\.git


cmd /k