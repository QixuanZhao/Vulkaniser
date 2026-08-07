#include "TrialVulkanWindow.h"

TrialVulkanRenderer::TrialVulkanRenderer(QVulkanWindow *window)
    : m_window(window), m_devFuncs(nullptr)
{
}

TrialVulkanRenderer::~TrialVulkanRenderer()
{
}

void TrialVulkanRenderer::initResources()
{
    m_devFuncs = m_window->vulkanInstance()->deviceFunctions(m_window->device());
}

void TrialVulkanRenderer::initSwapChainResources()
{
}

void TrialVulkanRenderer::releaseSwapChainResources()
{
}

void TrialVulkanRenderer::releaseResources()
{
    m_devFuncs = nullptr;
}

void TrialVulkanRenderer::startNextFrame() {
    // VkCommandBuffer cmdBuf = m_window->currentCommandBuffer();

    // m_window->frameReady();
}


TrialVulkanWindow::TrialVulkanWindow(QWindow *parent)
    : QVulkanWindow(parent)
{
}

TrialVulkanWindow::~TrialVulkanWindow()
{
}

QVulkanWindowRenderer *TrialVulkanWindow::createRenderer()
{
    return new TrialVulkanRenderer(this);
}