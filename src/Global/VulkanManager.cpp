#include "VulkanManager.h"
#include <string>
#include <vulkan/vulkan.hpp>

VulkanManager VulkanManager::vulkanManagerInstance = VulkanManager();

VulkanManager::~VulkanManager() {
    cleanup();
}

void VulkanManager::setInstance(const VkInstance& instance) {
    m_instance = vk::raii::Instance(m_context, vk::Instance(instance));
    m_physicalDevices = vk::raii::PhysicalDevices(m_instance);

    if (m_physicalDevices.empty()) {
        throw std::runtime_error("No physical devices found.");
    }

    m_physicalDeviceProperty = std::make_shared<PhysicalDeviceProperty>("Physical Devices");
    for (const auto& physicalDevice : m_physicalDevices) {
        auto properties = physicalDevice.getProperties();
        auto features = physicalDevice.getFeatures();
        m_physicalDeviceProperty->addChild(std::make_shared<PhysicalDeviceProperty>(
            std::string(properties.deviceName.data()),
            std::to_string(properties.deviceID),
            m_physicalDeviceProperty
        ));

#define ADD_TREE_NODE(value, name, parent) parent->addChild(std::make_shared<PhysicalDeviceProperty>(name, value, parent))
#define ADD_PROPERTY(property, name, parent) \
    parent->addChild(\
        ([&]() {\
            if constexpr (std ::is_same_v<std ::decay_t<decltype(properties.property)>, std ::string>)\
                return std ::make_shared<PhysicalDeviceProperty>(\
                                    name, properties.property,\
                                    parent);\
            else return std ::make_shared<PhysicalDeviceProperty>(\
                                    name, std ::to_string(properties.property),\
                                    parent);\
        }())\
    )
#define ADD_STRING(str, name, parent) \
    parent->addChild(std::make_shared<PhysicalDeviceProperty>(name, str, parent))

        auto majorApi = vk::apiVersionMajor(properties.apiVersion);
        auto minorApi = vk::apiVersionMinor(properties.apiVersion);
        auto patchApi = vk::apiVersionPatch(properties.apiVersion);
        QVersionNumber apiVersion(majorApi, minorApi, patchApi);
        ADD_STRING(apiVersion.toString().toStdString(), "API Version", m_physicalDeviceProperty->lastChild());

        majorApi = vk::apiVersionMajor(properties.driverVersion);
        minorApi = vk::apiVersionMinor(properties.driverVersion);
        patchApi = vk::apiVersionPatch(properties.driverVersion);
        QVersionNumber driverVersion(majorApi, minorApi, patchApi);
        ADD_STRING(driverVersion.toString().toStdString(), "Driver Version", m_physicalDeviceProperty->lastChild());
        ADD_PROPERTY(vendorID, "Vendor ID", m_physicalDeviceProperty->lastChild());
        ADD_PROPERTY(deviceID, "Device ID", m_physicalDeviceProperty->lastChild());
        ADD_STRING(vk::to_string(properties.deviceType), "Device Type", m_physicalDeviceProperty->lastChild());
        ADD_STRING(std::string(properties.deviceName.data()), "Device Name", m_physicalDeviceProperty->lastChild());

        std::string uuidStr;
        for (uint8_t b : properties.pipelineCacheUUID) uuidStr += std::format("{:02x}", b);
        ADD_STRING(uuidStr, "Pipeline Cache UUID", m_physicalDeviceProperty->lastChild());

        ADD_TREE_NODE("", "Limits", m_physicalDeviceProperty->lastChild());
        ADD_PROPERTY(limits.maxImageDimension1D, "Max Image Dimension 1D", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxImageDimension2D, "Max Image Dimension 2D", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxImageDimension3D, "Max Image Dimension 3D", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxImageDimensionCube, "Max Image Dimension Cube", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxImageArrayLayers, "Max Image Array Layers", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTexelBufferElements, "Max Texel Buffer Elements", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxUniformBufferRange, "Max Uniform Buffer Range", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxStorageBufferRange, "Max Storage Buffer Range", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxPushConstantsSize, "Max Push Constants Size", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxMemoryAllocationCount, "Max Memory Allocation Count", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxSamplerAllocationCount, "Max Sampler Allocation Count", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.bufferImageGranularity, "Buffer Image Granularity", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.sparseAddressSpaceSize, "Sparse Address Space Size", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxBoundDescriptorSets, "Max Bound Descriptor Sets", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxPerStageDescriptorSamplers, "Max Per Stage Descriptor Samplers", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxPerStageDescriptorUniformBuffers, "Max Per Stage Descriptor Uniform Buffers", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxPerStageDescriptorStorageBuffers, "Max Per Stage Descriptor Storage Buffers", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxPerStageDescriptorSampledImages, "Max Per Stage Descriptor Sampled Images", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxPerStageDescriptorStorageImages, "Max Per Stage Descriptor Storage Images", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxPerStageDescriptorInputAttachments, "Max Per Stage Descriptor Input Attachments", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxPerStageResources, "Max Per Stage Resources", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDescriptorSetSamplers, "Max Descriptor Set Samplers", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDescriptorSetUniformBuffers, "Max Descriptor Set Uniform Buffers", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDescriptorSetUniformBuffersDynamic, "Max Descriptor Set Uniform Buffers Dynamic", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDescriptorSetStorageBuffers, "Max Descriptor Set Storage Buffers", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDescriptorSetStorageBuffersDynamic, "Max Descriptor Set Storage Buffers Dynamic", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDescriptorSetSampledImages, "Max Descriptor Set Sampled Images", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDescriptorSetStorageImages, "Max Descriptor Set Storage Images", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDescriptorSetInputAttachments, "Max Descriptor Set Input Attachments", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxVertexInputAttributes, "Max Vertex Input Attributes", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxVertexInputBindings, "Max Vertex Input Bindings", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxVertexInputAttributeOffset, "Max Vertex Input Attribute Offset", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxVertexInputBindingStride, "Max Vertex Input Binding Stride", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxVertexOutputComponents, "Max Vertex Output Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTessellationGenerationLevel, "Max Tessellation Generation Level", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTessellationPatchSize, "Max Tessellation Patch Size", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTessellationControlPerVertexInputComponents, "Max Tessellation Control Per Vertex Input Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTessellationControlPerVertexOutputComponents, "Max Tessellation Control Per Vertex Output Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTessellationControlPerPatchOutputComponents, "Max Tessellation Control Per Patch Output Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTessellationControlTotalOutputComponents, "Max Tessellation Control Total Output Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTessellationEvaluationInputComponents, "Max Tessellation Evaluation Input Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTessellationEvaluationOutputComponents, "Max Tessellation Evaluation Output Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxGeometryShaderInvocations, "Max Geometry Shader Invocations", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxGeometryInputComponents, "Max Geometry Input Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxGeometryOutputComponents, "Max Geometry Output Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxGeometryOutputVertices, "Max Geometry Output Vertices", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxGeometryTotalOutputComponents, "Max Geometry Total Output Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxFragmentInputComponents, "Max Fragment Input Components", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxFragmentOutputAttachments, "Max Fragment Output Attachments", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxFragmentDualSrcAttachments, "Max Fragment Dual Src Attachments", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxFragmentCombinedOutputResources, "Max Fragment Combined Output Resources", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxComputeSharedMemorySize, "Max Compute Shared Memory Size", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(std::to_string(properties.limits.maxComputeWorkGroupCount[0]) + ", " + std::to_string(properties.limits.maxComputeWorkGroupCount[1]) + ", " + std::to_string(properties.limits.maxComputeWorkGroupCount[2]), "Max Compute Work Group Count", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxComputeWorkGroupInvocations, "Max Compute Work Group Invocations", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(std::to_string(properties.limits.maxComputeWorkGroupSize[0]) + ", " + std::to_string(properties.limits.maxComputeWorkGroupSize[1]) + ", " + std::to_string(properties.limits.maxComputeWorkGroupSize[2]), "Max Compute Work Group Size", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.subPixelPrecisionBits, "Sub Pixel Precision Bits", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.subTexelPrecisionBits, "Sub Texel Precision Bits", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.mipmapPrecisionBits, "Mipmap Precision Bits", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDrawIndexedIndexValue, "Max Draw Indexed Index Value", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxDrawIndirectCount, "Max Draw Indirect Count", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxSamplerLodBias, "Max Sampler LOD Bias", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxSamplerAnisotropy, "Max Sampler Anisotropy", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxViewports, "Max Viewports", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(std::to_string(properties.limits.maxViewportDimensions[0]) + " X " + std::to_string(properties.limits.maxViewportDimensions[1]), "Max Viewport Dimensions", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(std::to_string(properties.limits.viewportBoundsRange[0]) + ", " + std::to_string(properties.limits.viewportBoundsRange[1]), "Viewport Bounds Range", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.viewportSubPixelBits, "Viewport Sub Pixel Bits", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.minMemoryMapAlignment, "Min Memory Map Alignment", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.minTexelBufferOffsetAlignment, "Min Texel Buffer Offset Alignment", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.minUniformBufferOffsetAlignment, "Min Uniform Buffer Offset Alignment", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.minStorageBufferOffsetAlignment, "Min Storage Buffer Offset Alignment", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.minTexelOffset, "Min Texel Offset", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTexelOffset, "Max Texel Offset", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.minTexelGatherOffset, "Min Texel Gather Offset", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxTexelGatherOffset, "Max Texel Gather Offset", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.minInterpolationOffset, "Min Interpolation Offset", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxInterpolationOffset, "Max Interpolation Offset", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.subPixelInterpolationOffsetBits, "Sub Pixel Interpolation Offset Bits", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxFramebufferWidth, "Max Framebuffer Width", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxFramebufferHeight, "Max Framebuffer Height", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxFramebufferLayers, "Max Framebuffer Layers", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(vk::to_string(properties.limits.framebufferColorSampleCounts), "Framebuffer Color Sample Counts", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(vk::to_string(properties.limits.framebufferDepthSampleCounts), "Framebuffer Depth Sample Counts", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(vk::to_string(properties.limits.framebufferStencilSampleCounts), "Framebuffer Stencil Sample Counts", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(vk::to_string(properties.limits.framebufferNoAttachmentsSampleCounts), "Framebuffer No Attachments Sample Counts", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxColorAttachments, "Max Color Attachments", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(vk::to_string(properties.limits.sampledImageColorSampleCounts), "Sampled Image Color Sample Counts", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(vk::to_string(properties.limits.sampledImageIntegerSampleCounts), "Sampled Image Integer Sample Counts", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(vk::to_string(properties.limits.sampledImageDepthSampleCounts), "Sampled Image Depth Sample Counts", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(vk::to_string(properties.limits.sampledImageStencilSampleCounts), "Sampled Image Stencil Sample Counts", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(vk::to_string(properties.limits.storageImageSampleCounts), "Storage Image Sample Counts", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxSampleMaskWords, "Max Sample Mask Words", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.timestampComputeAndGraphics, "Timestamp Compute And Graphics", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.timestampPeriod, "Timestamp Period", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxClipDistances, "Max Clip Distances", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxCullDistances, "Max Cull Distances", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.maxCombinedClipAndCullDistances, "Max Combined Clip And Cull Distances", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.discreteQueuePriorities, "Discrete Queue Priorities", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(std::to_string(properties.limits.pointSizeRange[0]) + ", " + std::to_string(properties.limits.pointSizeRange[1]), "Point Size Range", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_STRING(std::to_string(properties.limits.lineWidthRange[0]) + ", " + std::to_string(properties.limits.lineWidthRange[1]), "Line Width Range", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.pointSizeGranularity, "Point Size Granularity", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.lineWidthGranularity, "Line Width Granularity", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.strictLines, "Strict Lines", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.standardSampleLocations, "Standard Sample Locations", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.optimalBufferCopyOffsetAlignment, "Optimal Buffer Copy Offset Alignment", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.optimalBufferCopyRowPitchAlignment, "Optimal Buffer Copy Row Pitch Alignment", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(limits.nonCoherentAtomSize, "Non Coherent Atom Size", m_physicalDeviceProperty->lastChild()->lastChild());

        ADD_TREE_NODE("", "Sparse Properties", m_physicalDeviceProperty->lastChild());
        ADD_PROPERTY(sparseProperties.residencyStandard2DBlockShape, "Residency Standard 2D Block Shape", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(sparseProperties.residencyStandard2DMultisampleBlockShape, "Residency Standard 2D Multisample Block Shape", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(sparseProperties.residencyStandard3DBlockShape, "Residency Standard 3D Block Shape", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(sparseProperties.residencyAlignedMipSize, "Residency Aligned Mip Size", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_PROPERTY(sparseProperties.residencyNonResidentStrict, "Residency Non Resident Strict", m_physicalDeviceProperty->lastChild()->lastChild());

        ADD_TREE_NODE("", "Features", m_physicalDeviceProperty->lastChild());

#define ADD_FEATURE(property, name, parent) \
    parent->addChild(\
        ([&]() {\
            if constexpr (std ::is_same_v<std ::decay_t<decltype(features.property)>, std ::string>)\
                return std ::make_shared<PhysicalDeviceProperty>(\
                                    name, features.property,\
                                    parent);\
            else return std ::make_shared<PhysicalDeviceProperty>(\
                                    name, std ::to_string(features.property),\
                                    parent);\
        }())\
    )

        ADD_FEATURE(robustBufferAccess, "Robust Buffer Access", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(fullDrawIndexUint32, "Full Draw Index Uint32", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(imageCubeArray, "Image Cube Array", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(independentBlend, "Independent Blend", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(geometryShader, "Geometry Shader", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(tessellationShader, "Tessellation Shader", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sampleRateShading, "Sample Rate Shading", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(dualSrcBlend, "Dual Src Blend", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(logicOp, "Logic Op", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(multiDrawIndirect, "Multi Draw Indirect", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(drawIndirectFirstInstance, "Draw Indirect First Instance", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(depthClamp, "Depth Clamp", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(depthBiasClamp, "Depth Bias Clamp", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(fillModeNonSolid, "Fill Mode Non Solid", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(depthBounds, "Depth Bounds", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(wideLines, "Wide Lines", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(largePoints, "Large Points", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(alphaToOne, "Alpha To One", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(multiViewport, "Multi Viewport", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(samplerAnisotropy, "Sampler Anisotropy", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(textureCompressionETC2, "Texture Compression ETC2", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(textureCompressionASTC_LDR, "Texture Compression ASTC LDR", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(textureCompressionBC, "Texture Compression BC", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(occlusionQueryPrecise, "Occlusion Query Precise", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(pipelineStatisticsQuery, "Pipeline Statistics Query", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(vertexPipelineStoresAndAtomics, "Vertex Pipeline Stores And Atomics", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(fragmentStoresAndAtomics, "Fragment Stores And Atomics", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderTessellationAndGeometryPointSize, "Shader Tessellation And Geometry Point Size", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderImageGatherExtended, "Shader Image Gather Extended", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderStorageImageExtendedFormats, "Shader Storage Image Extended Formats", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderStorageImageMultisample, "Shader Storage Image Multisample", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderStorageImageReadWithoutFormat, "Shader Storage Image Read Without Format", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderStorageImageWriteWithoutFormat, "Shader Storage Image Write Without Format", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderUniformBufferArrayDynamicIndexing, "Shader Uniform Buffer Array Dynamic Indexing", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderSampledImageArrayDynamicIndexing, "Shader Sampled Image Array Dynamic Indexing", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderStorageBufferArrayDynamicIndexing, "Shader Storage Buffer Array Dynamic Indexing", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderStorageImageArrayDynamicIndexing, "Shader Storage Image Array Dynamic Indexing", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderClipDistance, "Shader Clip Distance", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderCullDistance, "Shader Cull Distance", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderFloat64, "Shader Float64", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderInt64, "Shader Int64", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderInt16, "Shader Int16", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderResourceResidency, "Shader Resource Residency", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(shaderResourceMinLod, "Shader Resource Min Lod", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sparseBinding, "Sparse Binding", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sparseResidencyBuffer, "Sparse Residency Buffer", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sparseResidencyImage2D, "Sparse Residency Image 2D", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sparseResidencyImage3D, "Sparse Residency Image 3D", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sparseResidency2Samples, "Sparse Residency 2 Samples", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sparseResidency4Samples, "Sparse Residency 4 Samples", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sparseResidency8Samples, "Sparse Residency 8 Samples", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sparseResidency16Samples, "Sparse Residency 16 Samples", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(sparseResidencyAliased, "Sparse Residency Aliased", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(variableMultisampleRate, "Variable Multisample Rate", m_physicalDeviceProperty->lastChild()->lastChild());
        ADD_FEATURE(inheritedQueries, "Inherited Queries", m_physicalDeviceProperty->lastChild()->lastChild());
#undef ADD_PROPERTY
#undef ADD_TREE_PROPERTY
#undef ADD_FEATURE
    }
}