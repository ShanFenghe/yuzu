// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/acc/acc.h"

namespace Service {
namespace Account {

class ACC_U0 final : public Module::Interface {
public:
    explicit ACC_U0(std::shared_ptr<Module> module);
};

} // namespace Account
} // namespace Service
