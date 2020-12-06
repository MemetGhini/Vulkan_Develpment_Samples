#ifndef TexDrawableObject_H
#define TexDrawableObject_H

#include <vulkan/vulkan.h>
#include "vulkan_wrapper.h"
#include <string>
#include "TextureManager.h"

class TexDrawableObject
{
public:
    VkDevice* devicePointer;
    float* vdata;
    int vCount;
    float* pushConstantData;


    VkBuffer vertexDatabuf;

    VkDeviceMemory vertexDataMem;

    VkDescriptorBufferInfo vertexDataBufferInfo;


    TexDrawableObject(float* vdataIn,int dataByteCount,int vCountIn,VkDevice& device,VkPhysicalDeviceMemoryProperties& memoryroperties);
    ~TexDrawableObject();

    void drawSelf(VkCommandBuffer& cmd,VkPipelineLayout& pipelineLayout,VkPipeline& pipeline,VkDescriptorSet* desSetPointer);

};


#endif
