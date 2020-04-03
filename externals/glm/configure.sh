#!/bin/bash

if [ -z "$BASH_VERSION" ]; then
	echo "Invalid shell, re-running using bash..."
	exec bash "$0" "$@"
	exit $?
fi
SRCLOC="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source "$SRCLOC/../../../build/utils/functions.sh"

prepareUpstreamFromZipArchive "$SRCLOC" "https://builder.osmand.net/dependencies-mirror/glm-0.9.5.3.zip"
patchUpstream "$SRCLOC"
