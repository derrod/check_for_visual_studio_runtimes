/*
	MIT License

	Copyright (c) 2017 Richard Stanway

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <windows.h>
#include <winver.h>

static BOOL IsVSRedistOutdated()
{
	VS_FIXEDFILEINFO *info = NULL;
	UINT len = 0;
    char* buf = NULL;

	DWORD size = GetFileVersionInfoSizeW(L"msvcp140", NULL);
	if (!size)
		return TRUE;

	buf = LocalAlloc(LMEM_FIXED, size);
	if (!GetFileVersionInfoW(L"msvcp140", 0, size, buf))
		return TRUE;

	BOOL success = VerQueryValueW(buf, L"\\", (LPVOID *)&info, &len);
	if (!success || !info || !len)
		return TRUE;

	return LOWORD(info->dwFileVersionMS) < 40;
}

int WINAPI _start (void)
{
	SetErrorMode (SEM_FAILCRITICALERRORS);
        
    // VC runtime is outdated
    if (IsVSRedistOutdated())
			ExitProcess(126);
    
	ExitProcess(0);
}
