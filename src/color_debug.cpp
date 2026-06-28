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

// Color the program's output in the terminal so the three streams are easy to
// tell apart while debugging:
//   - cout (your real answer)  -> green
//   - cerr (your debug output) -> yellow
//   - whatever you type as input stays the terminal's default color
// Each stream is colored only when IT is an interactive terminal, checked
// independently: when cout is piped to a file or read by an online judge it gets
// no color codes at all (even if you keep cerr on the terminal).
inline void enable_color_debug(){
#ifndef _MSC_VER
	if(isatty(1)){
		static ColorStreambuf b(cout.rdbuf(), "\033[32m", "\033[0m"); // green
		cout.rdbuf(&b);
	}
	if(isatty(2)){
		static ColorStreambuf b(cerr.rdbuf(), "\033[33m", "\033[0m"); // yellow
		cerr.rdbuf(&b);
	}
#endif
}

// Auto-enable at startup so cout/cerr are colored without any extra call.
static need_int _color_debug_init = (enable_color_debug(), 0);

}
//ENDCOPY

#endif
