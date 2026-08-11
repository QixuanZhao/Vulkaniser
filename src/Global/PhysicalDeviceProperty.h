#pragma once

class PhysicalDeviceProperty final : public std::enable_shared_from_this<PhysicalDeviceProperty> {
    std::string m_name;
    std::string m_value;
    std::vector<std::shared_ptr<PhysicalDeviceProperty>> m_children;
    std::weak_ptr<PhysicalDeviceProperty> m_parent;
public:
    PhysicalDeviceProperty(
        const std::string &name, 
        const std::string &value = "", 
        std::shared_ptr<PhysicalDeviceProperty> parent = nullptr
    ) : m_name(name), m_value(value), m_parent(parent) { }

    inline void addChild(const std::shared_ptr<PhysicalDeviceProperty>& child) {
        m_children.push_back(child);
        child->m_parent = weak_from_this();
    }

    inline void removeChild(const std::shared_ptr<PhysicalDeviceProperty>& child) {
        auto it = std::find(m_children.begin(), m_children.end(), child);
        if (it != m_children.end()) {
            m_children.erase(it);
            child->m_parent.reset();
        }
    }

    inline const std::string& name() const { return m_name; }
    inline const std::string& value() const { return m_value; }

    inline const std::vector<std::shared_ptr<PhysicalDeviceProperty>>& children() const { return m_children; }
    inline std::shared_ptr<PhysicalDeviceProperty> parent() const { return m_parent.lock(); }

    inline int childIndex(const std::shared_ptr<PhysicalDeviceProperty>& child) const {
        auto it = std::find(m_children.begin(), m_children.end(), child);
        if (it != m_children.end()) {
            return static_cast<int>(std::distance(m_children.begin(), it));
        }
        return -1; // Child not found
    }
    inline bool hasChildren() const { return !m_children.empty(); }
    inline bool isLeaf() const { return m_children.empty(); }
    inline bool isRoot() const { return m_parent.expired(); }
    inline size_t childCount() const { return m_children.size(); }
    inline std::shared_ptr<PhysicalDeviceProperty> childAt(size_t index) const { 
        if (index >= m_children.size()) {
            return nullptr;
        }
        return m_children[index]; 
    }

    inline std::shared_ptr<PhysicalDeviceProperty> firstChild() const {
        return m_children.empty() ? nullptr : m_children.front();
    }

    inline std::shared_ptr<PhysicalDeviceProperty> lastChild() const {
        return m_children.empty() ? nullptr : m_children.back();
    }
};