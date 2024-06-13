PROJECT_NAME := MissionControl
MC_MITM_TID := 010000000000bd00

GIT_BRANCH := $(shell git symbolic-ref --short HEAD | sed s/[^a-zA-Z0-9_-]/_/g)
GIT_HASH := $(shell git rev-parse --short HEAD)
GIT_TAG := $(shell git describe --tags `git rev-list --tags --max-count=1`)

VERSION := $(shell printf "0x%02X%02X%02X" $(shell echo "$(GIT_TAG)" | sed -E 's/^v([0-9]+).([0-9]+).([0-9]+)/\1 \2 \3/g'))
BUILD_VERSION := $(GIT_TAG:v%=%)-$(GIT_BRANCH)-$(GIT_HASH)
BUILD_DATE := $(shell date)

TARGETS := mcmitm_version.cpp mc_mitm

all: $(TARGETS)

mcmitm_version.cpp: .git/HEAD .git/index
	echo "namespace ams::mc { unsigned int mc_version = $(VERSION); const char *mc_build_name = \"$(BUILD_VERSION)\"; const char *mc_build_date = \"$(BUILD_DATE)\"; }" > mc_mitm/source/$@

mc_mitm:
	$(MAKE) -C $@

clean:
	$(MAKE) -C mc_mitm clean
	rm mc_mitm/source/mcmitm_version.cpp
	rm -rf dist

dist: all
	rm -rf dist

	

	mkdir -p dist/MissionControl/$(MC_MITM_TID)
	cp mc_mitm/out/nintendo_nx_arm64_armv8a/release/mc_mitm.nsp dist/MissionControl/$(MC_MITM_TID)/exefs.nsp
	echo "btdrv" >> dist/MissionControl/$(MC_MITM_TID)/mitm.lst
	echo "btm" >> dist/MissionControl/$(MC_MITM_TID)/mitm.lst

	mkdir -p dist/MissionControl/$(MC_MITM_TID)/flags
	touch dist/MissionControl/$(MC_MITM_TID)/flags/boot2.flag

	cp mc_mitm/toolbox.json dist/MissionControl/$(MC_MITM_TID)/toolbox.json

	cp -r exefs_patches/bluetooth_patches dist/MissionControl/
	cp -r exefs_patches/btm_patches dist/MissionControl/

	mkdir -p dist/MissionControl/MissionControl
	cp mc_mitm/config.ini dist/MissionControl/MissionControl/missioncontrol.ini

.PHONY: all clean dist $(TARGETS)
