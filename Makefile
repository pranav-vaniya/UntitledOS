.PHONY: all build run clean headers iso bye

.SILENT:

all: clean headers build iso run bye

headers:
	scripts/headers.sh

build:
	scripts/build.sh

run:
	scripts/qemu.sh

iso:
	scripts/iso.sh

bye:
	@echo -e "\033[0;33m=> Successfully Completed Compilation.\e[0m"

clean:
	scripts/clean.sh
