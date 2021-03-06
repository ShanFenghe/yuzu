// Copyright 2019 yuzu Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <vector>

#include "common/common_types.h"
#include "video_core/renderer_vulkan/wrapper.h"

namespace Layout {
struct FramebufferLayout;
}

namespace Vulkan {

class VKDevice;
class VKFence;

class VKSwapchain {
public:
    explicit VKSwapchain(VkSurfaceKHR surface, const VKDevice& device);
    ~VKSwapchain();

    /// Creates (or recreates) the swapchain with a given size.
    void Create(u32 width, u32 height, bool srgb);

    /// Acquires the next image in the swapchain, waits as needed.
    void AcquireNextImage();

    /// Presents the rendered image to the swapchain. Returns true when the swapchains had to be
    /// recreated. Takes responsability for the ownership of fence.
    bool Present(VkSemaphore render_semaphore, VKFence& fence);

    /// Returns true when the framebuffer layout has changed.
    bool HasFramebufferChanged(const Layout::FramebufferLayout& framebuffer) const;

    VkExtent2D GetSize() const {
        return extent;
    }

    std::size_t GetImageCount() const {
        return image_count;
    }

    std::size_t GetImageIndex() const {
        return image_index;
    }

    VkImage GetImageIndex(std::size_t index) const {
        return images[index];
    }

    VkImageView GetImageViewIndex(std::size_t index) const {
        return *image_views[index];
    }

    VkFormat GetImageFormat() const {
        return image_format;
    }

    bool GetSrgbState() const {
        return current_srgb;
    }

private:
    void CreateSwapchain(const VkSurfaceCapabilitiesKHR& capabilities, u32 width, u32 height,
                         bool srgb);
    void CreateSemaphores();
    void CreateImageViews();

    void Destroy();

    const VkSurfaceKHR surface;
    const VKDevice& device;

    vk::SwapchainKHR swapchain;

    std::size_t image_count{};
    std::vector<VkImage> images;
    std::vector<vk::ImageView> image_views;
    std::vector<vk::Framebuffer> framebuffers;
    std::vector<VKFence*> fences;
    std::vector<vk::Semaphore> present_semaphores;

    u32 image_index{};
    u32 frame_index{};

    VkFormat image_format{};
    VkExtent2D extent{};

    u32 current_width{};
    u32 current_height{};
    bool current_srgb{};
};

} // namespace Vulkan
