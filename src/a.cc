#include <cstdio>

void draw_number(int number, int base) {
	static char s[17] = "0123456789ABCDEF";
	static char nums[32];

	for (int i = 0; i < 32; i++) {
		nums[i] = 0;
	}

	int len = 0;
	int n = number > 0 ? number : -number;
	while (n) {
		n /= base;
		len++;
	}
	std::printf("%d\n", len);
	if (number < 0) {
		nums[0] = '-';
		number = -number;
		len++;
	}

	while (number) {
		nums[--len] = s[number % base];
		number /= base;
	}

	std::printf("%s\n", nums);
}

int main() {
	draw_number(-123442134, 10);
	return 0;
}
