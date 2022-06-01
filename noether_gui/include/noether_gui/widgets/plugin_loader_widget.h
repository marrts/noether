#pragma once

#include <plugin_loader/plugin_loader.h>
#include <QWidget>

namespace Ui
{
class PluginLoader;
}

namespace noether
{
/**
 * @brief
 */
template <typename PluginT>
class PluginLoaderWidget : public QWidget
{
public:
  PluginLoaderWidget(plugin_loader::PluginLoader loader, const QString& title, QWidget* parent = nullptr);

  QWidgetList getWidgets() const;

private:
  Ui::PluginLoader* ui_;
  const plugin_loader::PluginLoader loader_;
};

}  // namespace noether
