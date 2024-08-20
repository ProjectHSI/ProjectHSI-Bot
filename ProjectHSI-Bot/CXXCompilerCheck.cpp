#include <cmath>
#include <cstdio>
#include <format>
#include <format>
#include <source_location>

static void sourceLocationTest(const std::source_location sourceLocation = std::source_location::current()) {
	printf("%s\n", sourceLocation.line());
}

static void formatTest() {
	std::format("{}", rand());
}

int main() { return 0; }