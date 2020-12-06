#ifndef VULKANEXBASE_HELPFUNCTION_H
#define VULKANEXBASE_HELPFUNCTION_H
#include <vulkan/vulkan.h>
#include "../vksysutil/vulkan_wrapper.h"
bool memoryTypeFromProperties(VkPhysicalDeviceMemoryProperties& memoryProperties, uint32_t typeBits,VkFlags requirements_mask,uint32_t *typeIndex);
float toRadians(float degree);//角度转换成弧度的方法
float toDegrees(float radian);//弧度转换成角度的方法
#endif
