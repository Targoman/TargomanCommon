################################################################################
#   QBuildSystem
#
#   Copyright(c) 2021 by Targoman Intelligent Processing <http://tip.co.ir>
#
#   Redistribution and use in source and binary forms are allowed under the
#   terms of BSD License 2.0.
################################################################################
PRJ_BASE_DIR=$$PWD
include (./qmake/configs.pri)
TEMPLATE = subdirs
CONFIG += ordered
# +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-#
addSubdirs(libsrc)
addSubdirs(test, libsrc)
addSubdirs(unitTest, libsrc)
addSubdirs(apps, libsrc)

OTHER_FILES += \
    README.md \
    INSTALL \
    LICENSE \
    LICENSE.note
