CONTAINER_NAME  = php7-multisearch-debian-build
WORKSPACE_DIR   = /var/workspace

build:
	export BASE_DIR=`pwd`; \
	docker build --tag "${CONTAINER_NAME}" -f build/dockerfiles/debian.dockerfile . && \
	docker run -it --rm \
		-v "$$BASE_DIR"/src/:"${WORKSPACE_DIR}"/src \
		-v "$$BASE_DIR"/tests/:"${WORKSPACE_DIR}"/tests \
		-v "$$BASE_DIR"/build/output/:"${WORKSPACE_DIR}"/modules \
		"${CONTAINER_NAME}"

	@echo "\n\n\n"
	@echo "   DONE ... check build/output directory"
	@echo "\n\n\n"

clean:
	rm -rf src/*.o src/*/*.o src/.libs src/*/.libs src/*.lo src/*/*.lo build/output/*

.PHONY: build

