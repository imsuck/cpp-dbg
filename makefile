.PHONY: format fmt

fmt: format

format:
	find src/ -name "*.hpp" -o -name "*.cpp" | xargs clang-format -i
