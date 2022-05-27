#pragma once

#include <QWidget>

namespace plugin_loader
{
class PluginLoader;
}

namespace Ui
{
class TPP;
}

namespace noether
{
class TPPWidget : public QWidget
{
  Q_OBJECT
public:
  TPPWidget(plugin_loader::PluginLoader&& loader, QWidget* parent = nullptr);

private:
  void onLoadMesh(const bool);
  void onPlan(const bool);

  Ui::TPP* ui_;
};

}  // namespace noether
