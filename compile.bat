@echo off
cd /d d:\xu_doc\project\git\MFCAppTest4
"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
msbuild MFCApplication2.sln /p:Configuration=Debug /p:Platform=x64
pause