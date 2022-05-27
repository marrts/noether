#pragma once

#include <noether_gui/widgets.h>
#include <string>
#include <memory>

class QWidget;

namespace plugin_loader
{
class PluginLoader;
}

namespace noether
{
template <typename T>
class WidgetPlugin
{
public:
  using Ptr = std::shared_ptr<WidgetPlugin>;
  virtual ~WidgetPlugin() = default;

  virtual QWidget* create(QWidget* parent = nullptr) const = 0;

private:
  friend class plugin_loader::PluginLoader;
  static const std::string section;
};

using ToolPathPlannerWidgetPlugin = WidgetPlugin<ToolPathPlannerWidget>;
using DirectionGeneratorWidgetPlugin = WidgetPlugin<DirectionGeneratorWidget>;
using OriginGeneratorWidgetPlugin = WidgetPlugin<OriginGeneratorWidget>;
using ToolPathModifierWidgetPlugin = WidgetPlugin<ToolPathModifierWidget>;

}  // namespace noether

#include <plugin_loader/macros.h>
#define EXPORT_TPP_WIDGET_PLUGIN(DERIVED_CLASS, ALIAS) EXPORT_CLASS_SECTIONED(DERIVED_CLASS, ALIAS, tpp)
#define EXPORT_DIRECTION_GENERATOR_WIDGET_PLUGIN(DERIVED_CLASS, ALIAS) EXPORT_CLASS_SECTIONED(DERIVED_CLASS, ALIAS, dg)
#define EXPORT_ORIGIN_GENERATOR_PLUGIN(DERIVED_CLASS, ALIAS) EXPORT_CLASS_SECTIONED(DERIVED_CLASS, ALIAS, og)
#define EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(DERIVED_CLASS, ALIAS) EXPORT_CLASS_SECTIONED(DERIVED_CLASS, ALIAS, mod)
