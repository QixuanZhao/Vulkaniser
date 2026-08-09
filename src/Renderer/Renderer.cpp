#include "Renderer.h"

Renderer::Renderer(QVulkanWindow *window)
    : m_window(window)
    , m_devFuncs(nullptr)
{
}

Renderer::~Renderer()
{
}

void Renderer::initResources()
{
    if (m_window && m_window->device()) {
        m_devFuncs = m_window->vulkanInstance()->deviceFunctions(m_window->device());
    }
}

void Renderer::initSwapChainResources()
{
    // Initialize swap chain resources here
}

void Renderer::releaseSwapChainResources()
{
    // Release swap chain resources here
}

void Renderer::releaseResources()
{
    m_devFuncs = nullptr;
}

void Renderer::startNextFrame()
{
    // Start the next frame rendering here
}