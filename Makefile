SHELL := /bin/bash
.SHELLFLAGS = -e -c
.DEFAULT_GOAL := help
.ONESHELL:
.SILENT:

BUILD_DIR := build

.PHONY: setup/ubuntu
setup/ubuntu: ## Setup Ubuntu dependencies
	sudo apt-get update
	# https://github.com/libsdl-org/SDL/blob/main/docs/README-linux.md#build-dependencies
	sudo apt-get install -y \
		build-essential \
		cmake \
		git \
		gnome-desktop-testing \
		libasound2-dev \
		libaudio-dev \
		libdbus-1-dev \
		libdrm-dev \
		libegl1-mesa-dev \
		libgbm-dev \
		libgl1-mesa-dev \
		libgles2-mesa-dev \
		libibus-1.0-dev \
		libjack-dev \
		libpulse-dev \
		libsndio-dev \
		libudev-dev \
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

build/drakon: build
.PHONY: build
build: ## ## Build the drakon library
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

build/Debug/hello: build/examples/hello
.PHONY: build/examples/hello
build/examples/hello: ## Build the hello example (debug)
	cmake -DCMAKE_BUILD_TYPE=Debug -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --target hello

.PHONY: clean
clean: ## Clean build artifacts
	rm -rf $(BUILD_DIR) CMakeFiles

.PHONY: run/examples/hello
run/examples/hello: build/Debug/hello ## Run the example (debug)
	$<

format: ## Format code
	echo "TODO: $@"

lint: ## Lint code
	echo "TODO: $@"

fix: ## Fix code issues
	echo "TODO: $@"

env-%: ## Check for env var
	if [ -z "$($*)" ]; then \
		echo "Error: Environment variable '$*' is not set."; \
		exit 1; \
	fi

help: ## Displays help info
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m\033[0m\n"} /^[a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)
