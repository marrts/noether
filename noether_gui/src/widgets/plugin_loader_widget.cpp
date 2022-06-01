#include <noether_gui/widgets/plugin_loader_widget.hpp>
#include <noether_gui/plugin_interface.h>

namespace noether
{
template class PluginLoaderWidget<MeshModifierWidgetPlugin>;
template class PluginLoaderWidget<ToolPathModifierWidgetPlugin>;

}  // namespace noether
