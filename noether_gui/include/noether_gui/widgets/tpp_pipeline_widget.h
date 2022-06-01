#pragma once

#include <noether_gui/plugin_interface.h>

#include <noether_tpp/core/tool_path_planner_pipeline.h>
#include <plugin_loader/plugin_loader.h>
#include <QWidget>

namespace Ui
{
class TPPPipeline;
}

namespace noether
{
template <typename T>
class PluginLoaderWidget;

class TPPPipelineWidget : public QWidget
{
  Q_OBJECT
public:
  TPPPipelineWidget(plugin_loader::PluginLoader loader, QWidget* parent = nullptr);

  ToolPathPlannerPipeline createPipeline() const;

private:
  const plugin_loader::PluginLoader loader_;
  PluginLoaderWidget<MeshModifierWidgetPlugin>* mesh_modifier_loader_widget_;
  PluginLoaderWidget<ToolPathModifierWidgetPlugin>* tool_path_modifier_loader_widget;
  Ui::TPPPipeline* ui_;
};

}  // namespace noether
