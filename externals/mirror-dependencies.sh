#!/bin/bash

if [ -z "$BASH_VERSION" ]; then
	echo "Invalid shell, re-running using bash..."
	exec bash "$0" "$@"
	exit $?
fi

# Function: download(from, to)
function download
{
	local from=$1
	local to=$2
	
	curl -L --fail "$from" > "$to"
	local exitCode=$?

	if [ $exitCode -ne 0 ]; then
		echo "Download $from failed"
		exit $exitCode
	fi
}

# Should point to local path, exposed to public as https://builder.osmand.net/dependencies-mirror/
if [ -z "$DEPENDENCIES_MIRROR" ]; then
	DEPENDENCIES_MIRROR=$1
fi
if [ -z "$DEPENDENCIES_MIRROR" ]; then
	echo "DEPENDENCIES_MIRROR is not set!"
	exit 1
fi

mkdir -p "$DEPENDENCIES_MIRROR/"
mkdir -p "$DEPENDENCIES_MIRROR/bak/"
find "$DEPENDENCIES_MIRROR/" -maxdepth 1 -type f -exec mv {} "$DEPENDENCIES_MIRROR/bak/" \;


download "https://sourceforge.net/projects/boost/files/boost/1.56.0/boost_1_56_0.tar.bz2/download" "$DEPENDENCIES_MIRROR/boost_1_56_0.tar.bz2"
download "https://sourceforge.net/projects/expat/files/expat/2.1.0/expat-2.1.0.tar.gz/download" "$DEPENDENCIES_MIRROR/expat-2.1.0.tar.gz"
download "https://sourceforge.net/projects/freetype/files/freetype2/2.5.0/freetype-2.5.0.1.tar.bz2/download" "$DEPENDENCIES_MIRROR/freetype-2.5.0.1.tar.bz2"
download "http://download.osgeo.org/gdal/1.11.1/gdal-1.11.1.tar.gz" "$DEPENDENCIES_MIRROR/gdal-1.11.1.tar.gz"
download "https://sourceforge.net/projects/glew/files/glew/1.11.0/glew-1.11.0.tgz/download" "$DEPENDENCIES_MIRROR/glew-1.11.0.tgz"
download "https://sourceforge.net/projects/ogl-math/files/glm-0.9.5.3/glm-0.9.5.3.zip/download" "$DEPENDENCIES_MIRROR/glm-0.9.5.3.zip"
download "http://download.icu-project.org/files/icu4c/52.1/icu4c-52_1-src.tgz" "$DEPENDENCIES_MIRROR/icu4c-52_1-src.tgz"
download "http://www.ijg.org/files/jpegsrc.v9.tar.gz" "$DEPENDENCIES_MIRROR/jpegsrc.v9.tar.gz"
download "http://www.libarchive.org/downloads/libarchive-3.1.2.tar.gz" "$DEPENDENCIES_MIRROR/libarchive-3.1.2.tar.gz"
download "https://sourceforge.net/projects/libpng/files/libpng16/older-releases/1.6.33/libpng-1.6.33.tar.xz/download" "$DEPENDENCIES_MIRROR/libpng-1.6.33.tar.xz"
download "https://github.com/google/protobuf/releases/download/v2.5.0/protobuf-2.5.0.tar.bz2" "$DEPENDENCIES_MIRROR/protobuf-2.5.0.tar.bz2"
download "http://zlib.net/zlib-1.2.11.tar.gz" "$DEPENDENCIES_MIRROR/zlib-1.2.11.tar.gz"
download "https://sourceforge.net/projects/giflib/files/giflib-4.x/giflib-4.2.3.tar.bz2/download" "$DEPENDENCIES_MIRROR/giflib-4.2.3.tar.bz2"
download "https://sourceforge.net/projects/freeglut/files/freeglut/2.8.1/freeglut-2.8.1.tar.gz/download" "$DEPENDENCIES_MIRROR/freeglut-2.8.1.tar.gz"
download "https://sourceforge.net/projects/geographiclib/files/distrib/archive/GeographicLib-1.46.tar.gz/download" "$DEPENDENCIES_MIRROR/GeographicLib-1.46.tar.gz"
