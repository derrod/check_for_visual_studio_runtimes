# check_for_visual_studio_runtimes
Tiny app to check for presence of various versions of Visual Studio DLLs, designed for use in installers. Simply execute and check the exit code (126 = missing DLL).

Recommended compiler command:

`
CL /Os /Zi check_for_64bit_visual_studio_2022_runtimes.c kernel32.lib version.lib /link /ENTRY:_start /subsystem:windows /DEBUG:NONE /EMITPOGOPHASEINFO /MERGE:.pdata=.rdata /MERGE:.data=.rdata
`

This will produce a tiny .exe with no dependencies other than kernel32.dll. Note that the architecture of Visual Studio DLLs (x86 / x64) that get checked depends on whether the exe was built with a 32 bit or 64 bit compiler.
