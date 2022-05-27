#pragma once

#include <noether_tpp/core/tool_path_planner_pipeline.h>
#include <plugin_loader/plugin_loader.h>
#include <QWidget>

namespace Ui
{
class TPPPipeline;
}

namespace noether
{
class TPPPipelineWidget : public QWidget
{
  Q_OBJECT
public:
  TPPPipelineWidget(plugin_loader::PluginLoader&& loader, QWidget* parent = nullptr);

  ToolPathPlannerPipeline createPipeline() const;

private:
  const plugin_loader::PluginLoader loader_;
  Ui::TPPPipeline* ui_;
};

}  // namespace noether
