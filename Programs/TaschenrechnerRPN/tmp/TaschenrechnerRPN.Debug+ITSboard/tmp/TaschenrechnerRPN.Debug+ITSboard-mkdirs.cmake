# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/yunis/GitHubRepo/GS_Programms_clone/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard"
  "/Users/yunis/GitHubRepo/GS_Programms_clone/Programs/TaschenrechnerRPN/tmp/1"
  "/Users/yunis/GitHubRepo/GS_Programms_clone/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard"
  "/Users/yunis/GitHubRepo/GS_Programms_clone/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/tmp"
  "/Users/yunis/GitHubRepo/GS_Programms_clone/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src/TaschenrechnerRPN.Debug+ITSboard-stamp"
  "/Users/yunis/GitHubRepo/GS_Programms_clone/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src"
  "/Users/yunis/GitHubRepo/GS_Programms_clone/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src/TaschenrechnerRPN.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/yunis/GitHubRepo/GS_Programms_clone/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src/TaschenrechnerRPN.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/yunis/GitHubRepo/GS_Programms_clone/Programs/TaschenrechnerRPN/tmp/TaschenrechnerRPN.Debug+ITSboard/src/TaschenrechnerRPN.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
