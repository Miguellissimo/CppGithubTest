#ifndef TRIVIAL_H_
#define TRIVIAL_H_

struct primitives {
	int x;
	float y;
	int a[2];
};

struct constructor {
	constructor() = default;
	int x;
};

struct with_static {
	static int f() { return -1; };
	with_static() = default;
	int x;
};

struct not_trivial_1 {
	not_trivial_1() {};
	int a;
};

struct not_trivial_2 {
public:
	not_trivial_2() : b(5) {};
	int x;
	float y;
	int a[2];
private:
	int b;
};

#endif
