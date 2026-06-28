#include "base.cpp"

#ifndef COLOR_DEBUG_CPP
#define COLOR_DEBUG_CPP

#ifndef _MSC_VER
#include <unistd.h>
#endif

//STARTCOPY
namespace mytl{

// A streambuf that wraps every line it forwards in ANSI color codes, so that
// text sent through it shows up in a distinct color in the terminal.
struct ColorStreambuf : streambuf {
	streambuf* dest;
	string pre, post, buf;
	ColorStreambuf(streambuf* dest, string pre, string post) : dest(dest), pre(pre), post(post) {}
	void emit(){
		if(buf.empty()) return;
		dest->sputn(pre.data(), pre.size());
		dest->sputn(buf.data(), buf.size());
		dest->sputn(post.data(), post.size());
		buf.clear();
	}
	need_int overflow(need_int c) override {
		if(c == EOF) return c;
		if(c == '\n'){ emit(); dest->sputc('\n'); }
		else buf.push_back(char(c));
		return c;
	}
	need_int sync() override { emit(); return dest->pubsync(); }
};

// Make cerr (your debug output) appear in a different color from cout (the real
// answer), so the two are easy to tell apart while debugging in the terminal.
// Only activates on an interactive terminal: when stderr is redirected to a file
// or read by an online judge, nothing is changed and no color codes are emitted.
inline void enable_color_debug(){
#ifndef _MSC_VER
	if(isatty(2)){
		static ColorStreambuf b(cerr.rdbuf(), "\033[33m", "\033[0m"); // yellow
		cerr.rdbuf(&b);
	}
#endif
}

// Auto-enable at startup so cerr is colored without any extra call.
static need_int _color_debug_init = (enable_color_debug(), 0);

}
//ENDCOPY

#endif
