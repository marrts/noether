#pragma once

#include <noether_gui/widgets.h>

#include <noether_tpp/tool_path_planners/raster/raster_planner.h>
#include <plugin_loader/plugin_loader.h>

namespace Ui
{
class RasterPlanner;
}

namespace noether
{
class RasterPlannerWidget : public ToolPathPlannerWidget
{
public:
  RasterPlannerWidget(plugin_loader::PluginLoader&& loader, QWidget* parent = nullptr);

protected:
  DirectionGeneratorWidget* getDirectionGeneratorWidget() const;
  OriginGeneratorWidget* getOriginGeneratorWidget() const;

  const plugin_loader::PluginLoader loader_;
  Ui::RasterPlanner* ui_;
};

}  // namespace noether
