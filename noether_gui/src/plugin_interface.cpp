#include <noether_gui/plugin_interface.h>

#include <noether_tpp/core/tool_path_planner.h>
#include <noether_tpp/core/tool_path_modifier.h>
#include <noether_tpp/tool_path_planners/raster/raster_planner.h>
#include <plugin_loader/plugin_loader.hpp>

using namespace noether;

namespace noether
{
template <>
const std::string noether::ToolPathPlannerWidgetPlugin::section = "tpp";
template <>
const std::string DirectionGeneratorWidgetPlugin::section = "dg";
template <>
const std::string OriginGeneratorWidgetPlugin::section = "og";
template <>
const std::string ToolPathModifierWidgetPlugin::section = "mod";
}  // namespace noether

namespace plugin_loader
{
template std::vector<std::string> PluginLoader::getAllAvailablePlugins<ToolPathPlannerWidgetPlugin>() const;
template ToolPathPlannerWidgetPlugin::Ptr PluginLoader::createInstance(const std::string&) const;

template std::vector<std::string> PluginLoader::getAllAvailablePlugins<DirectionGeneratorWidgetPlugin>() const;
template DirectionGeneratorWidgetPlugin::Ptr PluginLoader::createInstance(const std::string&) const;

template std::vector<std::string> PluginLoader::getAllAvailablePlugins<OriginGeneratorWidgetPlugin>() const;
template OriginGeneratorWidgetPlugin::Ptr PluginLoader::createInstance(const std::string&) const;

template std::vector<std::string> PluginLoader::getAllAvailablePlugins<ToolPathModifierWidgetPlugin>() const;
template ToolPathModifierWidgetPlugin::Ptr PluginLoader::createInstance(const std::string&) const;

}  // namespace plugin_loader
