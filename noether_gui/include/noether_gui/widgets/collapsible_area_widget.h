#pragma once

#include <QWidget>
#include <QScrollArea>

class QParallelAnimationGroup;
class QGridLayout;
class QToolButton;
class QFrame;

namespace noether
{
/**
 * @brief The CollapsibleArea class
 * @ref https://stackoverflow.com/questions/32476006/how-to-make-an-expandable-collapsable-section-widget-in-qt
 */
class CollapsibleArea : public QWidget
{
  Q_OBJECT
public:
  CollapsibleArea(QWidget* parent = nullptr);
  CollapsibleArea(const QString& label, QWidget* parent = nullptr);
  virtual ~CollapsibleArea();

  void setWidget(QWidget* widget);
  QWidget* getWidget() const;

  template <typename T>
  T* getWidget() const
  {
    T* widget = dynamic_cast<T*>(content->widget());

    if (!widget)
      throw std::runtime_error("Failed to get widget with specified type");

    return widget;
  }

private:
  QGridLayout* layout;
  QToolButton* tool_button;
  QFrame* line;
  QScrollArea* content;
  QParallelAnimationGroup* animation_;
};

}  // namespace noether
