/// @author YellowAfterlife

#include "stdafx.h"
#include <stdio.h>

#if defined(WIN32)
#define dllx extern "C" __declspec(dllexport)
#elif defined(GNUC)
#define dllx extern "C" __attribute__ ((visibility("default"))) 
#else
#define dllx extern "C"
#endif

#define trace(...) { printf("[window_embed_:%d] ", __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }

class StringConv {
public:
	char* cbuf = NULL;
	size_t cbuf_size = 0;
	WCHAR* wbuf = NULL;
	size_t wbuf_size = 0;
	StringConv() {

	}
	LPCWSTR wget(size_t size) {
		if (wbuf_size < size) {
			if (wbuf != NULL) delete wbuf;
			wbuf = new WCHAR[size];
			wbuf_size = size;
		}
		return wbuf;
	}
	LPCWSTR proc(char* src, int cp = CP_UTF8) {
		if (src == nullptr) return nullptr;
		size_t size = MultiByteToWideChar(cp, 0, src, -1, NULL, 0);
		LPCWSTR buf = wget(size);
		MultiByteToWideChar(cp, 0, src, -1, wbuf, size);
		return wbuf;
	}
	char* get(size_t size) {
		if (cbuf_size < size) {
			if (cbuf != NULL) delete cbuf;
			cbuf = new char[size];
			cbuf_size = size;
		}
		return cbuf;
	}
	char* proc(LPCWSTR src, int cp = CP_UTF8) {
		if (src == nullptr) return nullptr;
		size_t size = WideCharToMultiByte(cp, 0, src, -1, NULL, 0, NULL, NULL);
		char* buf = get(size);
		WideCharToMultiByte(cp, 0, src, -1, buf, size, NULL, NULL);
		return buf;
	}
} c1, c2;

HWND window_embed_parent = 0;
dllx double window_embed_into_raw(void* pwnd, char* className, char* title, double fflags) {
	int flags = (int)fflags;
	HWND hwnd = (HWND)pwnd;
	auto wClass = (flags & 1) ? c1.proc(className) : nullptr;
	auto wTitle = (flags & 2) ? c2.proc(title) : nullptr;
	if (!wClass && !wTitle) {
		window_embed_parent = 0;
		//SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) & ~WS_EX_TOOLWINDOW);
		SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CHILD | WS_POPUP);
		SetParent(hwnd, nullptr);
		return true;
	}
	HWND target = FindWindowW(wClass, wTitle);
	if (target == NULL) return 0;
	//SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_POPUP | WS_CHILD);
	if (SetParent(hwnd, target) == NULL) return 0;
	window_embed_parent = target;
	return 1;
}

RECT window_embed_get_parent_rect() {
	HWND hwnd = window_embed_parent;
	if (!hwnd) {
		RECT rr;
		rr.left = 0;
		rr.top = 0;
		rr.right = GetSystemMetrics(SM_CXSCREEN);
		rr.bottom = GetSystemMetrics(SM_CYSCREEN);
		return rr;
	}
	RECT wr, cr, ar;
	GetClientRect(hwnd, &cr);
	ar.left = cr.left; ar.right = cr.right;
	ar.top = cr.top; ar.bottom = cr.bottom;
	AdjustWindowRect(&ar, GetWindowLong(hwnd, GWL_STYLE), false);
	GetWindowRect(hwnd, &wr);
	wr.left -= (ar.left - cr.left);
	wr.top -= (ar.top - cr.top);
	wr.right -= (ar.right - cr.right);
	wr.bottom -= (ar.bottom - cr.bottom);
	return wr;
}
///
dllx double window_embed_has_parent() {
	return window_embed_parent != 0;
}
///
dllx double window_embed_get_parent_width() {
	auto r = window_embed_get_parent_rect();
	return (double)r.right - r.left;
}
///
dllx double window_embed_get_parent_height() {
	auto r = window_embed_get_parent_rect();
	return (double)r.bottom - r.top;
}