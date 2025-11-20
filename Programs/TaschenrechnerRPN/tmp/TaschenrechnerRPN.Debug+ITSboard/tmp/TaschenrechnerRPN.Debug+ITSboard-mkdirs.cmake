# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard")
  file(MAKE_DIRECTORY "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard")
endif()
file(MAKE_DIRECTORY
  "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/1"
  "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard"
  "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/tmp"
  "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src/TaschenrechnerRPN.Debug+ITSboard-stamp"
  "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src"
  "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src/TaschenrechnerRPN.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src/TaschenrechnerRPN.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/yunis/GitHubRepo/GS_Programms/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src/TaschenrechnerRPN.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
