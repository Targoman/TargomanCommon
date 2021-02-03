################################################################################
#   TargomanBuildSystem
#
#   Copyright 2010-2021 by Targoman Intelligent Processing <http://tip.co.ir>
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
################################################################################
DIST_HEADERS += \
    libTargomanCommon/exTargomanBase.h \
    libTargomanCommon/Macros.h \
    libTargomanCommon/clsSafeCoreApplication.h \
    libTargomanCommon/CmdIO.h \
    libTargomanCommon/Logger.h \
    libTargomanCommon/FastOperations.hpp \
    libTargomanCommon/Constants.h \
    libTargomanCommon/Types.h \
    libTargomanCommon/clsCmdProgressBar.h \
    libTargomanCommon/HashFunctions.hpp \
    libTargomanCommon/Configuration/intfConfigurable.hpp \
    libTargomanCommon/Configuration/clsFileBasedConfig.hpp \
    libTargomanCommon/Configuration/tmplConfigurable.h \
    libTargomanCommon/Configuration/ConfigManager.h \
    libTargomanCommon/Configuration/intfConfigurableModule.hpp \
    libTargomanCommon/CompressedStream/clsCompressedInputStream.h \
    libTargomanCommon/CompressedStream/clsCompressedOutputStream.h \
    libTargomanCommon/CompressedStream/clsCompressedStreamBuff.h \
    libTargomanCommon/Configuration/Validators.hpp \
    libTargomanCommon/FStreamExtended.h \
    libTargomanCommon/PrefixTree/tmplPrefixTree.h \
    libTargomanCommon/PrefixTree/tmplOnMemoryPrefixTreeNode.hpp \
    libTargomanCommon/PrefixTree/tmplAbstractPrefixTreeNode.hpp \
    libTargomanCommon/PrefixTree/tmplOnDemandPrefixTreeNode.hpp \
    libTargomanCommon/JSONConversationProtocol.h \
    libTargomanCommon/Configuration/tmplConfigurableArray.hpp \
    libTargomanCommon/SimpleAuthentication.h \
    libTargomanCommon/Configuration/intfRPCExporter.hpp \
    libTargomanCommon/Helpers.hpp \
    libTargomanCommon/PrefixTree/tmplAbstractOnDiskPrefixTreeNode.hpp \
    libTargomanCommon/PrefixTree/tmplFullCachePrefixTreeNode.hpp \
    libTargomanCommon/PrefixTree/tmplNoCachePrefixTreeNode.hpp \
    libTargomanCommon/tmplBoundedCache.hpp \
    libTargomanCommon/Configuration/tmplConfigurableMultiMap.hpp \
    libTargomanCommon/Configuration/tmplModuleConfig.hpp \
    libTargomanCommon/Configuration/tmplAddinConfig.hpp \
    libTargomanCommon/clsCountAndSpeed.h \
    libTargomanCommon/tmplExpirableCache.hpp

# +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-#
PRIVATE_HEADERS += \
    libTargomanCommon/Private/clsCountAndSpeed_p.h \
    libTargomanCommon/Private/intfConfigManagerOverNet.hpp \
    libTargomanCommon/Private/clsConfigByJsonRPC.h \
    libTargomanCommon/Private/clsBaseConfigOverNet.h \
    libTargomanCommon/Private/clsLegacyConfigOverTCP.h \
    libTargomanCommon/Private/Logger_p.h \
    libTargomanCommon/Private/RPCRegistry.hpp \
    libTargomanCommon/Private/clsConfigManager_p.h \

# +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-#
SOURCES += \
    libTargomanCommon/exTargomanBase.cpp \
    libTargomanCommon/clsSafeCoreApplication.cpp \
    libTargomanCommon/CmdIO.cpp \
    libTargomanCommon/Logger.cpp \
    libID.cpp \
    libTargomanCommon/Constants.cpp \
    libTargomanCommon/clsCmdProgressBar.cpp \
    libTargomanCommon/Configuration/tmplConfigurable.cpp \
    libTargomanCommon/Configuration/ConfigManager.cpp \
    libTargomanCommon/CompressedStream/clsCompressedInputStream.cpp \
    libTargomanCommon/CompressedStream/clsCompressedOutputStream.cpp \
    libTargomanCommon/CompressedStream/clsCompressedStreamBuff.cpp \
    libTargomanCommon/FStreamExtended.cpp \
    libTargomanCommon/JSONConversationProtocol.cpp \
    libTargomanCommon/SimpleAuthentication.cpp \
    libTargomanCommon/Configuration/ConfigManagerPrivate.cpp \
    libTargomanCommon/Configuration/clsConfigByJsonRPC.cpp \
    libTargomanCommon/Configuration/clsLegacyConfigOverTCP.cpp \
    libTargomanCommon/Configuration/clsBaseConfigOverNet.cpp \
    libTargomanCommon/clsCountAndSpeed.cpp

OTHER_FILES += \
    libTargomanCommon/Private/primeGenerator.sh

################################################################################
include(../qmake/libConfigs.pri)
