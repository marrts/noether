#pragma once

#include <plugin_loader/plugin_loader.h>
#include <QLayoutItem>
#include <QLayout>
#include <QStringList>
#include <QWidget>
#include <string>
#include <vector>

namespace noether
{
template <typename PluginT>
inline QStringList getAllAvailablePlugins(const plugin_loader::PluginLoader& loader)
{
  std::vector<std::string> plugins = loader.getAllAvailablePlugins<PluginT>();
  QStringList out;
  out.reserve(plugins.size());
  std::transform(plugins.begin(), plugins.end(), std::back_inserter(out), &QString::fromStdString);

  // Insert blank at the beginning
  out.insert(out.begin(), QString{});

  return out;
}

inline void overwriteWidget(QLayout* layout, QWidget*& from, QWidget* to)
{
  assert(from != nullptr);
  assert(to != nullptr);
  assert(layout != nullptr);

  QLayoutItem* ret = layout->replaceWidget(from, to);  // , Qt::FindDirectChildrenOnly);
  assert(ret != nullptr);
  assert(ret->widget() == from);

  // Delete the replaced widget (which is no longer managed), and reset it to the widget that replaced it for future
  // reference
  delete from;
  from = to;
}

}  // namespace noether
