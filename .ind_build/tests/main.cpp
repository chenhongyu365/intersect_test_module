/*********************************************************************
 * @file    main.cpp
 * @brief
 * @details
 * @author  Shivelino
 * @date    2023.10.4
 * @version 0.2.0
 * @par Copyright(c): Concloud Software Corporation
 * @par todo:
 * @par history:
 *********************************************************************/
#include "gtest/gtest.h"
int main(int argc, char** argv) {
    // 此处用于添加GTest预处理操作。
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}