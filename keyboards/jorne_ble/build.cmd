@echo off

set keyboard=jorne_ble
set keymap=default
set role=master

::echo "Building with WSL1"
::wsl --set-default Ubuntu
::set SDK_ROOT=/c/mnt/SDK/nRF5_SDK_15.0.0_a53641a
::set PROJ_ROOT=../

echo "Building with WSL2"
wsl --set-default Ubuntu-20.04
set SDK_ROOT=~/nRF5_SDK_15.0.0_a53641a
set PROJ_ROOT=~/qmk

if "%1"=="slave" set role=slave

echo building %role%

set file=%keyboard%_%role%_%keymap%.hex

bash -c "cd %PROJ_ROOT% && export NRFSDK15_ROOT=%SDK_ROOT% && make %keyboard%/%role%:%keymap%" || exit

cd ..\..\.build

%~dp0/uf2conv.py %file% -c -f 0xADA52840

copy /Y flash.uf2 %~dp0\precompiled\%role%.uf2

echo dfu| plink.exe -serial com9

echo Waiting for the UF2 drive. Press Reset twice...

:loop
if not exist e:\ goto :loop

timeout 1

copy flash.uf2 e:\

