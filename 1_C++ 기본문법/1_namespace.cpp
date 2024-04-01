#include <stdio.h>

namespace Video
{
	void init()	{ printf("init Video module\n"); }
	void reset(){ printf("reset Video module\n");}
}

namespace Audio
{
	void init() { printf("init Audio module\n"); }
	void reset(){ printf("reset Audio module\n");}
}

void init() { printf("init global module\n"); }

int main()
{
	Audio::init(); // init Audio module

	using Audio::init;
	// using Video::init;
	init(); // init Audio modul
    ::init(); // init global module

    using namespace Video;
	init(); // init Audio module
	reset(); // reset Video module
}