# ?= sets a default that can be overridden, for example: make CXX=clang++.
CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -Wfatal-errors

# := assigns these values immediately; $(NAME) expands a variable.
TARGET ?= main
SOURCE_FILES := $(TARGET).cpp

# These targets are commands, not files that Make should look for.
.PHONY: all clean run run_single_test rat

# target: (prerequisite files). The first target is the default for `make`.
# Rebuild if the source changes; recipe lines beneath a target must start with a tab.
all: $(TARGET)

$(TARGET): $(SOURCE_FILES)
	$(CXX) $(CXXFLAGS) $(SOURCE_FILES) -o $(TARGET)
#   Next line ignored if compile fails 
	@echo "Build successful: $(TARGET)"

# Remove the generated executable.
clean:
	rm -f $(TARGET)
	@echo "Removed: $(TARGET)"

run: all
	@echo "Running: $(TARGET)"
	./$(TARGET)

run_single_test: all $(TEST_INPUT)
	@echo "TEST: $(TEST_INPUT)"
	./$(TARGET) < $(TEST_INPUT)

# Run all matching test input files.
rat: all
	@set -e; for test_input in $(TARGET)-test*; do \
		$(MAKE) --no-print-directory run_single_test TEST_INPUT="$$test_input"; \
	done


# what is the difference in assigns immediately := and simple assignment =
# 	A = $(B)
# 	B = hello
# 	$(A) expands to "hello" when used

# 	C := $(B)
# 	B = goodbye
# 	C stays "hello"; it captured B's value when C was assigned