#include "Renderer/Renderer.h"
#include "TrialVulkanWindow.h"

TrialVulkanWindow::TrialVulkanWindow(QWindow *parent)
    : QVulkanWindow(parent)
{
}

TrialVulkanWindow::~TrialVulkanWindow()
{
}

QVulkanWindowRenderer *TrialVulkanWindow::createRenderer()
{
    return new Renderer(this);
}