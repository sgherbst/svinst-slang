VERSION = $(patsubst "%",%, $(word 3, $(shell grep version VERSION)))
BUILD_TIME = $(shell date +"%Y/%m/%d %H:%M:%S")
GIT_REVISION = $(shell git log -1 --format="%h")
LONG_VERSION = "$(VERSION) ( rev: $(GIT_REVISION), build at: $(BUILD_TIME) )"
BIN_NAME = svinst-slang

.PHONY: all test clean release_lnx release_win release_mac

all: test

test:

watch:

clean:

release_lnx:
    mkdir -p target
	zip -j ${BIN_NAME}-v${VERSION}-x86_64-lnx.zip target

release_win:
	mkdir -p target
	7z a ${BIN_NAME}-v${VERSION}-x86_64-win.zip target

release_mac:
	mkdir -p target
	zip -j ${BIN_NAME}-v${VERSION}-x86_64-mac.zip target
