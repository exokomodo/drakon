SHELL := /bin/bash
.SHELLFLAGS = -e -c
.DEFAULT_GOAL := help
.ONESHELL:
.SILENT:

BUILD_DIR := ./build

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CMAKE_OS_FLAGS :=
else ifeq ($(UNAME_S),Darwin)
	CMAKE_OS_FLAGS := 
endif
CMAKE_ADDITIONAL_FLAGS ?= 

##@ Setup

.PHONY: setup/ubuntu
setup-ubuntu: ## Setup Ubuntu dependencies
	sudo apt-get update
	# https://github.com/libsdl-org/SDL/blob/main/docs/README-linux.md#build-dependencies
	sudo apt-get install -y \
		build-essential \
		clang-format \
		cmake \
		git \
		gnome-desktop-testing \
		libasound2-dev \
		libaudio-dev \
		libdbus-1-dev \
		libdecor-0-dev \
		libdrm-dev \
		libegl1-mesa-dev \
		libgbm-dev \
		libgl1-mesa-dev \
		libgles2-mesa-dev \
		libibus-1.0-dev \
		libjack-dev \
		libpipewire-0.3-dev \
		libpulse-dev \
		libsndio-dev \
		libudev-dev \
		liburing-dev \
		libwayland-dev \
		libx11-dev \
		libxcursor-dev \
		libxext-dev \
		libxfixes-dev \
		libxi-dev \
		libxkbcommon-dev \
		libxrandr-dev \
		libxss-dev \
		libxtst-dev \
		make \
		ninja-build \
		pkg-config

.PHONY: setup/mac
setup-mac: ## Setup macOS dependencies
	if ! command -v brew &> /dev/null; then
		echo "Homebrew is not installed. Please install Homebrew first (https://brew.sh/)"
		exit 1
	fi
	brew update
	brew install \
		clang-format \
		cmake

##@ Build

.PHONY: build
build: ## Build the drakon library
	cmake -S . -B $(BUILD_DIR) $(CMAKE_OS_FLAGS) $(CMAKE_ADDITIONAL_FLAGS)
	cmake --build $(BUILD_DIR)

build/Debug/hello: build-examples-hello
.PHONY: build/examples/hello
build-examples-hello: ## Build the hello example (debug)
	cmake -DCMAKE_BUILD_TYPE=Debug -S . -B $(BUILD_DIR) $(CMAKE_OS_FLAGS) $(CMAKE_ADDITIONAL_FLAGS)
	cmake --build $(BUILD_DIR) --target hello

.PHONY: run/examples/hello
run-examples-hello: build/Debug/hello ## Run the example (debug)
	$<

##@ Utilities

.PHONY: clean
clean: ## Clean build artifacts
	rm -rf $(BUILD_DIR)

.PHONY: format
format: ## Format code
	find . \
		-not -path "./vendor/*" \
		-not -path "./build/*" \
		-not -path "./examples/*/build/*" \
		-type f \
		\( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \) \
		-exec clang-format -i {} \;

.PHONY: format/check
format-check: ## Check code formatting
	find . \
		-not -path "./vendor/*" \
		-not -path "./build/*" \
		-not -path "./examples/*/build/*" \
		-type f \
		\( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \) \
		-exec clang-format --dry-run -Werror {} \;

env-%: ## Check for env var
	if [ -z "$($*)" ]; then \
		echo "Error: Environment variable '$*' is not set."; \
		exit 1; \
	fi

.PHONY: help
help: ## Displays help info
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m\033[0m\n"} /^[a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)
