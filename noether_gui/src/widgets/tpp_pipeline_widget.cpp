#include <noether_gui/widgets/tpp_pipeline_widget.h>
#include "ui_tpp_pipeline_widget.h"
#include <noether_gui/plugin_interface.h>
#include <noether_gui/widgets/collapsible_area_widget.h>
#include <noether_gui/utils.h>

#include <noether_tpp/core/tool_path_planner_pipeline.h>
#include <noether_tpp/tool_path_modifiers/compound_modifier.h>
#include <noether_tpp/tool_path_planners/raster/origin_generators.h>
#include <QMenu>
#include <QMessageBox>

namespace noether
{
TPPPipelineWidget::TPPPipelineWidget(plugin_loader::PluginLoader&& loader, QWidget* parent)
  : QWidget(parent), loader_(std::move(loader)), ui_(new Ui::TPPPipeline())
{
  ui_->setupUi(this);

  // Populate the combo boxes
  ui_->combo_box_tpp->addItems(getAllAvailablePlugins<ToolPathPlannerWidgetPlugin>(loader_));
  ui_->combo_box_mod->addItems(getAllAvailablePlugins<ToolPathModifierWidgetPlugin>(loader_));

  connect(ui_->combo_box_tpp, &QComboBox::currentTextChanged, [this](const QString& text) {
    if (text.isEmpty())
    {
      overwriteWidget(ui_->group_box_tpp->layout(), ui_->widget_tpp, new QWidget(this));
    }
    else
    {
      try
      {
        auto plugin = loader_.createInstance<ToolPathPlannerWidgetPlugin>(text.toStdString());
        overwriteWidget(ui_->group_box_tpp->layout(), ui_->widget_tpp, plugin->create(this));
      }
      catch (const std::exception& ex)
      {
        QMessageBox::warning(this, "Tool Path Planner Error", QString::fromStdString(ex.what()));
      }
    }
  });

  connect(ui_->push_button_add, &QPushButton::clicked, [this](const bool) {
    const QString plugin_name = ui_->combo_box_mod->currentText();
    if (!plugin_name.isEmpty())
    {
      try
      {
        auto plugin = loader_.createInstance<ToolPathModifierWidgetPlugin>(plugin_name.toStdString());

        auto collapsible_area = new CollapsibleArea(plugin_name, this);
        collapsible_area->setWidget(plugin->create(this));
        collapsible_area->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

        ui_->vertical_layout_mods->addWidget(collapsible_area);

        // Add a right click menu option for deleting this tool path modifier widget
        connect(collapsible_area, &QWidget::customContextMenuRequested, [this, collapsible_area](const QPoint& pos) {
          QMenu context_menu;
          QAction* remove_action = context_menu.addAction("Remove");
          QAction* action = context_menu.exec(collapsible_area->mapToGlobal(pos));
          if (action == remove_action)
          {
            ui_->vertical_layout_mods->removeWidget(collapsible_area);
            delete collapsible_area;
          }
        });

        // Reset the combo box to the blank value
        ui_->combo_box_mod->setCurrentIndex(0);
      }
      catch (const std::exception& ex)
      {
        QMessageBox::warning(this, "Tool Path Modifier Error", QString::fromStdString(ex.what()));
      }
    }
  });
}

ToolPathPlannerPipeline TPPPipelineWidget::createPipeline() const
{
  auto widget_tpp = dynamic_cast<ToolPathPlannerWidget*>(ui_->widget_tpp);
  if (!widget_tpp)
    throw std::runtime_error("No tool path planner specified");

  ToolPathPlanner::ConstPtr tpp = widget_tpp->create();

  std::vector<ToolPathModifier::ConstPtr> mods;
  for (const QObject* obj : ui_->verticalLayout->children())
  {
    auto mod_widget = dynamic_cast<const ToolPathModifierWidget*>(obj);
    if (mod_widget)
    {
      mods.push_back(std::move(mod_widget->create()));
    }
  }

  ToolPathModifier::ConstPtr mod;
  if (mods.empty())
    mod = std::make_unique<const ToolPathModifier>();
  else
    mod = std::make_unique<const CompoundModifier>(std::move(mods));

  return ToolPathPlannerPipeline(std::make_unique<MeshModifier>(), std::move(tpp), std::move(mod));
}

}  // namespace noether
