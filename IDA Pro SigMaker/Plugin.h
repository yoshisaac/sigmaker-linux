#pragma once

#define __LINUX__
#include "/home/yoshk4e/Downloads/sigmaker-main/SDK/include/ida.hpp"
#include "/home/yoshk4e/Downloads/sigmaker-main/SDK/include/idp.hpp"

#include "/home/yoshk4e/Downloads/sigmaker-main/SDK/include/loader.hpp"
#include "/home/yoshk4e/Downloads/sigmaker-main/SDK/include/search.hpp"

// Plugin specific definitions

struct plugin_ctx_t : public plugmod_t {
  ~plugin_ctx_t() {}
  virtual bool idaapi run(size_t) override;
};

static plugmod_t *idaapi init() { return new plugin_ctx_t; }
