#pragma once

#include <QWidget>

namespace noether
{
class ToolPathPlanner;
class ToolPathModifier;
class DirectionGenerator;
class OriginGenerator;

template <typename T>
class BaseWidget : public QWidget
{
public:
  BaseWidget(QWidget* parent = nullptr) : QWidget(parent) {}

  virtual typename T::ConstPtr create() const = 0;
};

using ToolPathPlannerWidget = BaseWidget<ToolPathPlanner>;
using DirectionGeneratorWidget = BaseWidget<DirectionGenerator>;
using OriginGeneratorWidget = BaseWidget<OriginGenerator>;
using ToolPathModifierWidget = BaseWidget<ToolPathModifier>;

}  // namespace noether
