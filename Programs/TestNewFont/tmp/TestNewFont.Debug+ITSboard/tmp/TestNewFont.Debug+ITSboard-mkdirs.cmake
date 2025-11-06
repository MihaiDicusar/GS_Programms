# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard"
  "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/TestNewFont/tmp/1"
  "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard"
  "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/tmp"
  "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src/TestNewFont.Debug+ITSboard-stamp"
  "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src"
  "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src/TestNewFont.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src/TestNewFont.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src/TestNewFont.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
