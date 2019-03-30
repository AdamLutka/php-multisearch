WORKSPACE_DIR   = /var/workspace
CONTAINER_NAME ?= php7-multisearch-builder
PHP_VERSION    ?= 7.1


# check PHP_VERSION =================================================
ifeq "${PHP_VERSION}" "7.1"
else ifeq "${PHP_VERSION}" "7.2"
else ifeq "${PHP_VERSION}" "7.3"
else
$(error "Invalid PHP_VERSION value (choose 7.1|7.2|7.3): ${PHP_VERSION}")
endif

# functions =========================================================
define msg_done
	@echo "\n\n\n"
	@echo "   DONE ... check build/output directory"
	@echo "\n\n\n"
endef

define docker_build
	docker build \
		--tag "${CONTAINER_NAME}:$(1)-php${PHP_VERSION}" \
		-f build/dockerfiles/$(1).dockerfile \
		--build-arg WORKSPACE_DIR=${WORKSPACE_DIR} \
		--build-arg PHP_VERSION=${PHP_VERSION} \
		build/context
endef

define docker_run
	export BASE_DIR=`pwd`; \
	docker run -it --rm \
		-v "$$BASE_DIR"/src/:"${WORKSPACE_DIR}"/src \
		-v "$$BASE_DIR"/tests/:"${WORKSPACE_DIR}"/tests \
		-v "$$BASE_DIR"/build/output/:"${WORKSPACE_DIR}"/modules \
		"${CONTAINER_NAME}:$(1)-php${PHP_VERSION}" $(2)
endef

define print_extension_dir
	php -r "echo ini_get('extension_dir');"
endef


# targets ===========================================================
all:
	@echo "Choose distribution:"
	@echo "  - debian.stretch"
	@echo "  - debian.jessie"


debian.stretch: debian.stretch.prepare debian.stretch.tests
	$(call msg_done)

debian.jessie: debian.jessie.prepare debian.jessie.tests
	$(call msg_done)

%.prepare:
	$(call docker_build,$*)

%.build:
	$(call docker_run,$*)

%.tests: %.tests.aho_corasick %.tests.extension_api
	@:

%.tests.aho_corasick:
	$(call docker_run,$*,-C tests/aho_corasick)

%.tests.extension_api:
	$(call docker_run,$*,test NO_INTERACTION=yes)


install:
	cp build/output/multisearch.so `$(call print_extension_dir)`
	cp config/multisearch.ini /etc/php/${PHP_VERSION}/mods-available/
	phpenmod multisearch

purge:
	phpdismod multisearch
	rm -f /etc/php/${PHP_VERSION}/mods-available/multisearch.ini
	rm -f `$(call print_extension_dir)`/multisearch.so

clean:
	rm -rf src/*.o src/*/*.o src/.libs src/*/.libs src/*.lo src/*/*.lo build/output/* tests/*/*.o tests/aho_corasick/aho_corasick_tests


.PHONY: build

