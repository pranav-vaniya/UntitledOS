run: build
	scripts/qemu.sh
	scripts/clean.sh

headers: clean
	scripts/headers.sh

build: clean headers
	scripts/build.sh

todo:
	scripts/todo.sh

clean:
	scripts/clean.sh
