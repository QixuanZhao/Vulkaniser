#pragma once
#include "../TrialVulkanWindow/TrialVulkanWindow.h"

class TrialVulkanWindow;

class TrialVulkanWidget : public QWidget {
    Q_OBJECT
public:
    explicit TrialVulkanWidget(QWidget *parent = nullptr);
    explicit TrialVulkanWidget(TrialVulkanWindow *window, QWidget *parent = nullptr);
    ~TrialVulkanWidget() override;

private:
    TrialVulkanWindow *m_window = nullptr;
    QWidget *m_container = nullptr;
};