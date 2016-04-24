#pragma once

/* 最小Nuz引擎头文件
 * 包含了最小的Nuz引擎。
 */

#include "Nuz/Engine.h"	//引擎主体

#include "Nuz/SceneManager/SceneManager.h"	//场景管理器
#include "Nuz/SceneManager/Scene.h"	//场景接口
#include "Nuz/SceneManager/GameObject.h"	//物件接口
#include "Nuz/SceneManager/Component.h"	//组件接口
#include "Nuz/SceneManager/Components/Logic.h"	//逻辑组件接口
#include "Nuz/SceneManager/Components/Sprite2D.h"	//2D精灵组件接口
#include "Nuz/SceneManager/Components/Camera2D.h"	//2D摄像机接口

#include "Nuz/FileSystem/FileSystem.h"	//文件系统
#include "Nuz/FileSystem/FileSource.h"	//文件系统的数据源
#include "Nuz/FileSystem/LocalFile.h"	//本地文件系统

#include "Nuz/Input/InputDeviceManager.h"	//输入设备管理器
#include "Nuz/Input/Keyboard.h"	//键盘设备

#include "Nuz/Logs.h"	//日志工具

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年4月18日：
 * 星翼 删除二进制缓存
 * 星翼 增加2D摄像机
 * 2016年4月24日：
 * 星翼 移入日志工具
 */
